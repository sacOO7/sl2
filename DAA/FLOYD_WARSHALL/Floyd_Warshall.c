/*
 ============================================================================
 Name        : Flyod_Warshall.c
 Author      : Naman Mandlik (3948)
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#define INF 999

void Floyd_Warshall(int Graph[][MAX],int Closure[MAX][MAX],int n)
{
	int Distance[MAX][MAX],i,j,k,start,end,min,pos,path[MAX];
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			Distance[i][j]=Graph[i][j];
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				if(Distance[i][k]+Distance[k][j]<Distance[i][j])
					Distance[i][j]=Distance[i][k]+Distance[k][j];
				if(Closure[i][j]==1 || (Closure[i][k] && Closure[k][j]))
					Closure[i][j]=1;
			}
		}
	}
	printf("\nFinal distance matrix is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",Distance[i][j]);
		}
		printf("\n");
	}
	printf("\nFinal closure matrix is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",Closure[i][j]);
		}
		printf("\n");
	}
	printf("\nEnter the vertices from which you want to find the shortest path:\n");
	printf("\nEnter the starting vertex:");
	scanf("%d",&start);
	printf("\nEnter the destination vertex:");
	scanf("%d",&end);

	if(start==end)
	{
		printf("\nStart and End node are same so I am on the end node only..");
	}
	else
	{
		path[0]=start;
		j=1;
		while(1)
		{
			min=INF;
			for(i=0;i<n;i++)
			{
				if(Distance[start][i]<min && i!=start)
				{	min=Distance[start][i];
				pos=i;
				}
			}
			if(min!=INF)
			{
				start=pos;
				if(start!=end)
				{
					path[j++]=pos;
				}
				else
				{
					printf("\nPath for %d to %d is:\n",path[0],end);
					for(k=0;k<j;k++)
					{
						printf("%d->",path[k]);
					}
					printf("%d",end);
					break;
				}
			}
			else
			{
				printf("\nPath does not exist...");
				break;
			}
		}
	}
}

int main(void) {

	int Graph[MAX][MAX],Closure[MAX][MAX],n,i,j;

	printf("\nEnter the number of vertices for the graph:");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			Closure[i][j]=0;
		}
	}
	printf("\nEnter the information about the graph:(Enter 999 if there is no path)\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\nEnter the distance from vertex %d to %d:",i,j);
			scanf("%d",&Graph[i][j]);
			if(Graph[i][j]!=INF)
			{
				Closure[i][j]=1;
			}
			else
			{
				Closure[i][j]=0;
			}
		}
	}
	printf("\nInitial directed graph is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",Graph[i][j]);
		}
		printf("\n");
	}
	printf("\nInitial closure matrix is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",Closure[i][j]);
		}
		printf("\n");
	}
	Floyd_Warshall(Graph,Closure,n);
	return 0;
}
