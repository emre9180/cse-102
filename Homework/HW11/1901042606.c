/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* NOTE for T.A. -> Movie_Budget linked list is filled descending order according to year-budget.You can test it by removing comment lines between 1404-1413. lines of code */


typedef struct Movie_budget
{
    double budget;
    int year;
    char *name;
    struct Movie_budget *next;
}Movie_Budget;

typedef struct Movie_name
{
    double score;
    char *genre;
    char *name;
    struct Movie_name *next;
}Movie_Name;

char *read_string_dynamically(FILE *file)
{
/* This function reads strings character by character and assigns it to a char array that is dynamically increasing. Stops the reading until EOF or ',' character */
    int i; /* Loop */
    int ct = 0; /* Indicates that how many characters we read */
    char read; /* Read char */

    char *string1 = NULL;
    char *string2 = NULL;

    while(1)
    {

        fscanf(file,"%c",&read);
        if(read==',' || read=='\n')
            break;

        if(feof(file))
            break;

        ct++;

        string1 = (char*)calloc(ct,sizeof(char));

        for(i=0;i<ct-1;i++)
            string1[i]=string2[i];

        string1[ct-1] = read;

        if(string2!=NULL) free(string2);
        string2=string1;
    }

    /* Adding the '\0' character to array's end */
    ct++;
    string1 = (char*)calloc(ct,sizeof(char));
    for(i=0;i<ct-1;i++)
        string1[i]=string2[i];

    string1[ct-1] = '\0';
    /* ---------------------------------------- */

    if(string2!=NULL) free(string2);
    string2=string1;

    return string2;
}

Movie_Name *add_movieName(Movie_Name *head_name,char *name)
{
	/* This function adds or updates new movie entry in the linked list */

    Movie_Name *copy_head = head_name; /* head node of head name linked list */
    char *genre; /* genre that will be read from file. */
    char garbage; /* garbage */

    /* check that whether there is a movie that matches the '*name' parameter until the last node. if there is a match, return that node */
    while(copy_head->next!=NULL)
    {
        if(strcmp(copy_head->name,name)==0)
            return copy_head;

        copy_head = copy_head->next;
    }

    /* check the last node, if it does not match; allocate and return new node in the tail of linked list. if it match, return that node. */
    if(strcmp(copy_head->name,name)==0)
        return copy_head;

    else
    {
        /* memory allocation for the new entry */
        copy_head->next = (Movie_Name*)malloc(sizeof(Movie_Name));
        copy_head->next->next = NULL;
        copy_head->next->genre = NULL;
        copy_head->next->name = NULL;
        return copy_head->next;
    }
}

Movie_Budget *check_movieBudget(Movie_Budget *head_budget,char *name)
{
	/* This function checks whether read movie is in the budget linked list. If it is in the list, returns that node */

    Movie_Budget *copy_head = head_budget; /* head node of head name linked list */
    char *genre; /* genre that will be read from file. */
    char garbage; /* garbage */

    /* check that whether there is a movie that matches the '*name' parameter until the last node. if there is a match, return that node */
    while(copy_head->next!=NULL)
    {
        if(strcmp(copy_head->name,name)==0)
            return copy_head;

        copy_head = copy_head->next;
    }

    /* check the last node, if it does not match. Return NULL */
    if(strcmp(copy_head->name,name)==0)
        return copy_head;

    return NULL;

}

/* --------------------------------------------------------------------------------------------------------------------------- */

int sort_print_budget(Movie_Budget *head_budget, int upper, int lower, int op)
{
/* This function sorts and prints. */

    int i,k=0; /* Loop */
    Movie_Budget *iter_budget = head_budget;
    Movie_Budget *iter_budget2 = head_budget;

    double temp;
    char *temp_name;

    double min_number; /* Will be used for sorting */
    Movie_Budget *min_index; /* Will be used for sorting */

    int unknown_ct = 0; /* Number of unknown movies */

    /* Sort the linked list */
    while(iter_budget->next->next!=NULL)
    {
        min_number = iter_budget->budget;
        min_index = iter_budget;

        iter_budget2 = iter_budget->next;
        while(iter_budget2->next!=NULL)
        {
            if (iter_budget2->budget<min_number)
            {
                min_number =iter_budget2->budget;
                min_index = iter_budget2;
            }
            iter_budget2 = iter_budget2->next;
        }

        temp = iter_budget->budget;
        temp_name = iter_budget->name;

        iter_budget->budget = min_index->budget;
        min_index->budget = temp;

        iter_budget->name = min_index->name;
        min_index->name = temp_name;

        iter_budget = iter_budget->next;
    }


    iter_budget = head_budget;
    /* Count the unknown budget movies, and arrange the upper-lower bounds */
    while(1)
    {
        if(iter_budget==NULL)
            break;
        if(iter_budget->budget==-1)
            unknown_ct++;
        else
            break;
        iter_budget = iter_budget->next;
    }
    
    /* Printing structs in desired range by user */
    iter_budget = head_budget;

    if(op==1) /* Fetch single movie */
    {
    	int ct = 1;
    	/* Count the unknown budget movies, and arrange the upper-lower bounds */
    	upper += unknown_ct;
  		lower += unknown_ct;
    	while(iter_budget!=NULL)
    	{	
    		if(ct==lower && iter_budget->budget!=-1)
    		{
    			printf("%-50s,%-10f\n",iter_budget->name,iter_budget->budget);
    			break;
    		}
    		iter_budget = iter_budget->next;
    		ct++;
    	}
 
    	if(iter_budget==NULL) return -1;  /*If there is no record as user wants */
    }

    else /* Fetch multiple movies between a range */
    {
    	int ct = 0;
    	while(1)
	    {
	    	double num;
	        if(iter_budget==NULL)
	            break;
	        num = iter_budget->budget;
	        if(num>=lower && num<=upper)
	        {
	            printf("%-50s,%-10f\n",iter_budget->name,iter_budget->budget);
	            ct++;
	        }
	        iter_budget = iter_budget->next;
	    }

	    if(ct==0) return -1; /* If there is no record as user wants */
    }

    printf("\n");
    return 1;

}

int sort_print_genres(Movie_Name *head_name, int upper, int lower)
{
/* This function, creates a copy of movies array, then sorts that array according to budgets */
    int ct = 0; /* indicates which movie we are checking */
    int print_num = 0; /* indicates how many movies we printed */
    int i,k=0; /* Loop */
    Movie_Name *iter_name = head_name;
    Movie_Name *iter_name2 = head_name;

    double temp;
    char *temp_genre;
    char *temp_name;
    double temp_score;

    char *min_genre; /* Will be used for sorting */
    Movie_Name *min_index; /* Will be used for sorting */

    int unknown_ct = 0; /* Number of unknown movies */

    while(iter_name->next->next!=NULL)
    {
        min_genre = (char*)calloc(strlen(iter_name->genre)+1,sizeof(char));
        strcpy(min_genre,iter_name->genre);
        min_index = iter_name;

        iter_name2 = iter_name->next;
        while(iter_name2->next!=NULL)
        {
            if (strcmp(iter_name2->genre,min_genre)<0)
            {
                free(min_genre);
                min_genre = (char*)calloc(strlen(iter_name2->genre)+1,sizeof(char));
                strcpy(min_genre,iter_name2->genre);
                min_index = iter_name2;
            }
            iter_name2 = iter_name2->next;
        }

        temp_genre = iter_name->genre;
        temp_name = iter_name->name;
        temp_score = iter_name->score;

        iter_name->genre = min_index->genre;
        min_index->genre = temp_genre;

        iter_name->name = min_index->name;
        min_index->name = temp_name;

        iter_name->score = min_index->score;
        min_index->score = temp_score;

        iter_name = iter_name->next;
        free(min_genre);
    }


    iter_name = head_name;

    ct = 0;
    /* Printing structs in desired range by user */
    iter_name = head_name;
    while(1)
    {
        if(iter_name==NULL)
            break;
        if(ct>=lower && ct<=upper)
        {
            printf("%-30s,%-50s%f\n",iter_name->genre,iter_name->name,iter_name->score);
            print_num++;
        }
        iter_name = iter_name->next;
        ct++;
    }

    if(print_num==0) return -1; /* if there is no movie in range as user wanted */
   	else return 1;
}

int sort_print_names(Movie_Name *head_name, double upper, double lower)
{
/* This function, creates a copy of movies array, then sorts that array according to budgets */
    int ct = 0; /* indicates which movie we are checking */
    int print_num = 0; /* number of printed movies */
    int i,k=0; /* Loop */
    Movie_Name *iter_name = head_name;
    Movie_Name *iter_name2 = head_name;

    double temp;
    char *temp_name;
    char *temp_genre;
    double temp_score;

    char *min_name; /* Will be used for sorting */
    Movie_Name *min_index; /* Will be used for sorting */


    while(iter_name->next->next!=NULL)
    {
        min_name = (char*)calloc(strlen(iter_name->name)+1,sizeof(char));
        strcpy(min_name,iter_name->name);
        min_index = iter_name;

        iter_name2 = iter_name->next;
        while(iter_name2->next!=NULL)
        {
            if (strcmp(iter_name2->name,min_name)<0)
            {
                free(min_name);
                min_name = (char*)calloc(strlen(iter_name2->name)+1,sizeof(char));
                strcpy(min_name,iter_name2->name);
                min_index = iter_name2;
            }
            iter_name2 = iter_name2->next;
        }

        temp_name = iter_name->name;
        temp_genre = iter_name->genre;
        temp_score = iter_name->score;

        iter_name->name = min_index->name;
        min_index->name = temp_name;

        iter_name->genre = min_index->genre;
        min_index->genre = temp_genre;

        iter_name->score = min_index->score;
        min_index->score = temp_score;

        iter_name = iter_name->next;
        free(min_name);
    }

    /* Printing structs in desired range by user */
    iter_name = head_name;
    while(1)
    {
        if(iter_name==NULL)
            break;
        if(ct>=lower && ct<=upper)
        {
            printf("%-30s,%-50s%f\n",iter_name->genre,iter_name->name,iter_name->score);
            print_num++;
        }
        
        iter_name = iter_name->next;
        ct++;
    }

    if(print_num!=0) return 1;
    else return -1; /* if there is no movie in range as user wanted */

}

int sort_print_score(Movie_Name *head_name, double upper, double lower, int op)
{
/* This function, creates a copy of movies array, then sorts that array according to budgets */
    int i,k=0; /* Loop */
    Movie_Name *iter_name = head_name;
    Movie_Name *iter_name2 = head_name;

    double temp;
    char *temp_genre;
    char *temp_name;
    double temp_score;

    double min_score; /* Will be used for sorting */
    Movie_Name *min_index; /* Will be used for sorting */

    while(iter_name->next->next!=NULL)
    {
        min_score = iter_name->score;
        min_index = iter_name;

        iter_name2 = iter_name->next;
        while(iter_name2->next!=NULL)
        {
            if (iter_name2->score<min_score)
            {
                min_score = iter_name2->score;
                min_index = iter_name2;
            }
            iter_name2 = iter_name2->next;
        }

        temp_genre = iter_name->genre;
        temp_name = iter_name->name;
        temp_score = iter_name->score;

        iter_name->genre = min_index->genre;
        min_index->genre = temp_genre;

        iter_name->name = min_index->name;
        min_index->name = temp_name;

        iter_name->score = min_index->score;
        min_index->score = temp_score;

        iter_name = iter_name->next;
    }

    /* Printing structs in desired range by user */
    iter_name = head_name;

    if(op==2)
    {
    	int ct = 0; /* indicates how many movies we printed */
    	while(1)
	    {
	        if(iter_name==NULL)
	            break;
	        if(iter_name->score>=lower && iter_name->score<=upper)
	        {
	            printf("%-30s,%-50s%f\n",iter_name->genre,iter_name->name,iter_name->score);
	            ct++;
	        }
	        iter_name = iter_name->next;
	    }
	    if(ct==0) return -1; /*If there is no record as user wants */
   		else return 1;
    }

    else
    {
		int ct = 1;
    	while(iter_name!=NULL)
    	{	
    		if(ct==lower)
    		{
    			printf("%-30s,%-50s%f\n",iter_name->genre,iter_name->name,iter_name->score);
    			break;
    		}
    		iter_name = iter_name->next;
    		ct++;
    	}
 
    	if(iter_name==NULL) return -1;  /*If there is no record as user wants */
    	else return 1;
    
    }
}

int sort_print_year(Movie_Budget *head_budget, int upper, int lower, int op)
{
/* This function, creates a copy of movies array, then sorts that array according to budgets */
    int ct = 0;
    int i,k=0; /* Loop */
    Movie_Budget *iter_budget = head_budget;
    Movie_Budget *iter_budget2 = head_budget;

    double temp;
    char *temp_name;

    double min_year; /* Will be used for sorting */
    Movie_Budget *min_index; /* Will be used for sorting */

    int unknown_ct = 0; /* Number of unknown movies */

    while(iter_budget->next->next!=NULL)
    {
        min_year = iter_budget->year;
        min_index = iter_budget;

        iter_budget2 = iter_budget->next;
        while(iter_budget2->next!=NULL)
        {
            if (iter_budget2->year<min_year)
            {
                min_year =iter_budget2->year;
                min_index = iter_budget2;
            }
            iter_budget2 = iter_budget2->next;
        }

        temp = iter_budget->year;
        temp_name = iter_budget->name;

        iter_budget->year = min_index->year;
        min_index->year = temp;

        iter_budget->name = min_index->name;
        min_index->name = temp_name;

        iter_budget = iter_budget->next;
    }

    /* Printing structs in desired range by user */
    iter_budget = head_budget;
    if(op==2)
    {
    	int ct = 0; /* indicates how many movies we printed */
    	while(1)
	    {
	        if(iter_budget==NULL)
	            break;
	        if(iter_budget->year>=lower && iter_budget->year<=upper)
	        {
	            printf("%-50s%d\n",iter_budget->name,iter_budget->year);
	            ct++;
	        }
	        iter_budget = iter_budget->next;
	    }
	    if(ct==0) return -1; /*If there is no record as user wants */
   		else return 1;
    }

    else
    {
		int ct = 1;
    	while(iter_budget!=NULL)
    	{	
    		if(ct==lower)
    		{
    			printf("%-50s%d\n",iter_budget->name,iter_budget->year);
    			break;
    		}
    		iter_budget = iter_budget->next;
    		ct++;
    	}
 
    	if(iter_budget==NULL) return -1;  /*If there is no record as user wants */
    	else return 1;
    
    }
}


void listof_sorted_data(Movie_Budget *head_budget, Movie_Name *head_name, int movies_ct)
{
/* This function does the operation in the first selection of menu */

    int sort; /* Sort choice of user */
    int op; /* Operation choice of user, single or multiple */
    double lower; /* Lower limit of range */
    double upper = -1; /* Upper limit of range */

    printf("1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n\nPlease select an operation: ");
    scanf("%d",&sort);
    if(sort<1 || sort>5) /* If choice of user is invalid, bring the menu again */
    {
        printf("PLEASE ENTER VALID OPERATION.\n\n");
        listof_sorted_data(head_budget, head_name,movies_ct);
        return;
    }

    printf("\n1. Single Selection\n2. Multiple Selection\n\nPlease select an operation: ");
    scanf("%d",&op);
    if(op<1 || op>2) /* If choice of user is invalid, bring the menu again */
    {
        printf("PLEASE ENTER VALID OPERATION.\n\n");
        listof_sorted_data(head_budget, head_name,  movies_ct);
        return;
    }


    if(op==1) /* Single selection */
    {
        printf("Enter value: ");
        scanf("%lf",&lower);
        upper = lower;
    }
    else if(op==2) /* Multiple selection */
    {
        printf("Enter start value: ");
        scanf("%lf",&lower);
        printf("Enter end value: ");
        scanf("%lf",&upper);
    }
    else /* If choice of user is invalid, bring the menu again */
    {
        printf("PLEASE ENTER VALID OPERATION.\n\n");
        listof_sorted_data(head_budget, head_name,movies_ct);
        return;
    }

    /* Calling the sorting-printing functions according to user selected areas */
    switch(sort)
    {
        case 1:
            if(op==1) /* Single selection */
                printf("\n%.0f. Movie\n\n",lower);
            else /* Multiple selection */
                printf("\nMovies between %.0f and %.0f sorted by budget\n\n",lower,upper);

            if((sort_print_budget(head_budget, upper ,lower,op))!=1) /* Sort and print. But firstly, we have to check range. */
            {
            	/* if there is no record as user wants, ask again */
            	printf("PLEASE ENTER VALID VALUES.\n\n");
		        listof_sorted_data(head_budget, head_name,movies_ct);
		        return;
            }

            printf("\n");
            break;

        case 2:
            if(op==1) /* Single selection */
                printf("\n%.0f. Movie\n\n",lower);
            else /* Multiple selection */
                printf("\nMovies between %.0f and %.0f sorted by genres:\n\n",lower,upper);

            if(sort_print_genres(head_name,upper ,lower)!=1) /* Sort and print */
            {
            	/* if there is no record as user wants, ask again */
            	printf("PLEASE ENTER VALID VALUES.\n\n");
		        listof_sorted_data(head_budget, head_name,movies_ct);
		        return;
            }

            printf("\n");
            break;

        case 3:
            if(op==1) /* Single selection */
                printf("\n%.0f. Movie\n\n",lower);
            else /* Multiple selection */
                printf("\nMovies between %.0f and %.0f sorted by names:\n\n",lower,upper);

            if(sort_print_names(head_name,upper ,lower)!=1)
            {
            	/* if there is no record as user wants, ask again */
            	printf("PLEASE ENTER VALID VALUES.\n\n");
		        listof_sorted_data(head_budget, head_name,movies_ct);
		        return;
            }

            printf("\n");
            break;

        case 4:
        	
        {
            if(op==1) /* Single selection */
                printf("\n%.0f. Movie\n\n",lower);
            else /* Multiple selection */
                printf("\nMovies between %.1f and %.1f sorted by scores:\n\n",lower,upper);

            if(sort_print_score(head_name,upper ,lower, op)!=1) /* Sort and print */
            {
            	/* if there is no record as user wants, ask again */
            	printf("PLEASE ENTER VALID VALUES.\n\n");
		        listof_sorted_data(head_budget, head_name,movies_ct);
		        return;
            }
            printf("\n");
            break;
        }
        	

        case 5:
            if(op==1) /* Single selection */
                printf("\n%.0f. Movie\n\n",lower);
            else /* Multiple selection */
                printf("\nMovies between %.0f and %.f sorted by years:\n\n",lower,upper);

            if(sort_print_year(head_budget,upper ,lower,op)!=1) /* Sort and print */
            {
            	/* if there is no record as user wants, ask again */
            	printf("PLEASE ENTER VALID VALUES.\n\n");
		        listof_sorted_data(head_budget, head_name,movies_ct);
		        return;
            }
            printf("\n");
            break;
    }

}

void frequence_genres(Movie_Name *head_name, char **genres, int genre_ct)
{
/* This function calculates the frequence of genres and prints it */
    Movie_Name *iter_name = head_name;

    int *frequence = (int*)calloc(genre_ct,sizeof(int)); /* Array that keeps frequence of genres */
    int i; /* Loop */

    /* Calculate the frequences */
    while(iter_name!=NULL)
    {
        for(i=0;i<genre_ct;i++)
        {
            if(strcmp(genres[i],iter_name->genre)==0)
                frequence[i]++;
        }
        iter_name = iter_name->next;
    }

    /* Print the frequences */
    for(i=0;i<genre_ct;i++)
    {
        printf("%-20s%d\n",genres[i],frequence[i]);
    }

    free(frequence);
    printf("\n");
}

void listof_genres(char **genres, int genre_ct)
{
/* This function prints the all genres */
    int i;

    for(i=0;i<genre_ct;i++)
    {
        printf("%s\n",genres[i]);
    }
    printf("\n");
}

int check_movieName(Movie_Name *head_name, char *name)
{
/* This function checks that the movie that has just read from file whether is read before. If it read before, return indice; if it is no read before, return -1 */
    Movie_Name *iter_name = head_name;
    int i;
    int check = -1;

    while(iter_name!=NULL)
    {
        if(strcmp(iter_name->name,name)==0)
        {
            check=i;
            break;
        }
        iter_name = iter_name->next;
    }

    return check;
}

void all_infos_single_movie(Movie_Name *head_name,Movie_Budget *head_budget)
{
/* This function gets a movie name as input from user, then it searchs the linked list to find a match, and print the matched movie information */
    Movie_Name *iter_name = head_name;
    Movie_Budget *iter_budget = head_budget;

    char *buf_name = (char*)calloc(200,sizeof(char)); /* Name input */
    char *name;
    int check; /* Indicates that there is a movie in the linked list as user entered or not */

    /* Getting input */
    printf("Please enter the name of the movie: ");
    scanf(" %[^\n]s",buf_name);
    name = (char*)calloc(strlen(buf_name+1),sizeof(char));
    strcpy(name,buf_name);
    free(buf_name);

    check = check_movieName(head_name, name); /* Check that the movie that user entered is in the movie linked list or not */

    if(check==-1) /* If the movie user entered is not in the linked list, ask again */
    {
        printf("Your movie is not in the list. Please enter a new name.\n\n");
        all_infos_single_movie(head_name, head_budget);
        return;
    }
    else /* If the movie user entered is in the linked list, print it */
    {
        while(strcmp(iter_name->name,name)!=0)
            iter_name = iter_name->next;

        while(strcmp(iter_budget->name,name)!=0)
            iter_budget = iter_budget->next;

        if(iter_budget->budget==-1)
            printf("Budget: Unknown\n");
        else
            printf("Budget: %f\n", iter_budget->budget);
        printf("Genre: %s\n", iter_name->genre);
        printf("Score: %f\n",iter_name->score);
        printf("Year: %d\n\n", iter_budget->year);
    }
    free(name);
}

void average(Movie_Name *head_name)
{
/* This function calculates the averages of scores and prints it */
    Movie_Name *iter_name = head_name;

    double sum = 0;
    int movies_ct = 0;

    while(iter_name!=NULL)
    {
        sum += iter_name->score;
        iter_name = iter_name->next;
        movies_ct++;
    }

    printf("Average: %f\n\n",sum/movies_ct);
}

void list_through_years(Movie_Budget *head_budget)
{
/* This function prints movies until or since a user selected year */

    int choice; /* Since-Until choice */
    int year; /* Year choice */
    int i,k=0; /* Loop */
    Movie_Budget *iter_budget = head_budget; /* Copy of head node */
    int find_ct = 0; /* Indicates that how many match is found */


    /* Getting inputs from user */
    printf("Enter a year: ");
    scanf("%d",&year);
    printf("Until(0) or Since(1) %d?: ",year);
    scanf("%d",&choice);
    if(choice<0 || choice>1) /* If input is invalid, ask again */
    {
        printf("Please enter a valid choice.\n\n");
        list_through_years(head_budget);
        return;
    }

    /* Printing results according to since or until choice */
    if(choice==0)
    {
        while(iter_budget!=NULL)
        {
            if(year>iter_budget->year)
            {
                printf("%-10d%s\n",iter_budget->year,iter_budget->name);
                find_ct++;
            }

            iter_budget = iter_budget->next;
        }
    }

    if(choice==1)
    {
        while(iter_budget!=NULL)
        {
            if(year<iter_budget->year)
            {
                printf("%-10d%s\n",iter_budget->year,iter_budget->name);
                find_ct++;
            }

            iter_budget = iter_budget->next;
        }
    }

    if(find_ct==0) /* If there is no match, ask a new year */
    {
        printf("\nTRY AGAIN!\n");
        list_through_years(head_budget);
        return;
    }

    printf("\n");
}

void list_through_scores(Movie_Name *head_name)
{
/* This function prints movies until or since a user selected year */

    int choice; /* Since-Until choice */
    double score; /* Year choice */
    int i,k=0; /* Loop */
    Movie_Name *iter_name = head_name; /* Copy of head node */
    int find_ct = 0; /* Indicates that how many match is found */


    /* Getting inputs from user */
    printf("Enter a score: ");
    scanf("%lf",&score);
    printf("Less(0) or Greater(1) %.1f?: ",score);
    scanf("%d",&choice);
    if(choice<0 || choice>1) /* If input is invalid, ask again */
    {
        printf("Please enter a valid choice.\n\n");
        list_through_scores(head_name);
        return;
    }

    /* Printing results according to since or until choice */
    if(choice==0)
    {
        while(iter_name!=NULL)
        {
            if(score>iter_name->score)
            {
                printf("%-10f%s\n",iter_name->score,iter_name->name);
                find_ct++;
            }

            iter_name = iter_name->next;
        }
    }

    if(choice==1)
    {
        while(iter_name!=NULL)
        {
            if(score<iter_name->score)
            {
                printf("%-10f%s\n",iter_name->score,iter_name->name);
                find_ct++;
            }

            iter_name = iter_name->next;
        }
    }

    if(find_ct==0) /* If there is no match, ask a new score */
    {
        printf("\nTRY AGAIN!\n");
        list_through_scores(head_name);
        return;
    }

    printf("\n");
}

void menu(Movie_Budget *head_budget, Movie_Name *head_name, int movies_ct, char**genres, int genres_ct)
{
/* This function is the main menu. */
    int choice = 0;

    do
    {
        printf("1. List of Sorted Data\n2. List of Genres\n3. List of the Movies Through the Years\n4. List of the Movies Through the Scores\n5. All Informations of a Single Movie\n6. Average of the IMDB Scores\n7. Frequence of the Genres\n8. EXIT");
        printf("\n\nPlease select an operation: ");
        scanf("%d",&choice);

        if(choice>8 || choice<0) /* If the selection of user is invalid, ask again */
        {
            printf("PLEASE ENTER A VALID CHOICE.\n\n");
            menu(head_budget,head_name, movies_ct,genres,genres_ct);
            return;
        }

        switch(choice)
        {
            case 1:
                listof_sorted_data(head_budget, head_name, movies_ct);
                break;

            case 2:
                listof_genres(genres, genres_ct);
                break;

            case 3:
                list_through_years(head_budget);
                break;

            case 4:
                list_through_scores(head_name);
                break;

            case 5:
                all_infos_single_movie(head_name,head_budget);
                break;

            case 6:
                average(head_name);
                break;

            case 7:
                frequence_genres(head_name, genres, genres_ct);
                break;

            case 8:
                printf("Bye.");
                break;

        }

    }while(choice!=8);
}

int check_genreName(char **genre, char*check ,int ct)
{
/* This function checks that the genre '*check' that has just read, is in the genre array that read before. If it read before, return the indice; if it is not, return -1 */

    int i; /* Loop */
    int flag = -1;

    if(genre==NULL)
        return flag;

    for(i=0;i<ct;i++)
    {
        if(strcmp(genre[i],check)==0)
        {
            flag = i;
            break;
        }
    }
    return flag;
}

char **copy_genres(char **genres,char *genre_read, int ct)
{
/* This function adds the genre that has just read to genres array that keeps all the genres. This function does this operation dynamically. */

    int length = strlen(genre_read);
    char **new_genres = (char**)calloc(ct+1,8); /* Declaration of new array. Genres array will be copied here and new genre will be added here. Then we return this array */
    int i;

    /* Copying genres array to new array */
    for(i=0;i<ct;i++)
        new_genres[i] = genres[i];

    /* Adding new entry to array */
    new_genres[ct] = (char*)calloc(length+1,sizeof(char));
    strcpy(new_genres[ct],genre_read);

    if(genres!=NULL) free(genres);
    return new_genres;
}

Movie_Budget *add_node(FILE *file, Movie_Budget *head_budget, char *name, double budget)
{
	/* This function adds new node to linked list descending order according to year and budget */

	Movie_Budget *iter_budget = head_budget;
    Movie_Budget *prev_budget = head_budget;
    int k = 0;
    Movie_Budget *temp_node;
    Movie_Budget *new_entry;
    
    new_entry = (Movie_Budget*)malloc(sizeof(Movie_Budget));
    new_entry->name = (char*)calloc(strlen(name)+1,sizeof(char));
    strcpy(new_entry->name,name);
    new_entry->next = NULL;
    fscanf(file,"%d",&new_entry->year);
    new_entry->budget = budget;

    /* Inserting first entry excluding head node*/
    if(head_budget->next == NULL)
    {
        if(new_entry->year<head_budget->year)
        {
            head_budget->next = new_entry;
        }

        else if(new_entry->year>head_budget->year)
        {
            new_entry->next = head_budget;
            head_budget = new_entry;
        }

        else if(new_entry->year==head_budget->year)
        {
            if(new_entry->budget<head_budget->budget)
            {
                new_entry->next = head_budget;
                head_budget = new_entry;
            }

            else
            {
                iter_budget = head_budget->next;
                head_budget->next = new_entry;
                new_entry->next = iter_budget;
            }
        }
        return head_budget;
    }

    /* Inserting an entry between two nodes */

    else if(new_entry->year > head_budget->year)
    {
        new_entry->next = head_budget;
        head_budget = new_entry;
        return head_budget;
    }

    else
    {
    	/* Checking until the last node */
        while(iter_budget->next!=NULL)
        {
            if(iter_budget->year < new_entry->year)
            {
                prev_budget->next = new_entry;
                new_entry->next = iter_budget;
                return head_budget;
            }

            else if(iter_budget->year > new_entry->year)
            {
                if(iter_budget->next->year > new_entry->year)
                {
                    prev_budget = iter_budget;
                    iter_budget = iter_budget->next;
                    continue;
                }

                else if(iter_budget->next->year < new_entry->year)
                {
                    temp_node = iter_budget->next;
                    iter_budget->next = new_entry;
                    new_entry->next = temp_node;
                    return head_budget;
                }

                else if(iter_budget->next->year == new_entry->year)
                {
                    if(new_entry->budget >= iter_budget->next->budget)
                    {
                        temp_node = iter_budget->next;
                        iter_budget->next = new_entry;
                        new_entry->next = temp_node;
                        return head_budget;
                    }

                    else if(new_entry->budget < iter_budget->next->budget)
                    {
                        prev_budget = iter_budget;
                        iter_budget = iter_budget->next;
                        continue;
                    }
                }
            }

            else if (iter_budget->year == new_entry->year)
            {
                if(new_entry->budget >= iter_budget->budget)
                {
                    if(iter_budget==head_budget)
                    {
                        new_entry->next = iter_budget;
                        head_budget = new_entry;
                        return head_budget;
                    }
                    else
                    {
                        prev_budget->next = new_entry;
                        new_entry->next = iter_budget;
                        return head_budget;
                    }

                }

                else
                {
                    prev_budget = iter_budget;
                    iter_budget = iter_budget->next;
                    continue;
                }
            }

            prev_budget = iter_budget;
            iter_budget = iter_budget->next;
        }

        /* Checking the last node */
        if(new_entry->year > iter_budget->year)
        {
            prev_budget->next = new_entry;
            new_entry->next = iter_budget;
            return head_budget;
        }

        else if(new_entry->year == iter_budget->year)
        {
            if(new_entry->budget > iter_budget->budget)
            {
                prev_budget->next = new_entry;
                new_entry->next = iter_budget;
                return head_budget;
            }

            else
            {
                iter_budget->next = new_entry;
                return head_budget;
            }
        }

        else
        {
            iter_budget->next = new_entry;
            return head_budget;
        }
    }
    return head_budget;
}

void delete_node(Movie_Budget* head_budget, Movie_Budget *deleted_node)
{
	/* If the movie that has just read is in the linked list already, we delete it from list to add again soon*/
    Movie_Budget *iter = head_budget;
    Movie_Budget *iter_prev = head_budget;

    while(strcmp(iter->name,deleted_node->name)!=0)
    {
        iter_prev = iter;
        iter = iter->next;
    }

    iter_prev->next = deleted_node->next;
    free(deleted_node);
}

void file_read(char *text)
{

    Movie_Budget *head_budget = NULL; /* head node of head budget linked list */
    Movie_Name *head_name = NULL; /* head node of head name linked list */
    Movie_Budget *iter_budget = NULL; /*   */
    Movie_Name *iter_name = NULL;/* */
    char **all_genres = NULL;
    int ct_genres = 0;
    int check;
    int ct;

    FILE *file;
    char *garbage2 = NULL; /* garbage string */
    char garbage;

    int movies_ct = 0;
    double budget;
    double score;
    int year;
    char *genre = NULL;
    char *name = NULL;
    int i;
    int k=0;

    file = fopen(text,"r");

    /* Reading first line */
    for(i=0;i<5;i++)
    {
        garbage2 = read_string_dynamically(file);
        free(garbage2);
    }

    while(1)
    {
        /* Read the budget and indicate whether it is unknown. If it is NOT unknown, convert it to double type */
        char *unknown = NULL;
        char *double_str = NULL;
        iter_budget = head_budget;
        iter_name = head_name;

        unknown = read_string_dynamically(file);

        if(feof(file))
            break;

        if(strcmp(unknown,"unknown")==0)
        {
            budget=-1;
        }
        else
        {
            budget = strtod(unknown,&double_str);
        }
        /* -------------------------------------------------------------------------------------------------- */

        genre = read_string_dynamically(file);
        name = read_string_dynamically(file);

        check = check_genreName(all_genres,genre, ct_genres);
        if(check==-1)
        {
            all_genres = copy_genres(all_genres, genre, ct_genres);
            check = ct_genres;
            ct_genres++;

        }

        /* if there is no entry yet. */
        if(head_name==NULL &&  head_budget==NULL)
        {
            /* fill the head_name linked list's first entry */
            head_name = (Movie_Name*)malloc(sizeof(Movie_Name));
            head_name->name = (char*)calloc(strlen(name)+1,sizeof(char));
            head_name->genre = (char*)calloc(strlen(genre)+1,sizeof(char));
            strcpy(head_name->name,name);
            strcpy(head_name->genre,genre);
            fscanf(file,"%lf",&head_name->score);
            head_name->next = NULL;
            fscanf(file,"%c",&garbage); /* read comma */

            /* fill the head_name linked list's first entry */
            head_budget = (Movie_Budget*)malloc(sizeof(Movie_Budget));
            head_budget->name = (char*)calloc(strlen(name)+1,sizeof(char));
            strcpy(head_budget->name,name);
            head_budget->next = NULL;
            fscanf(file,"%d",&head_budget->year);
            head_budget->budget = budget;

            movies_ct++;

            /* Go to new line */
            garbage2 = read_string_dynamically(file);
            free(garbage2);
            /*fscanf(file,"%c",&garbage);
            fscanf(file,"%c",&garbage);*/

            if(feof(file))
                break;
        }

        /* if there are already nodes in the linked list */
        else
        {
            iter_name = add_movieName(head_name,name);
            iter_budget = check_movieBudget(head_budget,name);

            /* if we are adding new entry to tail */
            if(iter_name->name==NULL)
            {
                Movie_Budget *new_entry;
                /* fill the head_name linked list's new entry */
                iter_name->name = (char*)calloc(strlen(name)+1,sizeof(char));
                iter_name->genre = (char*)calloc(strlen(genre)+1,sizeof(char));
                strcpy(iter_name->name,name);
                strcpy(iter_name->genre,genre);
                fscanf(file,"%lf",&iter_name->score);
                iter_name->next = NULL;
                fscanf(file,"%c",&garbage); /* read comma */

                /* fill the head_budget linked list's first entry */

                head_budget = add_node(file,head_budget,name,budget);

                /* Go to new line */
                garbage2 = read_string_dynamically(file);
                movies_ct++;
                free(garbage2);

                if(feof(file))
                    break;

            }

                /* if we are updating a entry that exists */
            else
            {
                Movie_Budget *new_entry;
                /* update the entry of head_name linked list */
                free(iter_name->genre);
                iter_name->genre = (char*)calloc(strlen(genre)+1,sizeof(char));
                strcpy(iter_name->genre,genre);
                fscanf(file,"%lf",&iter_name->score);
                fscanf(file,"%c",&garbage); /* read comma */

                if(iter_budget!=NULL)
                {
                	/* If the movie that has just read is in the linked list, we have to remove and update it */
            	    delete_node(head_budget, iter_budget); /* delete */
          	  	}
                head_budget = add_node(file, head_budget, name, budget); /* add again */

                /* Go to new line */
                garbage2 = read_string_dynamically(file);
                free(garbage2);
            }

        }

        free(name);
        free(genre);
        free(unknown);
        k++;
    }

    fclose(file);
    
    /*ct = 0;
    iter_budget = head_budget;
    while(1)
    {
        printf("%d\nBudget List -> %-40s%-10d%-10f\n\n",ct+1,iter_budget->name,iter_budget->year,iter_budget->budget);
        ct++;
        iter_budget = iter_budget->next;
        if(iter_budget == NULL)
            return;
    }*/
    menu(head_budget,head_name,movies_ct,all_genres,ct_genres);
}

int main()
{
    file_read("Movies.txt");
}

