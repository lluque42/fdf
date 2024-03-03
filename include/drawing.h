/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/03 09:51:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file drawing.h
 * TODO Header file for linearly-storaged matrixes (row-major order) operations.
*/

#ifndef DRAWING_H
# define DRAWING_H
# include "MLX42.h"
# include "lin_alg.h"
# include "fdf.h"

/**
 * @struct s_fdf_rectangle
 * @brief Base for typedef <b>t_fdf_rectangle</b>.
 * @details This type is used to store the coordinates of a rectangle as double
 * type values.
 * @var s_fdf_rectangle::x0
 * The x component of corner 0.
 * @var s_fdf_rectangle::y0
 * The y component of corner 0.
 * @var s_fdf_rectangle::x1
 * The x component of corner 1.
 * @var s_fdf_rectangle::y1
 * The y component of corner 1.
*/
typedef struct s_fdf_rectangle
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
}				t_fdf_rectangle;

/**
 * @brief <b>ft_draw_vertexes</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] img - TODO.
 *
 * @param [in] v_mx - Vertex matrix.
 *
 * @param [in] col - Color (32 bits RGB).
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_drw_vertexes(mlx_image_t *img, t_ft_mx *v_mx, uint32_t col);

/**
 * @brief <b>fdf_scale_center</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] fdf - The fdf struct.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_scale_center(t_fdf *fdf);

#endif
