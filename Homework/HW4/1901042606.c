/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>
#include <math.h>

int if_palindrom(int number) /* this function checks that number is 'palindrom' number or not */
{
	int sum = 0;
	int temp_number = number;
	int digit_number = 0;

	while(temp_number>=1) /* finding digit number of 'number' variable */
	{
		digit_number++;
		temp_number = temp_number/10;
	}

	temp_number = number;

	while(temp_number>=1) /* we REVERSE the number according to its digits */
	{
		sum+= temp_number%10 * (pow(10,digit_number-1));
		temp_number = temp_number/10;
		digit_number--;
	}

	if(sum==number) /* if our number is the same as REVERSED number */
		return 1;
	else
		return 0;
}

void armstrong_number()
{
	int number; /* the number that user will enter */
	int sum = 0; /* sum of cubes of 'number's digits  */
	int temp_number; /* temporary  variable of 'number' to make calculations without loosing 'number' */
	int armstrong_flag = 0; /* if the number is armstrong number, this flag will be 1 */
	int palindrom_flag = 0; /* if the number is palindrom number, this flag will be 1 */

	while(1) /* getting input until user enters a correct input */
	{
		printf("Please enter a positive integer: ");
		scanf("%d",&number);

		if(number<0) /* if number is negative we must get new input that is positive */
		{
			printf("ERROR -> Please enter a positive number.\n\n");
			continue;
		}

		else
		{
			temp_number = number;
			break;
		}
		
	}
	


	while(temp_number>=1) /* checking that if the 'number' is armstrong number */
	{
		sum += pow(temp_number%10,3);
		temp_number = temp_number/10;
	}

	if (sum == number)
		armstrong_flag = 1;

	palindrom_flag = if_palindrom(number); /* checking that if the 'number' is palindrom number */

	if (palindrom_flag==1 && armstrong_flag==1)
		printf("Your number %d is both Palindrom and Armstong number.\n\n",number);

	else if (palindrom_flag==1 && armstrong_flag==0)
		printf("Your number %d is only Palindrom number.\n\n",number);

	else if (palindrom_flag==0 && armstrong_flag==1)
		printf("Your number %d is only Armstrong number.\n\n",number);

	else if (palindrom_flag==0 && armstrong_flag==0)
		printf("Your number %d does not satisfy any special cases\n\n",number);


}


int if_prime(int number) /* this function checks that number is prime or not */
{
	int i; /* loop */
	int prime_flag = 1; /* if the number is NOT prime number, flag will be 0 */

	for(i=2;i<number;i++) /* this loop is checking whether 'number' variable has a divisor. if it has, then we say 'number' is NOT prime number */
	{
		if (number%i == 0)
			prime_flag = 0;
	}

	return prime_flag;
}

void sum_prime()
{
	int number1; /* first number that user will enter */
	int number2; /* second number that user will enter */
	int sum = 0; /* sum of prime numbers between number1 and number2 */
	int i; /* loop */

	while(1)
	{
		printf("Please enter first positive integer number: ");
		scanf("%d",&number1);
		printf("Please enter second positive integer number: ");
		scanf("%d",&number2);

		if (number1<0 || number2<0)
		{
			printf("ERROR -> Your integers MUST be POSITIVE. Please enter new numbers!\n\n");
			continue;
		}
		if(number2<number1) /* first integer number must greater than  second integer */
		{
			printf("ERROR -> Your first integer number MUST greater than your second integer number. Please enter new numbers!\n\n");
			continue;
		}

		else
			break;

	}
	

	for(i=number1+1;i<number2;i++) /* find the prime numbers and add them to 'sum' variable */
	{
		if (i<=1) /* there is NO prime number until 2 */
			continue;
			
		else
		{
			if (if_prime(i) == 1)
			sum+=i;
		}
		
	}

	printf("Sum of prime numbers between %d and %d is: %d\n\n",number1,number2,sum);

}


void polynom()
{
	float inputs; /* coeffeciant inputs */
	int degree; /* degree input */
	int degree_ct = 0;

	printf("Enter your polynomial [n a_n a_n-1 a_n-2 ... a_0]: ");
	scanf("%d",&degree); /* getting degree input */
	degree_ct = degree;

	while(degree_ct>=0)
	{
		scanf("%f",&inputs);

		if(degree_ct==degree) /* we will check the rule that largest coefficient that user entered can not be smaller than polynom degree */
		{

			if(inputs==0) /* largest coefficient that user entered can not be smaller than polynom degree */
			{
				printf("\nLargest coefficient you entered does not match your polynomial degree. Please enter new input.\n\n");
				degree_ct--;

				while(degree_ct>=0) /* cleaning inputs */
				{
					scanf("%f",&inputs);
					degree_ct--;
				}

				polynom();
				return;
			}
			
		}

		if (degree_ct==1) /* printing bx term (first degree term) */
		{
			if(inputs==0); /* do nothing */

			else if(inputs==1 && degree_ct!=degree) /* if the coefficient is 1, and we are NOT printing the first term */
				printf("+x");

			else if(inputs==1 && degree_ct==degree) /* if the coefficient is 1, and we are printing the first term.  We must not print the sign */
				printf("x");
 
			else if(inputs==-1) /* if the coefficient is -1 */
				printf("-x");

			else if (degree_ct!=degree) /* if we are NOT printing the first term */
				printf("%+.1fx",inputs);

			else if (degree_ct==degree) /* if we are printing the first term */
				printf("%.1fx",inputs);
		}

		else if (degree_ct==0) /* printing constant term */
		{
			if(inputs==0);

			else if(degree_ct!=degree) /* if we are NOT printing the first term */
				printf("%+.1f",inputs);

			else
				printf("%.1f",inputs);
		}

		else /* printing other degree terms  */
		{
			if(inputs==0);

			else if(inputs==1 && degree_ct==degree) /* if the coefficient is 1, and we are printing the first term. We must not print the sign */
				printf("x^%d",degree_ct);

			else if(inputs==1 && degree_ct!=degree) /* if the coefficient is 1, and we are NOT printing the first term */
				printf("+x^%d",degree_ct);

			else if(inputs==-1) /* if the coefficient is -1 */
				printf("-x^%d",degree_ct);

			else if (degree_ct!=degree) /* if we are NOT printing the first term */
				printf("%+.1fx^%d",inputs,degree_ct);

			else if (degree_ct==degree)
				printf("%.1fx^%d",inputs,degree_ct);
		}

		degree_ct--;
		

	}

}


int main()
{	printf("\t\t\tPART-1\n\n");
	polynom();
	printf("\n\n\t\t\tPART-2\n\n");
	armstrong_number();
	printf("\t\t\tPART-3\n\n");
	sum_prime();
	

}
