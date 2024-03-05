/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 00:21:59 by lluque           ###   ########.fr       */
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
 * @enum e_render_level
 * @brief Base for typedef <b>t_render_level</b>.
 * @details This type is used in function fdf_render to indicate what is needed
 * to re-calculate and redraw.
 * @var e_render_level::FROM_WORLD
 * The re-calculations must begin at transormations from model to WORLD space.
 * @var e_render_level::FROM_CAMERA
 * The re-calculations must begin at transormations from world to CAMERA space.
 * @var e_render_level::FROM_SCREEN
 * The re-calculations must begin at transormations from camera to SCREEN view
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
