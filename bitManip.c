#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 *---Author: Kyle Krueger---
 *
 * Objective:
 * 	Allow user to indicate decimal number and bit system (4/8/16/32/64)
 * 	Output the binary number of the indicated system
 *	
 *	*ptr stores an address, the right hand of the assignment, allocates a memory of n1 bits to it*
 *	int* ptr
 *	ptr = (int*)malloc(n1*sizeof(int))
 *	
 *	
 */
//Converts the decimal number (val) into a binary input of size (size), and stores the result into (arr)
void DecToBin(int* arr, unsigned long long* val, int* size);
//Converts the binary array in (arr) of size (size) into its one's Compliment
void BinToOnes(int* arr, int* size);
//Converts the binary array in (arr) of size (size) into its Two's Compliment by adding 1 to the number
void OnesToTwos(int* arr, int* size);
//Exits the program if the value passed in is not an integer
void DecCheck(char* val);
//Exits the program if the bit system is not a power of 2
void BitCheck(char* val);
//Prints the array (arr) of size (size) to the console
void DisplayArr(int* arr, int* size);
//Used to calculate 2^(exp)
unsigned long long power2(int* exp);

int main(int argc, char *argv[])
{
	//---INPUT VALIDATION---
	//Check if there is correct number of arguments
	if(argc != 3){
		printf("[ERROR 1]: Expected 2 arguments, received %d\n",argc-1);
		exit(1);
	}

	//Validate arguments. argv[1] should be the decimal, argv[2] should be the bit system
	DecCheck(argv[1]);
	BitCheck(argv[2]);

	//---VARIABLES---
	//Create an array using the second argument as the size of bits
	int* arr, *bin;
	unsigned long long* dec;
	dec = (unsigned long long*)malloc(sizeof(unsigned long long));
	bin = (int*)malloc(sizeof(int));
	sscanf(argv[1],"%llu",dec);
	sscanf(argv[2],"%d",bin);
	//Check if the decimal is able to fit in that binary representation
	if((*dec/2) >= power2(bin)){
		printf("[ERROR 2]: %llu is not able to be represented in %d bits\n",*dec, *bin);
		exit(2);
	}
	arr = (int*)malloc(*bin * sizeof(int));

	//---FUNCTIONALITY---
	//Convert the Decimal to its binary representation
	DecToBin(arr,dec,bin);
	//Convert the Binary representation to One's and Two's Compliment
	BinToOnes(arr,bin);
	OnesToTwos(arr,bin);
	//Program Completed
	free(dec);
	free(bin);
	free(arr);

	return EXIT_SUCCESS;
}
void DecCheck(char* val){
	//Checks that the first argument passed in is a valid Decimal
	int i = 0;
	for (i = 0; i<strlen(val); i++){
		if(!isdigit(val[i])){
		printf("[ERROR 3]: Argument passed in is not an integer\n"); 
		exit(3);
		}
	}

}
void BitCheck(char* val){
	//Checks that the second argument passed in is a valid bit system
	//Check if the input is a number using DecCheck
	DecCheck(val);
	//Check if the number is divisable by 2
	unsigned long long *num = (unsigned long long*)malloc(sizeof(unsigned long long));
	sscanf(val,"%llu",num);
	while(((*num & 1) == 0) && *num > 1){ //Checks if the rightmost bit is a 1, if it is, exit the program, for it is not a power of two, keep doing this check and shifting bits by 1 until we have reached the final bit
		*num >>= 1;
		if (*num == 1) {
			free(num);
			return;
		}
		//printf("%d <- num in BitCheck\n",*num);
	}
	printf("[ERROR 4]: Second argument is not a power of 2\n,");
	exit(4);
	
	
	
}
void DecToBin(int* arr, unsigned long long* val, int* size){
	//Converts the number of 'val' into a bit system of size 'size', populating the result into arr
	//Populate the array with 0's to begin
	int* arrayStart = arr;
	int* arrayEnd = arr + *size;
	while (arrayStart < arrayEnd){
		// If our value is less than 2^(our current bit)
		*arrayStart = *val % 2;
		*val = *val / 2;
		arrayStart++;
	}
	printf("Binary: ");
	DisplayArr(arr, size);
	
}

void BinToOnes(int* arr, int* size){
	//Converts the binary representation of an integer into its Ones Compliment
	int* arrayStart = arr;
	int* arrayEnd = arr + *size;
	//Loop through the array, flip the bits
	while(arrayStart < arrayEnd--){
		//printf("%d",arr[*i]);
		if(*arrayEnd == 0) *arrayEnd = 1;
		else *arrayEnd = 0;
	}
	printf("One's Compliment: ");
	DisplayArr(arr,size);
}
void OnesToTwos(int* arr, int* size){
	//Converts the Ones Compliment of an integer into its Twos Compliment
	int* arrayStart = arr;
	int* arrayEnd = arr + *size;
	char* carry = (char*)malloc(sizeof(char));
	*carry = 0;
	//Adding the initial 1
	if (*arrayStart == 0) *arrayStart = 1;
	else{
		*arrayStart = 0;
		*carry = 1;
		arrayStart++;
		while(1==1){
			if (*carry == 0) break;
			else if(*arrayStart == 0){
			*carry = 0;
			*arrayStart = 1;
			}
			else if (*arrayStart == 1) {
			*arrayStart = 0;
			*carry = 1;
			}
			arrayStart++;
		}
	}
	free(carry);
	printf("Two's Compliment: ");
	DisplayArr(arr,size);
}

void DisplayArr(int* arr, int* size){
	//Displays the passed in Array of size Size to the console
	int* arrayStart = arr;
	int* arrayEnd = arr + *size;
	while(arrayStart < arrayEnd--){
		//printf("%d",arr[*i]);
		printf("%d",*arrayEnd);
		//arrayEnd--;
	}
	printf("\n");
	
}

unsigned long long power2(int* exp)
{
	//Note: to deal with 64 bit numbers, I decided to have this function return the 2^(exp -1) value. This goes around an overflow issue
    unsigned long long* result = (unsigned long long*)malloc(sizeof(unsigned long long));
    int* tempExp = (int*)malloc(sizeof(int));
    *tempExp = *exp;
    *result = 1;
    while(*tempExp -1) 
    {   
        *result = *result * 2; 
        *tempExp = *tempExp - 1; 
    }
	
    free(tempExp);

    return *result;
}
