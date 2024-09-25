#include <stdio.h>



int main ()
{
	int c,cnt;
		
	c = cnt = 0;

	while ((c=getchar()) != EOF)
	{
		if ( c == ' ' )
			cnt++;
		else {
			if (cnt > 0)
			{
				cnt = 0;
				putchar(' ');
			}
			putchar(c);
		}
	}
	return 0;		
			
}
