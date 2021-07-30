/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include <stdio.h>

void calculate_fibonacci_sequence()
{
	int user_choice; /* the input */
	int num1 = 1; /*  be initiliazed as first term of fibonacci.*/
	int num2 = 1; /* be beinitiliazed as second term of fibonacci. */
	int num; /* next term to be printed of fibonacci*/
	int ct; /* counter that warns us to stop the printing fibonacci series due to reach the bound that user entered */
				    

	char check; /* it will check that if the input is '*' character or another character */

	while(1)
	{
		printf("\nEnter terms number: ");
		scanf("%d",&user_choice);

		check = getchar();

		if (check=='*') /* if user enters '*' char, we will stop */
			break;

		else if (check!='\n') /* if char that come from getchar function is NOT new line character, we can say that user entered a non-numeric thing */
			{
				printf("Please enter a numeric value.\n");
				continue;
			}


		if(user_choice<0) /* if the input number is negative, we must get a new input. */
		{
			printf("Please enter positive number.\n");
			continue;
		}

		else /* if our input is valid, then we struct the fibonacci number serie */
		{	
			if (user_choice == 1) /* if user wants to write 1 element, we only print 1 */
			{
				printf("%d",num1);
				continue;
			}

			num1 = 1; /* in the homework pdf, fibonacci serie is started from 1 */
			num2 = 1;
			ct = 2; /* starts from 2, since first 2 terms are 0 already */
			printf("%d %d ",num1,num2); /* starts to print fibonacci series with first 2 terms. */
			while (ct<user_choice)
			{
				num = num1+num2;
				printf("%d ",num);
				num1 = num2;
				num2 = num;
				ct++;
			}
		}
		
	}
}

void calculate_perfect_harmonic_number(int number)
{
	int divisor = 1; 
	int sum = 0; /* will be used for finding 'perfect number' */
	float sum2 = 0; /* will be used for finding 'harmonic number' */
	int divisor_number = 0; /* will be used for finding 'harmonic number'. it represents number of divisor that divides without remaining  */
	int harmonic_flag = 0; /* if the number is harmonic number flag will be 1, else will be 0 */
	int ct; /* will be used for finding 'harmonic number'. it represents a divisor */ 

	if(number==0) /* if the user enters 0, it means that the number is not Perfect and Harmonic */
	{
		printf("Is Perfect Number? : No\n");
		printf("Is Harmonic Divisor Number? : No\n\n");
		return;
	}


	/*---------------------------------*//*  Finding 'Perfect Number' and Printing Natural Divisors  *//*---------------------------------*/

	printf("Natural Number Divisors: ");

	while(divisor<=number) /* Decide if the number 'Perfect' number or not */
	{
		if(number==divisor) /* printing the last natural divisor */
			printf("%d\n",divisor);

		else if(number%divisor == 0)
		{
			printf("%d,",divisor); /* print a natural divisor */
			sum += divisor; /* add the natural divisor to sum */
		}

		divisor++;
	}

	if (sum==number)
		printf("Is Perfect Number? : Yes\n");
	else
		printf("Is Perfect Number? : No\n");



	/*---------------------------------*//*  Finding 'Harmonic Number'  *//*---------------------------------*/

	divisor=1; /* divisor must start from 1 */

	while(divisor<=number) /* Decide if the number 'Harmonic Divisor' number or not */
	{
		if(number%divisor == 0) /* if the divisor divides without remaining, we will add the  1/divisor to sum2 */
		{
			sum2 += 1.0/divisor;
			divisor_number++;
		}

		divisor++;
	}


	ct = 1; /* will start to divide from 1 */ 
	while(ct*sum2<=divisor_number)
	{	
		/* In this loop, we check that there is a number divide 'divisor_number' without remaining. If there is, we will update the flag as 1 */
		if (ct*sum2==divisor_number)
			harmonic_flag = 1;

		ct++;

	}

	if (harmonic_flag==1)
		printf("Is Harmonic Divisor Number? : Yes\n\n");
	else
		printf("Is Harmonic Divisor Number? : No\n\n");

}


void decide_perfect_harmonic_number()
{
	int number; /* input */
	char check; /* it will check that if the input is '*' character or another character */

	while(1)
	{
		printf("Please enter a number as input: ");
		scanf("%d",&number);

		check = getchar();
		if(check=='*') return;
		else if(check!='\n')
		{
			printf("Please enter a numeric value!\n\n");
			continue;
		}


		if(number<0) /* if number is negative, we must get a new input */
		{
			printf("Please enter a natural number!\n\n");
			continue;
		}

		else
			calculate_perfect_harmonic_number(number);
	}

}


void difference_max_min ()
{
	float users_number; /* number that user enters */
	float difference;
	float min,max;
	int i; /* loop */

	char check; /* it will use for checking input is numeric value or not */

	printf("Please enter 5 numbers \n\n");
	

	for(i=0;i<5;i++)
	{
		if (i==0)
		{
			printf("Enter your %d. number: ",i+1);
			scanf("%f",&users_number);
			
			/* checking if the input is numeric value. if it is NOT, we must get a new input */
			check=getchar(); 
			if(check!='\n')
			{
				printf("\nWARNING -> Please enter a numeric value!\n");
				i--;
				continue;
			}
			/* checking is over */

			max = users_number;
			min = users_number;
		}

		else
		{
			printf("Enter your %d. number: ",i+1);
			scanf("%f",&users_number);

			/* checking if the input is numeric value. if it is NOT, we must get a new input */
			check=getchar(); 
			if(check!='\n')
			{
				printf("\nWARNING -> Please enter a numeric value!\n");
				i--;
				continue;
			}
			/* checking is over */

			if(users_number>max)
				max=users_number;

			if(users_number<min)
				min=users_number;
		}
	}
	
	difference = max-min;
	printf("Difference: %.6g",difference);
}



void bmi_calculation ()
{
	float bmi;
	float kg;
	float meter;
	printf("Enter your weight (kg) :");
	scanf("%f",&kg);
	printf("Enter your height (m)) :");
	scanf("%f",&meter);	

	bmi = kg / (meter*meter);
	
	printf("\n");
	
	if (bmi<16.0) printf("Your BMI is %f. You are Severely Underweight.",bmi);
	
	if (bmi>=16.0 && bmi<18.5) printf("Your BMI is %f. You are Underweight.",bmi);
	
	if (bmi>=18.5 && bmi<25)  printf("Your BMI is %f. You are Normal.",bmi);
	
	if (bmi>=25 && bmi<30) printf("Your BMI is %f. You are Overweight.",bmi);
	
	if (bmi>=30 ) printf("Your BMI is %f. You are Severaly Obese.",bmi);
	
}




int main()
{
	printf("\n\n\t\tWELCOME TO calculate_fibonacci_sequence FUNCTION!\n");
	calculate_fibonacci_sequence();
	printf("\n\n\t\tWELCOME TO decide_perfect_harmonic_number FUNCTION!\n\n");
	decide_perfect_harmonic_number();
	printf("\n\n\t\tWELCOME TO difference_max_min FUNCTION!\n\n");
	difference_max_min();
	printf("\n\n\t\tWELCOME TO bmi_calculation FUNCTION!\n\n");
	bmi_calculation();


}
