#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* Given a number, return the maximum number that could be formed with digits of the number given.
* For example: number = 7389, return 9873
*/
void swap(char *xp, char *yp)
{
	char temp = *xp;
	*xp = *yp;
	*yp = temp;
}
int form_the_largest_number(int number)
{
	int digits_counter = 0;
	int number_copy = number;
	char * number_str;
	int largest;
	
	// Calculate number of digits in given integer
	while (number_copy != 0)
	{
		number_copy /= 10;
		digits_counter++;
	}
	
	// Allocate memory for string to store converted integer
	number_str = (char *) malloc(digits_counter * sizeof (char) + 1);
	// Convert integer to string 
	sprintf(number_str, "%d", number);
	
	// Bubble sort digits of the string
	for (int i = 0; i < strlen(number_str); i++)
	{
		for (int j = 0; j < strlen(number_str) - i - 1; j++)
		{
			// If digit is smaller than next one change their order
			if (number_str[j] < number_str[j+1])
				swap(&number_str[j+1], &number_str[j]);
		}
	}	

	// Convert string to integer
	largest = atoi(number_str);
	free(number_str);
	
	return largest;
}

void test_cases()
{
	int result = form_the_largest_number(213);
	assert(result == 321);

	result = form_the_largest_number(7389);
	assert(result == 9873);

	result = form_the_largest_number(63729);
	assert(result == 97632);

	result = form_the_largest_number(566797);
	assert(result == 977665);
}

int main()
{
	test_cases();
}
