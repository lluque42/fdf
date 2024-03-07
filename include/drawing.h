/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/07 20:33:51 by lluque           ###   ########.fr       */
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
 * @struct s_fdf_line
 * @brief Base for typedef <b>t_ft_mx_size</b>.
 * @details This type is used to store a size (int x int).
 * @var s_fdf_line::m
 * The slope of the line.
 * @var s_fdf_line::b
 * The y coordinate value when the associated rect intersects the y axis.
 * @var s_fdf_line::first_x
 * The minimum x coordinate value from where the drawing of the line
 * should start.
 * @var s_fdf_line::last_x
 * The maximum x coordinate value from where the drawing of the line
 * should stop.
*/
typedef struct s_fdf_line
{
	double		m;
	double		b;
	uint32_t	first_x;
	uint32_t	last_x;
	int			m_is_infinite;
	double		vertical_line_x;
}				t_fdf_line;

/**
 * @enum e_render_level
 * @brief Base for typedef <b>t_render_level</b>.
 * @details This type is used in function fdf_render to indicate what is needed
 * to re-calculate and redraw.
 * @var e_render_level::FROM_WORLD
 * The re-calculations must begin at transformations from model to WORLD space.
 * @var e_render_level::FROM_CAMERA
 * The re-calculations must begin at transformations from world to CAMERA space.
 * @var e_render_level::FROM_SCREEN
 * The re-calculations must begin at transformations from camera to SCREEN view
 * space.
 * @var e_render_level::FROM_IMAGE
 * The re-calculations must begin at IMAGE (pixel-based) level.
*/
typedef enum e_render_level
{
	FROM_WORLD,
	FROM_CAMERA,
	FROM_SCREEN,
	FROM_IMAGE
}	t_render_level;

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
//											Cambiar como el fdf_drw_edges/////////////

/**
 * @brief <b>ft_draw_edges</b> -- TODO.
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
int		fdf_drw_edges(t_fdf *fdf);

/**
 * @brief <b>fdf_get_autofit_transf_matrixes</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] fdf - The fdf struct.
 *
 * @return Non-zero value if correct.
 * Value of 0 if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_get_autofit_transf_matrixes(t_fdf *fdf);

/**
 * @brief <b>fdf_render</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf struct.
 *
 * @param [in] render_level - The level from which phase to start the rendering.
 *
 * @return Non-zero value if correct.
 * Value of 0 if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_render(t_fdf *fdf, t_render_level render_level);

#endif
