/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/04/04 23:40:04 by lluque           ###   ########.fr       */
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
//# include "drawing.h"

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and window.h have structs typedefs with member
// types defined in the other file.
typedef struct s_fdf_wlayout	t_fdf_wlayout;

/**
 * @enum e_render_request
 * @brief Base for typedef <b>t_render_request</b>.
 * @details This type is used in function fdf_render to indicate what is needed
 * to re-calculate and redraw.
 * @var e_render_request::FROM_MODEL
 * The re-calculations must begin at the tesselation of the data from the map_mx
 * to MODEL space.
 * @var e_render_request::FROM_WORLD
 * The re-calculations must begin at transformations from model to WORLD space.
 * @var e_render_request::FROM_CAMERA
 * The re-calculations must begin at transformations from world to CAMERA space.
 * @var e_render_request::FROM_SCREEN
 * The re-calculations must begin at transformations from camera to SCREEN view
 * space.
 * @var e_render_request::FROM_IMAGE
 * The re-calculations must begin at IMAGE (pixel-based) level.
 * @var e_render_request::NO_RENDER
 * There is no need to render.
*/
typedef enum e_render_request
{
	FROM_MODEL,
	FROM_WORLD,
	FROM_CAMERA,
	FROM_SCREEN,
	FROM_IMAGE,
	NO_RENDER
}	t_render_request;
/**
 * @typedef t_render_request
 * Based on the @link e_render_request @endlink enum.
 */

/**
 * @struct s_fdf
 * @brief Base for typedef <b>t_fdf</b>.
 * TODO
 * @details TODO.
 * @var s_fdf::object
 * The current 3D object to render.
 * @var s_fdf::wlayout
 * The GUI window layout.
 * @var s_fdf::render_request
 * Enum to signal the need and depth of renderization.
 * @var s_fdf::autofit
 * When 1: Every renderization will draw an auto-scaled and centered drawing; 
 * user's zoom (scale) and translation request will be ignored while set;
 * but user's rotations will still be available.
*/
typedef struct s_fdf
{
	t_fdf_object		*object;
	t_fdf_wlayout		*wlayout;
	int					autofit;
	t_render_request	render_request;
}				t_fdf;
/**
 * @typedef t_fdf
 * Based on the @link s_fdf @endlink struct.
 */

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
 * @param [in] map_mx - The map to create the 3D object from.
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
t_fdf			*fdf_create_fdf(int32_t drawing_w,
					int32_t drawing_h,
					t_ft_mx *map_mx);

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
