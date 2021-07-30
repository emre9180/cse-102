/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	int i,k; /* Loop */
	char garbage; /* For cleaning */
	char operator;
	double a3,a2,a1,a0,b3,b2,b1,b0; /* Coefficients */
	double input; /* Coefficient input to assign variables above 1 line */
	char degree; /* /* This variable represents the degree of the term in which we will write the coefficients. */

	/* Getting first polynomial from user*/
	printf("Enter your coefficients of FIRST polynomial:\n");
	for(i=0;i<4;i++)
	{
		scanf("(%c, %lf), ",&degree,&input);
		switch(degree)
		{
			case '3':
				a3 = input;
				break;
			case '2':
				a2 = input;
				break;
			case '1':
				a1 = input;
				break;
			case '0':
				a0 = input;
				break;
			default:/* When the input is wrong */
				{
					/* Clean the inputs and ask for CORRECT inputs */
					printf("Please enter your polynom in correct format: (3, a), (2, b), (1, c), (0, d)\n");
					
					/* Cleaning */
					for(k=i+1;k<4;k++)
						{
							scanf("(%c, %lf), ",&degree,&input);
						}
					garbage = getchar(); /* cleaning */
					printf("\n");
					test_operate_polynomials(); /* Call the function again, to get correct inputs */
					return;
				}
		}
	}   
	 
	garbage = getchar(); /* cleaning enter */

	/* Getting second polynomial from user*/
	printf("Enter your coefficients of SECOND polynomial:\n");
	for(i=0;i<4;i++)
	{
		scanf("(%c, %lf), ",&degree,&input);
		switch(degree)
		{
			case '3':
				b3 = input;
				break;
			case '2':
				b2 = input;
				break;
			case '1':
				b1 = input;
				break;
			case '0':
				b0 = input;
				break;
			default:/* When the input is wrong */
			{
				/* Clean the inputs and ask for CORRECT inputs */
				printf("Please enter your polynom in correct format: (3, a), (2, b), (1, c), (0, d)\n");
				
				/* Cleaning */
				for(k=i+1;k<4;k++)
					{
						scanf("(%c, %lf), ",&degree,&input);
					}
				garbage = getchar(); /* cleaning */
				printf("\n");
				test_operate_polynomials(); /* Call the function again, to get correct inputs */
				return;
			}
		}
	}

	/* Getting operator from user */
	while(1)
	{
		printf("Enter your operator: ");
		scanf(" %c",&operator);
		if (operator!='-' && operator!='*' && operator!='+')
			printf("WARNING < PLEASE ENTER A VALID OPERATOR > WARNING\n");
		else
			break;
	}
	
	operate_polynomials(&a3, &a2, &a1, &a0, &b3, &b2, &b1, &b0,operator);
	printf("\n6th degree term: %f\n5th degree term: %f\n4th degree term: %f\n3rd degree term: %f\n2nd degree term: %f\n1st degree term: %f\n0th degree term: %f\n\n",a2,a1,a0,b3,b2,b1,b0);
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
