/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 14:49:42 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file fdf.h
 * Header file for defining the structures with pointers to every piece
 * of data needed to create the GUI and handle the rendering of the 3D model
 * into the application window. TODO
*/

#ifndef FDF_H
# define FDF_H
# include <stdint.h>
# include "MLX42.h"
# include "tesselator.h"
# include "window.h"

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and window.h have structs typedefs with member
// types defined in the other file.
typedef struct s_fdf_wlayout	t_fdf_wlayout;

/**
 * @struct s_fdf
 * @brief Base for typedef <b>t_fdf</b>.
 * TODO
 * @details TODO.
 * @var s_fdf::object
 * The current 3D object to render.
 * @var s_fdf::wlayout
 * The GUI window layout.
 * @var s_fdf::render_needed
 * Flag to signal the need to compute a drawing renderization.
 * @var s_fdf::autofit
 * When 1: Every renderization will draw an auto-scaled and centered drawing; 
 * user's zoom (scale) and translation request will be ignored while set;
 * but user's rotations will still be available.
*/
typedef struct s_fdf
{
	t_fdf_object	*object;
	t_fdf_wlayout	*wlayout;
	int				autofit;
	int				render_needed;
}				t_fdf;

/**
 * @brief <b>fdf_create_fdf</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] drawing_w - Width in pixels of the actual drawing inside the
 * image.
 *
 * @param [in] drawing_h - Height in pixels of the actual drawing inside the
 * image.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf			*fdf_create_fdf(int32_t drawing_w, int32_t drawing_h);

/**
 * @brief <b>fdf_destroy_fdf</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] fdf - The fdf structure to be freed.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_destroy_fdf(t_fdf *fdf);

#endif
