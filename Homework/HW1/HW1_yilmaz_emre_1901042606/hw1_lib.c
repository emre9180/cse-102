/* Emre YILMAZ - 1901042606 - Gebze Technical University */

/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include "hw1_lib.h"


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta) /* assumed that 'a0' is the coefficient of x^3 term */
{
	/* Trepozoid Rule Integration Formula => (delta/2) * [(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] */

    double sum_of_functionx = 0; /* This is the sum of the expression ([(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] in formula  */
    double x = xs; /* x is starting from xs and it goes to xe. */
    double result; /* return variable */
    while(x<=xe)
    {
    	sum_of_functionx += (2*((a0*(x*x*x)) + (a1*(x*x)) + (a2*x) + a3)); 
    	x += delta;
    }

    /* We need this subtraction belove since the first and the last terms (xs and xe)
   	   which should not be multiplied by 2 according to the formula, are multiplied by 2 in the loop above. */
    sum_of_functionx -= ((a0*(xs*xs*xs)) + (a1*(xs*xs)) + (a2*xs) + a3) + ((a0*(xe*xe*xe)) + (a1*(xe*xe)) + (a2*xe) + a3);

    result = (delta/2) * sum_of_functionx;
    return result;

}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta) /* assumed that 'a0' is the coefficient of x^4 term */
{
    /* Trepozoid Rule Integration Formula => (delta/2) * [(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] */

    double sum_of_functionx = 0; /* This is the sum of the expression ([(f(x0) + 2f(x1) + 2f(x2) + 2f(x3) ...... f(xn))] in formula.  */
    double x = xs; /* x is starting from xs and it goes to xe. */
    double result; /* return variable */
    while(x<=xe)
    { 
    	sum_of_functionx += (2*((a0*(x*x*x*x)) + (a1*(x*x*x)) + (a2*(x*x)) + (a3*x) + a4));
    	x += delta;
    }
    
    /* We need this subtraction belove since the first and the last terms (xs and xe)
   	   which should not be multiplied by 2 according to the formula, are multiplied by 2 in the loop above. */
    sum_of_functionx -= ((a0*(xs*xs*xs*xs)) + (a1*(xs*xs*xs)) + (a2*(xs*xs)) + (a3*xs) + a4) + ((a0*(xe*xe*xe*xe)) + (a1*(xe*xe*xe)) + (a2*(xe*xe)) + (a3*xe) + a4); 

    result = (delta/2) * sum_of_functionx;
    return result;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe) /* assumed that 'a0' is the coefficient of x^3 term */
{
    double ct_x = xs; /* it will start to try from 'xs' to 'xe' */
    double increaser = 0.0001; /* it will increase the variable ct_x. For more sensitive root finding, please decrease the value of this variable */
    double sum; /* result of polynom f(ct_x) */

    while(ct_x <= xe)
    {
    	sum = ((a0 * (ct_x*ct_x*ct_x)) + (a1* (ct_x*ct_x)) + (ct_x * a2) + a3);
    	if (sum <= 0.000001 && sum>= -0.000001) return ct_x; /* if we close enough to 0, we can say we have found the root. */
    	ct_x += increaser;
    }
}

double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe) /* assumed that 'a0' is the coefficient of x^4 term */
{
    double ct_x = xs; /* it will start to try from 'xs' to 'xe' */
    double increaser = 0.0001; /* it will increase the variable ct_x.  For more sensitive root finding, please decrease the value of this variable */
    double sum; /* result of polynom f(ct_x) */

    while(ct_x <= xe)
    {
    	sum = (a0 * (ct_x*ct_x*ct_x*ct_x)) + (a1* (ct_x*ct_x*ct_x)) + (a2 * (ct_x * ct_x)) + (a3*ct_x) + (a4); 
    	if (sum <= 0.000001 && sum>= -0.000001) return ct_x; /* if we close enough to 0, we can say we have found the root. */
    	ct_x += increaser;
    }
}
