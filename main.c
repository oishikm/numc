#include "numc.h"

int main()
{
	int **throw, **in;
	in = NULL;
	throw = rot90(in, 4, 5, 1);
	printf("%d", *throw);
	return 0;
}
