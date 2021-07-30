/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* Emre YILMAZ 1901042606 | Gebze Technical University */

/* NOTES FOR T.A. */
/* Binary file format is: (s1word). [ s -> word type, synonym(s) or antonym(a) || 1 -> correctness, 1:true ; 0:false || word -> asked word] */
/* Maximum word length is assumed as 35 characters */
/* The probability that the antonym of the word -asked for a synonym previously- is increased, as said in the PDF. ( of course, if this word is in the antonyms list) */


typedef struct calculator
{
    int index;
    int ct;
}probability;

typedef struct syn
{
    char *word;
    char **syn_word;
    int word_num;
    struct syn *next;
}syn_list;

typedef struct ant
{
    char *word;
    char **ant_word;
    int word_num;
    struct ant *next;
}ant_list;

/* ----------------------- REALLOCATION FUNCTIONS STARTS HERE. THIS FUNCTIONS REALLOCATE MEMORY WITHOUT realloc() FUNCTION -----------------------*/

void reallocate_copy_ant(ant_list *node, char *word)
{
/* This function reallocates the memory that double char pointer -inside antonym linked list- points without using realloc() function. Then, copy the word. */
	char **ptr;
	int i;

	ptr = (char**)calloc((node->word_num)+1,8);

	for(i=0;i<node->word_num;i++)
	{
		int length = strlen(node->ant_word[i]);
		ptr[i] =  (char*)calloc(length+1,sizeof(char));
		strcpy(ptr[i],node->ant_word[i]);
	}

	ptr[i] = (char*)calloc(strlen(word)+1,sizeof(char));
	strcpy(ptr[i],word);
	free(node->ant_word);
	node->ant_word = ptr;

}

void reallocate_copy_syn(syn_list *node, char *word)
{
/* This function reallocates the memory that double char pointer -inside synonym linked list- points without using realloc() function. Then, copy the word. */
	char **ptr;
	int i;

	ptr = (char**)calloc((node->word_num)+1,8);

	for(i=0;i<node->word_num;i++)
	{
		int length = strlen(node->syn_word[i]);
		ptr[i] =  (char*)calloc(length+1,sizeof(char));
		strcpy(ptr[i],node->syn_word[i]);
	}

	ptr[i] = (char*)calloc(strlen(word)+1,sizeof(char));
	strcpy(ptr[i],word);
	free(node->syn_word);
	node->syn_word = ptr;
}

void reallocate_syn(syn_list *node)
{
/* This function reallocates the memory that double char pointer -inside synonym linked list- points without using realloc() function. */
	char **ptr;
	int i;

	ptr = (char**)calloc((node->word_num+1),8);

	for(i=0;i<node->word_num;i++)
	{
		int length = strlen(node->syn_word[i]);
		ptr[i] =  (char*)calloc(length+1,sizeof(char));
		strcpy(ptr[i],node->syn_word[i]);
	}

	free(node->syn_word);
	node->syn_word = ptr;
}

void reallocate_ant(ant_list *node)
{
/* This function reallocates the memory that double char pointer -inside anotonym linked list- points without using realloc() function. */
	char **ptr;
	int i;

	ptr = (char**)calloc((node->word_num+1),8);

	for(i=0;i<node->word_num;i++)
	{
		int length = strlen(node->ant_word[i]);
		ptr[i] =  (char*)calloc(length+1,sizeof(char));
		strcpy(ptr[i],node->ant_word[i]);
	}

	free(node->ant_word);
	node->ant_word = ptr;
}

void reallocate3_ant(ant_list *node, int letter_ct, int word_ct)
{
/* This function reallocates the memory that a char pointer -inside antonym linked list- points without using realloc() function */
    int i;
    char *ptr = (char*)calloc(letter_ct+1,sizeof(char));
    for(i=0;i<letter_ct;i++)
        ptr[i] = node->ant_word[word_ct][i];
    free(node->ant_word[word_ct]);
    node->ant_word[word_ct] = ptr;
}

void reallocate3_syn(syn_list *node, int letter_ct, int word_ct)
{
/* This function reallocates the memory that a char pointer -inside synonym linked list- points without using realloc() function */
    int i;
    char *ptr = (char*)calloc(letter_ct+1,sizeof(char));
    for(i=0;i<letter_ct;i++)
        ptr[i] = node->syn_word[word_ct][i];
    free(node->syn_word[word_ct]);
    node->syn_word[word_ct] = ptr;
}

/* ----------------------- REALLOCATION FUNCTIONS ENDS HERE. THIS FUNCTIONS REALLOCATE MEMORY WITHOUT realloc() FUNCTION -----------------------             */

/*                           -                   -                         -                        -                    -                            -        */

/* ---------------------------------------------- READING FILES AND CREATING LINKED LIST PROCESSES STARTS HERE. ---------------------------------------------- */

syn_list *initialize_Syn_list(syn_list *syn_head, FILE *file)
{
/* This function reads the first line of synonym words text, then crate the head of synonym linked list */

    char read[35]; /* Read word */
    char readc; /* Read character */
    char garbage; /* garbage */

    int word_ct = 0; /* Indicates which synonym we read in a line */
    int letter_ct = 0; /* Indicates which letter than belongs a word we read */

    /* Creating head node */
    syn_head = (syn_list*)malloc(sizeof(syn_list));
    syn_head->syn_word = (char**)calloc(1,8);
    syn_head->syn_word[0] = (char*)calloc(1,sizeof(char));
    syn_head->word_num = 0;
    syn_head->next = NULL;

    /* Read and write word */
    fscanf(file,"%s",read);
    syn_head->word = (char*)calloc(strlen(read)+1,sizeof(char));
    strcpy(syn_head->word,read);

    /* Read '=' character and no need character(white-space) */
    fscanf(file,"%s",read);
    fscanf(file,"%c",&readc);

    /* Initiliaze the memory of 2D array that includes synonym words */
    syn_head->syn_word = (char**)calloc(1,8);
    syn_head->syn_word[0] = (char*)calloc(1,sizeof(char));

    /* Read anthonyms until '\n' char read */
    while(1)
    {
        fscanf(file,"%c",&readc);
        if(readc=='\n')
        {
        	syn_head->word_num++;
            reallocate3_syn(syn_head, letter_ct, word_ct);
            syn_head->syn_word[word_ct][letter_ct] = '\0';
            break;
        }
        else if(readc==' ')
        {
            reallocate3_syn(syn_head, letter_ct, word_ct);
            syn_head->syn_word[word_ct][letter_ct] = '\0';

        	syn_head->word_num++;
            word_ct++;
            reallocate_syn(syn_head);
            syn_head->syn_word[word_ct] = (char*)calloc(1,sizeof(char));
            letter_ct = 0;
        }

        else if((readc>=65 && readc<=122) || readc=='-')
        {
            reallocate3_syn(syn_head, letter_ct, word_ct);
            syn_head->syn_word[word_ct][letter_ct] = readc;
            letter_ct++;
        }
    }

    return syn_head;
}

syn_list *fill_Syn_list(syn_list *syn_head, FILE *file)
{
/* This function reads the rest of the synonym text, adds the read words-synonyms the tail of linked list */

    char read[35]; /* Read word */
    char readc; /* Read character */
    char garbage; /* garbage */

    int letter_ct = 0; /* Indicates which letter than belongs a word we read */
    int word_ct = 0; /* Indicates which synonym we read in a line */

    /* Creating second node */
    syn_list *iter;
    iter=syn_head;
    iter->next = (syn_list*)malloc(sizeof(syn_list));
    iter=iter->next;
    iter->word_num = 0;
    iter->next = NULL;
    /* Inilitiaze the memory of second node's 2D array that will be filled with synonym words */
    iter->syn_word = (char**)calloc(1,8);
    iter->syn_word[0] = (char*)calloc(1,sizeof(char));
    

    /* Read and write word */
    fscanf(file,"%s",read);
    iter->word = (char*)calloc(strlen(read)+1,sizeof(char));
    strcpy(iter->word,read);

    /* Read '< >' characters and no need character(white-space) */
    fscanf(file,"%s",read);
    fscanf(file,"%c",&readc);

    /* Read anthonyms until reach the End of FILE */
    while(1)
    {
        fscanf(file,"%c",&readc);

        if (feof(file))
        {   
        	/*iter->word_num++;*/ /* KEEP IT IN COMMENT LINES */
        	iter->next = NULL;
            break;
        }

        if(readc=='\n')
        {
            /* If we reach the new line, we have to create new node because we are reading new synonyms of a word */
            /* Creating new node and required memory of that node */
        	iter->word_num++;
            iter->next = (syn_list*)malloc(sizeof(syn_list));
            iter=iter->next;
            iter->word_num = 0;
            /*iter->syn_word = (char**)calloc(1,8);
            iter->syn_word[0] = (char*)calloc(1,sizeof(char));*/
            iter->next = NULL;

            /* Read and write word */
            fscanf(file,"%s",read);
            iter->word = (char*)calloc(strlen(read)+1,sizeof(char));
            strcpy(iter->word,read);

            /* Read '< >' characters and no need character(white-space) */
            fscanf(file,"%s",read);
            fscanf(file,"%c",&readc);

            /* Inilitiaze the memory of new node's 2D array that will be filled with synonym words */
            iter->syn_word = (char**)calloc(1,8);
            iter->syn_word[0] = (char*)calloc(1,sizeof(char));

            /* Reset the counters */
            word_ct= 0;
            letter_ct = 0;

        }

        else if(readc==' ')
        {
        	iter->word_num++;
        	word_ct++;
        	reallocate_syn(iter);
            iter->syn_word[word_ct] = (char*)calloc(1,sizeof(char));
            letter_ct = 0;
        }

        else if((readc>=65 && readc<=122) || readc=='-')
        {
            reallocate3_syn(iter, letter_ct, word_ct);
            iter->syn_word[word_ct][letter_ct] = readc;
            letter_ct++;
        }
    }

    return syn_head;
}


ant_list *initialize_Ant_list(ant_list *ant_head, FILE *file)
{
/* This function reads the first line of antonym words text, then crate the head of synonym linked list */
    char read[35]; /* Read word */
    char readc; /* Read character */
    char garbage; /* garbage */

    int word_ct = 0; /* Indicates which antonym we read in a line */
    int letter_ct = 0; /* Indicates which letter than belongs a word we read */

    /* Creating head node */
    ant_head = (ant_list*)malloc(sizeof(ant_list));
    ant_head->ant_word = (char**)calloc(1,8);
    ant_head->ant_word[0] = (char*)calloc(1,sizeof(char));
    ant_head->word_num = 0;
    ant_head->next = NULL;

    /* Read and write word */
    fscanf(file,"%s",read);
    ant_head->word = (char*)calloc(strlen(read)+1,sizeof(char));
    strcpy(ant_head->word,read);

    /* Read '< >' characters and no need character(white-space) */
    fscanf(file,"%s",read);
    fscanf(file,"%c",&readc);

    /* Intiliaze the memory of 2D array that will be filled with antonym words */
    ant_head->ant_word = (char**)calloc(1,8);
    ant_head->ant_word[0] = (char*)calloc(1,sizeof(char));

    /* Read anthonyms until '\n' char read */
    while(1)
    {
        fscanf(file,"%c",&readc);
        if(readc=='\n')
        {
            reallocate3_ant(ant_head, letter_ct, word_ct);
            ant_head->ant_word[word_ct][letter_ct] = '\0';

        	ant_head->word_num++;
            break;
        }
        else if(readc==' ')
        {
        	reallocate3_ant(ant_head, letter_ct, word_ct);
            ant_head->ant_word[word_ct][letter_ct] = '\0';

        	ant_head->word_num++;
        	word_ct++;
            reallocate_ant(ant_head);
            ant_head->ant_word[word_ct] = (char*)calloc(1,sizeof(char));
            letter_ct = 0;
        }
        else if((readc>=65 && readc<=122) || readc=='-')
        {
            reallocate3_ant(ant_head, letter_ct, word_ct);
            ant_head->ant_word[word_ct][letter_ct] = readc;
            letter_ct++;
        }
    }

    return ant_head;
}

ant_list *fill_Ant_list(ant_list *ant_head, FILE *file)
{
/* This function reads the rest of the antonym text, adds the read words-synonyms the tail of linked list */
    char read[35]; /* Read word */
    char readc; /* Read character */
    char garbage; /* garbage */

    int word_ct = 0; /* Indicates which synonym we read in a line */
    int letter_ct = 0; /* Indicates which letter than belongs a word we read */

    /* Creating second node */
    ant_list *iter;
    iter=ant_head;
    iter->next = (ant_list*)malloc(sizeof(ant_list));
    iter=iter->next;
    iter->next = NULL;
    iter->word_num = 0;
    /* Inilitiaze the memory of second node's 2D array that will be filled with synonym words */
    iter->ant_word = (char**)calloc(1,8);
    iter->ant_word[0] = (char*)calloc(1,sizeof(char));
    
    /* Read and write word */
    fscanf(file,"%s",read);
    iter->word = (char*)calloc(strlen(read)+1,sizeof(char));
    strcpy(iter->word,read);

    /* Read '< >' characters and no need character (white-space) */
    fscanf(file,"%s",read);
    fscanf(file,"%c",&readc);

    /* Read anthonyms until reach the End of FILE */
    while(1)
    {
        fscanf(file,"%c",&readc);

        if (feof(file))
        {
        	/*iter->word_num++;*/ /* KEEP IT IN COMMENT LINES */
        	iter->next = NULL;
            break;
        }

        if(readc=='\n')
        {
            /* If we reach the new line, we have to create new node because we are reading new synonyms of a word */
            /* Creating new node and required memory of that node */
            reallocate3_ant(iter, letter_ct, word_ct);
            iter->ant_word[word_ct][letter_ct] = '\0';
        	iter->word_num++;
            iter->next = (ant_list*)malloc(sizeof(ant_list));
            iter=iter->next;
            iter->word_num = 0;
            /*iter->ant_word = (char**)calloc(1,8);
            iter->ant_word[0] = (char*)calloc(1,sizeof(char));*/
            iter->next = NULL;

            /* Read and write word */
            fscanf(file,"%s",read);
            iter->word = (char*)calloc(strlen(read)+1,sizeof(char));
            strcpy(iter->word,read);

            /* Read '< >' characters */
            fscanf(file,"%s",read);
            fscanf(file,"%c",&readc);

            /* Inilitiaze the memory of new node's 2D array that will be filled with synonym words */
            iter->ant_word = (char**)calloc(1,8);
            iter->ant_word[0] = (char*)calloc(1,sizeof(char));

            /* Reset the counters */
            word_ct= 0;
            letter_ct = 0;

        }

        else if(readc==' ')
        {
        	reallocate3_ant(iter, letter_ct, word_ct);
            iter->ant_word[word_ct][letter_ct] = '\0';

        	iter->word_num++;
        	word_ct++;
            reallocate_ant(iter);
            
            iter->ant_word[word_ct] = (char*)calloc(1,sizeof(char));
            letter_ct = 0;
        }
        else if((readc>=65 && readc<=122) || readc=='-')
        {
            reallocate3_ant(iter, letter_ct, word_ct);
            iter->ant_word[word_ct][letter_ct] = readc;
            letter_ct++;
        }
    }

    return ant_head;
}

ant_list *create_ant_list(char *ant_text)
{
    
    FILE *file;
    ant_list *ant_head = NULL;
    ant_list *ant_iter = NULL;

    file=fopen(ant_text,"r");
    if(ant_head==NULL)
        ant_head = initialize_Ant_list(ant_head,file);

    ant_head = fill_Ant_list(ant_head, file);
   /*deleteLastNode_ant(ant_head);*/
    return ant_head;

    fclose(file);
}

syn_list *create_syn_list(char *syn_text)
{
    FILE *file;
    syn_list *syn_head = NULL;
    syn_list *syn_iter = NULL;

    file=fopen(syn_text,"r");
    if(syn_head==NULL)
        syn_head = initialize_Syn_list(syn_head,file);

    syn_head = fill_Syn_list(syn_head, file);
    /*deleteLastNode_syn(syn_head);*/
    return syn_head;

    fclose(file);
}

/* ---------------------------------------------- READING FILES AND CREATING LINKED LIST PROCESSES ENDS HERE. ---------------------------------------------- */

/*void deleteLastNode_ant(ant_list *head)
{
	while(head->next->next != NULL)
		head = head->next;

	free(head->next);
	head->next = NULL;
}

void deleteLastNode_syn(syn_list *head)
{
	while(head->next->next != NULL)
		head = head->next;

	free(head->next);
	head->next = NULL;
}*/

ant_list *search_ant(ant_list *head, char *word)
{
/* This function searches the node that includes 'word' string that is passed as parameter. If the node is found, return that node. Else, create new node and return new node */
	while(head->next!=NULL)
	{
		if(strcmp(head->word, word)==0)
			return head;
		head = head->next;
	}

	if(strcmp(head->word, word)==0)
			return head;
	else
	{
		head->next = (ant_list*)malloc(sizeof(ant_list));
	    head->next->ant_word = (char**)calloc(1,8);
	    head->next->ant_word[0] = (char*)calloc(1,sizeof(char));
	    head->next->word_num = 0;
	    head->next->next = NULL;
	    return head->next;
	}
}

syn_list *search_syn(syn_list *head, char *word)
{
/* This function searches the node that includes 'word' string that is passed as parameter. If the node is found, return that node. Else, create new node and return new node */

	while(head->next!=NULL)
	{
		if(strcmp(head->word, word)==0)
			return head;
		head = head->next;
	}

	if(strcmp(head->word, word)==0)
			return head;
	else
	{
		head->next = (syn_list*)malloc(sizeof(syn_list));
	    head->next->syn_word = (char**)calloc(1,8);
	    head->next->syn_word[0] = (char*)calloc(1,sizeof(char));
	    head->next->word_num = 0;
	    head->next->next = NULL;
	    return head->next;
	}
}

void update_ant_text(char *ant_text, ant_list *head_ant, char *word, char*userant)
{
/* This function updates the antonym text */

	int i;
	int flag = 1;
	FILE *file;
	file=fopen(ant_text,"r+");

	while(!feof(file) && flag==1)
	{
		char read[35];
		char garbage[3];
		fscanf(file,"%s",read);
		fscanf(file,"%s",garbage);

		if(strcmp(read,word)==0)
		{
			for(i=0;i<head_ant->word_num-1;i++)
				fscanf(file,"%s",read);

			fprintf(file," %s\n",userant);
			flag=-1;
		}

		else
			for(i=0;i<head_ant->word_num;i++)
				fscanf(file,"%s",read);

		head_ant = head_ant->next;
	}
	
	while(head_ant!=NULL && head_ant->word_num!=0)
	{
		fprintf(file,"%s %s",head_ant->word,"<> ");
		for(i=0;i<head_ant->word_num;i++)
		{
			if(head_ant->next==NULL && i==head_ant->word_num-1)
				fprintf(file,"%s",head_ant->ant_word[i]);

			else if(head_ant->next!=NULL && i==head_ant->word_num-1)
				fprintf(file,"%s\n",head_ant->ant_word[i]);

			else
				fprintf(file,"%s ",head_ant->ant_word[i]);

		}

		head_ant = head_ant->next;
	}
	fclose(file);
}

void update_syn_text(char *syn_text, syn_list *syn_head, char *word, char*usersyn)
{
/* This function updates the synonym text */

	int i;
	int flag = 1;
	FILE *file;
	file=fopen(syn_text,"r+");

	while(!feof(file) && flag==1)
	{
		char read[35];
		char garbage[3];
		fscanf(file,"%s",read);
		fscanf(file," %s ",garbage);

		if(strcmp(read,word)==0)
		{
			for(i=0;i<syn_head->word_num-1;i++)
				fscanf(file,"%s",read);

			fprintf(file," %s\n",usersyn);
			flag=-1;
		}
		else
			for(i=0;i<syn_head->word_num;i++)
				fscanf(file,"%s",read);
			

		syn_head = syn_head->next;
	}
	
	while(syn_head!=NULL && syn_head->word_num!=0)
	{
		fprintf(file,"%s %s",syn_head->word,"= ");
		for(i=0;i<syn_head->word_num;i++)
		{
			if(syn_head->next==NULL && i==syn_head->word_num-1)
				fprintf(file,"%s",syn_head->syn_word[i]);

			else if(syn_head->next!=NULL && i==syn_head->word_num-1)
				fprintf(file,"%s\n",syn_head->syn_word[i]);

			else
				fprintf(file,"%s ",syn_head->syn_word[i]);

		}

		syn_head = syn_head->next;
	}
	fclose(file);
}

/* */

ant_list *random_node_ant(ant_list *head, int random)
{
/* This function finds and returns the N'th node of the antonym linked list. (N is a random number that is generated randomly) [ N = 'random' as parameter] */
	
    int i = 0;
	while(1)
	{
		if(i==random)
			break;
		head = head->next;
		i++;
	}
	return head;
}

syn_list *random_node_syn(syn_list *head, int random)
{
/* This function finds and returns the N'th node of the synonym linked list. (N is a random number that is generated randomly) [ N = 'random' as parameter] */

	int i = 0;
	while(1)
	{
		if(i==random)
			break;
		head = head->next;
		i++;
	}
	return head;
}

/* */

int check_ant(ant_list *node, char *answer)
{
/* This function checks whether the string 'answer' that is passed as parameter is in a node in the antonym linked list */

	int i;
	for(i=0;i<node->word_num;i++)
	{
		if(strcmp(node->word, answer)==0)
			return 1;
	}
	return 0;
}

int check_syn(syn_list *node, char *answer)
{
/* This function checks whether the string 'answer' that is passed as parameter is in a node in the synonym linked list */

	int i;
	for(i=0;i<node->word_num;i++)
	{
		if(strcmp(node->word, answer)==0)
			return 1;
	}
	return 0;
}

/* ------------------------------------------- */
int antline_calculator(ant_list *head)
{
/* This function counts the nodes in the linked list */
    int ct = 0;
    while(head!=NULL)
    {
        if(head->word_num!=0) ct++;
        head = head->next;
    }
    return ct;
}

int synline_calculator(syn_list *head)
{
/* This function counts the nodes in the linked list */

    int ct = 0;
    while(head!=NULL)
    {
        if(head->word_num!=0) ct++;
        head = head->next;
    }
    return ct;
}

void initialize_prob(probability *arr, int ct)
{
/* This function initilize the struct array that indicates probabilities */ 
    int i;
    for(i=0;i<ct;i++)
    {
        arr[i].index = i;
        arr[i].ct = 1;
    }

}

int find_index_ant(ant_list *head, char *word)
{
/* This function finds out and returns what order the 'word' is */
    int ct = 0;
    while(head!=NULL)
    {
        if(strncmp(word,head->word,strlen(head->word))==0)
            return ct;
        else
        {
            head = head->next;
            ct++;
        }
    }
    return -1;
}

int find_index_syn(syn_list *head, char *word)
{
/* This function finds out and returns what order the 'word' is */

    int ct = 0;
    while(head!=NULL)
    {
        if(strncmp(word,head->word,strlen(head->word))==0)
            return ct;
        else
        {
            head = head->next;
            ct++;
        }
    }
    return -1;
}

probability *reallocate_arr(probability *arr, int ct)
{
/* This function reallocates the struct array without using realloc() function */
    int i;
    probability *new = (probability*)calloc(ct+1,sizeof(char));

    for(i=0;i<ct;i++)
        new[i] = arr[i];

    free(arr);
    return new; 
}

int random_func(probability *arr, int ct)
{
/* This function generates a random number that indicates which node we will ask to user */
    while(1)
    {
        int rand_num = rand()%((ct));

        if(arr[rand_num].ct==1)
            return arr[rand_num].index;
        else
        {
            int rand_num2 = rand()%((arr[rand_num].ct)-1) + 1;
            if(rand_num2==arr[rand_num].ct)
                return arr[rand_num].index;
            else
                continue;
        }
    }
}


void menu(char *ant_text,char *syn_text, ant_list *head_ant, syn_list *head_syn)
{
	ant_list *iter_ant = head_ant;
	syn_list *iter_syn = head_syn;

    /* --------------------- Creates a new binary file or read the binary file that already existed, edit the probabilites according to binary file-------------------- */
    FILE *file;
	char bin[5] = ".dat";
	char username[30];
    /* Count the entries in the linked lists */
    int antline_num = antline_calculator(head_ant);
    int synline_num = synline_calculator(head_syn);
    
    /* Intiliaze the struct arrays */
    probability *prob_syn = (probability*)calloc(synline_num,sizeof(probability));
    probability *prob_ant = (probability*)calloc(antline_num,sizeof(probability));

    printf("Enter your username: ");
    scanf("%s",username);
    strcat(username,bin);

    initialize_prob(prob_ant, antline_num);
    initialize_prob(prob_syn, synline_num);
    
        /* --------------------- Creates a new binary file or read the binary file that already existed, edit the probabilites according to binary file-------------------- */

        /* --------------------------------------------------------------------- GO ON ------------------------------------------------------------------------------ */

	

    while(1)
    {
        int choice;
        srand(time(NULL));

        /* EDIT THE PROBABILITIES */
        file = fopen(username,"a+b");
        while(!feof(file))
        {
            char type;
            char correct;
            char read_word[35];

            int index;

            fread(&type,sizeof(char),1,file);
            if(feof(file)) break;
            fread(&correct,sizeof(char),1,file);
            fread(read_word, 35, 1, file);

            /*printf("%c %c %s\n",type,correct,read_word);*/

            if(type=='a') 
            {
                index = find_index_ant(head_ant,read_word);
                prob_ant[index].ct++;

                if(correct==0)
                {
                   prob_ant = reallocate_arr(prob_ant,antline_num);
                   prob_ant[antline_num] = prob_ant[index];
                   antline_num++;
                }

                else if(correct==0 || correct==1)
                {
                   int index_syn = find_index_syn(head_syn, read_word);
                   if(index_syn!=-1)
                   {
                        prob_syn = reallocate_arr(prob_syn,synline_num);
                        prob_syn[synline_num] = prob_syn[index_syn];
                        synline_num++;
                      
                   }
                }    
            }

            if(type=='s')
            {
                index = find_index_syn(head_syn,read_word);
                prob_syn[index].ct++;

                if(correct==0)
                {
                   prob_syn = reallocate_arr(prob_syn,synline_num);
                   prob_syn[synline_num] = prob_syn[index];
                   synline_num++;
                }

               if(correct==0 || correct==1)
               {
                   int index_ant = find_index_ant(head_ant, read_word);
                   if(index_ant!=-1)
                   {
                        prob_ant= reallocate_arr(prob_ant,antline_num);
                        prob_ant[antline_num] = prob_ant[index_ant];
                        antline_num++;
                      
                   }
               }
               
            }
        }
        fclose(file);
        /* EDITING THE PROBABILITIES IS DONE */

        file=fopen(username,"a+b");
        printf("1. Add new entry\n2. GO ON\n3. EXIT");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: /* 'Add new entry' choice */
            {
                int choice2;
                char word[35];
                ant_list *add_nodeA;
                syn_list *add_nodeS;

                printf("Which list do you want to add an entry? (1: Antonym 2: Synonym): ");
                scanf("%d",&choice2);
                printf("Enter the word: ");
                scanf("%s",word);

                if(choice2==1) /* Synonym choice */
                {
                    add_nodeA = search_ant(head_ant,word); /* Find the node that includes word user entered */

                    while(1)
                    {
                        ant_list *np;
                        char userant[35];
                        int word_num = add_nodeA->word_num;
                        printf("Enter antonyms of %s (Enter STOP for exit): ",word);
                        scanf("%s",userant);
                        if(strcmp(userant,"STOP")==0) break;

                        reallocate_copy_ant(add_nodeA,userant); /* Reallocate the string array of node, then copy the new entry in it */
                        add_nodeA->word_num = (add_nodeA->word_num)+1; /* Increase the number counter of node */
                        update_ant_text(ant_text, head_ant, word, userant); /* Update the text */
                    }
                }

                else if(choice2==2) /* Antonym word */
                {
                    add_nodeS = search_syn(head_syn,word); /* Find the node that includes word user entered */

                    while(1)
                    {
                        syn_list *np;

                        char usersyn[35];
                        int word_num = add_nodeS->word_num;
                        printf("Enter synonyms of %s (Enter STOP for exit): ",word);
                        scanf("%s",usersyn);
                        if(strcmp(usersyn,"STOP")==0) break;

                        reallocate_copy_syn(add_nodeS,usersyn); /* Reallocate the string array of node, then copy the new entry in it */
                        add_nodeS->word_num = (add_nodeS->word_num)+1; /* Increase the number counter of node */
                        update_syn_text(syn_text, head_syn, word, usersyn); /* Update the text */
                    }
                }
                fclose(file);
                break;
            }

            case 2: /* 'GO ON' choice */
            {
                int random_word_type = ((rand() %  (((2) + 1) - (1))) + (1)); /* Generate random number ( 1 or 2), 1:Antonym, 2:Synonym */

                if(random_word_type==1) /* If random word will be anotnym word */
                {
                    int random_word = random_func(prob_ant, antline_num); /* Generate a random number according to rules in the PDF */ 
                    char answer[35];
                    ant_list *node;
                    node = random_node_ant(head_ant, random_word); /* Find the node in the RANDOM'th order */

                    printf("What is the antonym of %s?: ",node->word);
                    scanf("%s",answer);

                    if(check_ant(node,answer)==1) /* If the answer is true, update the binary file and inform the user */
                    {
                        char case1 = 'a';
                        char correctness = '1';
                        fwrite(&case1,sizeof(char),1,file);
                        fwrite(&correctness,sizeof(char),1,file);
                        fwrite(node->word,35,1,file);
                        printf("Your answer is correct!\n");
                    }
                    else /* If the answer is false, update the binary file and inform the user */
                    {
                        int yesno;
                        char case1 = 'a';
                        char correctness = '0';
                        fwrite(&case1,sizeof(char),1,file);
                        fwrite(&correctness,sizeof(char),1,file);
                        fwrite(node->word,35,1,file);
                       
                        printf("Your answer is wrong! Do you want to add your word %s as a valid antonym?(1:Yes, 2:No): ",answer);
                        scanf("%d",&yesno);
                        
                        if(yesno==1) /* If user wants to add the word to anyonym list */
                        {
                            reallocate_copy_ant(node,answer); /* Reallocate and copy the new word */
                            node->word_num = (node->word_num)+1;/* Increase the anyonym word number of node */
                            update_ant_text(ant_text, head_ant , node->word, answer); /* Update the text */
                        }
                            
                        else;
                    }
                    fclose(file);
                }

                else if(random_word_type==2) /* If random word will be synonnym word */
                {
                    int random_word = random_func(prob_syn, synline_num); /* Generate a random number according to rules in the PDF */
                    char answer[35];
                    syn_list *node;
                    node = random_node_syn(head_syn, random_word); /* Find the node in the RANDOM'th order */
                    printf("What is the synonym of %s?: ",node->word);
                    scanf("%s",answer);
                    if(check_syn(node,answer)==1) /* If the answer is true, update the binary file and inform the user */
                    {
                        char case1 = 's';
                        char correctness = '1';
                        fwrite(&case1,sizeof(char),1,file);
                        fwrite(&correctness,sizeof(char),1,file);
                        fwrite(node->word,35,1,file);
                        printf("Your answer is correct!\n");
                    }
                    else /* If the answer is false, update the binary file and inform the user */
                    {
                        int yesno;
                        char case1 = 's';
                        char correctness = '0';
                        fwrite(&case1,sizeof(char),1,file);
                        fwrite(&correctness,sizeof(char),1,file);
                        fwrite(node->word,35,1,file);
                      
                        printf("Your answer is wrong! Do you want to add your word %s as a valid synonym?(1:Yes, 2:No): ",answer);
                        scanf("%d",&yesno);
                        
                        if(yesno==1) /* If user wants to add the word to synonym list */
                        {
                            reallocate_copy_syn(node,answer); /* Reallocate and copy the new word */
                            node->word_num = (node->word_num)+1; /* Increase the synonym word number of node */
                            update_syn_text(syn_text, head_syn , node->word, answer); /* Update the text */
                        }
                        else;            
                    }
                    fclose(file);
                }
                break;
            }

            case 3:
            {
                printf("Bye.\n");
                fclose(file);
                return;
            }
        }
    }
}

	
int main()
{
    char *syn_text = "synonyms.txt";
    char *ant_text = "antonyms.txt";
    int i;
    syn_list *synonyms = NULL;  /* Linked list that keeps word-synonym matches */
    ant_list *antonyms = NULL;  /* Linked list that keeps word-antonym matches */

    antonyms = create_ant_list(ant_text);
    synonyms = create_syn_list(syn_text);
    
    menu(ant_text,syn_text,antonyms,synonyms);
}


