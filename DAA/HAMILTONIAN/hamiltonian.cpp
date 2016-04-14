#include <iostream>
#include <iomanip>
#define MAX 50

using namespace std;

int n;
int graph[MAX][MAX];
int count = 0;

void printSolution(int path[],int n) {
	int i;
	for(i = 0;i < n-1;i++)
		cout << path[i] << " -> ";
	cout << path[i] << "\n";
}

int check(int v,int graph[MAX][MAX],int path[],int pos) {
	if(pos == 0)
		return 1;
	if(graph[path[pos-1]][v] == 0)
		return 0;
	for(int i = 0;i < pos;i++)
		if(path[i] == v)
			return 0;
	return 1;
}

int findNext(int graph[MAX][MAX],int path[],int n,int pos) {
	int i;
	if(pos == 0) {
		if(path[pos] == -1)
			return 0;
		else if(path[pos] < n-1)
			return path[pos]+1;
		else
			return -1;
	}
	else if(pos >= n)
		return -1;
	else {
		i = path[pos]+1;
		while(i < n) {
			if(check(i,graph,path,pos) == 1)
				return i;
			i++;
		}
		return -1;
	}
}

void ham_path(int graph[MAX][MAX], int n) {
	int pos, v;
	int path[MAX];
	for(int i = 0;i < n;i++)
		path[i] = -1;
	pos = 0;
	while(1) {
		v = findNext(graph,path,n,pos);
		if(v == -1) {
			path[pos--] = -1;
			if(pos == -1)
				return;
		}
		else {
			path[pos++] = v;
			if(pos == n) {
				count++;
				printSolution(path,n);
				path[--pos] = -1;
				pos--;
			}
		}
	}
}

int main(void) {
	cout << "ENTER NUMBER OF VERTICES : ";
	cin >> n;
	cout << "ENTER GRAPH (1 for edge, 0 for no edge) :\n";
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			cin >> graph[i][j];
	cout << "\n";
	cout << "GRAPH IS : \n";
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++) 
			cout << graph[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	cout << "THE HAMILTONIAN PATHS ARE : \n";
	ham_path(graph,n);
	if(count == 0)
		cout << "\nHAMILTONIAN PATH DOES NOT EXIST!\n";
	else
		cout << "\nTOTAL HAMILTONIAN PATH/S FOUND : " << count << "\n";
}

