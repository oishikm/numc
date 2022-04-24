#include "numc.h"

int main()
{
	/* Testing reshape2d() */
	array2d arr;
	array2d reshaped_arr;
	int i, j, k;
	int r, c, nr, nc;

	printf("\n[INFO] Original Array to be reshaped will be auto-populated.\n");
	printf("\nEnter size of original array (r c) : ");
	scanf(" %d %d", &r, &c);	
	printf("\nEnter size of resized array (nr nc) : ");
	scanf(" %d %d", &nr, &nc);

	alloc2d(&arr, r, c);

	printf("\n[INFO] Original Array\n\n");
	for(i=0, k=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			arr.arr[i][j] = ++k;
			printf("%5d ", arr.arr[i][j]);
		}
		printf("\n");
	}

	reshaped_arr = reshape2d(arr, nr, nc);

	printf("\n[INFO] Reshaped Array\n\n");	
	for(i=0; i<nr; i++) 
	{
		for(j=0; j<nc; j++)
		{
			printf("%5d ", reshaped_arr.arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	free2d(&arr);
	free2d(&reshaped_arr);

	/* Testing zeros2d() */
	array2d zerosarr;
	printf("\nEnter size of zeros array (r c) : ");
	scanf(" %d %d", &r, &c);
	zerosarr = zeros2d(r, c);
	printf("\n[INFO] Zeros Array\n\n");	
	for(i=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			printf("%5d ", zerosarr.arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	free2d(&zerosarr);

	/* Testing fill2d() */
	array2d fillarr;
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
			printf("%5d ", fillarr.arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	free2d(&fillarr);

	/* Testing rot90() */
	array2d arr_square; 
	array2d rotated_arr;
	int n;

	printf("\n[INFO] Original Array to be rotated will be auto-populated.\n");
	printf("\nEnter size of original array (square matrix) (r) : ");
	scanf(" %d", &r);
	printf("\nEnter number of times to be rotated (enter negative value for anti-clockwise rotation) : ");
	scanf(" %d", &n);

	alloc2d(&arr_square, r, r);

	printf("\n[INFO] Original Array\n\n");
	for(i=0, k=0; i<r; i++) 
	{
		for(j=0; j<r; j++)
		{
			arr_square.arr[i][j] = ++k;
			printf("%5d ", arr_square.arr[i][j]);
		}
		printf("\n");
	}

	rotated_arr = rot90(arr_square, n);

	printf("\n[INFO] Rotated Array\n\n");	
	for(i=0; i<r; i++) 
	{
		for(j=0; j<r; j++)
		{
			printf("%5d ", rotated_arr.arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	free2d(&arr_square);
	free2d(&rotated_arr);

	/* Testing slice2d() */
	int x1, x2, y1, y2;
	array2d sliced_arr;
	printf("\n[INFO] Original Array to be sliced will be auto-populated.\n");
	printf("\nEnter size of original array (r c) : ");
	scanf(" %d %d", &r, &c);	
	printf("\nEnter slice indices for axis_0 (x1 x2) : ");
	scanf(" %d %d", &x1, &x2);
	printf("\nEnter slice indices for axis_1 (y1 y2) : ");
	scanf(" %d %d", &y1, &y2);

	alloc2d(&arr, r, c);

	printf("\n[INFO] Original Array\n\n");
	for(i=0, k=0; i<r; i++) 
	{
		for(j=0; j<c; j++)
		{
			arr.arr[i][j] = ++k;
			printf("%5d ", arr.arr[i][j]);
		}
		printf("\n");
	}

	sliced_arr = slice2d(arr, x1, x2, y1, y2);

	printf("\n[INFO] Sliced Array\n\n");	
	for(i=0; i<sliced_arr.r; i++) 
	{
		for(j=0; j<sliced_arr.c; j++)
		{
			printf("%5d ", sliced_arr.arr[i][j]);
		}
		printf("\n");
	}

	/* Garbage collection */
	free2d(&arr);
	free2d(&sliced_arr);

	/* End all tests */
	return 0;
}
