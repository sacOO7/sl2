/*
 ============================================================================
 Name        : f_w.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define INF 999
#define MAX 100

int graph[MAX][MAX];
int dist[MAX][MAX];
int closure[MAX][MAX];
int n;

void print(int A[][MAX])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(A[i][j]!=INF)
				printf("%d   ",A[i][j]);
			else
				printf("%d ",A[i][j]);
		}
		printf("\n");
	}
}

void f_w(int graph[][MAX])
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			dist[i][j]=graph[i][j];
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])
					dist[i][j]=dist[i][k]+dist[k][j];
				closure[i][j]=closure[i][j] || (closure[i][k] && closure[k][j]);
			}
		}
	}
}


int main()
{
	int i,j;
	printf("Enter number of vertices\n");
	scanf("%d",&n);
	printf("Enter the distance between the vertices\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&graph[i][j]);
			if(graph[i][j]== INF )
			{
				closure[i][j]=0;
			}
			else
				closure[i][j]=1;
		}
	}

	printf("The original distance matrix is\n");
	print(graph);
	printf("The initial closure matrix is\n");
	print(closure);
	f_w(graph);
	printf("The transitive closure matrix is\n");
	print(closure);
	printf("The final distance matrix is\n");
	print(dist);
	return 0;
}
