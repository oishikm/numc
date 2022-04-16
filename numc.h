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
