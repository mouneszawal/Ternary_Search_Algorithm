// C program to illustrate
// iterative approach to ternary search

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 100000000
#define ITERATION_SIZE 8



/*<<<<<<<<<<<<<<<<<<<<<<<	ProtoTypes	>>>>>>>>>>>>>>>>>>>>*/
void print(int *array);
// populates the array with numbers from 1-1000
void populateData(int *array);
// Generates random target value between 0 and upper
int generateRandomTarget(int upper);
// Function to perform Ternary Search
int ternarySearch(int left, int right, int key, int *array, int *);
void plot(int iteration_array[ITERATION_SIZE]);

//main method
int main(){	
	int startIndex=0, EndIndex, targetIndex, target,byTen;
	
	int *array = (int*)(malloc(sizeof(int) * SIZE)); //SIZE= 100000000
	// Storing the number of iterations made by ternary search algorithm
	// to find the target
	int number_of_iterations[ITERATION_SIZE],number_of_moves,i;
	//pupulates array with 100000000 numbers
	populateData(array);

	byTen=1; // to determine the array size in each iteration
	i=0;
	while(i<8){
		byTen*=10;
		target = generateRandomTarget(byTen);
		EndIndex = byTen -1;	
		targetIndex = ternarySearch(startIndex, EndIndex , target , array,&number_of_moves);
		number_of_iterations[i] = number_of_moves;
		// print the result
		printf("EndIndex: %d\n",EndIndex+1);
		targetIndex != -1 ? printf("Target %d found at index: %d with %d iterations\n\n", target, targetIndex,number_of_iterations[i])
		: printf("Target %d was not found with %d iterations\n\n", target,number_of_iterations[i]);
		
	    i++;
	}
	printf("\n\n\nnumber of iterations plot:\n");
	plot(number_of_iterations);// plot the number of iterations array

	return 0;
}

// populate the array with numbers
//from zero to SIZE = 100000000
void populateData(int *array){
	int i;
	// populate Array
	for(i=0;i<SIZE;i++){
		array[i] = i+1;
	}
	
}

void print(int *array){
	int i;
	for(i=0;i<SIZE;i++){
		printf("%4d", array[i] );
	}
	
}

int ternarySearch(int startIndex, int EndIndex, int target, int *array,int *number_of_moves){
	
	*number_of_moves=0; // variable to count the number of iterations
	while (EndIndex >= startIndex) {
		(*number_of_moves)++;
		// Find the mid1 and mid2
		int mid1 = startIndex + (EndIndex - startIndex) / 3;
		int mid2 = EndIndex - (EndIndex - startIndex) / 3;

		// Check if the target equals to any middle point
		// if this is the case, return the mid index
		if (array[mid1] == target) {
			printf("number of moves: %d\n",(*number_of_moves));
			return mid1;
		}
		if (array[mid2] == target) {
			printf("number of moves: %d\n",(*number_of_moves));
			return mid2;
		}

		// Since target is not present at mid,
		// check in which region it is present
		// then repeat the Search operation
		// in that region

		if (target < array[mid1]) {

			// The target is between startIndex and mid1
			EndIndex = mid1 - 1;
		}
		else if (target > array[mid2]) {
			// The target is between mid2 and EndIndex
			startIndex = mid2 + 1;
			
		}
		else {
			// The target is between mid1 and mid2
			startIndex = mid1 + 1;
			EndIndex = mid2 - 1;
		}
	}
	
	printf("number of moves: %d\n",(*number_of_moves));
	// target not found
	return -1;
}

// generates random number between 
// 0 and upper limit, but since our upper limit 
// might sometimes be bigger than RAND_MAX WHICH
// is 32767 in this library,so some modification
// is done
int generateRandomTarget(int upper){
	srand((unsigned int)time(0));
	unsigned long x;
	x = rand();
	x <<= 15;
	x ^= rand();
	return (x % (upper+1));
}

void plot(int iteration_array[ITERATION_SIZE]){
	int i,j,byTen=1;
	printf("data_size\tnumber_of_iterations\n");
	for(i=0;i<ITERATION_SIZE;i++){
		byTen*=10;
		if(i<6)
			printf("%d\t\t",byTen);
		else
			printf("%d\t",byTen);
		for(j=0;j<iteration_array[i];j++){
			printf("*");
		}
		printf("\n");
	}
}


