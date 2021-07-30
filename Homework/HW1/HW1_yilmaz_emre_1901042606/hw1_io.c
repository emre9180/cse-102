/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>
#include "hw1_io.h"


void write_polynomial3(double a0, double a1, double a2, double a3) /* assumed that 'a0' is the coefficient of x^3 term */
{
   
   /* Third Degree Term of Polynom (ax^3) */
   if (a0==1) printf("x^3");
   else if(a0==-1) printf("-x^3");
   else if (a0!=0) printf("%.6gx^3",a0); 

   /* Second Degree Term of Polynom (bx^2) */
   if (a0==0 && a1!=0)
   {	/* This condition above checks that this is the first term to be printed. We do not want to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		if (a1==1) printf("x^2");
   		else if(a1==-1) printf("-x^2");
   		else if (a1!=0) printf("%.6gx^2",a1); 
   }
   else if (a1==1) printf("+x^2");
   else if (a1==-1) printf("-x^2");
   else if (a1!=0) printf("%+.6gx^2",a1); /* %+ means printing the positive number with + sign */

   /* First Degree Term of Polynom (cx) */
   if (a0==0 && a1==0 && a2!=0)
   {	/* This condition above checks that this is the first term to be printed not to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		if (a2==1) printf("x");
   		else if(a2==-1) printf("-x");
   		else if (a2!=0) printf("%.6gx",a2);
   }
   else if (a2==1) printf("+x");
   else if (a2==-1) printf("-x");
   else if (a2!=0) printf("%+.6gx",a2);

   /* Constant Term of Polynom (d) */
   if (a0==0 && a1==0 && a2==0 && a3!=0)
   {	
   		printf("%.6g",a3);
   }
   else if(a3!=0) printf("%+.6g",a3);

   printf("\n");

}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4) /* assumed that 'a0' is the coefficient of x^4 term */
{
   
   /* Fourth Degree Term of Polynom (ax^4) */
   if (a0==1) printf("x^4");
   else if(a0==-1) printf("-x^4");
   else if (a0!=0) printf("%.6gx^4",a0); 

   /* Third Degree Term of Polynom (bx^3) */
   if (a0==0 && a1!=0)
   {	/* This condition above checks that this is the first term to be printed not to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		if (a1==1) printf("x^3");
   		else if(a1==-1) printf("-x^3");
   		else if (a1!=0) printf("%.6gx^3",a1); 
   }
   else if (a1==1) printf("+x^3");
   else if (a1==-1) printf("-x^3");
   else if (a1!=0) printf("%+.6gx^3",a1); /* %+ means printing the positive number with + sign */ 

   /* Second Degree Term of Polynom (cx^2) */
   if (a0==0 && a1==0 && a2!=0)
   {	/* This condition above checks that this is the first term to be printed not to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		if (a2==1) printf("x^2");
   		else if(a2==-1) printf("-x^2");
   		else if (a2!=0) printf("%.6gx^2",a2);
   }
   else if (a2==1) printf("+x^2");
   else if (a2==-1) printf("-x^2");
   else if (a2!=0) printf("%+.6gx^2",a2);

   /* First Degree Term of Polynom (dx) */
   if (a0==0 && a1==0 && a2==0 && a3!=0)
   {	/* This condition above checks that this is the first term to be printed not to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		if (a3==1) printf("x");
   		else if(a3==-1) printf("-x");
   		else if (a3!=0) printf("%.6gx",a3);
   }
   else if (a3==1) printf("+x");
   else if (a3==-1) printf("-x");
   else if (a3!=0) printf("%+.6gx",a3);

   /* Constant Term of Polynom (e) */
   if (a0==0 && a1==0 && a2==0 && a3==0 && a4!=0)
   {	/* This condition above checks that this is the first term to be printed not to start with '+' sign. e.g we do not want to print (+x^2 + x + 5) */
   		printf("%.6g",a4);
   }
   else if (a4!=0) printf("%+.6g",a4);

   printf("\n");
}
