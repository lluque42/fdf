/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 11:55:08 by lluque           ###   ########.fr       */
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
# include "tesselator.h"
# define DEF_WLAYOUT_RATIO 1.05
/**
 * @struct s_fdf
 * @brief Base for typedef <b>t_fdf</b>.
 * TODO
 * @details This type is used to store a linearly-storaged (row-major order)
 * matrix of double type elements.
 * @var s_ft_mx::d
 * The elements, stored linearly using a row-major order. Element addressing
 * follows this syntax: data[i * n + j] (where i represents the row, m the
 * number of rows and j the column).
 * @var s_ft_mx::m
 * Number of rows as a positive integer value.
 * @var s_ft_mx::n
 * Number of columns as a positive integer value.
 * @var s_ft_mx::is_sqr
 * Non-zero value to quickly check if this matrix is square (m == n).
*/
typedef struct s_wlayout
{
	int32_t	window_w;
	int32_t	window_h;
	int32_t	image_w;
	int32_t	image_h;
	int32_t	wintoimg_xoffset;
	int32_t	wintoimg_yoffset;
	int32_t	drawing_w;
	int32_t	drawing_h;
	int32_t	imgtodrw_xoffset;
	int32_t	imgtodrw_yoffset;
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
 * @var s_fdf::w
 * The 3D world view, that is, the 3D model transformed to be placed in the
 * 3D world.
 * @var s_fdf::c_rot_mx
 * Rotation matrix for world-to-camera space.
 * @var s_fdf::c_tra_mx
 * Translation matrix for world-to-camera space.
 * @var s_fdf::c_sca_mx
 * Scale matrix for world-to-camera space.
 * @var s_fdf::c
 * The 3D camera view, that is, the 3D world transformed from the perspective
 * of the camera.
 * @var s_fdf::vs_pro_mx
 * XY-plane projection matrix.
 * @var s_fdf::vs_tra_mx
 * Translation matrix for camera-to-view screen space.
 * @var s_fdf::vs_sca_mx
 * Scale matrix for camera-to-view screen space.
 * @var s_fdf::s
 * The 2D screen view, that is, the 3D world as the camera sees it transformed
 * to be placed in a finite XY-plane
 * @var s_fdf::wlayout
 * The GUI window layout.
*/
typedef struct s_fdf
{
	t_fdf_model		*m;
	t_ft_mx			*w_rot_mx;
	t_ft_mx			*w_tra_mx;
	t_ft_mx			*w_sca_mx;
	t_ft_mx			*mtow_tr_mx;
	t_fdf_model		*w;
	t_ft_mx			*c_rot_mx;
	t_ft_mx			*c_tra_mx;
	t_ft_mx			*c_sca_mx;
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
	double			s_scale_x;
	double			s_scale_y;
	double			s_offset_x;
	double			s_offset_y;
	t_fdf_wlayout	*wlayout;
}				t_fdf;

/**
 * @brief <b>fdf_create_wlayout</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] m - Number of rows.
 *
 * @param [in] n - Number of columns.
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
 * @param [in] m - Number of rows.
 *
 * @param [in] n - Number of columns.
 *
 * @return TODO..
 * NULL if error.
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
 * @param [in] m - Number of rows.
 *
 * @param [in] n - Number of columns.
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
 * @param [in] m - Number of rows.
 *
 * @param [in] n - Number of columns.
 *
 * @return TODO..
 * NULL if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
void			fdf_destroy_fdf(t_fdf *fdf);

#endif
