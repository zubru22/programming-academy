#include <assert.h>

/**
* Function takes a 'start' and 'end' number of a range, and should return the count of all numbers except numbers with 5 in it.
* For example: start = 4, end = 8. It should return 4, because: 4, 6, 7, 8
*/
int numbers_without_five(int start, int end)
{
	int count = 0;
	
	// Iterate in range 
	for (int i = start; i <= end; i++)
	{
		/* If it's possible to divide number by 5 without reminder
		 * and the number is not even then it has 5 in it */
		if (i % 5 == 0 && i % 2 != 0)
			continue;
		// Else it's just a number
		else
			count++;
	}
	
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
	assert(answer == 90);
}

int main(int argc, char *argv[])
{
	test_cases();
	return 0;
}
