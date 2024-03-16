/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_autofit_transf_par.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/16 12:27:24 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "drawing.h"

// For some reason norminette does not allows including <float.h> which
// I need to get DBL_MAX and DBL_MIN. So I had to use long type limits
// included in the "allowed" header limits.h.
static void	fdf_init_min_max(double *cmin, double *cmax)
{
	cmin[0] = LONG_MAX;
	cmin[1] = LONG_MAX;
	cmin[2] = LONG_MAX;
	cmax[0] = LONG_MIN;
	cmax[1] = LONG_MIN;
	cmax[2] = LONG_MIN;
}

static void	fdf_get_camera_min_max(t_fdf_object *object,
		double *cmin,
		double *cmax)
{
	int	v;
	int	n;

	n = object->camera_mx->n;
	v = 0;
	fdf_init_min_max(cmin, cmax);
	while (v < n)
	{
		if (object->camera_mx->d[v] > cmax[0])
			cmax[0] = object->camera_mx->d[v];
		if (object->camera_mx->d[v] < cmin[0])
			cmin[0] = object->camera_mx->d[v];
		if (object->camera_mx->d[n + v] > cmax[1])
			cmax[1] = object->camera_mx->d[n + v];
		if (object->camera_mx->d[n + v] < cmin[1])
			cmin[1] = object->camera_mx->d[n + v];
		if (object->camera_mx->d[2 * n + v] > cmax[2])
			cmax[2] = object->camera_mx->d[2 * n + v];
		if (object->camera_mx->d[2 * n + v] < cmin[2])
			cmin[2] = object->camera_mx->d[2 * n + v];
		v++;
	}
}

static void	fdf_get_screen_autoscale(uint32_t *img_wh,
		t_fdf_object *object,
		double *cmin,
		double *cmax)
{
	double	scale;
	double	scale_x;
	double	scale_y;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(cmax[0] - cmin[0]);
	delta_y = fabs(cmax[1] - cmin[1]);
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

static void	fdf_get_screen_autooffset(uint32_t *img_wh,
		t_fdf_object *object,
		double *cmin,
		double *cmax)
{
	double	s_x;
	double	s_y;

	s_x = (img_wh[0] / 2) / object->c2s_sca_par[0];
	s_x -= fabs(cmax[0] - cmin[0]) / 2;
	object->c2s_tra_par[0] = s_x - cmin[0];
	s_y = (img_wh[1] / 2) / object->c2s_sca_par[1];
	s_y -= fabs(cmax[1] - cmin[1]) / 2;
	object->c2s_tra_par[1] = s_y - cmin[1];
	object->c2s_tra_par[0] *= object->c2s_sca_par[0];
	object->c2s_tra_par[1] *= object->c2s_sca_par[1];
}

void	fdf_get_autofit_transf_par(uint32_t img_w,
			uint32_t img_h,
			t_fdf_object *object)
{
	double		cmin[3];
	double		cmax[3];
	uint32_t	img_wh[2];

	img_wh[0] = img_w;
	img_wh[1] = img_h;
	fdf_get_camera_min_max(object, cmin, cmax);
	fdf_get_screen_autoscale(img_wh, object, cmin, cmax);
	fdf_get_screen_autooffset(img_wh, object, cmin, cmax);
}
