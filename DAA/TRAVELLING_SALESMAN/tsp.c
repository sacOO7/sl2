/*
 ============================================================================
 Name        : tsp.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define INF 999


int tsp[10][10],visited[10],cost[10];
int l=0,node_no=1,n;

int find_min_row(int b[][10],int r)
{
	int i,j,min=INF;
	for(j=0;j<n;j++)
	{
		if(b[r][j]<min)
		{
			min=b[r][j];
		}
	}
	if(min==999)
	{
		min=0;
	}
	return min;
}


int find_min_col(int b[][10],int c)
{
	int i,j,min=INF;
	for(j=0;j<n;j++)
	{
		if(b[j][c]<min)
		{
			min=b[j][c];
		}
	}
	if(min==999)
	{
		min=0;
	}
	return min;
}

int reduced_sum(int tsp[][10])
{
	int i,j,sum=0,min;
	//row reduction
	for(i=0;i<n;i++)
	{
		min=find_min_row(tsp,i);
		sum += min;
		for(j=0;j<n;j++)
		{
			if(tsp[i][j]!=INF)
				tsp[i][j] -= min;
		}
	}

	//column reduction
	for(i=0;i<n;i++)
	{
		min=find_min_col(tsp,i);
		sum += min;
		for(j=0;j<n;j++)
		{
			if(tsp[j][i]!=INF)
				tsp[j][i] -= min;
		}
	}
	node_no++;
	return sum;
}

int check_visited(int m)
{
	int i;
	for(i=0;i<l;i++)
	{
		if(visited[i]==m)
			return 1;
	}
	return 0;
}

int min1(int temp[][2],int q)
{
	int small=INF,j,i;
	for(j=0;j<q;j++)
	{
		if(temp[j][1]<small)
		{
			small=temp[j][1];
			i=j;
		}
	}
	return i;
}

void display_path()
{
	int i;
	printf("The path of the tour is ");
	for(i=0;i<n;i++)
	{
		printf("%d -> ",visited[i]+1);
	}
	printf(" 1");
	printf("The minimum cost of the tour is %d ", cost[l-1]);
}

void dynamic_reduction()
{
	int p,q,temp[10][2],m[10][10],sum=0;
	int i,j,k;
	while(l<n)
	{
		q=0;
		for(i=0;i<n;i++)
		{
			p = check_visited(i);
			if(p==0)
			{
				temp[q++][0]=i;
			}
		}
		for(i=0;i<q;i++)
		{
			for(j=0;j<n;j++)
			{
				for(k=0;k<n;k++)
				{
					m[j][k]=tsp[j][k];
				}
			}
			for(k=0;k<l;k++)
			{
				for(j=0;j<n;j++)
				{
					m[visited[k]][j]=INF;
				}
			}

			for(k=1;k<l;k++)
			{
				for(j=0;j<n;j++)
				{
					m[j][visited[k]]=INF;
				}
			}


			for(j=0;j<n;j++)
			{
				m[j][temp[i][0]]=INF;
			}

			for(j=0;j<n;j++)
			{
				if(visited[j+1]!=-1)
				{
                                 m[visited[j+1]][0]=INF;
				}
			}
            m[temp[i][0]][0]=INF;
            sum=reduced_sum(m);
            temp[i][1]=cost[l-1]+sum+tsp[visited[l-1]][temp[i][0]];
            printf("The cost of node no %d is %d \n", node_no-1, temp[i][1]);
		}

		p=min1(temp,q);
		visited[l]=temp[p][0];
		cost[l++]=temp[p][1];
		printf("The minimum cost city is %d and its cost is %d \n",
				temp[p][0], temp[p][1]);
	}
}

int main()
{
	int i,j,k;
	printf("Enter the number of cities\n");
	scanf("%d",&n);
	printf("Enter the cost matrix\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&tsp[i][j]);
		}
	}
	printf("The cost matrix is\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d  ",tsp[i][j]);
		}
		printf("\n");
	}
	visited[l]=0;
	cost[l++]=reduced_sum(tsp);
	dynamic_reduction();
    display_path();
	return 0;
}
