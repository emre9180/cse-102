/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 2 /* Total word number in the delete word list */
#define MAX_LINE 200 /* Maximum character number in a line */

/* In this homework, number_of_words variable is assumed as total word number in the delete word list
   since there is no need to know how many words there are in a line. */


int check(char *word, char *word_to_delete, int flag) /* This functin checks whether the word that read is equals to a word that come from delete word list */
{
	if(flag==1)
		return flag;
	if((word[0]=='\0' && word_to_delete[0]!='\0') || (word[0]!='\0' && word_to_delete[0]=='\0'))
		return 1;
	if(word_to_delete[0]=='\0')
        return flag;

	if(word_to_delete[0]=='\0')
		return flag;

	if(word[0]==word_to_delete[0])
		check(word+1,word_to_delete+1,0);
	else
		check(word+1,word_to_delete+1,1);
}

int write_word(FILE* outfid, char* word, char *word_to_delete[WORDSIZE],int number_of_words, int flag)
{
	if(number_of_words==0) /* If there is no word to check in the list */
	{
		if(flag==1) /* IF the word is not in the delete word list */
		{
			fprintf(outfid,"%s",word);
			return 1;
		}
		return 0;
	}

	flag *= check(word,word_to_delete[number_of_words-1],0);
	write_word(outfid, word, word_to_delete, number_of_words-1, flag); /* Recurse */
}


void write_line(FILE* outfid, char *line, char* word_to_delete[WORDSIZE], int number_of_words, char*word, int ct)
{
	char lword[20];
	int flag = 1;


	if((line[0]>='a' && line[0]<='z') || (line[0]>='A' && line[0]<='Z')) /* If the character is a letter, add it to word array. */
	{
		word[ct]=line[0];  /* Add the letter to array */
		write_line(outfid,line+1,word_to_delete,number_of_words,word,ct+1); /* Recurse */
	}

	else /* If the character is NOT a letter, send the word to write_word function to check whether it is in the delete word list, then write the output according to result */
	{
		word[ct]='\0'; /* The last character of word must be '\0' */
		flag = write_word(outfid,word,word_to_delete,number_of_words,1);

		if(line[0]=='\n' || line[0]<0) /* If we reach end of line */
		{
			fprintf(outfid,"%c",line[0]);
			return;
		}
		
		if(flag==0 && line[0]==' ');
		else fprintf(outfid,"%c",line[0]); 
		write_line(outfid,line+1,word_to_delete,number_of_words,lword,0); /* We send to write_line function a new array (lword) since previous array is checked and written */
	}
}


void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)
{	
	char read[MAX_LINE]; /* A line that read at a time will be stored in this array */
	char word[20]; /* Words in a line will be stored in this array */
	
	fgets(read,MAX_LINE,infid); /* Read one line */

	if(feof(infid))
		return;
		
	write_line(outfid,read,words_to_delete,number_of_words,word,0);  /* Go write_line function to write the line that has just read */
	delete_words(infid,outfid,words_to_delete,number_of_words); /* Recurse */

	
}


void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE *infid, *outfid;
	infid = fopen(infile,"r");
	outfid = fopen(outfile,"w");
	delete_words (infid, outfid, words_to_delete, number_of_words);
	fclose(infid);
	fclose(outfid);
	printf("WORDS ARE DELETED SUCCESSFULLY.\n\n");
}


/*                    Part 2                    */

void print_maze(cell_type maze[][8],int x, int y) /* This function prints the maze game */
{
    if(x==7 && y==7)
    {
        switch(maze[x][y])
        {
            case cell_wall:
                printf("%-2c ",'*');
                break;

            case cell_free:
                printf("%-2s ","");
                break;

            case cell_target:
                printf("%-2c ",'T');
                break;

            case cell_p1:
                printf("%-2s ","P1");
                break;

            case cell_p2:
                printf("%-2s ","P2");
                break;
        }
        printf("\n");
        return;
    }

    if(y==7)
    {   
        switch(maze[x][y])
        {
            case cell_wall:
                printf("%-2c\n",'*');
                break;

            case cell_free:
                printf("%-2s\n","");
                break;

            case cell_target:
                printf("%-2c\n",'T');
                break;

            case cell_p1:
                printf("%-2s\n","P1");
                break;

            case cell_p2:
                printf("%-2s\n","P2");
                break;
        }
        print_maze(maze,x+1,0);
    }
    else
    {
        switch(maze[x][y])
        {
            case cell_wall:
                printf("%-2c ",'*');
                break;

            case cell_free:
                printf("%-2s ","");
                break;

            case cell_target:
                printf("%-2c ",'T');
                break;

            case cell_p1:
                printf("%-2s ","P1");
                break;

            case cell_p2:
                printf("%-2s ","P2");
                break;
        }
        print_maze(maze,x,y+1);
    }
}

void find_player_loc(cell_type maze[][8],cell_type player, int *x, int *y) /* This funcstion finds the location of player */ 
{
    if(maze[*x][*y]==player) /* If we found location, return the function */
        return;

    else if(*y==7) /* If we reacht the end of row */
    {
        *y = 0;
        *x += 1;
        find_player_loc(maze,player,x,y); /* Recurse */
    }

    else
    {
        *y += 1;
        find_player_loc(maze,player,x,y); /* Recurse */
    }

}

int move_valid(cell_type maze[][8], move_type movement, int loc_x, int loc_y) /* This function checks whether movement is valid */
{
    switch(movement)
    {
        case move_left:
        {
            if(loc_y<1)
                return 0;

            else if(maze[loc_x][loc_y-1]==cell_free || maze[loc_x][loc_y-1]==cell_target)
                return 1;

            else
                return 0;
            
        }

        case move_right:
        {
            if(loc_y>7)
                return 0;

            if(maze[loc_x][loc_y+1]==cell_free || maze[loc_x][loc_y+1]==cell_target)
                return 1;

            else
                return 0;
        }

        case move_up:
        {
            if(loc_x<1)
                return 0;

            if(maze[loc_x-1][loc_y]==cell_free || maze[loc_x-1][loc_y]==cell_target)
                return 1;

            else
                return 0;
        }

        case move_down:
        {
            
            if(loc_x>6)
                return 0;

            if(maze[loc_x+1][loc_y]==cell_free || maze[loc_x+1][loc_y]==cell_target)
                return 1;

            else return 0;
        }
    }
}

int gomove(cell_type maze[][8], move_type movement, int loc_x, int loc_y) /* This functions makes movement */
{
    cell_type temp; /* Temporary variable */

    switch(movement)
    {
        case move_left:
        {   
            if(maze[loc_x][loc_y-1]==cell_target) /* If player reaches the target, return 1 */
                return 1;

             /* Make move */
             temp = maze[loc_x][loc_y-1];
             maze[loc_x][loc_y-1]=maze[loc_x][loc_y];
             maze[loc_x][loc_y] = temp;
             break;

            
        }

        case move_right:
        {
            if(maze[loc_x][loc_y+1]==cell_target) /* If player reaches the target, return 1 */
                return 1;

             /* Make move */
             temp = maze[loc_x][loc_y+1];
             maze[loc_x][loc_y+1]=maze[loc_x][loc_y];
             maze[loc_x][loc_y] = temp;
             break;
        }

        case move_up:
        {
            if(maze[loc_x-1][loc_y]==cell_target) /* If player reaches the target, return 1 */
                return 1;

             /* Make move */
             temp = maze[loc_x-1][loc_y];
             maze[loc_x-1][loc_y]=maze[loc_x][loc_y];
             maze[loc_x][loc_y] = temp;
             break;
        }

        case move_down:
        {
            
             if(maze[loc_x+1][loc_y]==cell_target) /* If player reaches the target, return 1 */
                return 1;

             /* Make move */
             temp = maze[loc_x+1][loc_y];
             maze[loc_x+1][loc_y]=maze[loc_x][loc_y];
             maze[loc_x][loc_y] = temp;
             break;
        }
    }
    return 0;
}

int maze_move(cell_type maze[][8], cell_type player, move_type movement)
{

    int loc_x = 0; /* Location row of p1 */
    int loc_y = 0; /* Location column of p1 */
    int loc_x2 = 0; /* Location row of p2 */
    int loc_y2 = 0; /* Location column of p2 */

    print_maze(maze,0,0); /* Print the game */
    
    /* Getting player choice of user and assign it to enum variable */
    printf("Please choice player.(1) or (2): \n");
    scanf("%u",&player);
    player += 3;
    

    /* Getting movement choice of user and assign it to enum variable */
    printf("Please choice movement.\n1. Left\n2. Right\n3. Up\n4. Down\n");
    scanf("%u",&movement);


    find_player_loc(maze,player,&loc_x, &loc_y); /* Fing location of player in maze */

    
    if(move_valid(maze,movement,loc_x, loc_y)) /* If move that user chooses is valid, go move */
    {
        if(gomove(maze,movement,loc_x,loc_y)) /* If player finishes the game, terminate the program */
        {
            printf("\nPlayer %u is completed the game successfully! Congratulations!",player-3);
            return 1;
        }

        else
        {
            maze_move(maze,player,movement); /* Recurse */                          
        }
    }

    else /* If the move that user chooses is NOT valid, recurse */
    {
        printf("\nYour movement was invalid. Try again.\n");
        maze_move(maze,player,movement); /* Recurse */
    }
    

}




void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
	int start_n = 0;

	int i = n,j;

	/*while(1)
	{
		if(i==1)
			printf("Move disk 1 from peg %c to peeg %c\n",start_peg, end_peg);

		else
		{
			for(i=1;j<n;j++)
			{
				printf("Move disk %d from peg %c to peeg %c\n",n, start_peg, end_peg);
			}
		}

		i++;
	}*/

    if(n==1)
    	printf("Move disk 1 from peg %c to peeg %c\n",start_peg, end_peg);

    else
    {
    	towers_of_hanoi(start_peg, aux_peg, end_peg, n-1);
    	printf("Move disk %d from peg %c to peeg %c\n",n, start_peg, end_peg);
    	towers_of_hanoi(aux_peg, end_peg, start_peg, n-1);
    }
}
