/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_autofit_transf_par.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:41:29 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "fdf.h"

static void	fdf_get_screen_autoscale(double *img_wh,
		t_fdf_object *object)
{
	double	scale;
	double	scale_x;
	double	scale_y;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(object->c_max[0] - object->c_min[0]);
	delta_y = fabs(object->c_max[1] - object->c_min[1]);
	scale_x = img_wh[0] / delta_x;
	scale_y = img_wh[1] / delta_y;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	object->c2s_sca_par[0] = scale;
	object->c2s_sca_par[1] = scale;
	object->c2s_sca_par[2] = 1;
}

static void	fdf_get_screen_autooffset(double *img_wh,
		t_fdf_object *object)
{
	double	s_x;
	double	s_y;

	s_x = (img_wh[0] / 2) / object->c2s_sca_par[0];
	s_x -= fabs(object->c_max[0] - object->c_min[0]) / 2;
	object->c2s_tra_par[0] = s_x - object->c_min[0];
	s_y = (img_wh[1] / 2) / object->c2s_sca_par[1];
	s_y -= fabs(object->c_max[1] - object->c_min[1]) / 2;
	object->c2s_tra_par[1] = s_y - object->c_min[1];
	object->c2s_tra_par[0] *= object->c2s_sca_par[0];
	object->c2s_tra_par[1] *= object->c2s_sca_par[1];
}

void	fdf_get_autofit_transf_par(uint32_t img_w,
			uint32_t img_h,
			t_fdf_object *object)
{
	double		img_wh[2];

	img_wh[0] = img_w - 1;
	img_wh[1] = img_h - 1;
	fdf_get_vertex_min_max(object->camera_mx, object->c_min, object->c_max);
	fdf_get_screen_autoscale(img_wh, object);
	fdf_get_screen_autooffset(img_wh, object);
}
