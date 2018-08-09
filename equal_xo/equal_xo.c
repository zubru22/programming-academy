#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
/**
* Function checks if a string has the same amount of 'x' and 'o's. Function must be case insensitive.
*/
bool XO(const char *word, const int length)
{
	int i;
	int x_amount = 0;
	int o_amount = 0;
	bool equal;
	
	// Iterate over the word and count 'x's and 'o's
	for (i = 0; i < length; i++)
	{
		if (tolower(word[i]) == 'x')
			x_amount++;
		if (tolower(word[i]) == 'o')
			o_amount++;
	}
	
	// If amount of 'x's and 'o's are equal assign true value to equal flag
	if (x_amount == o_amount)
		equal = true;
	else
		equal = false;
	
	return equal;
}

void test_cases()
{
	bool answer = XO("ooxx", strlen("ooxx"));
	assert(answer == true);

	answer = XO("xooxx", strlen("xooxx"));
	assert(answer == false);

	answer = XO("ooxXm", strlen("ooxXm"));
	assert(answer == true);

	answer = XO("zzoo", strlen("zzoo"));
	assert(answer == false);
}

int main(int argc, char *argv[])
{
	test_cases();
	return 0;
}
