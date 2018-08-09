#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

/**
* Function duplicates letters based on their index. Each index means how many times the letter needs to be duplicated.
* See test cases for examples.
*/

char* accumulate(const char *word, const int length)
{
	char *curr_char, *mumbled_str;
	int mumble_size = (length - 1);
	
	// Calculate mumbled word length counting all the dashes and repeated letters
	for (int i = 0; i < length; i++)
		mumble_size += (i + 1);
	
	// Allocate memory for char pointer
	curr_char = (char *) malloc(sizeof(char));
	// Allocate memory for mumbled string
	mumbled_str = (char *) malloc(mumble_size * sizeof(char) + 1);
	
	// Iterate over input word
	for (int i = 0; i < length; i++)
	{
		// Store character
		*curr_char = word[i];
		
		// For every character from input word
		for (int j = 0; j < i + 1; j++)
		{
			// Append it to mumbled string n times
			// Make first occurance of letter uppercase
			if (j == 0)
			{
				*curr_char = toupper(*curr_char);
				strcat(mumbled_str, curr_char);
			}
			// Change it back to lower case and keep appending the letter
			else if (isupper(*curr_char))
			{
				*curr_char = tolower(*curr_char);
				strcat(mumbled_str, curr_char);
			}
			else
				strcat(mumbled_str, curr_char);
		}
		// Insert dashes until second to last letter of input word
		if (i != length - 1)
		{	
			*curr_char = '-';
			strcat(mumbled_str, curr_char);
		}
		
	}
	// Free single char pointer
	free(curr_char);
	
	return mumbled_str;
}

void test_cases()
{
	char* result = accumulate("abcd", strlen("abcd"));
	assert(strcmp(result, "A-Bb-Ccc-Dddd") == 0);

	result = accumulate("cwAt", strlen("cwAt"));
	assert(strcmp(result, "C-Ww-Aaa-Tttt") == 0);
	
	// Free mumbled string
	free(result);
}

int main(int argc, char *argv[])
{
	test_cases();
	return 0;
}
