/*
 *	libnumc2d.h
 *	2D library definitions for numc.h
 *
 *	Oishik Mukhopadhyay | 24 April 2022
 *
 *	Axis names for 3D Array: R, C = Row, Column
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>

void numc_exception(char *message)
{
	printf("\n[ERROR] NumCError: %s\n", message);
	exit(0);
}

void numc_info(char *message)
{
	printf("\n[INFO] NumCInfo: %s\n", message);
}

void numc_index_sanity_1d(int *index)
{
	if (*index < 0)
	{
		*index = -*index;
		char msg[200];
		sprintf(msg, "Index Sanity Check had to change an index."
					 "\n[INFO] %d has been converted to %d.\n",
				-*index, *index);
		numc_info(msg);
	}
}

void numc_index_sanity_2d(int *r, int *c)
{
	numc_index_sanity_1d(r);
	numc_index_sanity_1d(c);
}

void _free2d(int **arrptr, int r)
{
	numc_index_sanity_1d(&r);
	register int i;
	for (i = 0; i < r; i++)
		free(arrptr[i]);
	free(arrptr);
	arrptr = NULL;
}

int **_alloc2d(int r, int c)
{
	register int i;
	numc_index_sanity_2d(&r, &c);
	int **arrptr = (int **)malloc(r * sizeof(int *));
	for (i = 0; i < r; i++)
		arrptr[i] = (int *)malloc(c * sizeof(int));
	return arrptr;
}

int *_alloc1d(int r)
{
	numc_index_sanity_1d(&r);
	int *arrptr = (int *)malloc(r * sizeof(int));
	return arrptr;
}

int **_reshape2d(int **inarr, int r, int c, int nr, int nc)
{
	/* r = rows, c = columns */
	/* nr = new rows, nc = new columns */

	if (r * c != nr * nc)
	{
		char msg[200];
		sprintf(msg, "Input and Output arrays do not have equal size."
					 "\n[INFO] Input array has size %d elements while Output array has %d elements.\n",
				r * c, nr * nc);
		numc_exception(msg);
	}

	register int i, j, k;

	int *temp1d = _alloc1d(r * c);
	int **outarr = _alloc2d(nr, nc);

	for (i = 0, k = 0; i < r; i++)
		for (j = 0; j < c; j++)
			temp1d[k++] = inarr[i][j];

	for (i = 0, k = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			outarr[i][j] = temp1d[k++];

	return outarr;
}

int **_zeros2d(int r, int c)
{
	register int i, j;
	int **outarr = _alloc2d(r, c);
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			outarr[i][j] = 0;
	return outarr;
}

int **_fill2d(int r, int c, int fill)
{
	register int i, j;
	int **outarr = _alloc2d(r, c);
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			outarr[i][j] = fill;
	return outarr;
}

int **_rot90(int **inarr, int r, int k)
/*
 * 	rotate 2d square matrix 90*k degrees
 *	k can be positive (clockwise rotation) or negative (anti-clockwise rotation)
 */
{
	/* r = rows, k = times */
	register int i, j, rot_iter;
	int anticlkflag = 0;
	if (k < 0)
	{
		anticlkflag = 1;
		k = -k;
	}
	k %= 4;

	int **outarr = _alloc2d(r, r);
	int **temparr = _alloc2d(r, r);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			temparr[i][j] = inarr[i][j];
			outarr[i][j] = inarr[i][j];
		}
	}

	for (rot_iter = 0; rot_iter < k; rot_iter++)
	{
		for (i = 0; i < r; i++)
		{
			for (j = 0; j < r; j++)
			{
				if (!anticlkflag)
					outarr[j][r - i - 1] = temparr[i][j];
				else
					outarr[i][j] = temparr[j][r - i - 1];
			}
		}

		for (i = 0; i < r; i++)
			for (j = 0; j < r; j++)
				temparr[i][j] = outarr[i][j];
	}

	_free2d(temparr, r);

	return outarr;
}

int **_slice2d(int **inarr, int r, int c, int x1, int x2, int y1, int y2)
/*
 *	Returns inarr[x1:x2-1, y1:y2-1] slice
 */
{
	if (x1 > r || y1 > c || x2 > r || y2 > c)
	{
		char msg[200];
		sprintf(msg, "Slice index/indices are larger than array size."
					 "\n[INFO] Input array has size axis_0 = %d and axis_1 = %d."
					 "\nWhereas slice indices are axis_0 = %d:%d and axis_1 = %d:%d.\n",
				r, c, x1, x2, y1, y2);
		numc_exception(msg);
	}

	if (x2 <= x1 || y2 <= y1)
	{
		char msg[200];
		sprintf(msg, "Negative or Zero slice size."
					 "\n[INFO] Slice sizes are axis_0 = %d and axis_1 = %d.\n",
				x2 - x1, y2 - y1);
		numc_exception(msg);
	}

	int nr, nc;
	register int i, j;

	nr = x2 - x1;
	nc = y2 - y1;
	int **outarr = _alloc2d(nr, nc);

	for (i = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			outarr[i][j] = inarr[i + x1][j + y1];

	return outarr;
}