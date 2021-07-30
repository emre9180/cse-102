/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include "hw8_lib.h"




void test_clean_file () 
{
	char clean_filde[20] = "input.txt";
	char output_file[20] ="output.txt";
	char *clean[2] = {"selam","emre"};

	

	clean_file(clean_filde,output_file,clean,2);
}


void test_maze_move ()
{
	int i,j;
	

	cell_type maze[8][8] =
	{
		{cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall},
		{cell_wall, cell_free, cell_free, cell_free, cell_wall, cell_free, cell_target, cell_wall},
		{cell_wall, cell_free, cell_wall, cell_free, cell_wall, cell_p2, cell_wall, cell_wall},
		{cell_wall, cell_free, cell_wall, cell_free, cell_wall, cell_free, cell_free, cell_wall},
		{cell_wall, cell_free, cell_wall, cell_free, cell_p1, cell_wall, cell_free, cell_wall},
		{cell_wall, cell_free, cell_wall, cell_wall, cell_free, cell_wall, cell_free, cell_wall},
		{cell_wall, cell_free, cell_free, cell_free, cell_free, cell_free, cell_free, cell_wall},
		{cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall, cell_wall}
	};

	maze_move(maze,cell_p1,move_left);

	
}


void test_towers_of_hanoi ()
{

	towers_of_hanoi('A','C','B',3);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
