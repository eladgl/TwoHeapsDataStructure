

#include "heap.h"

#define TH 1

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>


int main() {

	float arr1[M], temp, insertedNum;
	database* data = NULL;
	int i, option = 1;
	int amount = 0;
	while (amount < M) {
		printf("\nPlease enter how many numbers you want to enter, it should be below %d numbers: ", M);
		scanf("%d", &amount);
		if (amount > M) {
			printf("the number you entered is too big, please enter a number below %d", M);
			amount = 0;
		}
		else
			break;
	}
	for (i = 0; i < amount; i++) {
		printf("\nEnter number: ");
		scanf("%f", &temp);
		arr1[i] = temp;
	}
	data = Init(&arr1, amount);
	if (data == NULL) {
		printf("\ncouldn't allocate memory and initializing the data. please try again later");
		exit(1);
	}



	while (TH) {
		fflush(stdin);
		option = message();
		switch (option) {
		case 1: {//find min
			if (data->dataBaseSize == 0) {
				printf("There are not numbers in the databse");


			}
			else {
				printf("\nThis is the minimum value: %f", Find_min(data));
			}
			break;
		}
		case 2: { //find max
			if (data->dataBaseSize == 0) {
				printf("There are not numbers in the databse");
			}
			else {
				printf("\nThis is the maxmimum value: %f", Find_max(data));
			}
			break;
		}
		case 3: {//Insert
			if (data->dataBaseSize < M) {
				printf("\nPlease enter a number that you want to enter the database: ");
				scanf("%f", &insertedNum);
				Insert(data, insertedNum);
			}
			else {
				printf("\nThere are too many numbers in the database, please delete some before insertting any more");
			}
			break;
		}
		case 4: {//Del MIN
			if (data->dataBaseSize > 0) {
				Del_Min(data);
			}
			else {
				printf("\nThere are no numbers in the database");
			}
			break;
		}
		case 5: {
			if (data->dataBaseSize > 0) {
				Del_Max(data);
			}
			else {
				printf("\nThere are no numbers in the database");
			}
			break;
		}
		case 6: {
			printf("Exiting program.. See Ya");
			exit(1);
			break;
		}
		default: {
			if (option < 1 || option > 6)
				printf("You entered wrong option. Please enter values '1-6' Thank you");
			break;
		}
		}
	}
	return 0;
}
