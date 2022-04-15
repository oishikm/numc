/*
 *	numc.h
 *	Inspired by python numpy module.
 *	Oishik Mukhopadhyay | 15 April 2022 
 */

#pragma once
#include<stdio.h>
#include<stdlib.h>

int** rot90(int** inarr, int r, int k)
{
	/* r = rows, k = rotation count */
	
	int** outarr = (int **)malloc(r * sizeof(int *));
	register int i;
	for(i=0; i<r; i++)
	{
		outarr[i] = (int *)malloc(r * sizeof(int));
	}
	
}
