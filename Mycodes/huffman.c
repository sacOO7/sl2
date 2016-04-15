#include <stdio.h>
#include <stdlib.h>


//Node that need to be added in a array
typedef struct minheapnode{

	char data;
	unsigned  freq;
	struct minheapnode *left,*right;
}node ;

//
typedef struct minheap{
	unsigned size;
	unsigned capacity;
	node ** heaparray; //Pointer to array which stores above nodes
						//Assign memory dynamically
}heap;

node * new_node(char data,unsigned freq){
	node * newnode=(node *)malloc (sizeof(node));
	newnode->data=data;
	newnode->freq=freq;
	newnode->left=newnode->right=NULL;

	return newnode;
}

/**
 * Used to assign memory dynamocally to above array
 */
heap * create_min_heap(unsigned capacity){
	heap * heaparray= (heap*)malloc (sizeof(heap));
	heaparray->capacity=capacity;
	heaparray->size=0;
	heaparray->heaparray=(node **)malloc (capacity *sizeof (node *));
	return heaparray;
}

//swap two nodes
void swapnode (node **a,node **b){
	node *c=*a;
	*a=*b;
	*b=c;
}
/**
 * heapify is a process in which prents always having value greater than their children
 * are generated
 *
 */
void meanheapify(heap * minheap , int idx){
	int root=idx;
	int left_child=2*idx+1;
	int right_child=2*idx+2;
if (left_child<minheap->size && minheap->heaparray[left_child]->freq<minheap->heaparray[root]->freq)
	root=left_child;

if (right_child<minheap->size && minheap->heaparray[right_child]->freq<minheap->heaparray[root]->freq)
	root=right_child;

if (idx!=root){
	swapnode(&minheap->heaparray[root],&minheap->heaparray[idx]);
	meanheapify(minheap,root);
}
}

//As parent has value lower than children root node or node at 0 th position in array
//has lowest value , get that value

node * extractmin (heap * heaparray ){
	node * min=heaparray->heaparray[0];
	heaparray->heaparray[0]=heaparray->heaparray[heaparray->size-1];
	--heaparray->size;
	meanheapify(heaparray,0);
	return min;
}

//If i is a position of node parent lies at (i-1)/2
//find perfect position for node to be inserted using interations
void insertinheap(heap * heaparray , node * heap_node){

	++ heaparray->size;
	int i=heaparray->size-1;

	while (i && heap_node->freq < heaparray->heaparray[(i-1)/2]->freq){
		heaparray->heaparray[i]=heaparray->heaparray[(i-1)/2];
		i=(i-1)/2;
	}
	heaparray->heaparray[i]=heap_node;
}

node * createandbuiltminheap (char data[], int freq[], int size){
int i;
heap * heaparray=create_min_heap(size);
heaparray->size=size;
for (i=0;i<heaparray->size;i++){
	heaparray->heaparray[i]=new_node(data[i],freq[i]);
}

int lastelementparent=((heaparray->size-1)-1)/2;
for (i=lastelementparent;i>=0;i--){
	meanheapify(heaparray,i);
}
node * root,*left,*right;

while (heaparray->size!=1){
	left=extractmin(heaparray);
	right=extractmin(heaparray);

	root=new_node('$',left->freq+right->freq);
	root->left=left;
	root->right=right;
	insertinheap(heaparray,root);

}
return extractmin(heaparray);
}

void HuffmanCodes(char data[], int freq[], int size)
{
	node * root=createandbuiltminheap(data,freq,size);

	int arr[100];
    printCodes(root, arr, 0);

}
void printCodes(node* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
	int i;
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (root->left==NULL && root->right==NULL)
    {
	printf("%c: ", root->data);
	    for (i = 0; i < top; ++i)
	        printf("%d", arr[i]);
	    printf("\n");
    }
}

int main (){
	int size=6;
	char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	int freq[] = {5, 12, 9, 16, 13, 45};
//	size = sizeof(arr)/sizeof(arr[0]);
//	printf ("%d",size);
	HuffmanCodes(arr, freq, size);
	return 0;
}

