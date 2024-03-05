/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 14:23:38 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.h
 * TODO.
*/

#ifndef WINDOW_H
# define WINDOW_H
# include "MLX42.h"
# include "tesselator.h"
# include "fdf.h"

/**
 * @brief <b>fdf_keyhook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] keydata - The data regarding the key event
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_keyhook(mlx_key_data_t keydata, void *fdf);

/**
 * @brief <b>fdf_closehook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_closehook(void *fdf);

/**
 * @brief <b>fdf_resizehook</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] width - The new width in pixels.
 *
 * @param [in] height - The new height in pixels.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_resizehook(int32_t width, int32_t height, void *fdf);

/**
 * @brief <b>fdf_start_gui</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @return Non-zero value if correct.
 * A value of 0 is returned if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int		fdf_start_gui(t_fdf *fdf);

#endif
