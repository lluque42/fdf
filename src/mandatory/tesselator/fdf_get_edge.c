/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_edge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:48:55 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:01:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fdf.h"

// Add edge from current vertex to its down neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2down_neig(int i, int j, t_fdf_object *obj)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (j + 1 >= obj->map_mx[Z]->n)
		return ;
	n = obj->map_mx[Z]->n;
	this_v = i * n + j;
	neighbor_v = i * n + j + 1;
	obj->edge[obj->edges].start = this_v;
	obj->edge[obj->edges].end = neighbor_v;
	if (obj->map_mx[C] != NULL)
	{
		obj->edge[obj->edges].start_color = obj->map_mx[C]->d[this_v];
		obj->edge[obj->edges].end_color = obj->map_mx[C]->d[neighbor_v];
	}
	obj->edge[obj->edges].is_hidden = 0;
	obj->edges++;
}

// Add edge from current vertex to its right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2right_neig(int i, int j, t_fdf_object *obj)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (i + 1 >= obj->map_mx[Z]->m)
		return ;
	n = obj->map_mx[Z]->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j;
	obj->edge[obj->edges].start = this_v;
	obj->edge[obj->edges].end = neighbor_v;
	if (obj->map_mx[C] != NULL)
	{
		obj->edge[obj->edges].start_color = obj->map_mx[C]->d[this_v];
		obj->edge[obj->edges].end_color = obj->map_mx[C]->d[neighbor_v];
	}
	obj->edge[obj->edges].is_hidden = 0;
	obj->edges++;
}

// Add edge from current vertex to its down-right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if this diagonal edge does not lie on the plane
// defined by this vertex and its (involved) neighbors.
//
// Always flagged as hidden to allow drawing or not this non-orthogonal edge.
// Do not confuse visibility (it makes sense to be considered for drawing) wiht
// hidden (don't draw if visible because we don't want non-orthogonal edges
// depicted on the drawing)
static int	edge2dr_neig(int i, int j, t_fdf_object *obj)
{
	int	this_v;
	int	neighbor_v;
	int	r_neigh_v;
	int	d_neigh_v;
	int	n;

	if (j + 1 >= obj->map_mx[Z]->n || i + 1 >= obj->map_mx[Z]->m)
		return (1);
	n = obj->map_mx[Z]->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j + 1;
	r_neigh_v = (i + 1) * n + j;
	d_neigh_v = i * n + (j + 1);
	obj->edge[obj->edges].start = this_v;
	obj->edge[obj->edges].end = neighbor_v;
	if (obj->map_mx[C] != NULL)
	{
		obj->edge[obj->edges].start_color = obj->map_mx[C]->d[this_v];
		obj->edge[obj->edges].end_color = obj->map_mx[C]->d[neighbor_v];
	}
	if (!fdf_set_diag_edge_validity(obj->edges, obj, r_neigh_v, d_neigh_v))
		return (0);
	obj->edge[obj->edges].is_hidden = 1;
	obj->edges++;
	return (1);
}

// Add edge from current vertex to its down-left neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-left neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if this diagonal edge does not lie on the plane
// defined by this vertex and its (involved) neighbors.
//
// Always flagged as hidden to allow drawing or not this non-orthogonal edge.
// Do not confuse visibility (it makes sense to be considered for drawing) wiht
// hidden (don't draw if visible because we don't want non-orthogonal edges
// depicted on the drawing)
static int	edge2dl_neig(int i, int j, t_fdf_object *obj)
{
	int	this_v;
	int	neighbor_v;
	int	l_neigh_v;
	int	d_neigh_v;
	int	n;

	if (j + 1 >= obj->map_mx[Z]->n || i - 1 < 0)
		return (1);
	n = obj->map_mx[Z]->n;
	this_v = i * n + j;
	neighbor_v = (i - 1) * n + j + 1;
	l_neigh_v = (i - 1) * n + j;
	d_neigh_v = i * n + (j + 1);
	obj->edge[obj->edges].start = this_v;
	obj->edge[obj->edges].end = neighbor_v;
	if (obj->map_mx[C] != NULL)
	{
		obj->edge[obj->edges].start_color = obj->map_mx[C]->d[this_v];
		obj->edge[obj->edges].end_color = obj->map_mx[C]->d[neighbor_v];
	}
	if (!fdf_set_diag_edge_validity(obj->edges, obj, l_neigh_v, d_neigh_v))
		return (0);
	obj->edge[obj->edges].is_hidden = 1;
	obj->edges++;
	return (1);
}

// TODO OBSOLETE
// This goes through each element of map_mx, which is a vertex.
// For each element it tries to add 4 edges to neighbors elements: right, 
// down, and diagonal down-right, and diagonal down-left.
// The later is set as hidden TODO. 
//
// The iteration depends on the order in which fdf_get_vertex_mx() walks through
// map_mx while adding the vertexes in vertex_mx: rows (i.e. 'i') increases
// first.
//
// The number of edges comes from adding up:
// 		+ For every row (except for the last row) and for every element in that
// 		row (except the last element in row), 3 new edges are formed (down, 
// 		right, and down-right).
// 		+ Same as above, mutatis mutandi, to form only one down-left edge per
// 		vertex.
//		+ The last element in every row only forms 1 edge to down neighbor,
//		except for the last element of the last row which forms NO new edge.
//		+ Every element in last row only forms 1 edge to right neighbor, except
//		for the last element in this last row which forms NO new edge.
int	fdf_get_edge(t_fdf_object *obj)
{
	int	i;
	int	j;
	int	edges;

	obj->edges = 0;
	edges = (obj->map_mx[Z]->m - 1) * (obj->map_mx[Z]->n - 1) * 4
		+ (obj->map_mx[Z]->m - 1) + (obj->map_mx[Z]->n - 1);
	obj->edge = ft_calloc(edges, sizeof (t_fdf_edge));
	if (obj->edge == NULL)
		return (0);
	j = -1;
	while (++j < obj->map_mx[Z]->n)
	{
		i = -1;
		while (++i < obj->map_mx[Z]->m)
		{
			edge2right_neig(i, j, obj);
			edge2down_neig(i, j, obj);
			if (!edge2dr_neig(i, j, obj) || !edge2dl_neig(i, j, obj))
				return (0);
		}
	}
	ft_printf("\tWireframe has a total of %d vertices and %d edges.\n",
		obj->map_mx[Z]->m * obj->map_mx[Z]->n, edges);
	return (1);
}
/*
 * For clarity, this is how the calculation for the number of edges was
 * before re-factoring to comply with 42's freakin norm after the function
 * grew:
	int	m;
	int	n;
	m = map_mx->m - 1;
	n = map_mx->n - 1;
	edges = m * n * 4 + m + n;
*/
/* At some point this was an auxiliary function. TODO check for obsolescence.
// The number of edges comes from adding up:
// 		+ For every row (except for the last row) and for every element in that
// 		row (except the last element in row), 3 new edges are formed (down, 
// 		right, and down-right).
// 		+ Same as above, mutatis mutandi, to form only one down-left edge per
// 		vertex.
//		+ The last element in every row only forms 1 edge to down neighbor,
//		except for the last element of the last row which forms NO new edge.
//		+ Every element in last row only forms 1 edge to right neighbor, except
//		for the last element in this last row which forms NO new edge.
static int	fdf_get_edge_number(t_ft_mx *map_mx)
{
	int	number;

	number = (map_mx->m - 1) * (map_mx->n - 1) * 3;
	number += (map_mx->m - 1) * (map_mx->n - 1);
	number += map_mx->m - 1;
	number += map_mx->n - 1;
	return (number);
}
*/
