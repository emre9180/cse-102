/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/* NOTE for T.A. -> It is assumed that array should be increased dynamically as the file's lines are read. */
/* NOTE for T.A. -> As told in Teams Forum by T.A. , the line that has NO year and score values is ignored. It is assumed that there is NO lines with missing information. */
/* NOTE for T.A. -> Information order is assumed as Budget-Genre-Name-Score-Year, read process is done according to this order. */
/* NOTE for T.A. -> Movies with budget information unknown are not included in the sorting process. */

struct Movie{
    double budget;
    int genre; /* Starts from 0, and increases as new genres read */
    char *name;
    double score;
    int year;
};

int sort_print_budget(struct Movie *movies, int movies_ct, int upper, int lower, char**genres) 
{
/* This function, creates a copy of movies array, then sorts that array according to budgets */

	int i,k=0; /* Loop */
	struct Movie *sort=NULL; /* Declaration of array to be sorted */
	int min_number; /* Will be used for sorting */
	int min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */
	int unknown_ct = 0; /* Number of unknown movies */ 

	sort = (struct Movie*)calloc(movies_ct, sizeof(struct Movie));  /* Declaration of array to be sorted */

	/* Copying movies array to new array to be sorted */
	for(i=0;i<movies_ct;i++)
	{
		sort[k] = movies[i];
		k++;
	}

	/* Sorting the new array ascending order according to budget */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = sort[i].budget;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (sort[k].budget<min_number)
			{
				min_number = sort[k].budget;
				min_index = k;
			}
		}
	
		temp = sort[i];
		sort[i] = sort[min_index];
		sort[min_index] = temp;
	}

	/* Count the unknown budget movies, and arrange the upper-lower bounds */
	for(i=0;i<movies_ct;i++)
	{
		if(sort[i].budget==-1)
			unknown_ct++;
		else
			break;
	}
	upper += unknown_ct;
	lower += unknown_ct;

	if(upper>=movies_ct || lower>=movies_ct)
		return movies_ct-unknown_ct;

	/* Printing structs in desired range by user */
	for(i=lower;i<=upper;i++)
	{
		if(sort[i].budget==-1)
			printf("%-20s","Unknown");
		else
			printf("%-20f", sort[i].budget);
		printf("%-20s", genres[sort[i].genre]);
		printf("%-50s",sort[i].name);
		printf("%-20f", sort[i].score);
		printf("%-20d\n", sort[i].year);;
	}
		
	free(sort);
	return 1;
}

void sort_print_year(struct Movie *movies, int movies_ct, int upper, int lower, char **genres)
{
/* This function, creates a copy of movies array, then sorts that array according to years */

	int i,k=0; /* Loop */
	struct Movie *sort = (struct Movie*)calloc(movies_ct, sizeof(struct Movie)); /* Declaration of array to be sorted */
	int min_number; /* Will be used for sorting */
	int min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */

	/* Copying movies array to new array to be sorted */
	for(i=0;i<movies_ct;i++)
	{
		sort[k] = movies[i];
		k++;
	}

	/* Sorting the new array ascending order according to year */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = sort[i].year;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (sort[k].year<min_number)
			{
				min_number = sort[k].year;
				min_index = k;
			}
		}
	
		temp = sort[i];
		sort[i] = sort[min_index];
		sort[min_index] = temp;
		
	}

	/* Printing structs in desired range by user */
	for(i=lower;i<=upper;i++)
	{
		if(sort[i].budget==-1)
			printf("%-20s","Unknown");
		else
			printf("%-20f", sort[i].budget);
		printf("%-20s", genres[sort[i].genre]);
		printf("%-50s",sort[i].name);
		printf("%-20f", sort[i].score);
		printf("%-20d\n", sort[i].year);;
	}
	free(sort);
}

void sort_print_score(struct Movie *movies, int movies_ct, int upper, int lower, char **genres)
{
/* This function, creates a copy of movies array, then sorts that array according to scores */
/* NOTE: Since there is a problem when comparing double-type variables, the scores are evaluated by multiplying by 10.*/

	int i,k=0; /* Loop */
	struct Movie *sort = (struct Movie*)calloc(movies_ct, sizeof(struct Movie)); /* Declaration of array to be sorted */
	int min_number; /* Will be used for sorting */
	int min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */

	/* Copying movies array to new array to be sorted */
	for(i=0;i<movies_ct;i++)
	{
		sort[k] = movies[i];
		k++;
	}

	/* Sorting the new array ascending order according to scores */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = sort[i].score*10;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (sort[k].score*10<min_number)
			{
				min_number = sort[k].score*10;
				min_index = k;
			}
		}
	
		temp = sort[i];
		sort[i] = sort[min_index];
		sort[min_index] = temp;
	
	}

	/* Printing structs in desired range by user */
	for(i=lower;i<=upper;i++)
	{
		if(sort[i].budget==-1)
			printf("%-20s","Unknown");
		else
			printf("%-20f", sort[i].budget);
		printf("%-20s", genres[sort[i].genre]);
		printf("%-50s",sort[i].name);
		printf("%-20f", sort[i].score);
		printf("%-20d\n", sort[i].year);;
	}
	free(sort);
}

void sort_print_genres(struct Movie *movies, int movies_ct, int upper, int lower, char **genres)
{
/* This function, creates a copy of movies array, then sorts that array according to genres */

	int i,k=0; /* Loop */
	struct Movie *sort = (struct Movie*)calloc(movies_ct, sizeof(struct Movie)); /* Declaration of array to be sorted */
	int min_number; /* Will be used for sorting */
	int min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */

	/* Copying movies array to new array to be sorted */
	for(i=0;i<movies_ct;i++)
	{
		sort[k] = movies[i];
		k++;
	}

	/* Sorting the new array ascending order according to genres */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = sort[i].genre;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (sort[k].genre<min_number)
			{
				min_number = sort[k].genre;
				min_index = k;
			}
		}
	
		temp = sort[i];
		sort[i] = sort[min_index];
		sort[min_index] = temp;
		
	}

	/* Printing structs in desired range by user */
	for(i=lower;i<=upper;i++)
	{
		if(sort[i].budget==-1)
			printf("%-20s","Unknown");
		else
			printf("%-20f", sort[i].budget);

		printf("%-20s", genres[sort[i].genre]);
		printf("%-50s",sort[i].name);
		printf("%-20f", sort[i].score);
		printf("%-20d\n", sort[i].year);;
	}
	free(sort);
}

void sort_print_names(struct Movie *movies, int movies_ct, int upper, int lower, char **genres)
{
/* This function, creates a copy of movies array, then sorts that array according to names */

	int i,k=0; /* Loop */
	struct Movie *sort = (struct Movie*)calloc(movies_ct, sizeof(struct Movie)); /* Declaration of array to be sorted */
	char *min_name; /* Will be used for sorting */
	int min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */

	/* Copying movies array to new array to be sorted */
	for(i=0;i<movies_ct;i++)
	{
		sort[k] = movies[i];
		k++;
	}

	/* Sorting the new array ascending order according to names */
	for(i=0;i<movies_ct-1;i++)
	{
		int length = strlen(sort[i].name);
		min_name = (char*)calloc(length+1,sizeof(char));
		strcpy(min_name,sort[i].name);
		min_index = i;

		for (k=i+1;k<movies_ct;k++)
		{
			if(strcmp(sort[k].name,min_name)<0)
			{
				free(min_name);
				length = strlen(sort[k].name);
				min_name = (char*)calloc(length+1,sizeof(char));
				strcpy(min_name,sort[k].name);
				min_index = k;
			}
		}
	
		temp = sort[i];
		sort[i] = sort[min_index];
		sort[min_index] = temp;
		
	}

	/* Printing structs in desired range by user */
	for(i=lower;i<=upper;i++)
	{
		if(sort[i].budget==-1)
			printf("%-20s","Unknown");
		else
			printf("%-20f", sort[i].budget);

		printf("%-20s", genres[sort[i].genre]);
		printf("%-50s",sort[i].name);
		printf("%-20f", sort[i].score);
		printf("%-20d\n", sort[i].year);;
	}
	free(min_name);
	free(sort);
}


void listof_sorted_data(struct Movie *movies, int movies_ct, char**genres)
{
/* This function does the operation in the first selection of menu */

	int sort; /* Sort choice of user */
	int op; /* Operation choice of user, single or multiple */
	int lower; /* Lower limit of range */
	int upper = -1; /* Upper limit of range */

	printf("1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n\nPlease select an operation: ");
	scanf("%d",&sort);
	if(sort<1 || sort>5) /* If choice of user is invalid, bring the menu again */
	{
		printf("PLEASE ENTER VALID OPERATION.\n\n");
		listof_sorted_data(movies, movies_ct,genres);
		return;
	}

	printf("\n1. Single Selection\n2. Multiple Selection\n\nPlease select an operation: ");
	scanf("%d",&op);
	if(op<1 || op>2) /* If choice of user is invalid, bring the menu again */
	{
		printf("PLEASE ENTER VALID OPERATION.\n\n");
		listof_sorted_data(movies, movies_ct,genres);
		return;
	}

	
	if(op==1) /* Single selection */
	{
		printf("Enter value: ");
		scanf("%d",&lower);
		upper = lower;
	}
	else if(op==2) /* Multiple selection */
	{
		printf("Enter start value: ");
		scanf("%d",&lower);
		printf("Enter end value: ");
		scanf("%d",&upper);
	}
	else /* If choice of user is invalid, bring the menu again */
	{
		printf("PLEASE ENTER VALID OPERATION.\n\n");
		listof_sorted_data(movies, movies_ct,genres);
		return;
	}

	if(lower<1 || upper<1 || lower>movies_ct || upper>movies_ct || upper<lower) /* If choice of user is invalid, bring the menu again */
	{
		printf("PLEASE ENTER VALID VALUES.(1-%d)\n\n",movies_ct);
		listof_sorted_data(movies, movies_ct,genres);
		return;
	}

	/* Calling the sorting-printing functions according to user selected areas */
	switch(sort)
	{
		case 1:
			if(op==1) /* Single selection */
				printf("\n%d. Movie\n\n",lower);
			else /* Multiple selection */
				printf("\nMovies between %d and %d sorted by budget\n\n",lower,upper);

			if(sort_print_budget(movies, movies_ct ,upper-1 ,lower-1, genres)!=1) /* Sort and print. But firstly, we have to check range. */
				{
					printf("Your budget selection range must be between 1-%d DUE TO unknown budget movies.\n\n",sort_print_budget(movies, movies_ct ,upper-1 ,lower-1, genres));
					listof_sorted_data(movies, movies_ct,genres);
					return;
				}
			printf("\n");
			break;

		case 2:
			if(op==1) /* Single selection */
				printf("\n%d. Movie\n\n",lower); 
			else /* Multiple selection */
				printf("\nMovies between %d and %d sorted by genres:\n\n",lower,upper);

			sort_print_genres(movies,movies_ct ,upper-1 ,lower-1,genres); /* Sort and print */
			printf("\n");
			break;

		case 3:
			if(op==1) /* Single selection */
				printf("\n%d. Movie\n\n",lower);
			else /* Multiple selection */
				printf("\nMovies between %d and %d sorted by names:\n\n",lower,upper);

			sort_print_names(movies, movies_ct, upper-1, lower-1,genres); /* Sort and print */
			printf("\n");
			break;

		case 4:
			if(op==1) /* Single selection */
				printf("\n%d. Movie\n\n",lower);
			else /* Multiple selection */
				printf("\nMovies between %d and %d sorted by scores:\n\n",lower,upper);

			sort_print_score(movies, movies_ct, upper-1, lower-1,genres); /* Sort and print */
			printf("\n");
			break;

		case 5:
			if(op==1) /* Single selection */
				printf("\n%d. Movie\n\n",lower);
			else /* Multiple selection */
				printf("\nMovies between %d and %d sorted by years:\n\n",lower,upper);

			sort_print_year(movies, movies_ct, upper-1, lower-1,genres); /* Sort and print */
			printf("\n");
			break;
	}
	
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

void sort_year_array(struct Movie *movies, int movies_ct)
{
/* This function sorts the array that come from as parameter according to years */
	int i,k; /* Loop */
	int min_number, min_index; /* Will be used for sorting */
	struct Movie temp; /* Temporary struct variable */

	/* Sorting the array that come from as parameter ascending order according to years */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = movies[i].year;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (movies[k].year<=min_number)
			{
				min_number = movies[k].year;
				min_index = k;
			}
		}
	
		temp = movies[i];
		movies[i] = movies[min_index];
		movies[min_index] = temp;
	}
	
}

void sort_score_array(struct Movie *movies, int movies_ct)
{
/* This function sorts the array that come from as parameter according to years */
/* NOTE: Since there is a problem when comparing double-type variables, the scores are evaluated by multiplying by 10.*/

	int i,k; /* Loop */
	struct Movie temp; /* Temporary struct variable */
	int min_index, min_number; /* Will be used for sorting */

	/* Sorting the new array ascending order according to scoores */
	for(i=0;i<movies_ct-1;i++)
	{
		min_number = movies[i].score*10;
		min_index = i;
		for (k=i+1;k<movies_ct;k++)
		{
			if (movies[k].score*10<=min_number)
			{
				min_number = movies[k].score*10;
				min_index = k;
			}
		}
	
		temp = movies[i];
		movies[i] = movies[min_index];
		movies[min_index] = temp;
	}
}

void list_through_years(struct Movie *movies, int movies_ct)
{
/* This function creates a new array as copy of movies array and sort it according to years. Then it prints movies until or since a user selected year */

	int choice; /* Since-Until choice */
	int year; /* Year choice */
	int i,k=0; /* Loop */
	struct Movie *sort_year; /* Declaration of array to be sorted */
	int find_ct = 0; /* Indicates that how many match is found */

	sort_year = (struct Movie*)calloc(movies_ct,sizeof(struct Movie));

	/* Copying movies array to new array */
	for(i=0;i<movies_ct;i++)
	{
		sort_year[i]=movies[k];
		k++;
	}

	/* Getting inputs from user */
	printf("Enter a year: ");
	scanf("%d",&year);
	printf("Until(0) or Since(1) %d?: ",year);
	scanf("%d",&choice);
	if(choice<0 || choice>1) /* If input is invalid, ask again */
	{
		printf("Please enter a valid choice.\n\n");
		list_through_years(movies, movies_ct);
		return;
	}

	sort_year_array(sort_year, movies_ct); /* Sort the new array ascending order according to years */

	/* Printing results according to since or until choice */
	if(choice==0)
	{
		for(i=0;i<movies_ct;i++)
		{
			if(year>sort_year[i].year)
			{
				printf("%-10d%s\n",sort_year[i].year,sort_year[i].name);
				find_ct++;
			}
			else
				break;
		}
	}

	if(choice==1)
	{
		for(i=0;i<movies_ct;i++)
		{
			if(year<sort_year[i].year)
			{
				printf("%-10d%s\n",sort_year[i].year,sort_year[i].name);
				find_ct++;
			}
		}
	}

	if(find_ct==0) /* If there is no match, ask a new year */
	{
		printf("\nTRY AGAIN!\n");
		free(sort_year);
		list_through_years(movies,movies_ct);
		return;
	}
	
	printf("\n");
	free(sort_year);
}

void list_through_scores(struct Movie *movies, int movies_ct)
{
/* This function creates a new array as copy of movies array and sort it according to scores. Then it prints movies less or greaatr a user selected score */
	int choice; /* Less or greater choice of user */
	double score; /* Score choice of user */
	int i,k=0; /* Loop */
	int find_ct = 0; /* Indicates that how many match is found */
	struct Movie *sort_score = (struct Movie*)calloc(movies_ct,sizeof(struct Movie)); /* Declaration of array that to be sorted *

	/* Copying movies array to new array */
	for(i=0;i<movies_ct;i++)
	{
		sort_score[i]=movies[k];
		k++;
	}

	/* Getting inputs from user */
	printf("Enter a score: ");
	scanf("%lf",&score);
	printf("Less(0) or Greater(1) %f?: ",score);
	scanf("%d",&choice);
	if(choice<0 || choice>1)
	{
		printf("Please enter a valid choice.\n\n");
		list_through_scores(movies, movies_ct);
		return;
	}

	sort_score_array(sort_score, movies_ct); /* Sort the new array ascending order according to scores */
	
	/* Printing results according to since or until choice */
	if(choice==0)
	{
		for(i=0;i<movies_ct;i++)
		{
			if(score>sort_score[i].score)
			{
				printf("%-10f%s\n",sort_score[i].score,sort_score[i].name);
				find_ct++;
			}
			else
				break;
		}
	}

	if(choice==1)
	{
		for(i=0;i<movies_ct;i++)
		{
			if(score<sort_score[i].score)
			{
				printf("%-10f%s\n",sort_score[i].score,sort_score[i].name);
				find_ct++;
			}
		}
	}

	if(find_ct==0) /* If there is no match, ask a new score */
	{
		free(sort_score);
		printf("TRY AGAIN.\n");
		list_through_scores(movies, movies_ct);
		return;
	}
	printf("\n");
	free(sort_score);
}

int check_movieName(struct Movie *movies, int movies_ct, char *name)
{
/* This function checks that the movie that has just read from file whether is read before. If it read before, return indice; if it is no read before, return -1 */
	int i;
	int check = -1;

	for(i=0;i<movies_ct;i++)
	{
		if(strcmp(movies[i].name,name)==0)
		{
			check=i;
			break;
		}
	}

	return check;
}

void all_infos_single_movie(struct Movie *movies, int movies_ct, char **genres)
{
/* This function gets a movie name as input from user, then it searchs the array to find a match, and print the matched movie information */

	char *buf_name = (char*)calloc(200,sizeof(char)); /* Name input */
	char *name;
	int check; /* Indicates that there is a movie in the array as user entered or not */

	/* Getting input */
	printf("Please enter the name of the movie: ");
	scanf("%s",buf_name);
	name = (char*)calloc(strlen(buf_name+1),sizeof(char));
	strcpy(name,buf_name);
	free(buf_name);

	check = check_movieName(movies, movies_ct, name); /* Check that the movie that user entered is in the movie array or not */

	if(check==-1) /* If the movie user entered is not in the array, ask again */
	{
		printf("Your movie is not in the list. Please enter a new name.\n\n");
		all_infos_single_movie(movies,movies_ct,genres);
		return;
	}
	else /* If the movie user entered is in the array, print it */
	{
		if(movies[check].budget==-1)
			printf("Budget: Unknown\n");
		else
			printf("Budget: %f\n", movies[check].budget);
		printf("Genre: %s\n", genres[movies[check].genre]);
		printf("Score: %f\n", movies[check].score);
		printf("Year: %d\n\n", movies[check].year);
	}
	free(name);
}

void average(struct Movie *movies, int movies_ct)
{
/* This function calculates the averages of scores and prints it */
	double sum = 0;
	int i;

	for(i=0;i<movies_ct;i++)
	{
		sum += movies[i].score;
	}

	printf("Average: %f\n\n",sum/movies_ct);
}

void frequence_genres(struct Movie *movies, int movies_ct, char **genres, int genre_ct)
{
/* This function calculates the frequence of genres and prints it */

	int *frequence = (int*)calloc(genre_ct,sizeof(int)); /* Array that keeps frequence of genres */
	int i; /* Loop */

	/* Calculate the frequences */
	for(i=0;i<movies_ct;i++)
	{
		frequence[movies[i].genre]++;
	}

	/* Print the frequences */
	for(i=0;i<genre_ct;i++)
	{
		printf("%-20s%d\n",genres[i],frequence[i]);
	}

	free(frequence);
	printf("\n");
}

void menu (struct Movie *movies, int movies_ct, int genre_ct, char **genres)
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
			menu(movies,movies_ct,genre_ct,genres);
			return;
		}

		switch(choice)
		{
			case 1:
				listof_sorted_data(movies, movies_ct,genres);
				break;

			case 2:
				listof_genres(genres, genre_ct);
				break;

			case 3:
				list_through_years(movies, movies_ct);
				break;
		
			case 4:
				list_through_scores(movies, movies_ct);
				break;

			case 5:
				all_infos_single_movie(movies,movies_ct,genres);
				break;

			case 6:
				average(movies, movies_ct);
				break;

			case 7:
				frequence_genres(movies, movies_ct, genres, genre_ct);
				break;

			case 8:
				printf("Bye.");
				break;

		}

	}while(choice!=8);
}



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


void read_file(char *text)
{
/* This function creates a movie struct array and increases it dynamically. */

    int i,k=0; /* Loop */
    struct Movie *movies = NULL; /* Movie struct array */
    struct Movie *movies2 = NULL; /* Movie struct array. Will be used for increasing the array above dynamically */
    FILE *file;

    int ct = 0; /* This variable indicates how many movies we have */
    int write_ct; /* This variable indicates which element of struct array we will add the new entry */

    char *name = NULL;
    char *genre_read = NULL; /* This array keeps the genre of the movie that has just read */
    char **genres = NULL; /* This array keeps the all genres. This is a string array */
    int ct_genres = 0; /* This variable indicates how many different genres we have */
    int check;
    int check2;

    /* Budget, score and year values of movies. These variables will be assign to struct array */
    double budget = 0;
    double score;
    int year;

    int length; /* This variable indicates that length of string */

    char garbage; /* Garbage characters */
    char *garbage2; /* Garbage string */

    file=fopen(text,"r");

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

        movies = (struct Movie*)calloc(ct+1,sizeof(struct Movie));

        for(i=0;i<ct;i++)
            movies[i]=movies2[i];
        
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
        
        /* Read the genre and indicate that whether it is a new genre or it is in the genres array. */
        /* If it is a new genre, add it to genres array that keeps all genres. */
        /* Also, we indicate the genre's integer value.(check variable) */

        genre_read = read_string_dynamically(file);
        check = check_genreName(genres,genre_read,ct_genres);
        if(check==-1)
        {
            genres = copy_genres(genres, genre_read,ct_genres);
            check = ct_genres;
            ct_genres++;

        }

        name = read_string_dynamically(file);
        check2 = check_movieName(movies,ct,name);

        if(check2==-1)
        {
            ct++;
            write_ct = ct-1;
        }
        else
        {
            write_ct=check2;
        }

        /* ------------------------------------------------------------------------------------------- */
        /* Read the score and year values */

        fscanf(file,"%lf",&score);
        fscanf(file,"%c",&garbage); /* read comma */
        fscanf(file,"%d",&year);

        /* Go to new line */
        garbage2 = read_string_dynamically(file);
        free(garbage2);

        /* Assigning the all values to array's true indice */
        movies[write_ct].budget = budget;
        movies[write_ct].genre = check;

        length = strlen(name);
        movies[write_ct].name = (char*)malloc(length+1*sizeof(char));
        strcpy(movies[write_ct].name, name);

        movies[write_ct].score = score;
        movies[write_ct].year = year;

    	/* ------------------------------------------------------------------------------------------- */

        free(genre_read);
        free(name);
        free(unknown);
        genre_read = NULL;
        name = NULL;

        if(movies2!=NULL) free(movies2);
        movies2=movies;
    }

    fclose(file);
    menu(movies2,ct,ct_genres,genres); /* call the menu */

}

int main()
{
    read_file("Movies.txt");
}
