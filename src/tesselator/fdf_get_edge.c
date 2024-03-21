/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_edge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:48:55 by lluque            #+#    #+#             */
/*   Updated: 2024/03/21 13:43:56 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "tesselator.h"

// Add edge from current vertex to its down neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2down_neig(int i, int j, t_ft_mx *map_mx, t_fdf_object *object)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = i * n + j + 1;
	object->edge[object->edges].start = this_v;
	object->edge[object->edges].end = neighbor_v;
	object->edge[object->edges].is_hidden = 0;
	object->edges++;
}

// Add edge from current vertex to its right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2right_neig(int i, int j, t_ft_mx *map_mx, t_fdf_object *object)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (i + 1 >= map_mx->m)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j;
	object->edge[object->edges].start = this_v;
	object->edge[object->edges].end = neighbor_v;
	object->edge[object->edges].is_hidden = 0;
	object->edges++;
}

// Add edge from current vertex to its down-right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if this diagonal edge does not lie on the plane
// defined by this vertex and its (involved) neighbors.
static int	edge2dr_neig(int i, int j, t_ft_mx *map_mx, t_fdf_object *object)
{
	int	this_v;
	int	neighbor_v;
	int	right_neighbor_v;
	int	down_neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n || i + 1 >= map_mx->m)
		return (1);
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j + 1;
	right_neighbor_v = (i + 1) * n + j;
	down_neighbor_v = i * n + (j + 1);
	object->edge[object->edges].start = this_v;
	object->edge[object->edges].end = neighbor_v;
	ft_printf("\n[edge2dr_neig] Evaluating DOWN_RIGHT neighbor visibility\n");
	if (!fdf_set_edge_visibility(object->edges,
			object,
			right_neighbor_v,
			down_neighbor_v))
		return (0);
	object->edges++;
	return (1);
}

// Add edge from current vertex to its down-left neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-left neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if this diagonal edge does not lie on the plane
// defined by this vertex and its (involved) neighbors.
static int	edge2dl_neig(int i, int j, t_ft_mx *map_mx, t_fdf_object *object)
{
	int	this_v;
	int	neighbor_v;
	int	left_neighbor_v;
	int	down_neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n || i - 1 < 0)
		return (1);
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i - 1) * n + j + 1;
	left_neighbor_v = (i - 1) * n + j;
	down_neighbor_v = i * n + (j + 1);
	object->edge[object->edges].start = this_v;
	object->edge[object->edges].end = neighbor_v;
	ft_printf("\n[edge2dl_neig] Evaluating DOWN_LEFT neighbor visibility...\n");
	if (!fdf_set_edge_visibility(object->edges,
			object,
			left_neighbor_v,
			down_neighbor_v))
		return (0);
	object->edges++;
	return (1);
}

// This goes through each element of map_mx, which is a vertex.
// For each element it tries to add 3 edges to neighbors elements: right, 
// down, and diagonal down-right. The later is set as hidden.
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
int	fdf_get_edge(t_ft_mx *map_mx, t_fdf_object *object)
{
	int	i;
	int	j;
	int	edges;

	edges = (map_mx->m - 1) * (map_mx->n - 1) * 4
		+ (map_mx->m - 1)
		+ (map_mx->n - 1);
	object->edge = malloc(sizeof (t_fdf_edge) * edges);
	if (object->edge == NULL)
		return (0);
	j = -1;
	while (++j < map_mx->n)
	{
		i = -1;
		while (++i < map_mx->m)
		{
			edge2right_neig(i, j, map_mx, object);
			edge2down_neig(i, j, map_mx, object);
			if (!edge2dr_neig(i, j, map_mx, object))
				return (0);
			if (!edge2dl_neig(i, j, map_mx, object))
				return (0);
		}
	}
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
