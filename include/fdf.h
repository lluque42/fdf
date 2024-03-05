/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 22:44:11 by lluque           ###   ########.fr       */
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
# define DEF_WLAYOUT_RATIO 1.05
/**
 * @struct s_wlayout
 * @brief Base for typedef <b>t_wlayout</b>.
 * TODO
 * @details This type is used to store the values that define the GUI's window
 * layout.
 * @var s_wlayout::window_w
 * TODO.
 * @var s_wlayout::window_h
 * TODO.
 * @var s_wlayout::image_w
 * TODO.
 * @var s_wlayout::image_h
 * TODO.
 * @var s_wlayout::wintoimg_xoffset
 * TODO.
 * @var s_wlayout::wintoimg_yoffset
 * TODO.
 * @var s_wlayout::drawing_w
 * TODO.
 * @var s_wlayout::drawing_h
 * TODO.
 * @var s_wlayout::imgtodrw_xoffset
 * TODO.
 * @var s_wlayout::imgtodrw_yoffset
 * TODO.
 * @var s_wlayout::window
 * TODO.
 * @var s_wlayout::image
 * TODO.
*/
typedef struct s_wlayout
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
 * @struct s_fdf
 * @brief Base for typedef <b>t_fdf</b>.
 * TODO
 * @details TODO.
 * @var s_fdf::m
 * The raw 3D model as parsed from file.
 * @var s_fdf::w_rot_mx
 * Rotation matrix for model-to-world space.
 * @var s_fdf::w_tra_mx
 * Translation matrix for model-to-world space.
 * @var s_fdf::w_sca_mx
 * Scale matrix for model-to-world space.
 * @var s_fdf::w_deg_x
 * Rotation degree along X axis when transforming into world space.
 * @var s_fdf::w_deg_y 
 * Rotation degree along Y axis when transforming into world space.
 * @var s_fdf::w_deg_z
 * Rotation degree along Z axis when transforming into world space.
 * @var s_fdf::w_offset_x
 * Translation offset for X axis (TODO before/after scaling) when transforming
 * into world space.
 * @var s_fdf::w_offset_y
 * Translation offset for Y axis (TODO before/after scaling) when transforming
 * into world space.
 * @var s_fdf::w_offset_z
 * Translation offset for Z axis (TODO before/after scaling) when transforming
 * into world space.
 * @var s_fdf::w_sca_x
 * Scale factor for X axis (TODO before/after translating) when transforming
 * into world space.
 * @var s_fdf::w_sca_y
 * Scale factor for Y axis (TODO before/after translating) when transforming
 * into world space.
 * @var s_fdf::w_sca_z
 * Scale factor for Z axis (TODO before/after translating) when transforming
 * into world space.
 * @var s_fdf::mtow_tr_mx
 * The resulting transformation matrix for model-to-world space.
 * @var s_fdf::w
 * The 3D world view, that is, the 3D model transformed to be placed in the
 * 3D world.
 * @var s_fdf::c_rot_mx
 * Rotation matrix for world-to-camera space.
 * @var s_fdf::c_tra_mx
 * Translation matrix for world-to-camera space.
 * @var s_fdf::c_sca_mx
 * Scale matrix for world-to-camera space.
 * @var s_fdf::c_deg_x
 * Rotation degree along X axis when transforming into camera space.
 * @var s_fdf::c_deg_y 
 * Rotation degree along Y axis when transforming into camera space.
 * @var s_fdf::c_deg_z
 * Rotation degree along Z axis when transforming into camera space.
 * @var s_fdf::c_offset_x
 * Translation offset for X axis (TODO before/after scaling) when transforming
 * into camera space.
 * @var s_fdf::c_offset_y
 * Translation offset for Y axis (TODO before/after scaling) when transforming
 * into camera space.
 * @var s_fdf::c_offset_z
 * Translation offset for Z axis (TODO before/after scaling) when transforming
 * into camera space.
 * @var s_fdf::c_sca_x
 * Scale factor for X axis (TODO before/after translating) when transforming
 * into camera space.
 * @var s_fdf::c_sca_y
 * Scale factor for Y axis (TODO before/after translating) when transforming
 * into camera space.
 * @var s_fdf::c_sca_z
 * Scale factor for Z axis (TODO before/after translating) when transforming
 * into camera space.
 * @var s_fdf::wtoc_tr_mx
 * The resulting transformation matrix for world-to-camera space.
 * @var s_fdf::c
 * The 3D camera view, that is, the 3D world transformed from the perspective
 * of the camera.
 * @var s_fdf::s_pro_mx
 * XY-plane projection matrix.
 * @var s_fdf::s_tra_mx
 * Translation matrix for camera-to-screen view space.
 * @var s_fdf::s_sca_mx
 * Scale matrix for camera-to-screen view space.
 * @var s_fdf::ctos_tr_mx
 * The resulting transformation matrix for camera-to-screen view space.
 * @var s_fdf::s
 * The 2D screen view, that is, the 3D world as the camera sees it transformed
 * to be placed in a finite XY-plane
 * @var s_fdf::cminx
 * The minimum value of X of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::cminy
 * The minimum value of Y of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::cminz
 * The minimum value of Z of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::cmaxx
 * The maximum value of X of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::cmaxy
 * The maximum value of Y of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::cmaxz
 * The maximum value of Z of camera space vertexes. Used to autofit the drawing
 * in the screen view space.
 * @var s_fdf::s_sca_x
 * Current X scale for screen view space.
 * @var s_fdf::s_sca_y
 * Current Y scale for screen view space.
 * @var s_fdf::s_offset_x
 * TODO.
 * @var s_fdf::s_offset_y
 * TODO.
 * @var s_fdf::wlayout
 * The GUI window layout.
*/
typedef struct s_fdf
{
	t_fdf_model		*m;
	t_ft_mx			*w_rot_mx;
	t_ft_mx			*w_tra_mx;
	t_ft_mx			*w_sca_mx;
	double			w_deg_x;
	double			w_deg_y;
	double			w_deg_z;
	double			w_offset_x;
	double			w_offset_y;
	double			w_offset_z;
	double			w_sca_x;
	double			w_sca_y;
	double			w_sca_z;
	t_ft_mx			*mtow_tr_mx;
	t_fdf_model		*w;
	t_ft_mx			*c_rot_mx;
	t_ft_mx			*c_tra_mx;
	t_ft_mx			*c_sca_mx;
	double			c_deg_x;
	double			c_deg_y;
	double			c_deg_z;
	double			c_offset_x;
	double			c_offset_y;
	double			c_offset_z;
	double			c_sca_x;
	double			c_sca_y;
	double			c_sca_z;
	t_ft_mx			*wtoc_tr_mx;
	t_fdf_model		*c;
	t_ft_mx			*s_pro_mx;
	t_ft_mx			*s_tra_mx;
	t_ft_mx			*s_sca_mx;
	t_ft_mx			*ctos_tr_mx;
	double			cminx;
	double			cminy;
	double			cminz;
	double			cmaxx;
	double			cmaxy;
	double			cmaxz;
	t_fdf_model		*s;
	double			s_sca_x;
	double			s_sca_y;
	double			s_offset_x;
	double			s_offset_y;
	t_fdf_wlayout	*wlayout;
}				t_fdf;

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
