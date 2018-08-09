#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define ARR_LEN 5
#define MAX_NUM 49
#define MIN_NUM 1

/** 
* Function returns an array of 5 elements.
* Those 5 elements are created randomly in the range 1 - 49.
* Numbers can't repeat.
*/
bool in_array(int *numbers, int size, int num)
{	
	for (int i = 0; i < size; i++)
		if (numbers[i] == num)
			return true;
			
	return false;
}
int* Lotto_drawing()
{
	int random_number;
	int *random_numbers;
	
	// Allocate memory for array with ARR_LEN length
	random_numbers = (int *) calloc(ARR_LEN, sizeof(int));
	
	// Generate random numbers and insert them into array
	for (int i = 0; i < ARR_LEN; i++)
	{
		// Generate random number
		random_number = rand() % (MAX_NUM + 1 - MIN_NUM) + MIN_NUM;
		/* If generated number is already in the array try again
		 * - keep trying until distinct number is generated */
		while (in_array(random_numbers, i, random_number))
			random_number = rand() % (MAX_NUM + 1 - MIN_NUM) + MIN_NUM;
		// Assign number to the array
		random_numbers[i] = random_number;
	}
	
	// Return pointer to array of random numbers
	return random_numbers;
}

bool in_range(int *numbers)
{
	bool result = true;
	
	/* Iterate over array of random numbers and 
	 * check if any of them are outside the range */
	for (int i = 0; i < ARR_LEN; i++)
	{
		// If number is smaller or bigger than range assign false
		if (numbers[i] < MIN_NUM || numbers[i] > MAX_NUM)
			result = false;
	}
	
	return result;
}

bool distinct (int *numbers)
{
	bool  distinct = true;
	
	// Iterate over random numbers and check for duplicates
	for (int i = 0; i < ARR_LEN; i++)
	{
		for (int j = i + 1; j < ARR_LEN; j++)
		{
			// If there's duplicate set flag to false
			if (numbers[i] == numbers[j])
			{
				distinct = false;
				// Break out of inner loop
				break;
			}
			// If false break out outer loop
			if (!distinct)
				break;
		}
	}
	
	return distinct;
}

/* Please create test cases for this program. test_cases() function can return void, bool or int. */
void test_cases()
{
	bool result;
	int *random_numbers = Lotto_drawing();
	
	// Check if numbers are within range
	result = in_range(random_numbers);
	assert(result == true);
	
	// Check if numbers are not duplicated
	result = distinct(random_numbers);
	assert(result == true);
	
	// Free memory allocated for random number array
	free(random_numbers);
}


int main()
{
	// Random seed for generating random numbers
	srand(time(NULL));
	
	test_cases();
	return 0;
}
