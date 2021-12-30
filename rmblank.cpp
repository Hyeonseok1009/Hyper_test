#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void read_line(FILE* fp, char* input, int len)
{
	char c;
	int i = 0;
	while ((c = fgetc(fp)) != '\n')
	{		
		/* 공백은 다 없애기 */
		if (!isspace(abs(c)))
			input[i++] = c;
	}
	input[i] = '\0';
}