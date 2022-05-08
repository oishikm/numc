/*
 *	numc.h
 *	Inspired by python module "numpy".
 *
 *	Oishik Mukhopadhyay | 15 April 2022
 *
 * 	numc.h provides a wrapper (array2d) for C's 2D Array (int[][] i.e. int**)
 * 	If you wish to use numc features directly on int**, use definitions from libnumc.h
 */

#pragma once
#include "libnumc/libnumc.h"

typedef struct _array2d
{
	int **arr;
	int r, c;
} array2d;

typedef struct _array3d
{
	int ***arr;
	int r, c, d;
} array3d;

void free2d(array2d *inarr)
{
	_free2d(inarr->arr, inarr->r);
}

void free3d(array3d *inarr)
{
	_free3d(inarr->arr, inarr->r, inarr->c);
}

array2d reshape2d(array2d inarr, int nr, int nc)
{
	numc_index_sanity_2d(&nr, &nc);
	array2d outarr;
	outarr.r = nr;
	outarr.c = nc;
	outarr.arr = _reshape2d(inarr.arr, inarr.r, inarr.c, nr, nc);
	return outarr;
}

array3d reshape3d(array3d inarr, int nr, int nc, int nd)
{
	numc_index_sanity_3d(&nr, &nc, &nd);
	array3d outarr;
	outarr.r = nr;
	outarr.c = nc;
	outarr.d = nd;
	outarr.arr = _reshape3d(inarr.arr, inarr.r, inarr.c, inarr.d, nr, nc, nd);
	return outarr;
}

array2d zeros2d(int r, int c)
{
	numc_index_sanity_2d(&r, &c);
	array2d outarr;
	outarr.r = r;
	outarr.c = c;
	outarr.arr = _zeros2d(r, c);
	return outarr;
}

array2d fill2d(int r, int c, int fill)
{
	numc_index_sanity_2d(&r, &c);
	array2d outarr;
	outarr.r = r;
	outarr.c = c;
	outarr.arr = _fill2d(r, c, fill);
	return outarr;
}

array2d rot90(array2d inarr, int k)
/*
 * 	rotate 2d square matrix 90*k degrees
 *	k can be positive (clockwise rotation) or negative (anti-clockwise rotation)
 */
{
	array2d outarr;
	outarr.r = inarr.r;
	outarr.c = inarr.c;
	outarr.arr = _rot90(inarr.arr, inarr.r, k);
	return outarr;
}

void alloc2d(array2d *inarr, int r, int c)
{
	numc_index_sanity_2d(&r, &c);
	inarr->r = r;
	inarr->c = c;
	inarr->arr = _alloc2d(r, c);
}

void alloc3d(array3d *inarr, int r, int c, int d)
{
	numc_index_sanity_3d(&r, &c, &d);
	inarr->r = r;
	inarr->c = c;
	inarr->d = d;
	inarr->arr = _alloc3d(r, c, d);
}

array2d slice2d(array2d inarr, int x1, int x2, int y1, int y2)
{
	array2d outarr;
	numc_index_sanity_2d(&x1, &x2);
	numc_index_sanity_2d(&y1, &y2);
	outarr.r = x2 - x1;
	outarr.c = y2 - y1;
	outarr.arr = _slice2d(inarr.arr, inarr.r, inarr.c, x1, x2, y1, y2);
	return outarr;
}