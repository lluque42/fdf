/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_autofit_transf_matrixes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 22:30:10 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <limits.h>
#include "drawing.h"

// For some reason norminette does not allows including <float.h> which
// I need to get DBL_MAX and DBL_MIN. So I had to use long type limits
// included in the "allowed" header limits.h.
static void	fdf_init_min_max(t_fdf *fdf)
{
	fdf->cminx = LONG_MAX;
	fdf->cminy = LONG_MAX;
	fdf->cminz = LONG_MAX;
	fdf->cmaxx = LONG_MIN;
	fdf->cmaxy = LONG_MIN;
	fdf->cmaxz = LONG_MIN;
}

static void	fdf_get_camera_min_max(t_fdf *fdf)
{
	int	v;
	int	n;

	n = fdf->c->vertex_mx->n;
	v = 0;
	fdf_init_min_max(fdf);
	while (v < n)
	{
		if (fdf->c->vertex_mx->d[v] > fdf->cmaxx)
			fdf->cmaxx = fdf->c->vertex_mx->d[v];
		if (fdf->c->vertex_mx->d[v] < fdf->cminx)
			fdf->cminx = fdf->c->vertex_mx->d[v];
		if (fdf->c->vertex_mx->d[n + v] > fdf->cmaxy)
			fdf->cmaxy = fdf->c->vertex_mx->d[n + v];
		if (fdf->c->vertex_mx->d[n + v] < fdf->cminy)
			fdf->cminy = fdf->c->vertex_mx->d[n + v];
		if (fdf->c->vertex_mx->d[2 * n + v] > fdf->cmaxz)
			fdf->cmaxz = fdf->c->vertex_mx->d[2 * n + v];
		if (fdf->c->vertex_mx->d[2 * n + v] < fdf->cminz)
			fdf->cminz = fdf->c->vertex_mx->d[2 * n + v];
		v++;
	}
}

static void	fdf_get_screen_autoscale(t_fdf *fdf)
{
	double	scale;
	double	scale_x;
	double	scale_y;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(fdf->cmaxx - fdf->cminx);
	delta_y = fabs(fdf->cmaxy - fdf->cminy);
	scale_x = fdf->wlayout->drawing_w / delta_x;
	scale_y = fdf->wlayout->drawing_h / delta_y;
	if (scale_x < scale_y)
		scale = scale_x;
	else
		scale = scale_y;
	fdf->s_sca_x = scale;
	fdf->s_sca_y = scale;
}

static void	fdf_get_screen_autooffset(t_fdf *fdf)
{
	double	s_x;
	double	s_y;

	s_x = (fdf->wlayout->drawing_w / 2) / fdf->s_sca_x;
	s_x -= fabs(fdf->cmaxx - fdf->cminx) / 2;
	s_x += fdf->wlayout->imgtodrw_xoffset / fdf->s_sca_x;
	fdf->s_offset_x = s_x - fdf->cminx;
	s_y = (fdf->wlayout->drawing_h / 2) / fdf->s_sca_y;
	s_y -= fabs(fdf->cmaxy - fdf->cminy) / 2;
	s_y += fdf->wlayout->imgtodrw_yoffset / fdf->s_sca_y;
	fdf->s_offset_y = s_y - fdf->cminy;
	fdf->s_offset_x *= fdf->s_sca_x;
	fdf->s_offset_y *= fdf->s_sca_y;
}

int	fdf_get_autofit_transf_matrixes(t_fdf *fdf)
{
	fdf_get_camera_min_max(fdf);
	fdf_get_screen_autoscale(fdf);
	fdf_get_screen_autooffset(fdf);
	fdf->s_sca_mx = ft_mx_create_scale_mx(fdf->s_sca_x, fdf->s_sca_y, 0);
	if (fdf->s_sca_mx == NULL)
		return (0);
	fdf->s_tra_mx = ft_mx_create_transl_mx(fdf->s_offset_x, fdf->s_offset_y, 0);
	if (fdf->s_tra_mx == NULL)
		return (0);
	return (1);
}
