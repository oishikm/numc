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

	/* Garbage collection */
	numc_free2d(arr, r);
	numc_free2d(reshaped_arr, nr);

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

	/* Garbage collection */
	numc_free2d(zerosarr, r);

	/* Testing fill2d() */
	int **fillarr;
	int fill = 0;
	printf("\nEnter size of filled array (r c) : ");
	scanf(" %d %d", &r, &c);
	printf("\nEnter fill value (int) : ");
	scanf(" %d", &fill);
	fillarr = fill2d(r, c, fill);
	printf("\n[INFO] Filled Array\n\n");	
	for(i=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			printf("%5d ", fillarr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	numc_free2d(fillarr, r);

	/* Testing rot90() */
	int **arr_square; 
	int **rotated_arr;
	int n;

	printf("\n[INFO] Original Array to be rotated will be auto-populated.\n");
	printf("\nEnter size of original array (square matrix) (r) : ");
	scanf(" %d", &r);
	printf("\nEnter number of times to be rotated (enter negative value for anti-clockwise rotation) : ");
	scanf(" %d", &n);

	arr_square = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		arr_square[i] = (int *)malloc(r * sizeof(int));
	}

	printf("\n[INFO] Original Array\n\n");
	for(i=0, k=0; i<r; i++) 
	{
		for(j=0; j<r; j++)
		{
			arr_square[i][j] = ++k;
			printf("%5d ", arr_square[i][j]);
		}
		printf("\n");
	}

	rotated_arr = rot90(arr_square, r, n);

	printf("\n[INFO] Rotated Array\n\n");	
	for(i=0; i<r; i++) 
	{
		for(j=0; j<r; j++)
		{
			printf("%5d ", rotated_arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	numc_free2d(arr_square, r);
	numc_free2d(rotated_arr, r);

	/* End all tests */
	return 0;
}
