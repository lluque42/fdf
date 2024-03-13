/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_autofit_transf_par.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 22:50:13 by lluque           ###   ########.fr       */
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

static void	fdf_get_camera_min_max(t_fdf *fdf, double *cmin, double *cmax)
{
	int	v;
	int	n;

	n = fdf->object->camera_mx->n;
	v = 0;
	fdf_init_min_max(cmin, cmax);
	while (v < n)
	{
		if (fdf->object->camera_mx->d[v] > cmax[0])
			cmax[0] = fdf->object->camera_mx->d[v];
		if (fdf->object->camera_mx->d[v] < cmin[0])
			cmin[0] = fdf->object->camera_mx->d[v];
		if (fdf->object->camera_mx->d[n + v] > cmax[1])
			cmax[1] = fdf->object->camera_mx->d[n + v];
		if (fdf->object->camera_mx->d[n + v] < cmin[1])
			cmin[1] = fdf->object->camera_mx->d[n + v];
		if (fdf->object->camera_mx->d[2 * n + v] > cmax[2])
			cmax[2] = fdf->object->camera_mx->d[2 * n + v];
		if (fdf->object->camera_mx->d[2 * n + v] < cmin[2])
			cmin[2] = fdf->object->camera_mx->d[2 * n + v];
		v++;
	}
}

static void	fdf_get_screen_autoscale(t_fdf *fdf, double *cmin, double *cmax)
{
	double	scale;
	double	scale_x;
	double	scale_y;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(cmax[0] - cmin[0]);
	delta_y = fabs(cmax[1] - cmin[1]);
	scale_x = fdf->wlayout->drawing_w / delta_x;
	scale_y = fdf->wlayout->drawing_h / delta_y;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	fdf->object->c2s_sca_par[0] = scale;
	fdf->object->c2s_sca_par[1] = scale;
	fdf->object->c2s_sca_par[2] = 1;
}

static void	fdf_get_screen_autooffset(t_fdf *fdf, double *cmin, double *cmax)
{
	double	s_x;
	double	s_y;

	s_x = (fdf->wlayout->drawing_w / 2) / fdf->object->c2s_sca_par[0];
	s_x -= fabs(cmax[0] - cmin[0]) / 2;
	s_x += fdf->wlayout->imgtodrw_xoffset / fdf->object->c2s_sca_par[0];
	fdf->object->c2s_tra_par[0] = s_x - cmin[0];
	s_y = (fdf->wlayout->drawing_h / 2) / fdf->object->c2s_sca_par[1];
	s_y -= fabs(cmax[1] - cmin[1]) / 2;
	s_y += fdf->wlayout->imgtodrw_yoffset / fdf->object->c2s_sca_par[1];
	fdf->object->c2s_tra_par[1] = s_y - cmin[1];
	fdf->object->c2s_tra_par[0] *= fdf->object->c2s_sca_par[0];
	fdf->object->c2s_tra_par[1] *= fdf->object->c2s_sca_par[1];
}

void	fdf_get_autofit_transf_par(t_fdf *fdf)
{
	double	cmin[3];
	double	cmax[3];

	fdf_get_camera_min_max(fdf, cmin, cmax);
	fdf_get_screen_autoscale(fdf, cmin, cmax);
	fdf_get_screen_autooffset(fdf, cmin, cmax);
}
