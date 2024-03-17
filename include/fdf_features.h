/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_features.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/17 21:09:07 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file fdf_features.h
 * Header file for functions to respond to GUI events that are supposed to
 * offer a feature to the user (rotate, translate, zoom, ...).
 *
 * The GUI hooks just call these functions which take the required actions
 * and re-renders.
 *
 * Go to the GUI hooks functions (both key and generic hooks) to edit the
 * events (such as key presses) that match the features in this file.
*/

#ifndef FDF_FEATURES_H
# define FDF_FEATURES_H
# include "fdf.h"
# define DEG_STEP 1
# define TRA_STEP 1
# define SCA_STEP 1

/**
 * @brief <b>fdf_exit_program</b> -- TODO.
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
void	fdf_exit_program(t_fdf *fdf);

/**
 * @brief <b>fdf_toggle_autofit</b> -- TODO.
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
void	fdf_toggle_autofit(t_fdf *fdf);

/**
 * @brief <b>fdf_rotate_step</b> -- Increases/decreases rotation angles.
 *
 * @details Increases or decreases rotation angles along each axis by DEG_STEP
 * and re-renders.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] step_x - Number of steps (DEG_STEP degrees) to modify the
 * X rotation angle.
 *
 * @param [in] step_y - Number of steps (DEG_STEP degrees) to modify the
 * Y rotation angle.
 *
 * @param [in] step_z - Number of steps (DEG_STEP degrees) to modify the
 * Z rotation angle.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_rotate_step(t_fdf *fdf, int step_x, int step_y, int step_z);

/**
 * @brief <b>fdf_translate_step</b> -- Increases/decreases translation offsets.
 *
 * @details Increases or decreases translations offsets  along each axis by
 * TRA_STEP and re-renders.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] step_x - Number of steps (TRA_STEP degrees) to modify the
 * X translation offset.
 *
 * @param [in] step_y - Number of steps (TRA_STEP degrees) to modify the
 * Y translation offset.
 *
 * @param [in] step_z - Number of steps (TRA_STEP degrees) to modify the
 * Z translation offset.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_translate_step(t_fdf *fdf, int step_x, int step_y, int step_z);

/**
 * @brief <b>fdf_scale_step</b> -- Increases/decreases scale.
 *
 * @details Increases or decreases scale along each axis by SCA_STEP
 * and re-renders.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] step_x - Number of steps (SCA_STEP degrees) to modify the
 * X scale.
 *
 * @param [in] step_y - Number of steps (SCA_STEP degrees) to modify the
 * Y scale.
 *
 * @param [in] step_z - Number of steps (SCA_STEP degrees) to modify the
 * Z scale.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_scale_step(t_fdf *fdf, int step_x, int step_y, int step_z);

/**
 * @brief <b>fdf_window_resize</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @param [in] width - The new width of the window.
 *
 * @param [in] height - The new height of the window.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void	fdf_window_resize(t_fdf *fdf, int32_t width, int32_t height);

#endif
