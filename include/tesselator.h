/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesselator.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 10:58:12 by lluque           ###   ########.fr       */
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
 * @struct s_ft_edge
 * @brief Base for typedef <b>t_ft_edge</b>.
 * @details This type is used to store an edge, defined as two indexes to the
 * starting and ending vertexes as stored in a vertex matrix
 * @var s_ft_edge::start
 * The index of the starting vertex stored in a vertex matrix.
 * @var s_ft_edge::end
 * The index of the ending vertex stored in a vertex matrix.
 * @var s_ft_edge::is_hidden
 * A non-zero value to signal that this edge must not be drawn.
*/
typedef struct s_ft_edge
{
	int	start;
	int	end;
	int	is_hidden;
}				t_ft_edge;

/**
 * @struct s_fdf_model
 * @brief Base for typedef <b>t_fdf_model</b>.
 * @details This type is used to store a 3D model.
 * @var s_fdf_model::vertex_mx
 * The vertex matrix.
 * TODO
*/
typedef struct s_fdf_model
{
	t_ft_mx		*vertex_mx;
	t_ft_mx		*edge_mx;
	t_ft_mx		*triangle_mx;
}				t_fdf_model;

/**
 * @brief <b>fdf_create_model</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] model - The pointer to the model to be freed.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_model	*fdf_create_model(void);

/**
 * @brief <b>fdf_destroy_model</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] model - The pointer to the model to be freed.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void		fdf_destroy_model(t_fdf_model *model);

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
t_fdf_model	*fdf_tesselate_map(t_ft_mx	*map_mx);

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
 * TODO.
*/
t_ft_mx		*fdf_get_vertex_mx(t_ft_mx *map_mx);

/**
 * @brief <b>fdf_create_rotmx_x</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] degree - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx		*fdf_create_rotmx_x(double degree);

/**
 * @brief <b>fdf_create_rotmx_y</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] degree - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx		*fdf_create_rotmx_y(double degree);

/**
 * @brief <b>fdf_create_rotmx_z</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] degree - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx		*fdf_create_rotmx_z(double degree);

/**
 * @brief <b>fdf_get_rot_mx</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] degree - TODO.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_ft_mx		*fdf_get_rot_mx(double x, double y, double z);

/**
 * @brief <b>fdf_rotate_xyz_deg</b> -- TODO.
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
 * @param [in, out] vertex_mx - TODO.
 *
 * @param [in] x - Rotation degree from X axis.
 *
 * @param [in] y - Rotation degree from Y axis.
 *
 * @param [in] z - Rotation degree from Z axis.
 *
 * @return Non-zero value if correct.
 * A value of 0 is returned if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int			fdf_rot_xyz_deg(t_ft_mx *vertex_mx, double x, double y, double z);

#endif
