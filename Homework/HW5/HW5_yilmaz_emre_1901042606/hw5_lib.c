/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include "hw5_lib.h"
#include <math.h>


void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	/*															WARNING		 														 */
	/* Output format is assumed as a3 variable is 7th degree term, a2 variable is 6th degree term.... b0 variable is 0th degree term */
	/*															WARNING		 														 */


	/*These variables belove declared to keep the coeffecients in MULTIPLICATION CALCULATION 
	  These variables only used in Multiplication Calculation */
	double sixthdegree;
	double fifthdegree;
	double fourthdegree;
	double thirddegree;
	double seconddegree;
	double firstdegree;
	double constterm;

	if(op=='+')
	{
		/* Implementing addition */
		*b3 = *a3 + *b3;
		*b2 = *a2 + *b2;
		*b1 = *a1 + *b1;
		*b0 = *a0 + *b0;

		/* Make the coefficients that greater than 3th degree, ZERO */
		*a3 = 0; 
		*a2 = 0;
		*a1 = 0;
		*a0 = 0;
	}

	else if(op=='-')
	{
		/* Implementing substraction */
		*b3 = *a3 - *b3;
		*b2 = *a2 - *b2;
		*b1 = *a1 - *b1;
		*b0 = *a0 - *b0;

		/* Make the coefficients that greater than 3th degree, ZERO */
		*a3 = 0; 
		*a2 = 0;
		*a1 = 0;
		*a0 = 0;
	}

	else if(op=='*')
	{		
		/* Implementing multiplication */
		sixthdegree = (*a3) * (*b3);
		fifthdegree = (*a3 * (*b2)) + (*a2 * (*b3));
		fourthdegree = (*a3 * (*b1)) + (*b3 * (*a1)) + (*a2 * *b2);
		thirddegree = ((*a3) * (*b0)) + ((*b3) * (*a0)) + ((*a2) * (*b1)) + ((*b2) * (*a1));
		seconddegree = (*a2 * (*b0)) + (*b2 * (*a0)) + ((*a1) * (*b1));
		firstdegree = (*a1 * *b0) + (*b1 * *a0);
		constterm = *a0 * (*b0);

		/* Assign the result to our variables */
		*a2 = sixthdegree;
		*a1 = fifthdegree;
		*a0 = fourthdegree;
		*b3 = thirddegree;
		*b2 = seconddegree;
		*b1 = firstdegree;
		*b0 = constterm;

		/* make the coefficients that greater than 6th degree ZERO */
		*a3 = 0; 

	}

	else
	{
		printf("\nYour entry is INVALID.\n");
	}

	return;
}


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	int i;
	double sum_a0 = 0; /* sum of N Vector's a0 dimensions */
	double sum_a1 = 0; /* sum of N Vector's a1 dimensions */
	double sum_a2 = 0; /* sum of N Vector's a2 dimensions */
	double sum_a3 = 0; /* sum of N Vector's a3 dimensions */

	/* This variables keep the values of previous vector */
	double prev_a0;
	double prev_a1;
	double prev_a2;
	double prev_a3;

	/* This variables keep the values of vector's that user just have entered */
	double a0;
	double a1;
	double a2;
	double a3;

	double d0, d1, d2, d3, euclidian_distance;
	double max_distance = -1; /* Maximum distance, initilized as -1 */

	for(i=0;i<N;i++)
	{		
		printf("\nEnter a0 of your %d.Vector4D: ",i+1);
		scanf("%lf",&a0);
		printf("Enter a1 of your %d.Vector4D: ",i+1);
		scanf("%lf",&a1);
		printf("Enter a2 of your %d.Vector4D: ",i+1);
		scanf("%lf",&a2);
		printf("Enter a3 of your %d.Vector4D: ",i+1);
		scanf("%lf",&a3);

		/* Loop breaker option for user */
		if(a0==-1 && a1==-1 && a2==-1 && a3==-1)
		{
			N = i; /* Update total vector number */
			break;
		}

		/* Adding the values to sum variables */
		sum_a0 += a0;
		sum_a1 += a1; 
		sum_a2 += a2; 
		sum_a3 += a3; 
		
		
		/* ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

		if(i==0) /*  If we are getting first input, we do NOT need a distance calculation. */
		{
			/* Make the new inputs > previous inputs */
			prev_a3 = a3;
			prev_a2 = a2;
			prev_a1 = a1;
			prev_a0 = a0;
		}

		else /* If we are NOT getting first input, we need distance calculation */
		{
			/* Calculating distance and checking that if the distance is maximum */
			distance_between_4d_points(a0-prev_a0,a1-prev_a1,a2-prev_a2,a3-prev_a3,&euclidian_distance);
			
			if(euclidian_distance>max_distance)
				max_distance=euclidian_distance;

			/* Make the new inputs > previous inputs */
			prev_a3 = a3;
			prev_a2 = a2;
			prev_a1 = a1;
			prev_a0 = a0;
		}
	}

	/* Calculating and assigning means */
	*mean_a0 = sum_a0/N;
	*mean_a1 = sum_a1/N;
	*mean_a2 = sum_a2/N;
	*mean_a3 = sum_a3/N;

	/* Assigning maximum distance */
	*longest_distance = euclidian_distance;
	printf("\n");
}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
    *euclidian_distance = sqrt(d0*d0 + d1*d1 + d2*d2 + d3*d3);
}


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int initial_A = *partyA;
	int initial_B = *partyB;
	int initial_C = *partyC;
	int initial_D = *partyD;
	int initial_E = *partyE;
	/* This variables keep number of seats of parties */
	int Aparty_seat = 0;
	int Bparty_seat = 0;
	int Cparty_seat = 0;
	int Dparty_seat = 0;
	int Eparty_seat = 0;

	int maxParty; /* The party that get max. vote */

	while(numberOfSeats>=0)
	{
		if(*partyA>=*partyB && *partyA>=*partyC && *partyA>=*partyD && *partyA>=*partyE) /* If the A Party gets the maximum vote */
		{
			Aparty_seat++; /* Increase the seat number of A Party */
			*partyA = initial_A / (Aparty_seat+1);
		}

		else if(*partyB>=*partyA && *partyB>=*partyC && *partyB>=*partyD && *partyB>=*partyE) /* If the B Party gets the maximum vote */
		{
			Bparty_seat++; /* Increase the seat number of B Party */
			*partyB = initial_B / (Bparty_seat+1);
		}

		else if(*partyC>=*partyA && *partyC>=*partyB && *partyC>=*partyD && *partyC>=*partyE) /* If the C Party gets the maximum vote */
		{
			Cparty_seat++; /* Increase the seat number of C Party */
			*partyC = initial_C / (Cparty_seat+1);
		}

		else if(*partyD>=*partyA && *partyD>=*partyB && *partyD>=*partyC && *partyD>=*partyE) /* If the D Party gets the maximum vote */
		{
			Dparty_seat++; /* Increase the seat number of D Party */
			*partyD = initial_D / (Dparty_seat+1);
		}

		else if(*partyE>=*partyA && *partyE>=*partyB && *partyE>=*partyC && *partyE>=*partyD) /* If the E Party gets the maximum vote */
		{
			Eparty_seat++; /* Increase the seat number of E Party */
			*partyE = initial_E / (Eparty_seat+1);
		}

		numberOfSeats--;
	}

	*partyA = Aparty_seat;
	*partyB = Bparty_seat;
	*partyC = Cparty_seat;
	*partyD = Dparty_seat;
	*partyE = Eparty_seat;
}


double integral(double xend) 
{
	/* Expression of arc functions as INTEGRAL is used to calculate angle, expresion: https://hizliresim.com/LdGsSx */ 
	/* -------------------------------------------------------------------------------------------------------------*/

    /* Trepozoid Rule Integration Formula => (delta/2) * [(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] */
	double delta = 0.00001;
    double sum_of_functionx = 0; /* This is the sum of the expression ([(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] in formula.  */
    double x = 0; /* x is starting from 0 and it goes to xend. */
    double result; /* return variable */

    if(xend<0)
		xend *= -1;

    while(x<=xend)
    { 
    	sum_of_functionx += 2*(1/((x*x)+1));
    	x += delta;
    }
    
    /* We need this subtraction belove since the first and the last terms
   	   which should not be multiplied by 2 according to the formula, are multiplied by 2 in the loop above. */
    sum_of_functionx -=  2* (1/((x*x)+1));

    result = (delta/2) * sum_of_functionx;
    return result;
}

void find_angle(double x, double y, double *angle) /* gets the slope of point, and return the angle counter-clockwise */
{
	double slope; /*( y/x )*/
	int region; /* regions in the Cartesian Coordinate System */
	double angle_radian; /* angle in Radians */

	/* Finding the region of 2D points */
	if(x>=0 && y>=0)
		region=1;

	else if(x>0 && y<0)
		region=4;

	else if(x<0 && y>0)
		region=2;

	else if(x<=0 && y<=0)
		region=3;


	/* If the point is on the Y-axis */
	if(x==0)
		*angle=90;
	/* */
	else
	{
		slope = y/x;
		angle_radian = integral(slope); /* Finding angle of point with arctan function as integral calculation with trepozoid method */
	}
		
	*angle = angle_radian * (180/3.14); /* Convert the radian to degree */
	
	/* Update angles acording to their regions in the Cartesian Coordinate System */
	if(region==2)
		*angle = 180 - *angle;
	else if(region==3)
		*angle = 180 + *angle;
	else if(region==4)
		*angle = 360 - *angle;
}

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	double temp; /* Declared to keep temporary double variables */
	double slope1,slope2,slope3; /* Slopes of 2D points */
	double angle1,angle2,angle3; /* Angle of 2D points */

	/* Finding angles of 2D first point and second point */
	find_angle(*x1,*y1,&angle1); 
	find_angle(*x2,*y2,&angle2);

	/* Order the first point and second point in counter-clockwise */
	if(angle2<angle1)
	{
		temp = *x1;
		*x1 = *x2;
		*x2 = temp;

		temp = *y1;
		*y1 = *y2;
		*y2 = temp;

		temp = angle2;
		angle2 = angle1;
		angle1 = temp;
	}
	
	/* Find angles of third point */
	find_angle(*x3,*y3,&angle3);

	if(angle3<angle1)
	{
		temp = *x1;
		*x1 = *x3;
		*x3 = temp;

		temp = *y1;
		*y1 = *y3;
		*y3 = temp;

		temp = angle3;
		angle3 = angle1;
		angle1 = temp;
	}

	if(angle3<angle2)
	{
		temp = *x2;
		*x2 = *x3;
		*x3 = temp;

		temp = *y2;
		*y2 = *y3;
		*y3 = temp;

		temp = angle3;
		angle3 = angle2;
		angle2 = temp;
	}

}


void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
}


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	int i; /* loop variable */
	int remaining; /* The remainder of the division with 2 */
	int ct = 0; /* Bit counter */
	int copy_number = number;

	/* Make the bits 0 */
	*b7=0;
	*b6=0;
	*b5=0;
	*b4=0;
	*b3=0;
	*b2=0;
	*b1=0;
	*b0=0;

	/* Calculating and assigning bits */
	for(i=0;i<8;i++)
	{
		/* Calculate bit value */
		if (copy_number%2 == 1)
			remaining = 1;
		else
			remaining = 0;

		/* Assigning the bits to bit-ct */
		if(ct==0)
			*b0 = remaining;

		else if(ct==1)
			*b1 = remaining;

		else if(ct==2)
			*b2 = remaining;

		else if(ct==3)
			*b3 = remaining;

		else if(ct==4)
			*b4 = remaining;

		else if(ct==5)
			*b5 = remaining;

		else if(ct==6)
			*b6 = remaining;

		else if(ct==7)
			*b7 == remaining;

		copy_number /= 2;

		if(copy_number<1)
			break;

		ct++;
	}
}


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	/* Temporary char variables to shift and change process */
	char temp;
	char temp_b7;
	char temp_b6;
	char temp_b5;
	char temp_b4;
	char temp_b3;
	char temp_b2;
	char temp_b1;
	char temp_b0;

	/* Constructs a new number according to the algorithm in the PDF */
	temp = b7;
	b7 = b2;
	b2 = temp;

	temp = b6;
	b6 = b3;
	b3 = temp;

	temp = b5;
	b5 = b0;
	b0 = temp;

	temp = b4;
	b4 = b1;
	b1 = temp;

	/*Assigning new character variables to temp variables */
	temp_b7 = b7;
	temp_b6 = b6;
	temp_b5 = b5;
	temp_b4 = b4;
	temp_b3 = b3;
	temp_b2 = b2;
	temp_b1 = b1;
	temp_b0 = b0;

	/* Shifting */
	b7 = temp_b5;
	b6 = temp_b4;
	b5 = temp_b3;
	b4 = temp_b2;
	b3 = temp_b1;
	b2 = temp_b0;
	b1 = temp_b7;
	b0 = temp_b6;

	/* Converting Binary to Decimal */
	*number = 0;

	if(b7==1)
		*number += 128;

	if(b6==1)
		*number += 64;

	if(b5==1)
		*number += 32;

	if(b4==1)
		*number += 16;

	if(b3==1)
		*number += 8;

	if(b2==1)
		*number += 4;

	if(b1==1)
		*number += 2;

	if(b0==1)
		*number += 1;
}
