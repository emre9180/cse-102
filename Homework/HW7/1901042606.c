/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <string.h>

/* EMRE YILMAZ 1901042606 - GTU */
/* --------------------------------------------------------------------- NOTES FOR T.A. ----------------------------------------------------------------------------------------------------
/* 1-) Bonus part is done. */
/* 2-) In this homework, words that includes '&* character, is assumed as a compound word such as r&b. */
/* 3-) fix_spelling_error function is written considering bonus part. Fix_spelling_error function finds and fixes mistakes with 2 letters and with 1 letteer.
   Hence, fix_spelling_error2 function calls the fix_spelling_error function to fix mistakes with 1 or 2 letters */

void shifting(char *word) /* This function shifts all the letters in the word 1 character to the left */
{
	int i,j;
	int word_length = strlen(word);;

	for(i=0;i<word_length;i++)
	{
		word[i] = word[i+1];
	}

	return;
}

void up_again(char *best_word, char *read) /* this function capitalizes the letters of the word according to the text */
{
	int i,j;
	int word_length = strlen(read);
	for(i=0;i<word_length;i++)
	{
		if(read[i]!='&' && (read[i]>=65 && read[i]<=90)) /* If i'th letter of word in text is capital letter, we have to make i'th letter of best match capital too. */ 
		{
			best_word[i]-=32;
		}
	}
}

void extract(char *word) /* This function extracts the whitespace and punction mark characters from the Word */
{
	int i,j; /* Loop */
	int word_length;

	word_length = strlen(word);

	for(i=0;i<word_length;i++)
	{
		if(i==0 && ((word[i]<65 || word[i]>122 ) || (word[i]>=91 && word[i]<=96))) /* If the first letter is a punction mark or space, we need shifting */
		{
			shifting(word);
		}

		if(i!=0 && word[i]!='&' && ((word[i]<65 || word[i]>122 ) || (word[i]>=91 && word[i]<=96))) /* If a letter ,that is not FIRST character, is a punction mark or space, we need stop there */
		{
			word[i] = '\0'; /* if()*/
			return;
		}
	}

	return;
}

char *merge (char *correct_word, char *read) /* Combine the punctuation marks in the word read in the text file and the string 'best word' */
{	
	int i,j,k;
	int ct_cor = 0; /* Indicates what element of correct word we write */
	int read_length = strlen(read);
	char merge[20]; /* Merged string*/
	char *return_value; /* Points the address of merged string above, this address will be returned */

	for(i=0;i<read_length;i++)
	{
		if(read[i]!='&' && ((read[i]<65 || read[i]>122 ) || (read[i]>=91 && read[i]<=96)))
		{
			merge[i] = read[i];
		}

		else
		{
			merge[i] = correct_word[ct_cor];
			ct_cor++;
		}
	}

	merge[i] = '\0';

	return_value = merge;
	return return_value;

}

void toLower(char *read) /* Makes the string's letters lower case */
{
	int length = strlen(read);
	int i;
	for(i=0;i<length;i++)
	{
		if(read[i]!='&' && (!(read[i]<=122 && read[i]>=97))) /* If the letter is not lower case, make them lower case */
			read[i] += 32;
	}
}

int find_best_correction(char *word, char *dictionary, char *best_word)
{
	FILE *file;
	int best_difN = 1000; /* Number of wrong letters in best match. Initiliazed as 1000, will be changed */
	int diff_ct = 0; /* Keeps the number of different letters in word that read from text and currently read from dictionary words */

	int ct_consTovowel = 0; /* Number of letters that change from consonent to vowel in word that is currently read */
	int max_consTovowel; /* Number of letters that change from consonent to vowel in word that is best match */

	int match_number = 0; /* Number of best match  */

	char diff_let[3] = { '\0', '\0', '\0'} ; /* The letters of the word read from text, changing according to the word in the dictionary  */
	char correct_diff[3] = { '\0', '\0', '\0'} ; /* The letters of the word read from dictionary, chanhing according to the word in the text */

	int word_length; /* Lwngth of words that came from text file, (length of 'word' string) */
	int readWord_length; /* Length of words that read from text file */
	char read_dic[20]; /* Read words from text file will be kept in this variable */
	char temp_read_dic[20];
	int i,j,k; /* Loop */

	word_length = strlen(word);

	file = fopen(dictionary,"r+");

	while(!feof(file)) /* */
	{	
		diff_ct = 0;
		fscanf(file,"%s",read_dic);
		toLower(read_dic);

		/* If read word length is not equal to word that come from text, we can say that there is no match */
		if(strlen(read_dic)!=strlen(word))
			continue;

		/* Counting different letters and assigning those different letters to arrays */
		for(i=0;i<word_length;i++)
		{
			if(word[i]!=read_dic[i])
			{
				if(diff_ct<3)
				{
					diff_let[diff_ct] == word[i];
					correct_diff[diff_ct] = read_dic[i];
				}

				diff_ct++;
			}

		}
 
		if(diff_ct>2) /* If the number of different letters greater than 2, we can say that there is no match */
			continue;

		if(diff_ct==0) /* If we found the exact word, we are done. Return 1 */
		{
			strcpy(best_word,read_dic);
			return 1;
		}

		/* If the number of different letters of current read word equals to different letter number in best match, we must check its letters whether changing from consonant to vovel */
		if(diff_ct==best_difN)
		{	
			ct_consTovowel = 0;

			/* Comparing the different letters of dictionary word and read word */
			for(k=0;k<diff_ct;k++)
			{
				/* Check that changing words from consonant to vowel.  */
				if((diff_let[k]!='a' && diff_let[k]!='e' && diff_let[k]!='i' && diff_let[k]!='u' && diff_let[k]!='o') && 
					(correct_diff[k]=='a' || correct_diff[k]=='e' || correct_diff[k]=='i' || correct_diff[k]=='u' || correct_diff[k]=='o'))
				{
					ct_consTovowel++;
				}
			}

			if(ct_consTovowel>max_consTovowel)
			{
				match_number = 1; /* We found new best match. So, we have to restart our counter */
				best_difN = diff_ct; /* Update */
				strcpy(best_word,read_dic); /* Update best word */
				max_consTovowel=ct_consTovowel; /* Update */
			}

			else if(ct_consTovowel==max_consTovowel) /* We are expected to find the first three matching words and apply the rule in PDF. In case of a tie, we use the SECOND occurrence */
			{
				match_number++;
				if( match_number<3) /* In case of a tie, we use the SECOND occurrence */
				{
					best_difN = diff_ct; /* Update */
					strcpy(best_word,read_dic); /* Update best word */
					max_consTovowel=ct_consTovowel; /* Update */
				}	
			}
		}

		/* If the number of different letters of current read word and the word the text file smaller than different letter number in best match, we must update */
		else if (diff_ct<best_difN)
		{
			match_number = 1; /* We found new best match. So, we have to restart our counter */
			for(k=0;k<diff_ct;k++)
			{
				/* Check that changing words from consonant to vowel */
				if((diff_let[k]!='a' && diff_let[k]!='e' && diff_let[k]!='i' && diff_let[k]!='u' && diff_let[k]!='o') && 
					(correct_diff[k]=='a' || correct_diff[k]=='e' || correct_diff[k]=='i' || correct_diff[k]=='u' || correct_diff[k]=='o'))
				{
					ct_consTovowel++;
				}
			}

			best_difN = diff_ct; /* Update */
			strcpy(best_word,read_dic); /* Update best word */
			max_consTovowel = ct_consTovowel; /* Update */
		}
	}

	fclose(file);

	/* We found a valid match */
	if(match_number>0)
	{
		return 1;
	}
	/* We could NOT find a valid match */
	else
	{
		return 0;
	}
}



void fix_spelling_error(char *text, char *dictionary)
{

	int i = 0,j,k; /* Loop */
	int word_length = 0;
	char best_word[20]; /* Best match in the given dictionary */
	char read[20]; /* Read words will be kept in this variable */
	char temp_read[20]; /* Copy of read word from text file */
	char merged[20]; /* Combination the punctuation marks in the word read in the text file and the matching words in the dictionary */

	FILE *file; 
	file = fopen(text,"r+");
	
	while(1)
	{
	
		fscanf(file,"%s",read);
		if(feof(file))
		{
			break;
		}

		strcpy(temp_read,read); /* Copy of read word from text file */
		
		extract(read); /* Extract the word such that white spaces and punctuation marks */
		toLower(read); /* Make read word's letters lowercase */
		

		if (find_best_correction(read, dictionary, best_word)) /* If we find a matching word that is stored in 'best word' string, go in if block belove> */
		{
			up_again(best_word, temp_read); /* Correcting letters that are small in the dictionary but large in the text. */
			strcpy(merged,merge(best_word,temp_read)); /* Combine the punctuation marks in the word read in the text file and the string 'best word' */
			fseek(file, (strlen(temp_read))*-1, SEEK_CUR); /* Step back in the text file to write */
			fprintf(file,"%s",merged); /* Write the matching true word */		
		}
		else /* If we can't find a word in the dictionary, we have to write the same word back in the text unfortunately. */
		{
			fseek(file, (strlen(temp_read))*-1, SEEK_CUR); /* Step back in the text file to write */
			fprintf(file,"%s",temp_read); /* Write the matching true word */
		}


	}

	fclose(file);
	printf("Correction process is complated successfuly.\n");
	return;
}


void fix_spelling_error2(char *text, char *dictionary) /* In the normal part of homework, the bonus part is done too. Normal part of homework(fix_spelling_error function) can handle mistakes with 2 letters.*/
{													   /* So, this function calls the normal part to handle mistakes with 2 letters */
	fix_spelling_error(text,dictionary);
}

int main(){

 char text_file[30] = "text.txt";
 char dic_file[30] = "dictionary.txt";
 fix_spelling_error2(text_file,dic_file);
 return 1;

}
