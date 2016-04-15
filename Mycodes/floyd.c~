/*
 ============================================================================
 Name        : Floyd.c
 Author      : sachin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define INF 9999

void print_path(int original[][20],int pred[][20],int i,int j);
void floyd (int original[][20],int pred[][20],int n);
void display (int original[][20],int pred[][20],int n);

int main(void) {
//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
int i,j,n,temp,original_mat[20][20],pred_mat[20][20];
printf ("Enter the no of vertices");
scanf ("%d",&n);


for (i=0;i<n;i++){
	for (j=0;j<n;j++){
		scanf ("%d",&temp);
		if (i==j){
			original_mat[i][j]=0;
		}else{
			original_mat[i][j]=temp;
		}
		pred_mat[i][j]=INF;
	}
}
//display(original_mat,n);
floyd(original_mat,pred_mat,n);
display(original_mat,pred_mat,n);

	return EXIT_SUCCESS;
}

void print_path(int original[][20],int pred[][20],int i,int j){

	if (pred[i][j]==INF){

		if (original[i][j]==INF){
			printf ("-");

		}else{
		}
			printf ("%d=>%d ",i+1,j+1);

	}else{
		print_path(original,pred,i,pred[i][j]);  //go for i and k
		print_path(original,pred,pred[i][j],j); //go for k anf j
	}

}
void floyd (int original[][20],int pred[][20],int n){

	int k,i,j,temp;
	for (k=0;k<n;k++){
		for (i=0;i<n;i++){
			for (j=0;j<n;j++){
				temp=original[i][k]+original[k][j];
				if (temp<original[i][j]){
					original[i][j]=temp;
					pred[i][j]=k;
				}
			}
		}
	}

}
void display (int originsl[][20],int pred[][20],int n){

	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			if (i!=j){
			printf ("%d\t\t\t",originsl[i][j]);
			print_path(originsl,pred,i,j);
			printf ("\n\n");
			}
		}
		printf ("\n");
	}
}

