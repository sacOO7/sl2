/*
 ============================================================================
 Name        : nq.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 50
int x[MAX];

void print(int n)
{
	char q[10][10],i,j,k;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(x[i]==j)
			{
				q[i][j]='Q';
			}
			else
			{
				q[i][j]='_';
			}

		}
	}
	for(k=1;k<=n;k++)
	{
		printf(" _");
	}
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("|");
		for(j=1;j<=n;j++)
		{
			printf("%c",q[i][j]);
			printf("|");
		}
		printf("\n");
	}
}

void nqueens(int k,int n)
{
	int i;
	for(i=1;i<=n;i++)
	{
		if(place(k,i))
		{
			x[k]=i;
			if(k==n)
			{
				printf("The solution is\n");
				print(n);
			}
			else
				nqueens(k+1,n);
		}
	}
}

int place(int k,int i)
{
	int j;
	for(j=1;j<=k-1;j++)
	{
		if(x[j]==i || (abs(x[j]-i) == abs(j-k)))
		{
			return 0;
		}
	}
	return 1;
}


int main()
{
	int k=1,n;
	printf("Enter the number n for n X n chessboard\n");
	scanf("%d",&n);
	nqueens(k,n);
	return 0;
}
