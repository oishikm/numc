#include "numc.h"

int main()
{
	/* Testing reshape2d() */
	int **arr;
	int **reshaped_arr;
	int i, j, k;
	int r, c, nr, nc;

	printf("\n[INFO] Original Array to be reshaped will be auto-populated.\n");
	printf("\nEnter size of original array (r c) : ");
	scanf(" %d %d", &r, &c);	
	printf("\nEnter size of resized array (nr nc) : ");
	scanf(" %d %d", &nr, &nc);

	arr = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		arr[i] = (int *)malloc(c * sizeof(int));
	}

	printf("\n[INFO] Original Array\n\n");
	for(i=0, k=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			arr[i][j] = ++k;
			printf("%5d ", arr[i][j]);
		}
		printf("\n");
	}

	reshaped_arr = reshape2d(arr, r, c, nr, nc);

	printf("\n[INFO] Reshaped Array\n\n");	
	for(i=0; i<nr; i++) 
	{
		for(j=0; j<nc; j++)
		{
			printf("%5d ", reshaped_arr[i][j]);
		}
		printf("\n");
	}

	/* Testing zeros2d() */
	int **zerosarr;
	printf("\nEnter size of zeros array (r c) : ");
	scanf(" %d %d", &r, &c);
	zerosarr = zeros2d(r, c);
	printf("\n[INFO] Zeros Array\n\n");	
	for(i=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			printf("%5d ", zerosarr[i][j]);
		}
		printf("\n");
	}

	/* End all tests */
	return 0;
}
