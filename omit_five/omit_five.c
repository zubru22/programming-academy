#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
* Function takes a 'start' and 'end' number of a range, and should return the count of all numbers except numbers with 5 in it.
* For example: start = 4, end = 8. It should return 4, because: 4, 6, 7, 8
*/
int numbers_without_five(int start, int end)
{
	int count = 0;
	int end_copy = end;
	int digits = 0;
	char *num_str;
	
	// Calculate maximum number of digits to be stored inside the string
	while (end_copy != 0)
	{
		end_copy /= 10;
		digits++;
	}
	
	// Allocate memory for string to store converted integer
	num_str = (char *) malloc(digits * sizeof(char) + 1);
	
	// Iterate in range 
	for (int i = start; i <= end; i++)
	{
		sprintf(num_str, "%d", i);
		
		// If string contains 5 skip it
		if (strchr(num_str, '5'))
			continue;
		// Else count the number
		else
			count++;
	}
	
	// Free memory allocated for string
	free(num_str);
	return count;
}

void test_cases()
{
	int answer = numbers_without_five(4, 8);
	assert(answer == 4);

	answer = numbers_without_five(1, 9);
	assert(answer == 8);

	answer = numbers_without_five(4, 17);
	assert(answer == 12);
	
	// Test case in bigger range
	answer = numbers_without_five(1, 100);
	assert(answer == 81);
}

int main(int argc, char *argv[])
{
	test_cases();
	return 0;
}
