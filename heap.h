#pragma once


#ifndef HEAP_H
#define HEAP_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define M 50

typedef struct Heap {
	float heap[M];
	int twin[M];
	int heapSize;
} Heap;

typedef struct database {
	Heap* minHeap, * maxHeap;
	int dataBaseSize;
} database;


//index of parent
int Parent(int i);

//index of left child
int Left(int i);

//index of right child
int Right(int i);

//swap two elements
void fexchange(float* x, float* y);

void exchange(int* x, int* y);

//fix error on heap
void Heapify_down_max(Heap* A, Heap* B, int i); //A is max-heap, B is min-heap

void Heapify_down_min(Heap* A, Heap* B, int i); //A is min-heap, B is max-heap

////fix error on heap
void Heapify_up_max(Heap* A, Heap* B, int i); //A is max-heap, B is min-heap

void Heapify_up_min(Heap* A, Heap* B, int i); //A is min-heap, B is max-heap
//build max_heap from given array
void Build_Heap_max(Heap* A, Heap* B, int n);

//build min_heap from fiven array
void Build_Heap_min(Heap* A, Heap* B, int n);

//insert new node with key x to both data heaps
void Insert(database* data, float* x);

//insert key into max-heap.
void Heap_Insert_max(Heap* A, Heap* B, float* key);//A is max-heap, B is min-heap

//insert key into min-heap
void Heap_Insert_min(Heap* A, Heap* B, float* key);//A is min-heap, B is max-heap

//initialiaze struct by given array
database* Init(float* S, int n);

//adding x to struct, passing database struct in order to get to heaps
void Insert(database* data, float x);
//return max val in data in O(1) time-complexity
float Find_max(database* data);
//return min val in data in O(1) time-complexity
float Find_min(database* data);



void Del(Heap* A, Heap* B, int i);


//Delete root of min_heap, uses 'twin' index to delete value from max-heap
//then correct both heaps
void Del_Min(database* data);

//same as Del_min just for max value.
void Del_Max(database* data);

int message();


#endif
