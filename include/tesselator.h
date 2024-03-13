/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselator.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 15:02:42 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file tesselator.h
 * TODO
*/

#ifndef TESSELATOR_H
# define TESSELATOR_H
# include "lin_alg.h"

/**
 * @struct s_fdf_edge
 * @brief Base for typedef <b>t_fdf_edge</b>.
 * @details This type is used to store an edge, defined as two indexes to the
 * starting and ending vertexes as stored in a vertex matrix
 * @var s_fdf_edge::start
 * The index of the starting vertex stored in a vertex matrix.
 * @var s_fdf_edge::end
 * The index of the ending vertex stored in a vertex matrix.
 * @var s_fdf_edge::is_hidden
 * A non-zero value to signal that this edge must not be drawn.
*/
typedef struct s_fdf_edge
{
	int	start;
	int	end;
	int	is_hidden;
}				t_fdf_edge;

/**
 * @struct s_fdf_triangle
 * @brief Base for typedef <b>t_fdf_triangle</b>.
 * @details This type is used to store a triangle, defined as three indexes to
 * vertexes as stored in a vertex matrix
 * @var s_fdf_triangle::v1
 * The vertex 1 of the triangle.
 * @var s_fdf_triangle::v2
 * The vertex 2 of the triangle.
 * @var s_fdf_triangle::v3
 * The vertex 3 of the triangle.
*/
typedef struct s_fdf_triangle
{
	int	v1;
	int	v2;
	int	v3;
}				t_fdf_triangle;

/**
 * @struct s_fdf_object
 * @brief Base for typedef <b>t_fdf_object</b>.
 * @details This type is used to store a 3D object. That is: its vertex matrix
 * for each of the spaces (model, world, camera, and screen); its edges; and
 * its triangles. This type also contains the auxiliary parameters for vertex
 * transformations to go from one space to the next such as rotations,
 * translations, scaling, and 2D projection.
 * @var s_fdf_object::model_mx
 * The vertex matrix at model space.
 * @var s_fdf_object::world_mx
 * The vertex matrix at world sapce.
 * @var s_fdf_object::camera_mx
 * The vertex matrix at camera space.
 * @var s_fdf_object::screen_mx
 * The vertex matrix at screen space.
 * @var s_fdf_object::edge
 * Array of edges.
 * @var s_fdf_object::edges
 * Number of edges in object->edge array.
 * @var s_fdf_object::triangle
 * Array of triangles.
 * @var s_fdf_object::triangles
 * Number of edges in object->edge array.
 * @var s_fdf_object::m2w_rot_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * rotation transformation from model to world space.
 * @var s_fdf_object::m2w_tra_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * translation transformation from model to world space.
 * @var s_fdf_object::m2w_sca_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * scale transformation from world to camera space.
 * @var s_fdf_object::w2c_rot_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * rotation transformation from world to camera space.
 * @var s_fdf_object::w2c_tra_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * translation transformation from world to camera space.
 * @var s_fdf_object::w2c_sca_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * scale transformation from model world to camera space.
 * @var s_fdf_object::c2s_rot_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * rotation transformation from camera to screen space.
 * @var s_fdf_object::c2s_tra_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * translation transformation from camera to screen space.
 * @var s_fdf_object::c2s_sca_par
 * A double array for X, Y, and Z (indexes 0, 1 and 2 respectively)
 * scale transformation from camera to screen space.
*/
typedef struct s_fdf_object
{
	t_ft_mx			*model_mx;
	double			m2w_rot_par[3];
	double			m2w_tra_par[3];
	double			m2w_sca_par[3];
	t_ft_mx			*world_mx;
	double			w2c_rot_par[3];
	double			w2c_tra_par[3];
	double			w2c_sca_par[3];
	t_ft_mx			*camera_mx;
	double			c2s_rot_par[3];
	double			c2s_tra_par[3];
	double			c2s_sca_par[3];
	t_ft_mx			*screen_mx;
	t_fdf_edge		*edge;
	int				edges;
	t_fdf_triangle	*triangle;
	int				triangles;
}				t_fdf_object;

/**
 * @brief <b>fdf_create_object</b> -- TODO.
 *
 * @details TODO.
 *
 * @return TODO.
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_object	*fdf_create_object(void);

/**
 * @brief <b>fdf_destroy_object</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] object - The pointer to the object to be freed.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_destroy_object(t_fdf_object *object);

/**
 * @brief <b>fdf_tesselate_map</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] map_mx - TODO.
 *
 * @return TODO.
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_object	*fdf_tesselate_map(t_ft_mx	*map_mx);

/**
 * @brief <b>fdf_get_vertex_mx</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] map_mx - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * The vertex_mx is a col-vector matrix where each column represents a
 * xyzw vertex (each row, from top to bottom, has one of these components).
 * The order in which the vertex matrix is filled (which vertex is first
 * included as a column, then the second...) is the following: the first vertex
 * corresponds to the map_mx->d[0] (which is row 0, column 0 from the addressing
 * style map_mx->d[i * map_mx-n + j]). Then i (i.e. 'y') is increased while j 
 * (i.e. 'x' remains at 0)... In conclusion: map_mx is walked through by
 * increasing the row (i.e. increasing the vertex's 'y' coordinate).
 * TODO.
*/
t_ft_mx			*fdf_get_vertex_mx(t_ft_mx *map_mx);

/**
 * @brief <b>fdf_get_edge</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] map_mx - TODO.
 *
 * @param [in] object - The pointer to the 3D object.
 *
 * @return Non-zero value if correct.
 * Value of 0 if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * This goes through each element of map_mx, which is a vertex.
 * For each element it tries to add 3 edges to neighbors elements: right, 
 * down, and diagonal down-right. The later is set as hidden.
 *
 * The iteration depends on the order in which fdf_get_vertex_mx() walks through
 * map_mx while adding the vertexes in vertex_mx: rows (i.e. 'i') increases
 * first.
 *
 * The number of edges comes from adding up:
 *      + For every row (except for the last row) and for every element in that
 *      row (except the last element in row), 3 new edges are formed (down, 
 *      right, and down-right).
 *      + Same as above, mutatis mutandi, to form only one down-left edge per
 *      vertex.
 *      + The last element in every row only forms 1 edge to down neighbor,
 *      except for the last element of the last row which forms NO new edge.
 *      + Every element in last row only forms 1 edge to right neighbor, except
 *      for the last element in this last row which forms NO new edge.
*/
int				fdf_get_edge(t_ft_mx *map_mx, t_fdf_object *object);

/**
 * @brief <b>fdf_create_rot_mx</b> -- TODO.
 *
 * @details TODO.
 *
 * De wiki (https://en.wikipedia.org/wiki/Rotation_matrix):
 * R = RzRyRx
 * These matrices produce the desired effect only if they are used to
 * premultiply column vectors, and (since in general matrix multiplication
 * is not commutative) only if they are applied in the specified order
 * (see Ambiguities for more details). The order of rotation operations
 * is from right to left; the matrix adjacent to the column vector is the
 * first to be applied, and then the one to the left.[3]
 * ...
 * Pre-multiplication or post-multiplication
 * The same point P can be represented either by a column vector v or a
 * row vector w. Rotation matrices can either pre-multiply column vectors (Rv),
 *  or post-multiply row vectors (wR). However, Rv produces a rotation in the
 *  opposite direction with respect to wR. Throughout this article, rotations
 *  produced on column vectors are described by means of a pre-multiplication.
 *  To obtain exactly the same rotation (i.e. the same final coordinates of
 *  point P), the equivalent row vector must be post-multiplied by the transpose
 *  of R (i.e. wRT).
 *
 * @param [in] x - Rotation degree along the X axis.
 *
 * @param [in] y - Rotation degree along the Y axis.
 *
 * @param [in] z - Rotation degree along the Z axis.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx			*fdf_create_rot_mx(double x, double y, double z);

/**
 * @brief <b>fdf_create_ortoproj</b> -- Creates an transformation matrix
 * for ortographic projection to the XY-plane.
 *
 * @details Basically a 3x3 identity matrix with id22 as zero. TODO.
 *
 * De wiki (https://en.wikipedia.org/wiki/Rotation_matrix):
 * R = RzRyRx
 * These matrices produce the desired effect only if they are used to
 * premultiply column vectors, and (since in general matrix multiplication
 * is not commutative) only if they are applied in the specified order
 * (see Ambiguities for more details). The order of rotation operations
 * is from right to left; the matrix adjacent to the column vector is the
 * first to be applied, and then the one to the left.[3]
 * ...
 * Pre-multiplication or post-multiplication
 * The same point P can be represented either by a column vector v or a
 * row vector w. Rotation matrices can either pre-multiply column vectors (Rv),
 *  or post-multiply row vectors (wR). However, Rv produces a rotation in the
 *  opposite direction with respect to wR. Throughout this article, rotations
 *  produced on column vectors are described by means of a pre-multiplication.
 *  To obtain exactly the same rotation (i.e. the same final coordinates of
 *  point P), the equivalent row vector must be post-multiplied by the transpose
 *  of R (i.e. wRT).
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx			*fdf_create_ortoproj_mx(void);

/**
 * @brief <b>fdf_create_transl_mx</b> -- Creates a translation matrix.
 *
 * @details TODO.
 *
 * De wiki (https://en.wikipedia.org/wiki/Rotation_matrix):
 * R = RzRyRx
 * These matrices produce the desired effect only if they are used to
 * premultiply column vectors, and (since in general matrix multiplication
 * is not commutative) only if they are applied in the specified order
 * (see Ambiguities for more details). The order of rotation operations
 * is from right to left; the matrix adjacent to the column vector is the
 * first to be applied, and then the one to the left.[3]
 * ...
 * Pre-multiplication or post-multiplication
 * The same point P can be represented either by a column vector v or a
 * row vector w. Rotation matrices can either pre-multiply column vectors (Rv),
 *  or post-multiply row vectors (wR). However, Rv produces a rotation in the
 *  opposite direction with respect to wR. Throughout this article, rotations
 *  produced on column vectors are described by means of a pre-multiplication.
 *  To obtain exactly the same rotation (i.e. the same final coordinates of
 *  point P), the equivalent row vector must be post-multiplied by the transpose
 *  of R (i.e. wRT).
 *
 * @param [in] x - The translation offset for X axis.
 *
 * @param [in] y - The translation offset for Y axis.
 *
 * @param [in] z - The translation offset for Z axis.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx			*fdf_create_transl_mx(double x, double y, double z);

/**
 * @brief <b>fdf_create_scale_mx</b> -- Flip along the row axis (y axis).
 *
 * @details TODO.
 *
 * De wiki (https://en.wikipedia.org/wiki/Rotation_matrix):
 * R = RzRyRx
 * These matrices produce the desired effect only if they are used to
 * premultiply column vectors, and (since in general matrix multiplication
 * is not commutative) only if they are applied in the specified order
 * (see Ambiguities for more details). The order of rotation operations
 * is from right to left; the matrix adjacent to the column vector is the
 * first to be applied, and then the one to the left.[3]
 * ...
 * Pre-multiplication or post-multiplication
 * The same point P can be represented either by a column vector v or a
 * row vector w. Rotation matrices can either pre-multiply column vectors (Rv),
 *  or post-multiply row vectors (wR). However, Rv produces a rotation in the
 *  opposite direction with respect to wR. Throughout this article, rotations
 *  produced on column vectors are described by means of a pre-multiplication.
 *  To obtain exactly the same rotation (i.e. the same final coordinates of
 *  point P), the equivalent row vector must be post-multiplied by the transpose
 *  of R (i.e. wRT).
 *
 * @param [in] x - The scale factor for X axis.
 *
 * @param [in] y - The scale factor for Y axis.
 *
 * @param [in] z - The scale factor for Z axis.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx			*fdf_create_scale_mx(double x, double y, double z);

/**
 * @brief <b>fdf_print_edges</b> -- TODO.
 *
 * @details For debuggin purposes ONLY. This function prints the map_mx
 * (optional), one of its space vertex matrix (model, world, camera...), and the
 * list of edges in reference to the given space vertex matrix.
 *
 * @param [in] map_mx - Optional, can be NULL.
 *
 * @param [in] object - The object from which to print the data.
 *
 * @param [in] v_mx - The specific space vertex matrix of the object to print.
 * 
 * @warning For debuggin purposes ONLY.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_print_edges(t_ft_mx *map_mx,
					t_fdf_object *object,
					t_ft_mx *v_mx);

#endif
