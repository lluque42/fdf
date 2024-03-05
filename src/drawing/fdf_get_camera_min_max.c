/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_camera_min_max.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:47:12 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 12:04:04 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "drawing.h"

void	fdf_get_camera_min_max(t_fdf *fdf)
{
	int	v;
	int	n;

	n = fdf->c->vertex_mx->n;
	v = 0;
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
