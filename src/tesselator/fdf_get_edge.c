/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_edge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:48:55 by lluque            #+#    #+#             */
/*   Updated: 2024/03/09 21:21:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tesselator.h"

// Add edge from current vertex to its down neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2down_neig(int i, int j, t_ft_mx *map_mx, t_fdf_model *model)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = i * n + j + 1;
	model->edge[model->edges].start = this_v;
	model->edge[model->edges].end = neighbor_v;
	model->edge[model->edges].is_hidden = 0;
	model->edges++;
}

// Add edge from current vertex to its right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is always set to garantee at least the rendering of
// ortogonal (to x and y axis) lines.
static void	edge2right_neig(int i, int j, t_ft_mx *map_mx, t_fdf_model *model)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (i + 1 >= map_mx->m)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j;
	model->edge[model->edges].start = this_v;
	model->edge[model->edges].end = neighbor_v;
	model->edge[model->edges].is_hidden = 0;
	model->edges++;
}

// Add edge from current vertex to its down-right neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-right neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if the height of both vertexes is different.
static void	edge2dr_neig(int i, int j, t_ft_mx *map_mx, t_fdf_model *model)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n || i + 1 >= map_mx->m)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i + 1) * n + j + 1;
	model->edge[model->edges].start = this_v;
	model->edge[model->edges].end = neighbor_v;
	model->edge[model->edges].is_hidden = 1;
	if (map_mx->d[this_v] != map_mx->d[neighbor_v])
		model->edge[model->edges].is_hidden = 0;
	model->edges++;
}

// Add edge from current vertex to its down-left neighbor.
// Variable this_v represents the index (in vertex_mx) of the current vertex
// (element ij in the map_mx) from which to form the edge.
// If a down-left neighbor doesn't exist, this function does nothing.
// The main goal is to calculate neighbor_v based on i and j.
// Visibility is set ONLY if the height of both vertexes is different.
static void	edge2dl_neig(int i, int j, t_ft_mx *map_mx, t_fdf_model *model)
{
	int	this_v;
	int	neighbor_v;
	int	n;

	if (j + 1 >= map_mx->n || i - 1 < 0)
		return ;
	n = map_mx->n;
	this_v = i * n + j;
	neighbor_v = (i - 1) * n + j + 1;
	model->edge[model->edges].start = this_v;
	model->edge[model->edges].end = neighbor_v;
	model->edge[model->edges].is_hidden = 1;
	if (map_mx->d[this_v] != map_mx->d[neighbor_v])
		model->edge[model->edges].is_hidden = 0;
	model->edges++;
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
int	fdf_get_edge(t_ft_mx *map_mx, t_fdf_model *model)
{
	int	i;
	int	j;
	int	m;
	int	n;
	int	edges;

	m = map_mx->m - 1;
	n = map_mx->n - 1;
	edges = m * n * 4 + m + n;
	model->edge = malloc(sizeof (t_fdf_edge) * edges);
	if (model->edge == NULL)
		return (0);
	j = -1;
	while (++j < map_mx->n)
	{
		i = -1;
		while (++i < map_mx->m)
		{
			edge2right_neig(i, j, map_mx, model);
			edge2down_neig(i, j, map_mx, model);
			edge2dr_neig(i, j, map_mx, model);
			edge2dl_neig(i, j, map_mx, model);
		}
	}
	return (1);
}
/*
// For debugging purposes and legibility of the former code.
static void	print_edges(t_ft_mx *map_mx, t_fdf_model *model)
{
	int	e;
	int	x;
	int	y;
	int z;

	e = -1;
	ft_printf("The map_mx...\n");
	ft_mx_print(map_mx, ' ');
	ft_printf("\n");
	ft_printf("The vertex_mx...\n");
	ft_mx_print(model->vertex_mx, ' ');
	ft_printf("\n");
	while (++e < model->edges)
	{
		ft_printf("\tEdge %3d goes from ", e);
		ft_printf("vertex %3d to ", model->edge[e].start);
		x = (int)ft_mx_get_element(model->vertex_mx, 0, model->edge[e].start);
		y = (int)ft_mx_get_element(model->vertex_mx, 1, model->edge[e].start);
		z = (int)ft_mx_get_element(model->vertex_mx, 2, model->edge[e].start);
		ft_printf("(%d, %d, %d) ", x, y, z); 
		ft_printf("vertex %3d ", model->edge[e].end);
		x = (int)ft_mx_get_element(model->vertex_mx, 0, model->edge[e].end);
		y = (int)ft_mx_get_element(model->vertex_mx, 1, model->edge[e].end);
		z = (int)ft_mx_get_element(model->vertex_mx, 2, model->edge[e].end);
		ft_printf("(%d, %d, %d)", x, y, z);
		if (model->edge[e].is_hidden)
			ft_printf(" (hidden)");
		ft_printf("\n");
	}
}
*/
/*	
	int	e;
	int	x;
	int	y;
	int z;
	e = model->edges;
	ft_printf("Edge %d is formed to DOWN neighbor and is %shidden\n",
		model->edges, model->edge[model->edges].is_hidden ? "" : "NOT ");
	ft_printf("\tEdge %3d goes from ", e);
	ft_printf("vertex %3d to ", model->edge[e].start);
	x = (int)ft_mx_get_element(model->vertex_mx, 0, model->edge[e].start);
	y = (int)ft_mx_get_element(model->vertex_mx, 1, model->edge[e].start);
	z = (int)ft_mx_get_element(model->vertex_mx, 2, model->edge[e].start);
	ft_printf("(%d, %d, %d) ", x, y, z); 
	ft_printf("vertex %3d ", model->edge[e].end);
	x = (int)ft_mx_get_element(model->vertex_mx, 0, model->edge[e].end);
	y = (int)ft_mx_get_element(model->vertex_mx, 1, model->edge[e].end);
	z = (int)ft_mx_get_element(model->vertex_mx, 2, model->edge[e].end);
	ft_printf("(%d, %d, %d)", x, y, z);
	if (model->edge[e].is_hidden)
		ft_printf(" (hidden)");
	ft_printf("\n");
*/
/*
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
