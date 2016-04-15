#include <stdio.h>
int n;
int issafe(int i,int graph[][20],int *path,int pos);
int hamilutil (int graph[][20],int *path,int pos);
int hamilton(int graph[][20]);

int main (){
	int graph[20][20];
	printf ("Enter the number of vertices");
	scanf ("%d",&n);
	hamilton(graph);

}
int hamilton(int graph[][20]){
	int i,j,* path;
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			scanf ("%d",&graph[i][j]);
		}
	}

	path=(int *)malloc (n*sizeof(int));
	for (i=0;i<n;i++){
		path[i]=-1;
	}
	path[0]=0;
	if (hamilutil (graph,path,1)==0){
		printf ("doesnt exist");
		return 0;
	}
	printf ("exists");
	return 1;
}

int hamilutil (int graph[][20],int *path,int pos){
	int j;
	if (pos==n){
		if (graph[path[pos-1]][path[0]]){
			return 1;
		}else{
			return 0;
		}
	}
	for (j=0;j<n;j++){

		if (issafe(j,graph,path,pos)){
			path[pos]=j;

			if (hamilutil(graph,path,pos+1)==1){
				return 1;
			}
		}

	}
	return 0;

}

int issafe(int i,int graph[][20],int * path,int pos){
	int j;
	if (graph[path[pos-1]][i]==0){
	return 0;
	}
	for (j=0;j<pos;j++){
		if (path [j]==i)
			return 0;
	}
	return 1;
}

