/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselator.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 16:24:37 by lluque           ###   ########.fr       */
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
 * @enum e_tesselation_type
 * @brief Base for typedef <b>t_tesselation_type</b>.
 * @details This type is used in function fdf_tesselate_map() to indicate how
 * the map_mx matrix parsed from file must be transformed into a 3D object.
 * @var e_tesselation_type::PLANE_TESSELATION
 * Indicates that the X, Y and altitud values derived from the map_mx matrix
 * defines a horizontal XY plane with map's altitudes varying the Z values.
 * @var e_tesselation_type::SPHERICAL_TESSELATION
 * Indicates that the X, Y and altitud values derived from the map_mx matrix
 * defines a sphere with map's altitudes varying its radius from a base_radius.
 * @var e_tesselation_type::CYLINDRICAL_TESSELATION
 * Indicates that the X, Y and altitud values derived from the map_mx matrix
 * defines a cylinder along Z axis with map's altitudes varying its radius from
 * a base_radius.
*/
typedef enum e_tesselation_type
{
	PLANE_TESSELATION,
	SPHERICAL_TESSELATION,
	CYLINDRICAL_TESSELATION
}	t_tesselation_type;

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
 * @struct s_fdf_nv
 * @brief Base for typedef <b>t_fdf_nv</b>.
 * @details This type is used to store the four xyzw vertexes (as column-vectors
 * matrixes) from which the three edges are defined from every point of an
 * altitude map matrix (i.e. edge to right/left neighbor, edge to down neighbor,
 * edge to down-left/down-right neighbor) that is analyzed from the top-left
 * corner (row 0 and column 0) to the bottom righ corner.  
 * This type is used in functions that evaluate the convenience of setting each
 * of the diagonal edges in this per-four-vertexes-analysis as hidden.  
 * A diagonal edge is defined as the one that connect to a non-orthogonal
 * neighbor.  
 * A non-orthogonal neighbor is one that has both different X and Y (column,
 * row) coordinates.   
 * In brief: A diagonal edge (candidate to be hidden) is the edge from the
 * starting vertex to the end vertex (which is the former's down-left OR
 * down-right neighbor) in that local scope of analyzing the relationship of
 * four neighboring vertexes: two orthogonal, and two non-orthogonal.
 * @var s_fdf_nv::diag_start
 * The reference vertex from which three edges form when going through an
 * altitude map matrix from its top-left corner (row 0 and column 0) to its
 * bottom righ corner.
 * @var s_fdf_nv::diag_end
 * The diagonal vertex to diag_start. The edge that goes from diag_start to
 * diag_end is a candidate to be hidden (not to be drawn).
 * @var s_fdf_nv::ort1
 * One of the orthogonal neighbors to diag_start. It could be any of its down
 * neighbor or either its left OR right neighbor. It doesn't matter which one
 * for the purposes to which this structure type is used.
 * @var s_fdf_nv::ort2
 * One of the orthogonal neighbors to diag_start. It could be any of its down
 * neighbor or either its left OR right neighbor. It doesn't matter which one
 * for the purposes to which this structure type is used.
*/
typedef struct s_fdf_nv
{
	t_ft_mx	*diag_start;
	t_ft_mx	*diag_end;
	t_ft_mx	*ort1;
	t_ft_mx	*ort2;
}				t_fdf_nv;

/**
 * @struct s_fdf_3drect
 * @brief Base for typedef <b>t_ft_mx_3drect</b>.
 * @details This type is used to store the parameters of a 3D rect defined as  
 *     (x - x1) / tx        = (y - y1) / ty        = (z - z1) / tz  
 *     (x - x1) / (x2 - x1) = (y - y1) / (y2 - y1) = (z - z1) / (z2 -z1)  
 * Where x1, x2, y1, y2, z1, z2 are constants derived from two points that
 * belong to the rect.  
 * Notice that if tx, ty, or tz are 0, problems arise due to divisions by zero
 * when trying to solve the equation from a x, y, or z value respectively.
 * The rect's parallelism to the plane formed by two axis (which implies
 * the rect's perpendicularity to the remaining axis) is informed by the zero
 * value of tx, ty, and tz parameters. By the way, a rect can not be parallel
 * to the three axis planes (i.e. perpendicular to the three axis) at the same
 * time, such case results in a NULL when creating the rect.  
 * For example:  
 * If the rect is perpendicular to X axis (i.e. parallel to YZ), that is tx = 0
 * (tx = rect->x2 - rect->x1), it is impossible to obtain the Z value from
 * an X value. This is because for a given X value there is no unique (actually
 * infinite) Z values that checks the rect equation.
 * If possible (tx != 0), then if it is perpendicular to Z axis (i.e. parallel
 * to XY), that is tz = 0 (tz = rect->z2 - rect->z1), the solution is already in
 * rect->parallel_to_xy_at_z and is independent from the value of passed x.  
 * In the rest of cases the z value is calculated from:  
 *     z = ((x - x1) / tx ) * tz) + z1  
 * The fdf_create_3drect() function calculates the auxiliary members of this
 * struct: parallel_to_xy, parallel_to_xy_at_z, parallel_to_yz,
 * parallel_to_yz_at_x, parallel_to_xz, and parallel_to_xz_at_y.
 * @var s_fdf_3drect::x1
 * Parameter.
 * @var s_fdf_3drect::x2
 * Parameter.
 * @var s_fdf_3drect::y1
 * Parameter.
 * @var s_fdf_3drect::y2
 * Parameter.
 * @var s_fdf_3drect::z1
 * Parameter.
 * @var s_fdf_3drect::z2
 * Parameter.
 * @var s_fdf_3drect::parallel_to_xy
 * Auxiliary member to signal that the rect is parallel to XY plane (i.e
 * perpendicular to Z axis)
 * @var s_fdf_3drect::parallel_to_yz
 * Auxiliary member to signal that the rect is parallel to YZ plane (i.e
 * perpendicular to X axis)
 * @var s_fdf_3drect::parallel_to_xz
 * Auxiliary member to signal that the rect is parallel to XZ plane (i.e
 * perpendicular to Y axis)
 * @var s_fdf_3drect::parallel_to_xy_at_z
 * Auxiliary member to store the invariant Z value if this rect is parallel to
 * XY plane (i.e perpendicular to Z axis, hence, z remains constant)
 * @var s_fdf_3drect::parallel_to_yz_at_x
 * Auxiliary member to store the invariant X value if this rect is parallel to
 * YZ plane (i.e perpendicular to X axis, hence, x remains constant)
 * @var s_fdf_3drect::parallel_to_xz_at_y
 * Auxiliary member to store the invariant Y value if this rect is parallel to
 * XZ plane (i.e perpendicular to Y axis, hence, y remains constant)
*/
typedef struct s_fdf_3drect
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	z1;
	double	z2;
	int		parallel_to_xy;
	double	parallel_to_xy_at_z;
	int		parallel_to_yz;
	double	parallel_to_yz_at_x;
	int		parallel_to_xz;
	double	parallel_to_xz_at_y;
}				t_fdf_3drect;

/**
 * @struct s_fdf_plane
 * @brief Base for typedef <b>t_fdf_plane</b>.
 * @details This type is used to store the definition of a plane as:  
 *     a * x + b * y + c * z + k = 0
 * @var s_fdf_plane::a
 * The factor to multiply the X coordinate in the plane equation.
 * @var s_fdf_plane::b
 * The factor to multiply the Y coordinate in the plane equation.
 * @var s_fdf_plane::c
 * The factor to multiply the Z coordinate in the plane equation.
 * @var s_fdf_plane::k
 * The k additive factor in the plane equation.
*/
typedef struct s_fdf_plane
{
	double	a;
	double	b;
	double	c;
	double	k;
}				t_fdf_plane;

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
 * @var s_fdf_object::map_mx
 * The matrix with the raw data (altitude values at each row, column coordinate)
 * from which the tesselation is done.
 * @var s_fdf_object::tesselation_type
 * The tesselation type that shoul be used to interpret the altitud data when
 * creating the 3D object (plane, spherical, cylindrical, etc.).
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
	t_ft_mx				*map_mx;
	t_tesselation_type	tesselation_type;
	t_ft_mx				*model_mx;
	double				m2w_rot_par[3];
	double				m2w_tra_par[3];
	double				m2w_sca_par[3];
	t_ft_mx				*world_mx;
	double				w2c_rot_par[3];
	double				w2c_tra_par[3];
	double				w2c_sca_par[3];
	t_ft_mx				*camera_mx;
	double				c2s_rot_par[3];
	double				c2s_tra_par[3];
	double				c2s_sca_par[3];
	t_ft_mx				*screen_mx;
	t_fdf_edge			*edge;
	int					edges;
	t_fdf_triangle		*triangle;
	int					triangles;
}				t_fdf_object;

/**
 * @brief <b>fdf_create_object</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] map_mx
 * The matrix with the raw data (altitude values at each row, column coordinate)
 * from which the tesselation is done.
 * 
 * @return TODO.
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_object	*fdf_create_object(t_ft_mx *map_mx);

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
 * @param [in] object - TODO.
 *
 * @return TODO.
 * Zero value if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int				fdf_tesselate_map(t_fdf_object *object);

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

/**
 * @brief <b>fdf_create_plane</b> -- Creates a plane from 3 vertexes.
 *
 * @details TODO.
 *
 * https://math.stackexchange.com/questions/2686606/
 * equation-of-a-plane-passing-through-3-points
 *
 * @param [in] a - One of the vertexes that belongs to the plane as a
 * column vector.
 *
 * @param [in] b - One of the vertexes that belongs to the plane as a
 * column vector.
 *
 * @param [in] c - One of the vertexes that belongs to the plane as a
 * column vector.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_plane		*fdf_create_plane(t_ft_mx *a, t_ft_mx *b, t_ft_mx *c);

/**
 * @brief <b>fdf_point_is_in_plane</b> -- Evaluates if a vertex belongs to a
 * plane.
 *
 * @details TODO.
 *
 * https://math.stackexchange.com/questions/2686606/
 * equation-of-a-plane-passing-through-3-points
 *
 * @param [in] v - The vertex (as a column vector matrix) to evaluate in the
 * plane equation.
 *
 * @param [in] plane - The parameters of the plane equation to use
 * for evaluation.
 *
 * @return Non-zero value if point v belongs to plane.
 * A zero if v does not belong to the plane.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int				fdf_point_is_in_plane(t_ft_mx *v, t_fdf_plane *plane);

/**
 * @brief <b>fdf_create_3drect</b> -- Creates 3D rect equation parameter struct
 * from two 3D points.
 *
 * @details 
 * TODO If the rect is perpendicular to X axis (i.e. parallel to YZ),
 * that is tx = 0 (tx = rect->x2 - rect->x1), it is impossible to obtain
 * the Z value from a X value. This is because for a given X value there is
 * no unique (actually infinite) Z value that checks the rect equation.
 * If this is the case, NULL is returned.  
 * Otherwise (tx != 0), if it is perpendicular to Z axis (i.e. parallel
 * to XY), that is tz = 0 (tz = rect->z2 - rect->z1), the solution is already in
 * rect->parallel_to_xy_at_z and is independent from the value of passed x.  
 * In the rest of cases the z value is calculated from:  
 *     z = ((x - x1) / tx ) * tz) + z1  
 *TODO
 * @param [in] v1 - The first vertex (as a column vector matrix) that belongs
 * to the rect whose equation parameters will be calculated.
 *
 * @param [in] v2 - The second vertex (as a column vector matrix) that belongs
 * to the rect whose equation parameters will be calculated.
 *
 * @return Pointer to the struct that stores the parameters of the rect equation
 * to which the both vertexes belong.  
 * NULL if giving the two passed points it is impossible a rect that goes
 * through both.
 *
 * @warning Caller must free the returned pointer. TODO.
 *
 * @remark Implementation notes:
 * The fdf_create_3drect() function already calculates the auxiliary members of
 * the 3drect struct that report parallelism/perpendicularity with
 * 2-axis-planes/axis. This members are used for legibilty: parallel_to_xy,
 * parallel_to_xy_at_z, parallel_to_yz, parallel_to_yz_at_x, parallel_to_xz,
 * and parallel_to_xz_at_y.
 * https://www.geeksforgeeks.org/equation-of-a-line-in-3d/
 * https://math.stackexchange.com/questions/4496965/
 * how-to-find-the-equation-of-a-3d-straight-line-when-given-two-points
*/
t_fdf_3drect	*fdf_create_3drect(t_ft_mx *v1, t_ft_mx *v2);

/**
 * @brief <b>fdf_getz_3drect_fromx</b> -- Gets Z value from rect equation given
 * the X value.
 *
 * @details If the rect is perpendicular to X axis (i.e. parallel to YZ),
 * that is tx = 0 (tx = rect->x2 - rect->x1), it is impossible to obtain
 * the Z value from a X value. This is because for a given X value there is
 * no unique (actually infinite) Z value that checks the rect equation.
 * If this is the case, NULL is returned.  
 * Otherwise (tx != 0), if it is perpendicular to Z axis (i.e. parallel
 * to XY), that is tz = 0 (tz = rect->z2 - rect->z1), the solution is already in
 * rect->parallel_to_xy_at_z and is independent from the value of passed x.  
 * 
 * TODO review code's special case and re-write this...
 *
 * For the rest of cases the z value is calculated from:  
 *     z = ((x - x1) / tx ) * tz) + z1  
 *
 * @param [out] z - The pointer to a double to store the z value if possible.
 *
 * @param [in] rect - The struct with the parameters of the 3D rect equation.
 *
 * @param [in] x - The value of the X coordinate.
 *
 * @return Non-zero value if pointer to the Z value is valid.
 * A zero value if impossible to return Z coordinate value from an X coordinate
 * value.  
 * In this case rect->parallel_to_xy and rect->parallel_to_xy_at_z must
 * be checked.
 *
 * @warning Caller must free the returned pointer. TODO.
 *
 * @remark Implementation notes:
 * The fdf_create_3drect() function already calculates the auxiliary members of
 * the 3drect struct that report parallelism/perpendicularity with
 * axis/axis-planes. This members are used for legibilty: parallel_to_xy,
 * parallel_to_xy_at_z, parallel_to_yz, parallel_to_yz_at_x, parallel_to_xz,
 * and parallel_to_xz_at_y.
 * https://www.geeksforgeeks.org/equation-of-a-line-in-3d/
 * https://math.stackexchange.com/questions/4496965/
 * how-to-find-the-equation-of-a-3d-straight-line-when-given-two-points
*/
int				fdf_getz_3drect_fromx(double *z, t_fdf_3drect *rect, double x);

/**
 * @brief <b>fdf_getz_3drect_fromy</b> -- Gets Z value from rect equation given
 * the Y value.
 *
 * @details If the rect is perpendicular to Y axis (i.e. parallel to XZ),
 * that is ty = 0 (ty = rect->y2 - rect->y1), it is impossible to obtain
 * the Z value from a Y value. This is because for a given Y value there is
 * no unique (actually infinite) Z value that checks the rect equation.
 * If this is the case, NULL is returned.  
 * Otherwise (ty != 0), if it is perpendicular to Z axis (i.e. parallel
 * to XY), that is tz = 0 (tz = rect->z2 - rect->z1), the solution is already in
 * rect->parallel_to_xy_at_z and is independent from the value of passed y.  
 * 
 * TODO review code's special case and re-write this...
 *
 * For the rest of cases the z value is calculated from:  
 *     z = ((y - y1) / ty ) * tz) + z1  
 *
 * @param [out] z - The pointer to a double to store the z value if possible.
 *
 * @param [in] rect - The struct with the parameters of the 3D rect equation.
 *
 * @param [in] y - The value of the Y coordinate.
 *
 * @return Non-zero value if pointer to the Z value is valid.
 * A zero value if impossible to return Z coordinate value from an Y coordinate
 * value.  
 * In this case rect->parallel_to_xy and rect->parallel_to_xy_at_z must
 * be checked.
 *
 * @warning Caller must free the returned pointer. TODO.
 *
 * @remark Implementation notes:
 * The fdf_create_3drect() function already calculates the auxiliary members of
 * the 3drect struct that report parallelism/perpendicularity with
 * axis/axis-planes. This members are used for legibilty: parallel_to_xy,
 * parallel_to_xy_at_z, parallel_to_yz, parallel_to_yz_at_x, parallel_to_xz,
 * and parallel_to_xz_at_y.
 * https://www.geeksforgeeks.org/equation-of-a-line-in-3d/
 * https://math.stackexchange.com/questions/4496965/
 * how-to-find-the-equation-of-a-3d-straight-line-when-given-two-points
*/
int				fdf_getz_3drect_fromy(double *z, t_fdf_3drect *rect, double y);

/**
 * @brief <b>fdf_set_edge_visibility</b> -- TODO.
 *
 * @details TODO comments inside the function's definition file TODO.
 *
 * @param [in] this_edge - TODO.
 *
 * @param [in, out] obj - The object being tesselated.
 *
 * @param [in] ort_v1 - TODO.
 *
 * @param [in] ort_v2 - TODO.
 *
 * @return Non-zero value if OK.
 * A zero value if error.
 *
 * @warning This should be a static auxiliary funcion to fdf_get_edge(), but
 * due to 42's norm constraints I had to put it as a publicly accessible
 * function. TODO.
 *
 * @remark Implementation notes:  
 * TODO.
*/
int				fdf_set_edge_visibility(int this_edge,
					t_fdf_object *obj,
					int ort_v1,
					int ort_v2);

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

t_ft_mx			*fdf_get_vertex_mx_sph(t_ft_mx *map_mx, double r);
t_ft_mx			*fdf_get_vertex_mx_cyl(t_ft_mx *map_mx, double r, double h);

void			fdf_destroy_nv(t_fdf_nv *nv);
t_fdf_nv		*fdf_create_nv(t_ft_mx *diag_start,
					t_ft_mx *diag_end,
					t_ft_mx *ort1,
					t_ft_mx *ort2);

#endif
