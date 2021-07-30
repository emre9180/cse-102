/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <stdlib.h> /* rand funcs */

#define N 5 /* Puzzle Size */

/* The puzzle "1 2 3  is assumed as solved according to Teams Homework Forum, T.A. directive 
			     4 5
			   6 7 8"  */

typedef enum
{
	left = 1,
	right,
	up,
	down
}move;


void print_puzzle(int puzzle[N][N])
{
	int i,j,k; /* Loop */

	/* Printing the coordinates of columns */
	for(i=0;i<N;i++)
	{	
		if(i==0)
			printf("\n\t %3d   ",i);
		else
			printf("%3d   ",i);
	}
	printf("\n\n");
	
	/* Printing the puzzle */
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{

			if(j==0)
			{	printf("\t");

				/* Printing the bounds */
				for(k=0;k<(N*6)+1;k++)
				{
					printf("*");
				}
				printf("\n");

				/* Printing the numbers in the puzzle */
				if(puzzle[i][j]==-1)
					printf("%d\t*%3c%3c",i,' ','*');
				else
					printf("%d\t*%3d%3c",i,puzzle[i][j],'*');
				
			}

			else
				/*  Printing the numbers in the puzzle */
				if(puzzle[i][j]==-1)
					printf("%3c%3c",' ','*');
				else
					printf("%3d%3c",puzzle[i][j],'*');
				
		}
		printf("\n");

	}

	/* Printing lower bound */
	for(i=0;i<(N*6)+1;i++)
	{
		if(i==0)
			printf("\t");
		
		printf("*");
	}
}

int play_puzzle(int puzzle[N][N], int start_x, int start_y, move movement)
{
	int i,j; /* loop */
	int empty_x; /* row of empty square */
	int empty_y; /* column of empty square */
	int find_flag = 0; /* This variable indicates whether there is a move as user wants. If 0, there is no move. */
	switch(movement)
	{
		case left:
			{
				/* detect the EMPTY square by scanning from right to left */
				for(i=start_y;i>=0;i--)
				{
					if(puzzle[start_x][i] == -1)
					{
						empty_x = start_x;
						empty_y = i;
						find_flag = 1;
						break;
					}
				}

				/* Shifting the squares from empty square to start location*/
				if(find_flag==1)
				{
					for(i=empty_y;i<=start_y;i++)
					{
						if(i == start_y)
							puzzle[start_x][i] = -1;
						else
							puzzle[empty_x][i] = puzzle[empty_x][i+1];
					}
				}
				
				break;
			}

		case right:
		{		
				/* Detect the EMPTY square by scanning from left to right.  */
				for(i=start_y;i<N;i++)
				{
					if(puzzle[start_x][i] == -1)
					{
						empty_x = start_x;
						empty_y = i;
						find_flag = 1;
						break;
					}
				}

				/* Shifting the squares from empty square to start location*/
				if(find_flag==1)
				{
					for(i=empty_y;i>=start_y;i--)
					{
						if(i == start_y)
							puzzle[start_x][i] = -1;
						else
							puzzle[empty_x][i] = puzzle[empty_x][i-1];
					}
				}
				
				break;
			}


		case up:
		{		
			/* Detect the EMPTY square by scanning from down to up */
			for(i=start_x;i>=0;i--)
			{
				if(puzzle[i][start_y] == -1)
				{
					empty_x = i;
					empty_y = start_y;
					find_flag = 1;
					break;
				}
			}

			/* Shifting the squares from empty square to start location*/
			if(find_flag==1)
			{
				for(i=empty_x;i<=start_x;i++)
				{
					if(i == start_x)
						puzzle[i][start_y] = -1;
					else
						puzzle[i][start_y] = puzzle[i+1][empty_y];
				}
			}
			
			break;			
		}

		case down:
		
		{
			/* Detect the EMPTY square by scanning from up to down */
			for(i=start_x;i<N;i++)
			{
				if(puzzle[i][start_y] == -1)
				{
					empty_x = i;
					empty_y = start_y;
					find_flag = 1;
					break;
				}
			}

			/* Shifting the squares from empty square to start location*/
			if(find_flag==1)
			{
				for(i=empty_x;i>=start_x;i--)
				{
					if(i == start_x)
						puzzle[i][start_y] = -1;
					else
						puzzle[i][start_y] = puzzle[i-1][empty_y];
				}
			}
			break;
		}
	}

	return find_flag;
}

int solve_check(int puzzle[N][N]) /* This function checks that whether puzzle is solved */
{
	int flag = 1; /* Return variable. If flag is returned as 1, this means puzzle is solved */
	int i,j; /* Loop */
	int ct = 1; /* Puzzle must be ordered from 1. */

	/* Checking */
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			if(puzzle[i][j]==-1)
				continue;

			if(puzzle[i][j]==ct)
				ct++;

			else
			{
				flag=0;
			}
		}
	}

	return flag;
}


void fill_puzzleRandomly(int puzzle[N][N])
{
	int ct = 1; /* Puzzle must be start from 1 */
	int rand_x; /* Random row */
	int rand_y; /* Random column */
	int rand_move; /* Random movement -*/
	int i,j = 0,k; /* Loop */
	move movement;

	/* Initiliaze the puzzle in correct order */
	for(i=0;i<N;i++)
	{
		for(k=0;k<N;k++)
		{
			/* Make right bottom -1 */
			if(i==N-1 && k==N-1)
			{
				puzzle[i][k] = -1;
				break;
			}

			puzzle[i][k] = ct;
			ct++;
		}
	}

	/* Shuffle the puzzle 700 move */
	while(j<700)
	{
		rand_x = (rand() % (N));
		rand_y = (rand() % (N));
		rand_move = (rand() % 4) +1;
		movement = rand_move;
		if (play_puzzle(puzzle, rand_x, rand_y, movement))
			j++;
	}
}



int main()
{	
	int i,j; /* Loop */
	int puzzle[N][N]; /* 2D Game puzzle */
	int user_choice_x; /* User's row choice */
	int user_choice_y; /* User's column choice */
	int user_movement; /* User's movement choice */
	move user_choice_move; /* User's movement choice */

	fill_puzzleRandomly(puzzle); /** fill the puzzle randomly */

	do
	{
		print_puzzle(puzzle);
		printf("\nEnter row of starting point: ");
		scanf("%d",&user_choice_x);
		printf("Enter column of starting point: ");
		scanf("%d",&user_choice_y);
		printf("1.Left\n2.Right\n3.Up\n4.Down\n5.TERMINATE THE PROGRAM\nPlease select your movement: ");
		scanf("%d",&user_movement);
		user_choice_move = user_movement;

		/* Input checking */
		if(user_choice_x>N-1 ||  user_choice_x<0 || user_choice_y>N-1 || user_choice_y<0 || user_movement<1 || user_movement>5)
		{
			printf("\nPLEASE ENTER VALID VALUES.\n");
			continue;
		}

		if(user_movement==5)
			return 1;

		if(play_puzzle(puzzle, user_choice_x, user_choice_y, user_choice_move) == 1)
		{
			if(solve_check(puzzle) == 1)
			{
				print_puzzle(puzzle);
				printf("\nCongratulations! You did it!\n");
				return 1;
			}
		}
		else
			printf("\n\nWARNING WARNING -> Your movement was wrong. Try again <- WARNING WARNING.\n");
	}
	while(1);


}	
