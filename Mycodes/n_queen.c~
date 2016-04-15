/**
 *
 * Author :sachin
 */

#include <stdio.h>
#include <stdlib.h>
int x[20];


/**
 * Here X[] is an array which stores column index
 * i.e. if x[2]=3 means Queen is placed at 2nd row and 3rd column
 * so i in program deontes 3(column) and k denotes 2 (row).
 */


int place (int k,int i){
int j;
for (j=0;j<k;j++){
	if (x[j]==i || (abs (x[j]-i)==abs(j-k))){
		return 0;
	}
}
return 1;
}
void n_queen(int k,int n){
int i;
for (i=0;i<n;i++){

	if (place(k,i)){
		x[k]=i;

		if (k==n-1){

			printf ("\n");
			display(n);
		}else{
			n_queen(k+1,n);
		}
	}

}
}

void display(int n){
	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			if (x[i]==j){
				printf (" Q ");
			}else{
				printf (" . ");
			}
		}
		printf ("\n");
	}


}


int main (){
	int n;
	printf ("Enter dimensions");
	scanf ("%d",&n);
	n_queen(0,n);
}


