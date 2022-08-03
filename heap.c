#include "heap.h"

int Parent(int i) {
	return i / 2;
}


int Left(int i) {
	return 2 * i + 1;
}

int Right(int i) {
	return 2 * i + 2;
}


void fexchange(float* x, float* y) {
	float temp = *x;
	*x = *y;
	*y = temp;
}

void exchange(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Heapify_down_max(Heap* A, Heap* B, int i) {
	int l, r, n, largest;
	int location1, location2;
	largest = i;
	l = Left(i); r = Right(i); n = A->heapSize;
	if (l < n && (*(A->heap + l)) >(*(A->heap + i)))
		largest = l;
	if (r <= n - 1 && (*(A->heap + r)) > (*(A->heap + largest)))
		largest = r;
	if (largest != i) {
		location1 = A->twin[i]; //use locations to save current twin location in min heap
		location2 = A->twin[largest];
		exchange(&(B->twin[location1]), &(B->twin[location2])); //first swap the twin's indexes to look at the appropriate ones
		exchange(&(A->twin[i]), &(A->twin[largest]));
		fexchange(&(A->heap[i]), &(A->heap[largest])); //now swap the two elements
		Heapify_down_max(A, B, largest);
	}
}
void Heapify_down_min(Heap* A, Heap* B, int i) {
	int l, r, n, smallest;
	int location1, location2;
	smallest = i;
	l = Left(i); r = Right(i); n = A->heapSize;
	if (l < n && (*(A->heap + l)) < (*(A->heap + i)))
		smallest = l;
	if (r <= n - 1 && (*(A->heap + r)) < (*(A->heap + smallest)))
		smallest = r;
	if (smallest != i) {
		location1 = A->twin[i]; //use locations to save current twin location in min heap
		location2 = A->twin[smallest];
		exchange(&(B->twin[location1]), &(B->twin[location2])); //first swap the twin's indexes to look at the appropriate ones
		exchange(&(A->twin[i]), &(A->twin[smallest]));
		fexchange(&(A->heap[i]), &(A->heap[smallest]));
		Heapify_down_min(A, B, smallest);
	}
}


void Heapify_up_max(Heap* A, Heap* B, int i) {
	int location1, location2;
	if (i && (*(A->heap + Parent(i)) < *(A->heap + i))) {
		location1 = A->twin[i];
		location2 = A->twin[Parent(i)];
		exchange(&(B->twin[location1]), &(B->twin[location2]));
		exchange(&(A->twin[i]), &(A->twin[Parent(i)]));
		fexchange(&(A->heap[i]), &(A->heap[Parent(i)]));
		Heapify_up_max(A, B, Parent(i));
	}
}

void Heapify_up_min(Heap* A, Heap* B, int i) {
	int location1, location2;
	if (i && (*(A->heap + Parent(i)) > *(A->heap + i))) {
		location1 = A->twin[i];
		location2 = A->twin[Parent(i)];
		exchange(&(B->twin[location1]), &(B->twin[location2]));
		exchange(&(A->twin[i]), &(A->twin[Parent(i)]));
		fexchange(&(A->heap[i]), &(A->heap[Parent(i)]));
		Heapify_up_min(A, B, Parent(i));
	}
}


void Build_Heap_max(Heap* A, Heap* B, int n) {
	int i;
	A->heapSize = n;
	for (i = ((A->heapSize - 1) / 2); i >= 0; i--)
		Heapify_down_max(A, B, i);
}

void Build_Heap_min(Heap* A, Heap* B, int n) {
	int i;
	A->heapSize = n;
	for (i = (A->heapSize - 1) / 2; i >= 0; i--)
		Heapify_down_min(A, B, i);
}


void Heap_Insert_max(Heap* A, Heap* B, float key) {
	A->heapSize = A->heapSize + 1;
	B->heapSize = B->heapSize + 1;
	A->heap[A->heapSize - 1] = key;           //insert key to last node
	B->heap[A->heapSize - 1] = key;
	B->twin[B->heapSize - 1] = A->heapSize - 1; //insert node's index in twin
	A->twin[B->heapSize - 1] = B->heapSize - 1;
	Heapify_up_max(A, B, A->heapSize - 1);        //now correct node until getting a well defined heap
}

void Heap_Insert_min(Heap* A, Heap* B, float key) {
	Heapify_up_min(A, B, A->heapSize - 1);         //now correct node until getting a well defined heap
}

database* Init(float* S, int n) {
	//insert S's elements to 2 different arrays, where both indexes are the same in the "index of twin"
	float arr1[2][M], arr2[2][M];
	int i;
	database* data = (database*)malloc(sizeof(database));
	if (data == NULL) {
		return NULL;
	}
	data->minHeap = (Heap*)malloc(sizeof(Heap) + sizeof(float) * M + sizeof(int) * M);
	if (data->minHeap == NULL) {
		free(data);
		return NULL;
	}
	data->maxHeap = (Heap*)malloc(sizeof(Heap) + sizeof(float) * M + sizeof(int) * M);
	if (data->maxHeap == NULL) {
		free(data->minHeap); free(data);
		return NULL;
	}
	data->dataBaseSize = n;
	data->minHeap->twin[0] = 5;
	for (i = 0; i < n; i++) {                     //initialize two 2d arrays 
		data->minHeap->heap[i] = *(S + i);
		data->minHeap->twin[i] = i;

		data->maxHeap->heap[i] = *(S + i);
		(data->maxHeap->twin[i]) = i;
	}
	data->maxHeap->heapSize = n;                 //initialize their size
	data->minHeap->heapSize = n;

	Build_Heap_max(data->maxHeap, data->minHeap, n);  //make max_heap
	Build_Heap_min(data->minHeap, data->maxHeap, n);  //make min_heap
	return data;
}


float Find_min(database* data) {
	return data->minHeap->heap[0];      //return min value in struct at O(1)
}

float Find_max(database* data) {
	return data->maxHeap->heap[0];      //return max value in struct at O(1)
}

void Insert(database* data, float x) {
	Heap_Insert_max(data->maxHeap, data->minHeap, x);   //insert x into max heap
	Heap_Insert_min(data->minHeap, data->maxHeap, x);   //insert x into min heap
	data->dataBaseSize++;                 //increment struct size
}
void Del(Heap* A, Heap* B, int i) {
	int max_flag = 0, n = A->heapSize;
	int twin_of_root = A->twin[0];
	if (n <= 1) {			//check if heap has no nodes or one node. if there aren't nodes return as is
		if (n == 0)
			return;
		A->heapSize--;		//if there are no nodes, delete last node and return tree
		B->heapSize--;
		return;
	}
	n = n - 1;
	int twin_A_last_leaf = A->twin[n], twin_B_last_leaf = B->twin[n];
	if (A->heap[0] > A->heap[1] && A->heap[0] > A->heap[2]) {		//if heap is max heap and a correct heap, there wont be any overflow here
		max_flag = 1; //A is a max heap
	}
	fexchange(&A->heap[0], &A->heap[n]);			//swap A's root and last leaf
	exchange(&A->twin[0], &A->twin[n]);			//swap their indexes too
	B->twin[twin_A_last_leaf] = 0;					//make the twin of the node who was the last leaf indexes to look at the root
	B->twin[twin_of_root] = n;
	A->heapSize -= 1;										//decrement in both so the heapifying wont go so far up to the root
	B->heapSize -= 1;
	//make corrections to heaps
	if (max_flag == 1)
		Heapify_down_max(A, B, 0);
	else
		Heapify_down_min(A, B, 0);

	twin_B_last_leaf = B->twin[n];				//now begin swapping elements in B
	exchange(&B->twin[twin_of_root], &B->twin[n]);
	fexchange(&B->heap[twin_of_root], &B->heap[n]);
	exchange(&A->twin[n], &A->twin[twin_B_last_leaf]);

	if (max_flag == 1) {				//corect max heap A is the max heap and B is the min heap
		Heapify_down_max(A, B, 0);
		Heapify_down_min(B, A, twin_of_root);
		Heapify_up_min(B, A, twin_of_root);
	}
	else {								//correct min heap   A is yhe min heap and B is the max heap
		Heapify_down_min(A, B, 0);
		Heapify_down_max(B, A, twin_of_root);
		Heapify_up_max(B, A, twin_of_root);
	}
}


void Del_Max(database* data) {
	Del(data->maxHeap, data->minHeap, 0);
	data->dataBaseSize--;					//decrement data size
}

void Del_Min(database* data) {
	Del(data->minHeap, data->maxHeap, 0);
	data->dataBaseSize--;                  //decrement data size
}

int message() {
	int option; //menu for the user
	printf("\nHello, please enter option in order to advance.");
	printf("\nPlease press 1 to find min.");
	printf("\nPlease press 2 to find max.");
	printf("\nPlease press 3 to insert a number. ");
	printf("\nPlease press 4 to Delete minimum value in the databse.");
	printf("\nPlease press 5 to Delete maximum value in the database.");
	printf("\nPlease press 6 to exit program.");
	printf("\nChoose your option: ");
	scanf("%d", &option);
	return option;
}
