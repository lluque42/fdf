/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 00:39:26 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.h
 * TODO.
*/

#ifndef WINDOW_H
# define WINDOW_H
# include "MLX42.h"
//# include "tesselator.h"
# include "fdf.h"
# define DEF_WLAYOUT_RATIO 1.05

/**
 * @struct s_fdf_wlayout
 * @brief Base for typedef <b>t_fdf_wlayout</b>.
 * TODO
 * @details This type is used to store the values that define the GUI's window
 * layout.
 * @var s_fdf_wlayout::window_w
 * TODO.
 * @var s_fdf_wlayout::window_h
 * TODO.
 * @var s_fdf_wlayout::image_w
 * TODO.
 * @var s_fdf_wlayout::image_h
 * TODO.
 * @var s_fdf_wlayout::wintoimg_xoffset
 * TODO.
 * @var s_fdf_wlayout::wintoimg_yoffset
 * TODO.
 * @var s_fdf_wlayout::drawing_w
 * TODO.
 * @var s_fdf_wlayout::drawing_h
 * TODO.
 * @var s_fdf_wlayout::imgtodrw_xoffset
 * TODO.
 * @var s_fdf_wlayout::imgtodrw_yoffset
 * TODO.
 * @var s_fdf_wlayout::window
 * TODO.
 * @var s_fdf_wlayout::image
 * TODO.
*/
typedef struct s_fdf_wlayout
{
	int32_t		window_w;
	int32_t		window_h;
	int32_t		image_w;
	int32_t		image_h;
	int32_t		wintoimg_xoffset;
	int32_t		wintoimg_yoffset;
	int32_t		drawing_w;
	int32_t		drawing_h;
	int32_t		imgtodrw_xoffset;
	int32_t		imgtodrw_yoffset;
	mlx_t		*window;
	mlx_image_t	*image;
}				t_fdf_wlayout;

/**
 * @brief <b>fdf_create_wlayout</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] drw_w - Width in pixels of the actual drawing inside the
 * image. This and drw_h are the base base value to calculate every other
 * dimension of the GUI's window elements.
 *
 * @param [in] drw_h - Height in pixels of the actual drawing inside the
 * image. This and drw_w are the base base value to calculate every other
 * dimension of the GUI's window elements.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
t_fdf_wlayout	*fdf_create_wlayout(int32_t drw_w, int32_t drw_h);

/**
 * @brief <b>fdf_destroy_wlayout</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] wlayout - The window layout structure to be freed.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_destroy_wlayout(t_fdf_wlayout *wlayout);

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
void			fdf_keyhook(mlx_key_data_t keydata, void *fdf);

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
void			fdf_closehook(void *fdf);

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
void			fdf_resizehook(int32_t width, int32_t height, void *fdf);

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and window.h have structs typedefs with member
// types defined in the other file.
typedef struct s_fdf	t_fdf;

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
int				fdf_start_gui(t_fdf *fdf);

#endif
