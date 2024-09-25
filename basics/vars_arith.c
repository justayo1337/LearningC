#include <stdio.h>


int main()
{
	float celsius, fahr;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 5;

	fahr = lower;
	printf("%10s %10s\n", "Fahrenheit", "Celsius");
	while (fahr <= upper )
	{ 
		celsius = (5.0/9) * ( fahr - 32);
		printf("%10.0f %10.1f\n", fahr, celsius);
		fahr += step;
	}
	printf("\n\n");
	celsius = lower;
	printf("%10s %10s\n", "Celsius", "Fahrenheit");
	while (celsius <= upper )
	{ 
		fahr= ((9.0/5) * celsius) + 32;
		printf("%10.0f %10.1f\n", celsius, fahr);
		celsius += step;
	}
	return 0;
}
