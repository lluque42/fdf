/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale_center.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 12:29:20 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "drawing.h"

void	fdf_get_screen_autoscale(t_fdf *fdf)
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
	fdf->s_scale_x = scale;
	fdf->s_scale_y = scale;
}

void	fdf_get_screen_autooffset(t_fdf *fdf)
{
	double	s_x;
	double	s_y;

	s_x = (fdf->wlayout->drawing_w / 2) / fdf->s_scale_x;
	s_x -= fabs(fdf->cmaxx - fdf->cminx) / 2;
	s_x += fdf->wlayout->imgtodrw_xoffset / fdf->s_scale_x;
	fdf->s_offset_x = s_x - fdf->cminx;
	s_y = (fdf->wlayout->drawing_h / 2) / fdf->s_scale_y;
	s_y -= fabs(fdf->cmaxy - fdf->cminy) / 2;
	s_y += fdf->wlayout->imgtodrw_yoffset / fdf->s_scale_y;
	fdf->s_offset_y = s_y - fdf->cminy;
	fdf->s_offset_x *= fdf->s_scale_x;
	fdf->s_offset_y *= fdf->s_scale_y;
}

t_ft_mx	*fdf_create_vsautofit_scale_mx(t_fdf *fdf)
{
	fdf_get_screen_autoscale(fdf);
	return (ft_mx_create_scale_mx(fdf->s_scale_x, fdf->s_scale_y, 0));
}

t_ft_mx	*fdf_create_vsautofit_transl_mx(t_fdf *fdf)
{
	fdf_get_screen_autooffset(fdf);
	return (ft_mx_create_transl_mx(fdf->s_offset_x, fdf->s_offset_y, 0));
}
