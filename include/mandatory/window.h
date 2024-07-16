/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/04/04 23:22:44 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file window.h
 * TODO.
*/

#ifndef WINDOW_H
# define WINDOW_H
# include "MLX42.h"
# include "fdf.h"

/**
 * @def DEF_DRW_WIDTH
 * The default drawing width at startup. This also determines the GUI's window
 * width through @link DEF_WLAYOUT_RATIO @endlink.
 */
# define DEF_DRW_WIDTH 500

/**
 * @def DEF_DRW_HEIGHT
 * The default drawing height at startup. This also determines the GUI's window
 * height through @link DEF_WLAYOUT_RATIO @endlink.
 */
# define DEF_DRW_HEIGHT 500

/**
 * @def DEF_WLAYOUT_RATIO
 * The ratio to calculate the starting GUI's window size from
 * @link DEF_DRW_WIDTH @endlink and @link DEF_DRW_HEIGHT @endlink. After a
 * window resize, the inverse operation is done: the new window size
 * detemines the drawing's width and height using this constant.
 */
# define DEF_WLAYOUT_RATIO 1.05

// Forward declaration, something like a prototype for typedef.
// Needed because both fdf.h and window.h have structs typedefs with member
// types defined in the other file.
typedef struct s_fdf	t_fdf;

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
	mlx_t		*window;
	mlx_image_t	*image;
}				t_fdf_wlayout;
/**
 * @typedef t_fdf_wlayout
 * Based on the @link s_fdf_wlayout @endlink struct.
 */

/**
 * @brief <b>fdf_create_wlayout</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] drw_w - Width in pixels of the actual drawing inside the
 * image. This and drw_h are the base base value to calculate every other
 * dimension of the GUI's window elements when initializing.
 *
 * @param [in] drw_h - Height in pixels of the actual drawing inside the
 * image. This and drw_w are the base base value to calculate every other
 * dimension of the GUI's window elements when initializing.
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

/**
 * @brief <b>fdf_generichook</b> -- TODO.
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
void			fdf_generichook(void *fdf);

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

/**
 * @brief <b>fdf_zoom_keys_down</b> -- Detects a zooming user request.
 *
 * @details Evaluates pressing of specific function keys to call the apropiate
 * feature function to handle the event and to request re-rendering back to the
 * window's loop.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_zoom_keys_down(t_fdf *fdf);

/**
 * @brief <b>fdf_translation_keys_down</b> -- Detects a zooming user request.
 *
 * @details Evaluates pressing of specific function keys to call the apropiate
 * feature function to handle the event and to request re-rendering back to the
 * window's loop.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_translation_keys_down(t_fdf *fdf);

/**
 * @brief <b>fdf_rotation_keys_down</b> -- Detects a zooming user request.
 *
 * @details Evaluates pressing of specific function keys to call the apropiate
 * feature function to handle the event and to request re-rendering back to the
 * window's loop.
 *
 * @param [in, out] fdf - The fdf structure.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_rotation_keys_down(t_fdf *fdf);

#endif
