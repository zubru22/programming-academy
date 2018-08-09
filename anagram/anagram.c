#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
/** 
* Function returns true if word_1 and word_2 are anagrams to each other. Otherwise false.
* Case sensitivity doesn't matter.
*/
bool check_if_anagram(const char* word_1, int length_1, const char* word_2, int length_2)
{
	int i;
	// Assume that words are anagrams 
	bool anagram = true;
	char word_1_copy[length_1];
	char word_2_copy[length_2];
	
	// If either of words are empty return false
	if (length_2 == 0 || length_1 == 0)
		return false;
	
	// Create copies of strings
	strcpy(word_1_copy, word_1);
	strcpy(word_2_copy, word_2);
	
	// Make copies of strings lowercase
	for (i = 0; i < length_1; i++)
		word_1_copy[i] = tolower(word_1[i]);
		
	for (i = 0; i < length_2; i++)
		word_2_copy[i] = tolower(word_2[i]);

	// Iterate over second word
	for (i = 0; i < length_2; i++)
	{
		// If character is space just ignore it
		if (word_2_copy[i] == ' ')
			continue;
		/* Search for character from second word in first word 
		 * if character was not found second word is not anagram */
		if (strchr(word_1_copy, word_2_copy[i]) == NULL)
			anagram = false;
	}
	
	return anagram;
}

void test_cases()
{
	bool answer = check_if_anagram("LordVader", strlen("LordVader"), "VaderLord", strlen("VaderLord"));
	assert(answer == true);

	answer = check_if_anagram("silent", strlen("silent"), "listen", strlen("listen"));
	assert(answer == true);

	answer = check_if_anagram("funeral", strlen("funeral"), "real fun", strlen("real fun"));
	assert(answer == true);

	answer = check_if_anagram("Elon Musk", strlen("Elon Musk"), "Muskmelon", strlen("Muskmelon"));
	assert(answer == true);

	answer = check_if_anagram("Tieto", strlen("Tieto"), "Tietonator", strlen("Tietonator"));
	assert(answer == false);

	answer = check_if_anagram("Football", strlen("Football"), "Basketball", strlen("Basketball"));
	assert(answer == false);

	answer = check_if_anagram("F", strlen("F"), "", strlen(""));
	assert(answer == false);
}

int main()
{
	test_cases();
}
