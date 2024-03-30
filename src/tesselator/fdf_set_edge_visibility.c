/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_set_edge_visibility.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:48:55 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 16:24:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "tesselator.h"

#define ERROR_TESTING_VISIBILITY 0
#define DONE_TESTING_VISIBILITY 1
#define KEEP_TESTING_VISIBILITY 2

// By default this edge is visible (not hidden). Then this function evaluates
// if this edge MUST be DEFINITIVELY hidden because of the following reasons:
//     The four points belong to the same plane.
//         OR
//     This diagonal edge belongs to the XY plane.
// If this edge passes these tests, then it is tested (also by plane analysis)
// against the competitor diagonal. This test can have any of these two
// consequences:
//     The competitor diagonal edge IS DEFINITIVELY HIDDEN, so this edge
//     is already the winner and MUST BE VISIBLE.
//         OR
//     It is INCONCLUSIVE whether the competitior diagonal is visible or not,
//     so a rect analysis is needed to have a definite verdict: KEEP TESTING
//     outside this function, this edge remains visible (not hidden) unless
//     proven otherwise.
static int	fdf_plane_analysis(t_fdf_nv *nv, int *is_hidden)
{
	t_fdf_plane	*plane;

	*is_hidden = 0;
	plane = fdf_create_plane(nv->ort1, nv->ort2, nv->diag_start);
	if (plane == NULL)
		return (ERROR_TESTING_VISIBILITY);
	if (fdf_point_is_in_plane(nv->diag_end, plane)
		|| nv->diag_start->d[2] == nv->diag_end->d[2])
	{
		*is_hidden = 1;
		return (free(plane), DONE_TESTING_VISIBILITY);
	}
	free(plane);
	plane = fdf_create_plane(nv->diag_end, nv->diag_start, nv->ort1);
	if (plane == NULL)
		return (ERROR_TESTING_VISIBILITY);
	if (fdf_point_is_in_plane(nv->ort2, plane)
		|| nv->ort1->d[2] == nv->ort2->d[2])
		return (free(plane), DONE_TESTING_VISIBILITY);
	return (free(plane), KEEP_TESTING_VISIBILITY);
}

// When this function is called, it has already been tested with plane analysis
// but the results are inconclusive. This diagonal edge remains visible by
// default and it is this function task to definitively keep it that way or to
// hide this edge.
// Inconclusive plane analysis sets the following scenario that must be solved
// by this function:
//     Both this diagonal edge and its competitor diagonal edge may be visible
//     but ONLY ONE can. The winner (the one that gets to be visible) must
//     be the edge that, at the center of the XY square defined by the four
//     points of the nv struct, has a greater altitude (Z value).
// Since everything should be consistent and due to function length limitations
// imposed by the freaking 42 Norm, only one coordinate is evaluated and error
// checking is omitted when obtaining the Z value. The X coordinate was
// arbitrarily chosen to obtain the Z value.  
// On the other hand, the comparison of altitudes excludes equality because
// that would equire both diagonals to be on the same plane, which was
// already discarded outside of this function.
static int	fdf_rect_analysis(t_fdf_nv *nv, int *is_hidden)
{
	t_fdf_3drect	*this;
	t_fdf_3drect	*other;
	double			mid_x;
	double			z_this;
	double			z_other;

	this = fdf_create_3drect(nv->diag_start, nv->diag_end);
	other = fdf_create_3drect(nv->ort1, nv->ort2);
	if (this == NULL || other == NULL)
		return (free(this), free(other), ERROR_TESTING_VISIBILITY);
	mid_x = nv->diag_start->d[0];
	mid_x += (nv->diag_end->d[0] - nv->diag_start->d[0]) / 2;
	fdf_getz_3drect_fromx(&z_this, this, mid_x);
	fdf_getz_3drect_fromx(&z_other, other, mid_x);
	if (z_this < z_other)
		*is_hidden = 1;
	return (free(this), free(other), DONE_TESTING_VISIBILITY);
}

//OBSOLETE
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
//
//
//
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
//OBSOLETE
int	fdf_set_edge_visibility(int this_edge,
				t_fdf_object *obj,
				int ort_v1,
				int ort_v2)
{
	t_fdf_nv	*nv;
	int			verdict;

	nv = fdf_create_nv(ft_mx_get_col(obj->model_mx, obj->edge[this_edge].start),
			ft_mx_get_col(obj->model_mx, obj->edge[this_edge].end),
			ft_mx_get_col(obj->model_mx, ort_v1),
			ft_mx_get_col(obj->model_mx, ort_v2));
	if (nv == NULL)
		return (0);
	verdict = fdf_plane_analysis(nv, &obj->edge[this_edge].is_hidden);
	if (verdict == ERROR_TESTING_VISIBILITY)
		return (fdf_destroy_nv(nv), 0);
	if (verdict == DONE_TESTING_VISIBILITY)
		return (fdf_destroy_nv(nv), 1);
	verdict = fdf_rect_analysis(nv, &obj->edge[this_edge].is_hidden);
	if (verdict == ERROR_TESTING_VISIBILITY)
		return (fdf_destroy_nv(nv), 0);
	return (fdf_destroy_nv(nv), 1);
}
