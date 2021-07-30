/* Emre YILMAZ - 1901042606 - Gebze Technical University */

#include  <stdio.h>

typedef enum 
{
	employee,
	retired,
	student,
	unemployed
}label;

typedef struct 
{
	char name[30];
	int age;
	label c_label;
}customer;

int check_countRow_right(customer customerArray[50], int index) /* This function finds how many label there are in the row. It goes towards right */
{
	int ct = 0; /* Will be returned */
	int i;
	for(i=index;i<50;i++)
	{
		if(customerArray[i].c_label == customerArray[index].c_label)
			ct++;
		else
			break;
	}

	return ct;
}

int check_countRow_left(customer customerArray[50],int index,label c_label) /* This function finds how many label there are in the row. It goes towards left */
{
	int ct = 0;
	int i;
	for(i=index;i>0;i--)
	{
		if(customerArray[i].c_label == customerArray[index].c_label)
			ct++;
		else
			break;
	}
	return ct;
}

void shift_right(customer customerArray[50], int shift, int ct) /* This function adds the new customer to [shift]. element of array, then shifts the array right */
{
	int i; /* Loop */
	customer copy = customerArray[ct]; /* Copy of the last term of aray */

	for(i=ct;i>=shift;i--) /* Shifting */
	{
		customerArray[i+1] = customerArray[i];
	}

	customerArray[shift] = copy; /* Adding the new customer to [shift]. element of array */
}

void shift_left(customer customerArray[50], int ct) /* This function shifts the array left */
{
	int i;
	for(i=0;i<ct;i++)
		customerArray[i] = customerArray[i+1];
}

int valid_row(label c_label, int ct_row) /* This function checks that whether the label row exceeds its limit. If it exceeds, make and return the flag 0 */
{
	int flag = 1;

	if(c_label==0 && ct_row>=5)
		flag=0;
	else if((c_label==1 || c_label==2) && ct_row>=3)
		flag=0;
	else if((c_label==3 || c_label==4) && ct_row>=2)
		flag=0;

	return flag;
}

void order_customers(customer customerArray[50], int insert_ct) /* Menu choice 1 */
{
	int i,j; /* Loop */
	int max = -1; /* */
	int ct_row = -1; /* Indicates that the label how many times joined the row */
	int FLAG = 0; /* If the FLAG==0, we say that the label exceeds its limit */
	int index = -1;

	/* Find the label where the new user's label has priority */
	for(j=0;j<insert_ct;j++)
	{
		if(customerArray[j].c_label>customerArray[insert_ct].c_label)
		{
			max = j;
			break;
		}
	}

	/* Finding is there any label row that matches the new customer's label in the array. Then finds the row's length */
	for(i=0;i<insert_ct;i++)
	{
		if(customerArray[i].c_label==customerArray[insert_ct].c_label && customerArray[i].c_label!=customerArray[i-1].c_label)
		{
			ct_row = check_countRow_right(customerArray,i);
			if(valid_row(customerArray[i].c_label,ct_row))
			{
				FLAG=1;
				index=i;
			}
		}
	}
	
	if(FLAG==0 && max!=-1) /* If there is no valid row and new customer's label has prioty. */
	{
		/* We have to be sure that when we add the label to queue the row length that may occur is appropriate. If it is appropriate add and shift right. */
		int row_check = check_countRow_left(customerArray,max-1,customerArray[insert_ct].c_label);
		if(valid_row(customerArray[insert_ct].c_label,row_check+1))
			shift_right(customerArray,max,insert_ct);
	}
	else if(FLAG==0 && max==-1); /* Do nothing. It means new customer goes to end of queue */
	else if(FLAG!=0) /* If there is a valid row, add the new customer there. */
	{	
		shift_right(customerArray,index+ct_row-1,insert_ct);
	}
}

void add_customer(customer customerArray[50],int insert_ct)
{
	/* Getting name, age and label inputs from the user and assigning to struct array*/
	printf("Please enter the name of the customer: ");
	scanf("%s",customerArray[insert_ct].name);
	printf("Please enter the age of the customer: ");
	scanf("%d",&customerArray[insert_ct].age);
	printf("Please enter the label of the customer: ");
	scanf("%u",&customerArray[insert_ct].c_label);

	order_customers(customerArray, insert_ct);
}

void process_customer(customer customerArray[50], int insert_ct)
{
	printf("\nProceed customer is %s\n",customerArray[0].name);
	shift_left(customerArray,insert_ct);
}


void menu()
{
	int insert_ct = 0; /* Which user we are getting to insert to array */
	int choice; /* Menu choice */
	int i; /* Loop */
	
	customer customerArray[50]; /* Main array that keeps customers */

	printf("************ Banking System ************");
	while(1)
	{
		printf("\n\n1. Add Customer\n2. Process Customer\n3. EXIT\n");
		scanf("%d",&choice);

		/* Menu choice */
		switch(choice)
		{
			case 1:
				add_customer(customerArray,insert_ct);
				insert_ct++;
				break;
			case 2:
				process_customer(customerArray,insert_ct);
				insert_ct--;
				break;
			case 3:
				return;
			default:
				printf("Please enter a valid choice.\n");
		}

		/* Printing current sequence */
		for(i=0;i<insert_ct;i++)
		{
			if(i==0)
				printf("Current Sequence: %d ",customerArray[i].c_label);
			else if(i==insert_ct-1)
				printf("%d \n\n",customerArray[i].c_label);
			else
				printf("%d ",customerArray[i].c_label);
		}
	}

}

int main()
{
	menu();
}

