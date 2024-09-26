#include <stdio.h>
#define IN 1 
#define OUT 0


int main()
{
	int c, state;

	state = OUT;
	while ((c=getchar()) != EOF) {
		switch (c) {
			case '\n':
			case ' ':
			case '\t':	
				if ( state == IN ) {
					printf("\n");
				}
				state = OUT;
				break;
			default:
				if (state == OUT){
					state = IN;	
				}
				putchar(c);
		}
	}	
//	printf("Lines: %d, Words: %d, Chars: %d\n",n1,nw,nc);
	return 0;
}

