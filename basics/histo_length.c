#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
	int c, len , state, i;
	
	state = OUT;
	c = len = 0;
	while ((c=getchar()) != EOF) 
	{
		switch (c) {
			case '\t':
			case '\n':
			case ' ':
				if (state == IN) {
					putchar(' ');
					for (i = 0 ; i < len ; i++)
						printf("*");
					printf("  %d\n",len);
				}
				state = OUT;
				len = 0;
				break;
			default:
				state = IN;
				//putchar(c);
				++len;
				break;

			}
		}
	return 0;
}
