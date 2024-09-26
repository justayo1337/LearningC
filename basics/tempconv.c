#include <stdio.h>

#define  CELSIUS 1
#define  FAHR 0

float tempconv(float, int);

int main()
{
	int low,upper,step;
	float temp;
	
	low = temp =  0;
	upper = 300;
	step = 15;
	
	printf("%12s %12s\n","FAHRENHEIT","CELSIUS");
	while (temp <= upper) 
	{
		printf("%12.3f %12.3f\n",temp,tempconv(temp,CELSIUS) );
		temp += step;	
	}
	
	temp = 0;
	printf("%12s %12s\n","CELSIUS","FAHRENHEIT");
	while (temp <= upper) 
	{
		printf("%12.3f %12.3f\n",temp,tempconv(temp,FAHR) );
		temp += step;	
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
	
