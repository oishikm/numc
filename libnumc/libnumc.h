/*
 *	libnumc.h
 *	Library definitions for numc.h
 *
 *	Originally a part of numc.h, these definitions have
 *	been moved here for better readability of numc.h
 *
 *	Oishik Mukhopadhyay | 24 April 2022 
 */

#pragma once
#include<stdio.h>
#include<stdlib.h>

void numc_exception(char* message)
{
	printf("\n[ERROR] %s\n", message);
	exit(0);
}

void _free2d(int **arrptr, int r)
{
	register int i;
	for(i=0; i<r; i++)
		free(arrptr[i]);	
	free(arrptr);
	arrptr = NULL;
}

int** _reshape2d(int **inarr, int r, int c, int nr, int nc)
{
	/* r = rows, c = columns */
	/* nr = new rows, nc = new columns */

	if(r*c != nr*nc)
	{
		char msg[200];
		sprintf(msg, "Error: Input and Output arrays do not have equal size."
				"\n[INFO] Input array has size %d elements while Output array has %d elements.\n", 
				r*c, nr*nc);
		numc_exception(msg);		
	}	

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

int** _zeros2d(int r, int c)
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

int** _fill2d(int r, int c, int fill)
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

int** _rot90(int **inarr, int r, int k)	
/*
 * 	rotate 2d square matrix 90*k degrees
 *	k can be positive (clockwise rotation) or negative (anti-clockwise rotation)
 */
{
	/* r = rows, k = times */	
	register int i, j, rot_iter;
	int anticlkflag = 0;
	if(k<0)
	{
		anticlkflag = 1;
		k = -k;
	}
	k %= 4;

	int** outarr = (int **)malloc(r * sizeof(int *));	
	int** temparr = (int **)malloc(r * sizeof(int *));
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(r * sizeof(int));
		temparr[i] = (int *)malloc(r * sizeof(int));
		for(j=0; j<r; j++)
		{
			temparr[i][j] = inarr[i][j];
			outarr[i][j] = inarr[i][j];
		}
	}

	for(rot_iter=0; rot_iter<k; rot_iter++)
	{
		for(i=0; i<r; i++)
		{
			for(j=0; j<r; j++)
			{
				if(!anticlkflag)
					outarr[j][r-i-1] = temparr[i][j];
				else
					outarr[i][j] = temparr[j][r-i-1];
			}
		}

		for(i=0; i<r; i++)
			for(j=0; j<r; j++)
				temparr[i][j] = outarr[i][j];
	}

	return outarr;
}