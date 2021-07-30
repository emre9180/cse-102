/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include "hw2_lib.h"
#include <math.h> /* sqrt function and trigonometric functions is used in this program */

/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.11.15.45
** 
*/


int find_weekday_of_data (int day, int month, int year)
{
	/* Base date is 01.01.0001*/
	int base_year = 1;
	int base_day = 1; /* When we calculate 1th January 0001 mathematically, we see that it is Monday  */
	
	int total_day = 0; /* Days between user's date and base date */
	int i; /* for loops*/
	int mod_of_totalDay = 0; 
	int result = 0;


	/* Checking that if the date is valid or invalid */

	if (year<0 || day<0)
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (day>29 && month==2)
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (day>28 && month==2 && !((year%100!=0 && year%4==0) || (year%100==0 && year%400==0 && year%4000!=0)))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (day>30 && ((month==4 || month==6 || month==9 || month==11)))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (day>31)
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if(month>12 || month<1)
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

																		/* Checking is over */

	/* ---------------------------------------------------------------If the date is valid, go on >------------------------------------------------------------------------------------------*/

	 
	/* Adding the days in the 'year' starting from user's 'month' to January */

	total_day += day; /* Adding the days in the 'month' user entered */

	
	for (i=(month)-1;i!=0;i--)
	{
		if (i==2)
		{	
			if ((year%100!=0 && year%4==0) || (year%100==0 && year%400==0 && year%4000!=0)) /* leap year check */
				total_day += 29;
			else
				total_day += 28;
		}

		else if (i==1 || i==3 || i==5 || i==7 || i==8 || i==10 || i==12)
			total_day += 31;
		else
			total_day += 30;
	}

	/* Adding the days in the years starting from 'user's year - 1', to 'base date' */
	for(i=base_year;i!=year;i++)
	{
		if ((i%100!=0 && i%4==0) || (i%100==0 && i%400==0 && i%4000!=0)) /* leap year check */
			total_day += 366;
		else
			total_day += 365;
	}

	total_day -= 1; /* Subtract the 'base date' from the 'total day'  */

	mod_of_totalDay = total_day % 7;
	result = base_day + mod_of_totalDay;
	result = result%7;
	if (result==0) 
		return 7;
	else
		return result;
}



/* Calculations in this function were made excluding the END day, including the START day =>>>>>>>> */
int count_day_between_dates (int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
	int total_day = 0;
	int i,k;


	/* Checking that if the date is valid or invalid */

	if (start_year<0 || start_day<0 || end_year<0 || end_day<0)
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if ((start_day>29 && start_month==2) || (end_day>29 && end_month==2))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (start_day>28 && start_month==2 && !((start_year%100!=0 && start_year%4==0) || (start_year%100==0 && start_year%400==0 && start_year%4000!=0))
		|| (end_day>28 && end_month==2 && !((end_year%100!=0 && end_year%4==0) || (end_year%100==0 && end_year%400==0 && end_year%4000!=0))))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (start_day>30 && ((start_month==4 || start_month==6 || start_month==9 || start_month==11))
		|| (end_day>30 && ((end_month==4 || end_month==6 || end_month==9 || end_month==11))))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if (start_day>31 || (end_day>31))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	else if((start_month>12 || start_month<1) || (end_month>12 || end_month<1))
	{
		printf("\nYOUR DATE IS INVALID!\n");
		return -1;
	}

	/* Checking is over */

	
	if (start_year==end_year) /* The condition that the start and end years entered by the user are the same */
	{
		if(start_month==end_month) /* The condition that both start and end years and start and end months are the same */
		{				
			total_day += (end_day - start_day);
			return total_day;
		}

		else /* The condition that only the start and end years entered by the user are the same */
		{			
			total_day += end_day;

			/* Adding the days in the start month */
			if (start_month==2)
			{
				if ((start_year%100!=0 && start_year%4==0) || (start_year%100==0 && start_year%400==0 && start_year%4000!=0))
					total_day += 29 - start_day;
				else
					total_day += 28 - start_day;
			}
	
			else if (start_month==1 || start_month==3 || start_month==5 || start_month==7 || start_month==8 || start_month==10 || start_month==12)
				total_day += 31 - start_day;
			else
				total_day += 30 - start_day;

			/* Adding the days between 'start month + 1' and  'end month' - 1 */
			for(k=start_month+1;k<end_month;k++)
			{
				if (k==2)
				{
					if ((start_year%100!=0 && start_year%4==0) || (start_year%100==0 && start_year%400==0 && start_year%4000!=0))
						total_day += 29;
					else
						total_day += 28;
				}
	
				else if (k==1 || k==3 || k==5 || k==7 || k==8 || k==10 || k==12)
					total_day += 31;
				else
					total_day += 30;
			}
		}
		
	}

	
	else /* The condition that start year and year are different */
	{
		total_day += end_day; /* Adding the days in the 'end month' user entered to 'total days*/

		/* Adding the days in the 'start month' user entered to 'total days' */
		if (start_month==2)
		{
			if ((start_year%100!=0 && start_year%4==0) || (start_year%100==0 && start_year%400==0 && start_year%4000!=0))
				total_day += 29 - start_day;
			else
				total_day += 28 - start_day;
		}
		
		else if (start_month==1 || start_month==3 || start_month==5 || start_month==7 || start_month==8 || start_month==10 || start_month==12)
			total_day += 31 - start_day;
		else
			total_day += 30 - start_day;


		/* Adding the days in the start year to the 'total day' except the start month (since we added the days in the 'start month' already) */
		for(k=start_month+1;k<13;k++)
		{
			if (k==2)
			{
				if ((start_year%100!=0 && start_year%4==0) || (start_year%100==0 && start_year%400==0 && start_year%4000!=0))
					total_day += 29;
				else
					total_day += 28;
			}
		
				else if (k==1 || k==3 || k==5 || k==7 || k==8 || k==10 || k==12)
					total_day += 31;
				else
					total_day += 30;
		}

		/* Adding the days in the end year to the 'total day' except the end month (since we added days in the 'end month 'already) */
		for(k=end_month-1;k>0;k--)
		{
			if (k==2)
			{
				if ((end_year%100!=0 && end_year%4==0) || (end_year%100==0 && end_year%400==0 && end_year%4000!=0))
					total_day += 29;
				else
					total_day += 28;
			}
		
				else if (k==1 || k==3 || k==5 || k==7 || k==8 || k==10 || k==12)
					total_day += 31;
				else
					total_day += 30;
		}
		
		/* Adding the days between 'start year +1' and 'end year -1' */
		for (i=start_year+1;i<end_year;i++)
		{
			if ((i%100!=0 && i%4==0) || (i%100==0 && i%400==0 && i%4000!=0))
				total_day += 366;
			else
				total_day += 365;
		}
			
	}

	return total_day;
}




double find_angle(double a, double b, double c)
{
	
    double C_median; /* median of c side */
    double B_median; /* median of b side */
    double GB_side; /* the edge between G point and AC corner */
    double GC_side; /* the edge between G point and AB corner */
    double ALPHA; /* the cos(alpha) value that we calculate with cosinus theorem */
    double degree; /* converted value we calculated with the cosine theorem to degree

    /*  FORMULA => (a*a) = (GB_side * GB_side) +( GC_side * GC_side) - 2*GB_side*GC_side*cos(alpha) */
    
    C_median = sqrt(((b*b + a*a)- ((c*c)/2))/2);
    B_median = sqrt(((c*c + a*a)- ((b*b)/2))/2);
    GB_side = (B_median/3) * 2;
    GC_side = (C_median/3) * 2;
    ALPHA = ((GB_side * GB_side) + ( GC_side * GC_side) - (a*a)) / (2*GB_side*GC_side);
   /* degree = (acos(ALPHA)) * 180 / 3.14159265359; */ /* It is optional. We can see the degree value of alpha with this variable */

    return acos(ALPHA); /* we return the radian value of alpha */ 
   
}

void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
    int i;

    int digitof_r11 = 0; /* digit number of r11 */   
    int digitof_r21 = 0; /* digit number of r21 */     
    int digitof_r31 = 0; /* digit number of r31 */
 
    int digitof_r12 = 0; /* digit number of r12 */  
    int digitof_r22 = 0; /* digit number of r22 */  
    int digitof_r32 = 0; /* digit number of r32 */  

  	int row_length = 61; /* a row consists of 61 characters */

    digitof_r11 = (int)((log(r11) / (log(10))) + 1);
    digitof_r21 = (int)((log(r21) / (log(10))) + 1);
    digitof_r31 = (int)((log(r31) / (log(10))) + 1);

    digitof_r12 = (int)((log(r12) / (log(10))) + 1);
    digitof_r22 = (int)((log(r22) / (log(10))) + 1);
    digitof_r32 = (int)((log(r32) / (log(10))) + 1);


    if ((int)r11<0) /* check if the unsigned integer is sent as negative. if it is, we should show an error mesage */
    {
    	printf("\nWARNING\nWARNING\nYour r11 number is negative. It should not have been. Enter your numbers again.\n\n");
    	r11=0;
    }

    if ((int)r21<0) /* check if the unsigned integer is sent as negative. if it is, we should show an error mesage */
    {
    	printf("\nWARNING\nWARNING\nYour r21 number is negative. It should not have been. Enter your numbers again.\n\n");
    	r21=0;
    }

    if ((int)r31<0) /* check if the unsigned integer is sent as negative. if it is, we should show an error mesage */
    {
    	printf("\nWARNING\nWARNING\nYour r31 number is negative. It should not have been. Enter your numbers again.\n\n");
    	r31=0;
    }

 
    for(i=0;i<row_length;i++)
    {
    	if(i==0) 
    		printf("%s","⌜");

    	else if(i==row_length-1)
    		printf("%s\n","⌝");	  

    	else
    		printf("%c",border);	    	
    }
  
    printf("%c%12s%6c%16s%6c%15s%5c\n",'|',"Row 101",'|', "Row ABCDEFG",'|', "Row XYZ123",'|');

    printf("%c%*u%*c%c%-21.*g%c%-19d%c\n",'|',
    	(((digitof_r11-1)/2)+9),r11,
    	(8-(digitof_r11-1)/2),' ',
    	'|',
    	2+digitof_r12,r12,
    	'|',
    	r13,
    	'|');

    printf("%c%*u%*c%c%-21.*g%c%-19d%c\n",'|',
    	(((digitof_r21-1)/2)+9),r21,
    	(8-(digitof_r21-1)/2),' ',
    	'|',
    	2+digitof_r22,r22,
    	'|',
    	r23,
    	'|');

    printf("%c%*u%*c%c%-21.*g%c%-19d%c\n",'|',
    	(((digitof_r31-1)/2)+9),r31,
    	(8-(digitof_r31-1)/2),' ',
    	'|',
    	2+digitof_r32,r32,
    	'|',
    	r33,
    	'|');

    for(i=0;i<row_length;i++)
    {
    	if(i==0) 
    		printf("%s","⌞");

    	else if(i==row_length-1)
    		printf("%s\n","⌟");	  

    	else
    		printf("%c",border);	    	
    }

}

