//============================================================================
// Name        : strassens1.cpp
// Author      : sachin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

int ** create_mat(int n){

	int **s=(int **)malloc(n*sizeof (int *));
	for (int i=0;i<n;i++){
		s[i]=(int *)malloc (n*sizeof(int));
	}
	return s;
}
void read_mat(int **s,int n){

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cin>>s[i][j];
		}
	}
}

void display_mat(int **s,int n){

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			cout<<s[i][j]<<"\t";
		}
		cout<<"\n";
	}
}

void add_mat(int **out,int **mat1,int **mat2,int n){

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			out[i][j]=mat1[i][j]+mat2[i][j];
		}
	}
}

void sub_mat(int **out,int **mat1,int **mat2,int n){

	for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				out[i][j]=mat1[i][j]-mat2[i][j];
			}
		}
}

void add_padding (int **s,int n,int n_new){

	for (int i=0;i<n_new;i++){
		for (int j=n;j<n_new;j++){
			s[i][j]=0;
		}
	}

	for (int i=n;i<n_new;i++){
			for (int j=0;j<n_new;j++){
				s[i][j]=0;
			}
		}

}

int ** mat_mult(int ** mat1,int **mat2,int n){

	int **s1,**s2,**s3,**s4,**s5,**s6,**s7;
	int **a11,**a12,**a21,**a22,**b11,**b12,**b21,**b22;
	int **p1,**p2;
	int **output;

	output=create_mat(n);

	if (n<=1){
		output[0][0]=mat1[0][0]*mat2[0][0];
		return output;
	}else{

		int t=n/2;

		a11=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				a11[i][j]=mat1[i][j];
			}
		}
		a12=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				a12[i][j]=mat1[i][j+t];
			}
		}
		a21=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				a21[i][j]=mat1[i+t][j];
			}
		}
		a22=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				a22[i][j]=mat1[i+t][j+t];
			}
		}

		b11=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				b11[i][j]=mat2[i][j];
			}
		}
		b12=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				b12[i][j]=mat2[i][j+t];
			}
		}
		b21=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				b21[i][j]=mat2[i+t][j];
			}
		}
		b22=create_mat(t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				b22[i][j]=mat2[i+t][j+t];
			}
		}

		s1=create_mat(t);
		p1=create_mat(t);
		p2=create_mat(t);
		add_mat(p1,a11,a22,t);
		add_mat(p2,b11,b22,t);
		s1=mat_mult(p1,p2,t);


		s2=create_mat(t);
		add_mat(p1,a21,a22,t);
		s2=mat_mult(p1,b11,t);



		s3=create_mat(t);
		sub_mat(p1,b12,b22,t);
		s3=mat_mult(a11,p1,t);

		s4=create_mat(t);
		sub_mat(p1,b21,b11,t);
		s4=mat_mult(a22,p1,t);

		s5=create_mat(t);
		add_mat(p1,a11,a12,t);
		s5=mat_mult(p1,b22,t);

		s6=create_mat(t);
		sub_mat(p1,a21,a11,t);
		add_mat(p2,b11,b12,t);
		s6=mat_mult(p1,p2,t);

		s7=create_mat(t);
		sub_mat(p1,a12,a22,t);
		add_mat(p2,b21,b22,t);
		s7=mat_mult(p1,p2,t);

		add_mat(p1,s1,s4,t);
		sub_mat(p2,p1,s5,t);
		add_mat(p2,p2,s7,t);

		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				output[i][j]=p2[i][j];
			}
		}

		add_mat(p1,s3,s5,t);
		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				output[i][j+t]=p1[i][j];
			}
		}

		add_mat(p1,s2,s4,t);

		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				output[i+t][j]=p1[i][j];
			}
		}

		add_mat(p1,s1,s3,t);
		sub_mat(p2,p1,s2,t);
		add_mat(p2,p2,s6,t);

		for (int i=0;i<t;i++){
			for (int j=0;j<t;j++){
				output[i+t][j+t]=p2[i][j];
			}
		}

		return output;
	}

}
void delete_mat(int **s,int n){
for (int i=0;i<n;i++){
	free (s[i]);
}
free(s);
}
int main() {
	int **mat1,**mat2,n,**out;
	printf ("Enter the size of matrix");
	cin>>n;
	float temp=log(n)/log(2);
	int check=(int )temp;

	if (check==temp){
		//No need to add padding
		mat1=create_mat(n);
		read_mat(mat1,n);
		display_mat(mat1,n);
		mat2=create_mat(n);
		read_mat(mat2,n);
		display_mat(mat2,n);
		out=mat_mult(mat1,mat2,n);
		display_mat(out,n);

	}else{
		//Add padding

		int n_new=pow(2,ceil(temp));
		mat1=create_mat(n_new);
		read_mat(mat1,n);
		display_mat(mat1,n);
		add_padding(mat1,n,n_new);
		cout<<"\n\n";
		display_mat(mat1,n_new);

		mat2=create_mat(n_new);
		read_mat(mat2,n);
		display_mat(mat2,n);
		add_padding(mat2,n,n_new);
		cout<<"\n\n";
		display_mat(mat2,n_new);

		out=mat_mult(mat1,mat2,n_new);
		display_mat(out,n);

	}
	return 0;
}

