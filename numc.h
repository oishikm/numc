/*
 *	numc.h
 *	Inspired by python module "numpy".
 *	Oishik Mukhopadhyay | 15 April 2022 
 */

#pragma once
#include<stdio.h>
#include<stdlib.h>

void numc_exception(char* message)
{
	printf("\n[ERROR] %s\n", message);
	exit(0);
}

int** reshape2d(int **inarr, int r, int c, int nr, int nc)
{
	/* r = rows, c = columns */
	/* nr = new rows, nc = new columns */
	if(r*c == nr*nc)
	{	
		register int i, j, k;
		
		int* temp1d = (int *)malloc(r * c * sizeof(int));				
		int** outarr = (int **)malloc(nr * sizeof(int *));		
		for(i=0; i<nr; i++)
		{
			outarr[i] = (int *)malloc(nc * sizeof(int));
		}

		for(i=0, k=0; i<r; i++)
			for(j=0; j<c; j++)
				temp1d[k++] = inarr[i][j];
		
		for(i=0, k=0; i<nr; i++)
			for(j=0; j<nc; j++)
				outarr[i][j] = temp1d[k++];
		
		return outarr;
	}
	else
	{
		char msg[100];
		sprintf(msg, "Error: Input and Output arrays do not have equal size."
				"\n[INFO] Input array has %d bytes while Output array has %d bytes.\n", 
				r*c*sizeof(int), nr*nc*sizeof(int));
		numc_exception(msg);		
	}
}

int** zeros2d(int r, int c)
{
	register int i, j;
	int** outarr = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(c * sizeof(int));
		for(j=0; j<c; j++)
			outarr[i][j] = 0;
	}
	return outarr;
}

int** fill2d(int r, int c, int fill)
{
	register int i, j;
	int** outarr = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(c * sizeof(int));
		for(j=0; j<c; j++)
			outarr[i][j] = fill;
	}
	return outarr;
}

/* 	Declaration for non-user-facing function for anti-clockwise rotation*/
int** rot90_anticlkwise(int **inarr, int r, int k);

int** rot90(int **inarr, int r, int k)	
/*
 * 	rotate 2d square matrix 90*k degrees 
 */
{
	/* r = rows, k = times */
	if(k<0)	/* Anti-clockwise */
		return rot90_anticlkwise(inarr, r, -k);
	
	else
	{
		/* r = rows, k = times (anti-clockwise) */
		register int i, j, l, rot_iter, temp;
		k %= 4;

		int** outarr = (int **)malloc(r * sizeof(int *));	
		int** temparr = (int **)malloc(r * sizeof(int *));
		for(i=0; i<r; i++)
		{
			outarr[i] = (int *)malloc(r * sizeof(int));
			temparr[i] = (int *)malloc(r * sizeof(int));
			for(j=0; j<r; j++)
				temparr[i][j] = inarr[i][j];
				outarr[i][j] = inarr[i][j];
		}

		for(rot_iter=0; rot_iter<k; rot_iter++)
		{
			for(i=0; i<r; i++)
				for(j=0; j<r; j++)
					outarr[j][r-i-1] = temparr[i][j];
			for(i=0; i<r; i++)
				for(j=0; j<r; j++)
					temparr[i][j] = outarr[i][j];
		}

		return outarr;
	}
}

int** rot90_anticlkwise(int **inarr, int r, int k)	
/* 	
 *	rotate 2d square matrix -90*k degrees
 *	Should not be user-facing
 *	User should use rot90() with k<0 for anti-clockwise rotation
 */
{
	/* r = rows, k = times (anti-clockwise) */
	register int i, j, l, rot_iter, temp;
	k %= 4;

	int** outarr = (int **)malloc(r * sizeof(int *));	
	int** temparr = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(r * sizeof(int));
		temparr[i] = (int *)malloc(r * sizeof(int));
		for(j=0; j<r; j++)
			temparr[i][j] = inarr[i][j];
			outarr[i][j] = inarr[i][j];
	}

	for(rot_iter=0; rot_iter<k; rot_iter++)
	{
		for(i=0; i<r; i++)
			for(j=0; j<r; j++)
				outarr[i][j] = temparr[j][r-i-1];
		for(i=0; i<r; i++)
			for(j=0; j<r; j++)
				temparr[i][j] = outarr[i][j];
	}

	return outarr;
}