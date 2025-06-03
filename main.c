#include <llv/cstr.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a[] = ""; //78
	printf("%lu\n", lv_strlen(a));
}
