/*
 *	numc.h
 *	Inspired by python module "numpy".
 *	Oishik Mukhopadhyay | 15 April 2022 
 */

#pragma once
#include<stdio.h>
#include<stdlib.h>

int** reshape2d(int **inarr, int r, int c, int nr, int nc)
{
	/* r = rows, c = columns */
	/* nr = new rows, nc = new columns */
		
	int** outarr = (int **)malloc(nr * sizeof(int *));
	register int i, j, ni, nj;
	for(i=0; i<nr; i++)
	{
		outarr[i] = (int *)malloc(nc * sizeof(int));
	}
	printf("\nAllocated");
	/* Checkpoint : DEBUG : Transfer */
	for(i=0, ni=0; i<r, ni<nr; i++, ni++)
	{
		printf("\nTransfer to row %d", ni);
		for(j=0, nj=0; j<c, nj<nc; j++, nj++)
		{
			printf("\nTransfer to column %d", nj);
			outarr[ni][nj] = inarr[i][j];
		}
	}
	printf("\nSending");
	return outarr;
}
