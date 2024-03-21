/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_edge_visibility.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:48:55 by lluque            #+#    #+#             */
/*   Updated: 2024/03/21 13:21:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>															///////
#include <stdlib.h>
#include <math.h>
#include "tesselator.h"

//OBSOLETE
//
//
//
// Arguments edgex refer to indexes in object's edge arVray.
// This edges MUST be the orthogonal ones (i.e. the down and right or the
// down and left edges) which share the same start vertex. These indexes
// offer access to the 3 points needed to define a plane.
//
// The diag_v refer to the index in object's vertex matrix that stores
// the end vertex to which the diagonal edge was created and which I  want
// to determine if it should be hidden or not by evaluating if it belongs
// to the same plane defined by the start vertex and its 2 orthogonal
// neighbors.
//
//
//OBSOLETE




// The argument this_edge refer to the index of object's edge array that
// points to the edge being evaluated.
// The arguments ort_vX refer to indexes in object's vertex matrix that point
// to the two orthogonal neighbors (i.e. the down and right OR the down and
// left neighbor vertexes) of this_edge's start vertex.
//
// The this_edge's end vertex is the diagonal neighbor (down-right OR down-
// left neighbot vertexes) of this_edge's start vertex.
//
// This function creates a plane given three points: this_edge's start vertex;
// and both ort_v1 and ort_v2 vertexes. Then determines if this_edge's end
// vertex belong to that plane. If it does belong, this_edge is set as hidden.
// 
// If it does NOT, then its visibility is determined by 
//
// ????the altitude of the
// other two vertexes which are candidate to draw another diagonal edge:
// If any of the other two points have a greater altitud, then this_edge
// is set as hidden ????
//
// If this diagonal edge has a greater slope than the other diagonal edge.
// Since this will...
//
int	fdf_set_edge_visibility(int this_edge,
				t_fdf_object *obj,
				int ort_v1,
				int ort_v2) 
{
	t_ft_mx		*v1;
	t_ft_mx		*v2;
	t_ft_mx		*v_start;
	t_fdf_plane	*plane;
	t_ft_mx		*v_diag;
	
	printf("\t[set_edge_visibility] Starting...\n");
	v1 = ft_mx_get_col(obj->model_mx, ort_v1);
	v2 = ft_mx_get_col(obj->model_mx, ort_v2);
	v_start = ft_mx_get_col(obj->model_mx, obj->edge[this_edge].start);
	v_diag = ft_mx_get_col(obj->model_mx, obj->edge[this_edge].end);
	if (v1 == NULL || v2 == NULL || v_start == NULL || v_diag == NULL)
		return (free(v1), free(v2), free(v_start), free(v_diag), 0);
	printf("\t\t\tv_start_x = %f\n", v_start->d[0]);
	printf("\t\t\tv_start_y = %f\n", v_start->d[1]);
	printf("\t\t\tv_start_z = %f\n", v_start->d[2]);
	printf("\t\t\tv_diag_x = %f\n", v_diag->d[0]);
	printf("\t\t\tv_diag_y = %f\n", v_diag->d[1]);
	printf("\t\t\tv_diag_z = %f\n", v_diag->d[2]);
	printf("\t\t\tv1_x = %f\n", v1->d[0]);
	printf("\t\t\tv1_y = %f\n", v1->d[1]);
	printf("\t\t\tv1_z = %f\n", v1->d[2]);
	printf("\t\t\tv2_x = %f\n", v2->d[0]);
	printf("\t\t\tv2_y = %f\n", v2->d[1]);
	printf("\t\t\tv2_z = %f\n", v2->d[2]);
	plane = fdf_create_plane(v1, v2, v_start);
	if (plane == NULL)
		return (free(v1), free(v2), free(v_start), free(v_diag), 0);
	obj->edge[this_edge].is_hidden = 0;
	if (fdf_point_is_in_plane(v_diag, plane))
	{
		obj->edge[this_edge].is_hidden = 1;
		printf("\t\tHIDDEN (v_diag in same plane)\n");
		return (1);
	}
	
	// Posiblemente no haga falta esta prueba...
	if (v_start->d[2] == v_diag->d[2])
	{
		obj->edge[this_edge].is_hidden = 1;
		printf("\t\tHIDDEN (not in same plane BUT v_diag and v_start have same altitude)\n");
		return (1);
	}
	//mientras
	//return (1);
	
	// At this point the only possibility for hiding this edge is that its
	// competition (the other diagonal) will be visible and at their "XY
	// intersection" the later has a greater altitude.
	//
	// But first we must discard that the competition could actually be visible.
	free(plane);
	plane = fdf_create_plane(v_diag, v_start, v1);
	if (plane == NULL)
		return (free(v1), free(v2), free(v_start), free(v_diag), 0);
	if (fdf_point_is_in_plane(v2, plane))
	{
		printf("\t\tCool, the other diagonal is discarded because it won't be visible (same plane)\n");
		return (1);
	}
	else
	{
		printf("\t\tCompetition passed same plane test and could be drawable\n");
	}

	// Posiblemente no haga falta esta prueba...
	if (v1->d[2] == v2->d[2])
	{
		printf("\t\tCool, the other diagonal is discarded because it won't be visible (same altitude)\n");
		return (1);
	}
	


	t_fdf_3drect	*this;
	t_fdf_3drect	*other;
	double			x_this;
	double			y_this;
	double			x_other;
	double			y_other;
	double			z_this;
	double			z_other;

	this = fdf_create_3drect(v_start, v_diag);
	if (this == NULL)
		return (0);
	other = fdf_create_3drect(v1, v2);
	if (other == NULL)
		return (0);
	x_this = v_start->d[0] + (v_diag->d[0] - v_start->d[0]) / 2;
	y_this = v_start->d[1] + (v_diag->d[1] - v_start->d[1]) / 2;
	
	printf("\t[set_edge_visibility] For this:\n");
	printf("\t\tfirst_x = %f\n", v_start->d[0]);
	printf("\t\tsecond_x = %f\n", v_diag->d[0]);
	printf("\t\t\tx = %f\n", x_this);
	printf("\t\tfirst_y = %f\n", v_start->d[1]);
	printf("\t\tsecond_y = %f\n", v_diag->d[1]);
	printf("\t\t\ty = %f\n", y_this);
	printf("\t\tfirst_z = %f\n", v_start->d[2]);
	printf("\t\tsecond_z = %f\n", v_diag->d[2]);
	
	if (this->parallel_to_xy)
		z_this = this->parallel_to_xy_at_z;
	else
	{
		if (!fdf_getz_3drect_fromx(&z_this, this, x_this))
		{
			if (!fdf_getz_3drect_fromy(&z_this, this, y_this))
			{
				printf("\t[set_edge_visibility] Z (this) is still NULL!!!!????\n");
				obj->edge[this_edge].is_hidden = 1;
				printf("\t\tHIDDEN (not same plane nor altitude BUT perpendicular to Z!!!???\n");
				return (1);
			}
		}
	}
	printf("\t\tz_this = %f\n", z_this);



	x_other = v1->d[0] + (v2->d[0] - v1->d[0]) / 2;
	y_other = v1->d[1] + (v2->d[1] - v1->d[1]) / 2;
	
	printf("\t[set_edge_visibility] For other:\n");
	printf("\t\tfirst_x = %f\n", v1->d[0]);
	printf("\t\tsecond_x = %f\n", v2->d[0]);
	printf("\t\t\tx = %f\n", x_other);
	printf("\t\tfirst_y = %f\n", v1->d[1]);
	printf("\t\tsecond_y = %f\n", v2->d[1]);
	printf("\t\t\ty = %f\n", y_other);
	printf("\t\tfirst_z = %f\n", v1->d[2]);
	printf("\t\tsecond_z = %f\n", v2->d[2]);
	
	if (other->parallel_to_xy)
		z_other = other->parallel_to_xy_at_z;
	else
	{
		if (!fdf_getz_3drect_fromx(&z_other, other, x_other))
		{
			if (!fdf_getz_3drect_fromy(&z_other, other, y_other))
			{
				printf("\t[set_edge_visibility] Z (other) is still NULL!!!!????\n");
				printf("\t\tHIDDEN (not same plane nor altitude BUT perpendicular to Z!!!???\n");
				obj->edge[this_edge].is_hidden = 1;
				return (1);
			}
		}
	}
	printf("\t\t\tz_other = %f\n", z_other);
	
	if (z_this < z_other)
	{
		obj->edge[this_edge].is_hidden = 1;
		printf("\t\tHIDDEN (not same plane nor altitude nor perpendicular to Z BUT this Z is smaller than its competition)\n");
		return (1);
	}


	
	/*
	else
	{
		double	this_m;
		double	the_other_m;

		this_m = (v_start->d[2] - v_diag->d[2]) / (v_start->d[0] - v_diag->d[0]);
		the_other_m = (v1->d[2] - v2->d[2]) / (v1->d[0] - v2->d[0]);
		// Problemas: signo. div por 0
		if (fabs(this_m)  < fabs(the_other_m))
			obj->edge[this_edge].is_hidden = 1;
	}
*/
		/*	
		if (v_start->d[2] < v1->d[2]
			|| v_start->d[2] < v2->d[2]
			|| v_diag->d[2] < v1->d[2]
			|| v_diag->d[2] < v2->d[2])
			obj->edge[this_edge].is_hidden = 1;
		*/
//	obj->edge[this_edge].is_hidden = fdf_is_in_plane(vdiag, plane)
//		|| (!fdf_is_in_plane(vdiag, plane) && v3->d[2] == vdiag->d[2]);
	return (free(plane), free(v1), free(v2), free(v_start), free(v_diag), 1);
}
