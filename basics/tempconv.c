#include <stdio.h>

#define  CELSIUS 1
#define  FAHR 0
#define LOW 0 
#define UPPER 300
#define STEP 15
float tempconv(float, int);

int main()
{
	float temp;
	
	temp =  LOW;
	
	printf("%12s %12s\n","FAHRENHEIT","CELSIUS");
	while (temp <= UPPER) 
	{
		printf("%12.3f %12.3f\n",temp,tempconv(temp,CELSIUS) );
		temp += STEP;	
	}

	/* print this in reverse and use a for loop instead */
	printf("%12s %12s\n","CELSIUS","FAHRENHEIT");
	for (temp = UPPER ; temp > LOW ; temp -= STEP) { 
		printf("%12.3f %12.3f\n",temp,tempconv(temp,FAHR) );
	}

	return 0;
}


float tempconv(float temp, int convertto)
{

	switch (convertto) 
	{
		case CELSIUS:
			return ((5.0/9) * (temp - 32));
			break;
		case FAHR:
			return (((9.0/5) * (temp)) + 32);
			break;
		default:
			return 0.0;
			break;

	}
}
	
