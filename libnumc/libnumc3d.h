/*
 *	libnumc3d.h
 *	3D library definitions for numc.h
 *
 *	Oishik Mukhopadhyay | 08 May 2022
 *
 *  Axis names for 3D Array: R, C, D = Row, Column, Depth
 */

#pragma once
#include "libnumc/libnumc.h"

void numc_index_sanity_3d(int *r, int *c, int *d)
{
	numc_index_sanity_1d(r);
	numc_index_sanity_1d(c);
	numc_index_sanity_1d(d);
}

void _free3d(int ***arrptr, int r, int c)
{
	numc_index_sanity_1d(&r);
	numc_index_sanity_1d(&c);
	register int i, j;
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			free(arrptr[i][j]);
	for (i = 0; i < r; i++)
		free(arrptr[i]);
	free(arrptr);
	arrptr = NULL;
}

int ***_alloc3d(int r, int c, int d)
{
	register int i, j;
	numc_index_sanity_3d(&r, &c, &d);
	int ***arrptr = (int ***)malloc(r * sizeof(int **));
	for (i = 0; i < r; i++)
		arrptr[i] = (int **)malloc(c * sizeof(int *));
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			arrptr[i][j] = (int *)malloc(d * sizeof(int));
	return arrptr;
}

int ***_reshape3d(int ***inarr, int r, int c, int d, int nr, int nc, int nd)
{
	/* r = rows, c = columns, d = depth */
	/* nr = new rows, nc = new columns, nd = new depth */

	if (r * c * d != nr * nc * nd)
	{
		char msg[200];
		sprintf(msg, "Input and Output arrays do not have equal size."
					 "\n[INFO] Input array has size %d elements while Output array has %d elements.\n",
				r * c * d, nr * nc * nd);
		numc_exception(msg);
	}

	register int i, j, k, l;

	int *temp1d = _alloc1d(r * c * d);
	int ***outarr = _alloc3d(nr, nc, nd);

	for (i = 0, k = 0; i < r; i++)
		for (j = 0; j < c; j++)
			for (l = 0; l < d; l++)
				temp1d[k++] = inarr[i][j][l];

	for (i = 0, k = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			for (l = 0; l < nd; l++)
				outarr[i][j][l] = temp1d[k++];

	return outarr;
}