/*
 *	numc.h
 *	Inspired by python module "numpy".
 *	Oishik Mukhopadhyay | 15 April 2022 
 */

#pragma once
#include<stdio.h>
#include<stdlib.h>

int** reshape2d(int** inarr, int r, int c, int n_r, int n_c)
{
	/* r = rows, c = columns */
	/* n_r = new rows, n_c = new columns */
		
	int** outarr = (int **)malloc(n_r * sizeof(int *));
	register int i;
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(n_c * sizeof(int));
	}
	
}
