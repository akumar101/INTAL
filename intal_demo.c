#include<stdio.h>
#include"intal.h"


int main(void)
{
	intal* i1 = create_intal();
	intal* i2 = create_intal();
	intal *x = create_intal();
	read_intal(i1,"123456789987654321123456789");
	read_intal(i2,"123456789");

	printf(" \ninput1 for addition:\n\n");

	print_intal(i1);
	printf(" \ninput2 for addition:\n\n");
	
	print_intal(i2);
	
	
	printf("\noutput for addition:\n\n");
	x = add_intal(i1,i2);
	print_intal(x);
	printf("\n\n");

	printf("-----------------------------------------------\n\n");

	printf("\ninput1 for subtraction:\n\n");
	print_intal(i1);

	printf("\ninput2 for subtraction:\n\n");
	
	
	print_intal(i2);

	printf("\noutput for subtraction:\n\n");
	x = sub_intal(i1,i2);
	print_intal(x);
	printf("\n");
	printf("-----------------------------------------------\n\n");
	
	
	
	
	i1 = read1_intal(i1,"123456789987654321123456789");
	i2 = read1_intal(i2,"123456789");

	printf("\ninput1 for multiplication:\n\n");
	print_intal(i1);
	printf("\ninput2 for multiplication:\n\n");
	print_intal(i2);

	printf("\noutput for multiplication:\n\n");
	x = mul_intal(i1,i2);
	print_intal(x);
	printf("\n");

	
	
	
	i1 = read1_intal(i1,"123456789");
	i2 = read1_intal(i2,"1234");

	printf("\ninput1 for division:\n\n");
	print_intal(i1);
	printf("\ninput2 for division:\n\n");
	print_intal(i2);

	printf("\noutput for division:\n\n");
	x = divide_intal(i1,i2);
	print_intal(x);
	printf("\n");
	
	
	i1 = read1_intal(i1,"5");
	i2 = read1_intal(i2,"100");

	printf("\ninput1 for exponentiation:\n\n");
	print_intal(i1);
	printf("\ninput2 for exponentiation:\n\n");
	print_intal(i2);

	printf("\noutput for exponentiation:\n\n");
	x = exp_intal(i1,i2);
	print_intal(x);
	printf("\n");
}

