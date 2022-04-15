#include "numc.h"

int main()
{
	int **arr;
	int **reshaped_arr;
	int i, j;
	arr = (int **)malloc(2 * sizeof(int *));
	for(i=0; i<2; i++)
	{
		arr[i] = (int *)malloc(3 * sizeof(int));
	}
	for(i=0; i<2; i++) 
	{
		for(j=0; j<3; j++)
		{
			arr[i][j] = i + j;
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	reshaped_arr = reshape2d(arr, 2, 3, 6, 1);	
	for(i=0; i<3; i++) 
	{
		for(j=0; j<2; j++)
		{
			printf("%d ", reshaped_arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
