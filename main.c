#include <llv/conv.h>
#include <stdio.h>

int main()
{
	char *x = "-2.23";
	printf("%f\n", lv_atof(x));
}
