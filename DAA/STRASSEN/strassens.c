/*
 ============================================================================
 Name        : strassens.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int num;

int padding (int num)
{
	int final_num=1, original_num,i,power=0;
	original_num=num;
	if(num==1)
	{
		return 1;
	}
	while(num>1)
	{
		power++;
		num=num/2;
	}

	for(i=0;i<power;i++)
	{
		final_num=final_num*2;
	}

	if(original_num==final_num)
		return original_num;
	else
		return final_num*2;
}

void strassens(int a[][num],int b[][num],int c[][num],int size)
{
	int sz=(size/2);
	int i,j;
	int p1[sz][sz],p2[sz][sz],p3[sz][sz],p4[sz][sz],p5[sz][sz],p6[sz][sz],
	p7[sz][sz];
	int temp1[sz][sz],temp2[sz][sz];
	if(size>=2)
	{
		//p1
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i][j]+a[i+sz][j+sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i][j]+b[i+sz][j+sz];
			}
		}

		num=sz;
		strassens(temp1,temp2,p1,sz);

		//p2
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i+sz][j]+a[i+sz][j+sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i][j];
			}
		}

		num=sz;
		strassens(temp1,temp2,p2,sz);

		//p3
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i][j];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i][j+sz]-b[i+sz][j+sz];
			}
		}

		num=sz;
		strassens(temp1,temp2,p3,sz);

		//p4
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i+sz][j+sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i+sz][j]-b[i][j];
			}
		}

		num=sz;
		strassens(temp1,temp2,p4,sz);

		//p5
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i][j]+a[i][j+sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i+sz][j+sz];
			}
		}

		num=sz;
		strassens(temp1,temp2,p5,sz);

		//p6
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i+sz][j]-a[i][j];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i][j]+b[i][j+sz];
			}
		}
		num=sz;
		strassens(temp1,temp2,p6,sz);


		//p7
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j]=a[i][j+sz]-a[i+sz][j+sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j]=b[i+sz][j]+b[i+sz][j+sz];
			}
		}
		num=sz;
		strassens(temp1,temp2,p7,sz);


		//c00

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				c[i][j]=p1[i][j]+p4[i][j]-p5[i][j]+p7[i][j];
			}
		}

		//c01

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				c[i][j+sz]=p3[i][j]+p5[i][j];
			}
		}

		//c10

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				c[i+sz][j]=p2[i][j]+p4[i][j];
			}
		}

		//c11

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				c[i+sz][j+sz]=p1[i][j]+p3[i][j]-p2[i][j]+p6[i][j];
			}
		}

	}

	else if(size==1)
			{
				c[0][0]=a[0][0] * b[0][0];
			}

}

int main()
{
	int i,j,temp;
	printf("Enter the number n for n X n matrix\n");
	scanf("%d",&num);
	temp=num;
	if(num <= 0)
	{
		return 0;
	}
	num = padding(num);
	//printf("%d",num);
	int a[num][num],b[num][num],c[num][num];
	printf("Enter the elements of matrix A\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			scanf("%d",&a[i][j]);
		}
		for(j=temp;j<num;j++)
		{
			a[i][j]=0;
		}
	}
	for(i=temp;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			a[i][j]=0;
		}
	}
	printf("Enter the elements of matrix B\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			scanf("%d",&b[i][j]);
		}
		for(j=temp;j<num;j++)
		{
			b[i][j]=0;
		}
	}
	for(i=temp;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			b[i][j]=0;
		}
	}

	printf("The elements of matrix A are \n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}

	printf("The elements of matrix B are \n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
	strassens(a,b,c,num);
	printf("The resultant matrix is \n");
		for(i=0;i<temp;i++)
		{
			for(j=0;j<temp;j++)
			{
				printf("%d ",c[i][j]);
			}
			printf("\n");
		}

	return 0;
}
