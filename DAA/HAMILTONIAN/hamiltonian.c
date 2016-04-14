/*
 ============================================================================
 Name        : hamiltonian.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int graph[50][50],count=0;
int n;

void display(int path[],int n)
{
	int i;
	for(i=0;i<n-1;i++)
	{
		printf("%d -> ",path[i]);
	}
	printf("%d ",path[i]);
	printf("\n");
}


int check(int v,int graph[50][50],int path[50],int pos)
{
	int i;
	if(pos==0)
	{
		return 1;
	}
	if(graph[path[pos-1]][v]==0)
		return 0;
	for(i=0;i<pos;i++)
	{
		if(path[i]==v)
			return 0;
	}
	return 1;
}
int findnext(int graph[50][50],int path[50],int n,int pos)
{
	int i;
	if(pos==0)
	{
		if(path[pos]==-1)
			return 0;
		else if(path[pos]<n-1)
		{
			return (path[pos]+1);
		}
		else
			return -1;
	}

	else if(pos>=n)
	{
		return -1;
	}
	else
	{
		i=path[pos]+1;
		while(i<n)
		{
			if(check(i,graph,path,pos) ==1)
			{
				return i;
			}
			i++;
		}
		return -1;
	}
}

void hamiltonian(int graph[50][50],int n)
{
	int pos=0,v,i;
	int path[50];
	for(i=0;i<n;i++)
	{
		path[i]=-1;
	}
	while(1)
	{
		v=findnext(graph,path,n,pos);
		if(v==-1)
		{
			path[pos--]=-1;
			if(pos == -1)
			{
				return;
			}
		}
		else
		{
			path[pos++]=v;
			if(pos==n)
			{
				count++;
				display(path,n);
				path[--pos]=-1;
				pos--;
			}
		}
	}

}

int main()
{
	int i,j;
	printf("Enter the number of vertices \n");
	scanf("%d",&n);
	printf("Enter the elements of graph \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&graph[i][j]);
		}
	}
	printf("The graph is \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",graph[i][j]);
		}
		printf("\n");
	}
	printf("The Hamiltonian paths are \n");
	hamiltonian(graph,n);
	if(count==0)
	{
		printf("The Hamiltonian paths dont exist ");
	}
	else
		printf("The total number of Hamiltonian paths are %d ", count);
	return 0;
}
