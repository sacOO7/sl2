//============================================================================
// Name        : realhauff.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include </usr/include/linux/limits.h>
#include <string.h>
using namespace std;

typedef struct node {
	char ch;
	int freq;
	node* left;
	node* right;
}node;

int size;
node* heap[1000];

void insert(node* p)
{
	size++;
	heap[size]=p;
	int now=size;
	while(heap[now/2]->freq > p->freq)
	{
		heap[now]=heap[now/2];
		now=now/2;
	}
	heap[now]=p;
}

node* delmin()
{
	node *lastele, *minele;
	lastele=heap[size--];
	minele=heap[1];
	int i,child;
	for(i=1;i*2 <= size;i=child)
	{
		child=i*2;
		if(child!=size && heap[child+1]->freq < heap[child]->freq)
		{
			child++;
		}
		if(heap[child]->freq < lastele->freq)
		{
			heap[i]=heap[child];
		}
		else
			break;
	}
	heap[i]=lastele;
	return minele;
}


void printarr(int arr[],int top)
{
	int i;
	for(i=0;i<top;++i)
	{
		cout<<arr[i];
	}
	cout<<"\n";
}

void printcodes(node* root, int arr[], int top)
{
	if(root->left)
	{
		arr[top]=0;
		printcodes(root->left,arr,top+1);
	}
	if(root->right)
	{
		arr[top]=1;
		printcodes(root->right,arr,top+1);
	}
	if(root->left==NULL && root->right==NULL)
	{
		cout<<"\t  "<<root->ch <<" -> ";
		printarr(arr,top);
	}
}

int main()
{
	int i,n;
	int arr[5000];
	int size=0;
	cout << "Enter the number of alphabets ";
	cin>> n;
	node* element=new node();
	//element->freq= -LONG_MAX;
	heap[0]=element;
	for(i=1;i<=n;i++)
	{
		node* element=new node;
		cout << "Enter the alphabet "<< i << " : ";
		cin>>element->ch;
		cout << "Enter the frequency of the alphabet "<< i << " : ";
		cin>>element->freq;
		element->left=NULL;
		element->right=NULL;
		insert(element);
	}

	node* root= NULL;
	while(n>1)
	{
		node* nl=new node();
		node* nr=new node();
		node* temp=new node();

		nl=delmin();
		n--;
		nr=delmin();
		n--;
		temp->freq=nl->freq+nr->freq;
		temp->left=nl;
		temp->right=nr;
		insert(temp);
		n++;
		root=temp;
	}
	cout << "The Huffmann codes are \n";
	printcodes(root,arr,0);

	string decode;
	cout<<"Enter the string to decode \n";
	cin>>decode;
	int size1 = decode.size();
	cout<<size1;
	int f=0;
	node *top=root;
	cout<<"\nThe decoded string is:";
	while(f<size1)
	{
		if(decode[f]== '0')
		{
			top=top->left;
			f++;
		}
		else if(decode[f]== '1')
		{
			top=top->right;
			f++;
		}

		if(top->left==NULL && top->right==NULL)
		{
			cout<<top->ch;
			top=root;
		}
	}
	return 0;
}
