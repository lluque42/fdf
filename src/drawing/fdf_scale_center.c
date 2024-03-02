/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale_center.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/01 23:18:49 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "lin_alg.h"
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

void	fdf_scale_center(t_ft_mx *vertex_mx, double w, double h)
{
	t_fdf_rectangle	min_max;
	int				i;
	double			sc;
	double			offset_x;
	double			offset_y;

	min_max = get_min_max(vertex_mx);
	sc = w / fabs(min_max.x1 - min_max.x0);
	if (sc > h / fabs(min_max.y1 - min_max.y0))
		sc = h / fabs(min_max.y1 - min_max.y0);
	sc *= 0.9;
	ft_mx_smult(vertex_mx, sc);
	offset_x = (w - fabs(min_max.x1 - min_max.x0) * sc) / 2 - min_max.x0 * sc;
	offset_y = (h - fabs(min_max.y1 - min_max.y0) * sc) / 2 - min_max.y0 * sc;
	i = 0;
	while (i < vertex_mx->n * 3)
	{
		vertex_mx->d[i] = vertex_mx->d[i] + offset_x;
		vertex_mx->d[i + 1] = vertex_mx->d[i + 1] + offset_y;
		i += 3;
	}
}
