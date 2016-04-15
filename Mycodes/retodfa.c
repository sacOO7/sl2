//============================================================================
// Name        : retodfa1.cpp
// Author      : sachin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
#include <algorithm>
#include <stdio.h>
using namespace std;

typedef struct tree{

char data;
int pos;
char nullable;
int firstpos[30];
int lastpos[30];
struct tree * left,*right;
}node;

typedef struct follo{

char data;
int followpos[30];

}followtable;

stack <node *>mystack;  //stack for manipulating data
followtable foltable[30]; //Table for storing followpos of each character
int state [10][10];   //storing states and their corresponding positions
int dfaa[50],df=0;  //Storing all last table in a single row

int isoperator(char c){
	if (c=='|' || c=='*' || c=='.'){
		return 1;
	}
	return 0;

}

void copy (int arrin[],int arrout[])
{
	int i;
	for (i=0;arrin[i]!=-1;i++){
		arrout[i]=arrin[i];
	}
}

void union_ (int arrout[],int arrin1[],int arrin2[]){
	int k=0;
	for (int i=0;arrin1[i]!=-1;i++){
		arrout[k++]=arrin1[i];
	}
	int flag=0;
	for (int i=0;arrin2[i]!=-1;i++){
		for (int j=0;arrin1[j]!=-1;j++){
			if (arrin1[j]==arrin2[i]){
				flag=1;
				break;
			}
		}
		if (!flag){
		arrout[k++]=arrin2[i];
		flag=0;
		}
	}

}


void pushoperator(char c){
	node * newnode=(node *)malloc (sizeof(node));
	newnode->data=c;
	newnode->pos=0;
	for (int i=0;i<30;i++){
			newnode->firstpos[i]=newnode->lastpos[i]=-1;
	}
	switch (c){

	case '*':

		newnode->nullable='t';
		newnode->left=mystack.top();mystack.pop();
		newnode->right=NULL;
		copy(newnode->left->firstpos,newnode->firstpos);
		copy(newnode->left->lastpos,newnode->lastpos);
		for (int i=0;newnode->lastpos[i]!=-1;i++){
			copy (newnode->firstpos,foltable[newnode->lastpos[i]].followpos);
		}
		break;
	case '|':

		newnode->right=mystack.top();mystack.pop();
		newnode->left=mystack.top();mystack.pop();
		newnode->nullable='f';
		if (newnode->left->nullable=='t' || newnode->right->nullable=='t'){
			newnode->nullable='t';
		}
		union_(newnode->firstpos,newnode->left->firstpos,newnode->right->firstpos);
		union_(newnode->lastpos,newnode->left->lastpos,newnode->right->lastpos);

		break;
	case '.':

		newnode->right=mystack.top();mystack.pop();
		newnode->left=mystack.top();mystack.pop();
		newnode->nullable='f';
		if (newnode->left->nullable=='t' && newnode->right->nullable=='t'){
				newnode->nullable='t';
		}
		if (newnode->left->nullable=='t'){
			union_(newnode->firstpos,newnode->left->firstpos,newnode->right->firstpos);
		}else{
			copy(newnode->left->firstpos,newnode->firstpos);
		}
		if (newnode->right->nullable=='t'){

			union_(newnode->lastpos,newnode->left->lastpos,newnode->right->lastpos);
		}else{
			copy(newnode->right->lastpos,newnode->lastpos);
		}
		for (int i=0;newnode->left->lastpos[i]!=-1;i++){
			union_(foltable[newnode->left->lastpos[i]].followpos,foltable[newnode->left->lastpos[i]].followpos,newnode->right->firstpos);
		}


		break;
	}
	mystack.push (newnode);
}

void pushoperand(char c,int cnt){

	int i;
	node * newnode=(node *)malloc (sizeof(node));
	newnode->data=c;
	newnode->pos=cnt;
	for (i=0;i<30;i++){
		newnode->firstpos[i]=newnode->lastpos[i]=-1;
	}
	newnode->firstpos[0]=cnt;
	newnode->lastpos[0]=cnt;
	newnode->left=newnode->right=NULL;
	newnode->nullable='f';
	mystack.push(newnode);

}
void display_foll(int cnt)
{
	int i,j;
	printf("\n\tFollowpos Table::");
	printf("\n\tPos\tName\tFollowpos");
	//printf(cnt);
	for(i=0;i<cnt;i++)
	{
		printf("\n\t%d\t%c\t{",i,foltable[i].data);
		for(j=0;foltable[i].followpos[j]!=-1;j++)
		{
			printf("%d",foltable[i].followpos[j]);
		}
		printf("}");
	}
}
void inorder(node *new_node)
{
	int i;
	if(new_node!=NULL)
	{
		inorder(new_node->left);
		printf("%c\t%d\t%c\t\t{",new_node->data,new_node->pos,new_node->nullable);
		for(i=0;new_node->firstpos[i]!=-1;i++)
		{
			printf("%d",new_node->firstpos[i]);
		}
		printf("}\t\t\t{");
		for(i=0;new_node->lastpos[i]!=-1;i++)
		{
			printf("%d",new_node->lastpos[i]);
		}
		printf("}\n\t");
		inorder(new_node->right);
	}
}
int check(int temp[],int nos)
{
	int j,i;
	for(i=0;i<nos;i++)
	{
		for(j=0;temp[j]!=-1;j++)
		{
			if(temp[j]!=state[i][j])
				break;
		}
		if(temp[j]==-1 && state[i][j]==-1)
		{
			return i;
		}
	}
	return -1;
}
void union2(int ar1[],int ar2[])
{
	int i=0;
	while(ar1[i]!=-1)
		i++;
	int j=0;
	int k=0;
	while(ar2[j]!=-1)
	{
		for(k=0;k<i;k++)
		{
			if(ar2[j]==ar1[k])
			{
				break;
			}
		}
		if(k==i)
		{
			ar1[i]=ar2[j];
			i++;
		}
		j++;
	}
	ar1[i]=-1;
}

void dfa(char input[])
{
	int j=0,k=0,temp[10],m,i,x;
	for(i=0;i<10;i++)
	{
		temp[i]=-1;
	}
	int nos=1;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			state[i][j]=-1;
		}
	}
	union2(state[0],foltable[1].followpos);
	while(1)
	{
		for(i=0;input[i]!='\0';i++)
		{
			for(j=0;state[k][j]!=-1;j++)
			{
				if(foltable[state[k][j]].data==input[i])
				{
					union2(temp,foltable[state[k][j]].followpos);
				}
			}

			m=check(temp,nos);
			if(m==-1)
			{
				union2(state[nos++],temp);
				m=nos-1;
			}
			dfaa[df++]=m;
			for(x=0;x<10;x++)
			{
				temp[x]=-1;
			}
		}

		if(k==nos-1)
			break;
		k++;
	}
}
void display_dfa(char input[])
{
	int i,j,k;
	printf("\nDFA TABLE\n");
	for(i=0;input[i]!='\0';i++)
	{
		printf("\t\t%c",input[i]);
	}
	for(j=0;j<(df/i);j++)
	{
		printf("\n\t%c\t",j+65);
		for(k=j*i;k<(j*i)+i;k++)
		{
			printf("%c\t",dfaa[k]+65);
		}
	}
}
int main() {
	char input[20],uniqu[20];int i,uniqueindex=0,flag=0;
	cout<<"Enter postfix regular expression";
	cin>>input;
	int folcnt=1;
	for (int i=0;i<30;i++){
		for (int j=0;j<30;j++){
			foltable[i].followpos[j]=-1;
		}
	}

	for (i=0;input[i]!='\0';i++){
		if (!isoperator(input[i])){
			pushoperand(input[i],folcnt);
			foltable[folcnt].data=input[i];
			folcnt++;

			for (int k=0;input[k]!='\0';k++){
				if (input[i]==uniqu[k] || input[i]=='#'){
					flag=1;
					break;
				}
			}
			if (flag==0){
				uniqu[uniqueindex++]=input[i];
			}
			flag=0;

		}else{
			pushoperator(input[i]);
		}
	}

	uniqu[uniqueindex]='\0';
//	display_foll(folcnt);
	cout<<"size is"<<mystack.size()<<"\n";

	printf("\n\tdata \tpos \tnullable \tfirstpos\t\tlastpos\n\t");

	inorder(mystack.top());
	display_foll(folcnt);

	dfa(uniqu);
	display_dfa(uniqu);
	return 0;
}

