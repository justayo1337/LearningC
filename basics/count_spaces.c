#include <stdio.h>




int main ()

{
	int cnt,c;
	
	cnt=c = 0 ;
	while((c=getchar()) != EOF)
	{
		switch (c) {
			case '\t':
			case '\n':
			case ' ':
				cnt++;
		}
	}

	printf("NL, TAB, BLANKS: %d", cnt);
	return 0;

}
