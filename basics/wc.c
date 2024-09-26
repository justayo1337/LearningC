#include <stdio.h>
#define IN 1 
#define OUT 0


int main()
{
	int c,n1,nw, nc, state;

	state = OUT;
	n1 = nw = nc = 0;
	while ((c=getchar()) != EOF) {
		++nc;
		switch (c) {
			case '\n':
				++n1;
			case ' ':
			case '\t':
				state = OUT;
				break;
			default:
				if (state == OUT){
					state = IN;
					++nw;
				}
		}
	}	
	printf("Lines: %d, Words: %d, Chars: %d\n",n1,nw,nc);
	return 0;
}

