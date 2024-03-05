/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 13:46:23 by lluque           ###   ########.fr       */
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
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_get_autofit_transf_matrixes(t_fdf *fdf);

#endif
