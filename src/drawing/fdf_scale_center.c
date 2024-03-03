/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale_center.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/03 16:21:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "drawing.h"

static t_fdf_rectangle	get_min_max(t_ft_mx *vertex_mx)
{
	t_fdf_rectangle	min_max;
	int				i;

	ft_bzero(&min_max, sizeof (t_fdf_rectangle));
	i = 0;
	while (i < vertex_mx->n * 3)
	{
		if (vertex_mx->d[i] > min_max.x1)
			min_max.x1 = vertex_mx->d[i];
		if (vertex_mx->d[i] < min_max.x0)
			min_max.x0 = vertex_mx->d[i];
		if (vertex_mx->d[i + 1] > min_max.y1)
			min_max.y1 = vertex_mx->d[i + 1];
		if (vertex_mx->d[i + 1] < min_max.y0)
			min_max.y0 = vertex_mx->d[i + 1];
		i += 3;
	}
	return (min_max);
}

static	double get_scale(t_fdf_rectangle min_max, double w, double h)
{
	double			sc;

	sc = w / fabs(min_max.x1 - min_max.x0);
	if (sc > h / fabs(min_max.y1 - min_max.y0))
		sc = h / fabs(min_max.y1 - min_max.y0);
	sc *= 0.9;
	return (sc);
}

static	double	get_offsetx(t_fdf_rectangle min_max, double sc, double w)
{
	return ((w - fabs(min_max.x1 - min_max.x0) * sc) / 2 - min_max.x0 * sc);
}

static	double	get_offsety(t_fdf_rectangle min_max, double sc, double h)
{
	return ((h - fabs(min_max.y1 - min_max.y0) * sc) / 2 - min_max.y0 * sc);
}

void	fdf_scale_center(t_fdf *fdf)
{
	t_fdf_rectangle	min_max;
	int				i;
	double			sc;
	double			offset_x;
	double			offset_y;

	min_max = get_min_max(fdf->model->vertex_mx);
	sc = get_scale(min_max, fdf->wlayout->drawing_w, fdf->wlayout->drawing_h);
	offset_x = get_offsetx(min_max, sc, fdf->wlayout->drawing_w);
	offset_y = get_offsety(min_max, sc, fdf->wlayout->drawing_h);
	offset_x += fdf->wlayout->imgtodrw_xoffset;
	offset_y += fdf->wlayout->imgtodrw_yoffset;
	
	ft_mx_smult(fdf->model->vertex_mx, sc);
	
	i = 0;
	while (i < fdf->model->vertex_mx->n * 3)
	{
		fdf->model->vertex_mx->d[i] = fdf->model->vertex_mx->d[i] + offset_x;
		fdf->model->vertex_mx->d[i + 1] = fdf->model->vertex_mx->d[i + 1] + offset_y;
		i += 3;
	}
}
