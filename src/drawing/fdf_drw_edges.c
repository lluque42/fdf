/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:32 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 13:08:33 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "drawing.h"

/**
 * To draw a line I want to iterate x (from ??? to ???) and set the resulting
 * y value. To find out what 'y' value corresponds to each 'x' value I need the
 * line equation (y = f(x)).
 *
 * The generic line equation is:
 * 		y = m * x + b;
 *
 * The constants 'm' (slope) and 'b' (y value when x == 0) are a priori unknown
 * but can be obtained from 2 known points that we know belong to the line
 * (i.e. the start and end points).
 * 
 * The slope 'm' can be calculated as:
 * 		m = (end_y - start_y) / (end_x - start_x);
 *
 * The 'b' can be calculated evaluating the now known 'm' and any of the 2 known
 * points in the line equation:
 * 		y = m * x + b;
 * 		b = y - m * x;
 * 		b = end_y - m * end_x;
 */
// In this case the start_x and end_x are used to hold the range of the
// y component.
t_fdf_line	*fdf_vertical_line(double start_y,
		double end_y,
		double x,
		t_fdf_line *line)
{
	line->m_is_infinite = 1;
	line->first_x = start_y;
	line->last_x = end_y;
	line->vertical_line_x = x;
	if (start_y > end_y)
	{
		line->first_x = end_y;
		line->last_x = start_y;
	}
	return (line);
}

//start and end arguments are vertexes indexes in the model's vertex_mx
t_fdf_line	*fdf_create_line(t_fdf *fdf, int start, int end)
{
	t_fdf_line	*line;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;

	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	start_x = fdf->s->vertex_mx->d[start];
	start_y = fdf->s->vertex_mx->d[fdf->s->vertex_mx->n + start];
	end_x = fdf->s->vertex_mx->d[end];
	end_y = fdf->s->vertex_mx->d[fdf->s->vertex_mx->n + end];
	if ((int)(end_x - start_x) == 0)
		return (fdf_vertical_line(start_y, end_y, start_x, line));
	line->m = (double)(end_y - start_y) / (double)(end_x - start_x);
	line->b = (double)end_y - line->m * (double)end_x;
	line->first_x = start_x;
	line->last_x = end_x;
	if (start_x > end_x)
	{
		line->first_x = end_x;
		line->last_x = start_x;
	}
	return (line);
}

void	fdf_draw_line(t_fdf *fdf, t_fdf_line *line)
{
	uint32_t	pixel_x;
	uint32_t	pixel_y;

	if (!line->m_is_infinite)
	{
		pixel_x = line->first_x - 1;
		while (++pixel_x <= line->last_x)
		{
			pixel_y = (int)(pixel_x * line->m + line->b);
			if (pixel_y > (uint32_t)fdf->wlayout->image_h)
				pixel_y = fdf->wlayout->image_h;
			mlx_put_pixel(fdf->wlayout->image, pixel_x, pixel_y, 0xFFFFFFFF);
		}
		return ;
	}
	pixel_y = line->first_x - 1;
	while (++pixel_y <= line->last_x)
		mlx_put_pixel(fdf->wlayout->image,
			line->vertical_line_x,
			pixel_y, 0xFFFFFFFF);
	return ;
}

int	fdf_drw_edges(t_fdf *fdf)
{
	int			e;
	t_fdf_line	*line;

	// Por ahora...
	fdf->s->edge = fdf->m->edge;
	fdf->s->edges = fdf->m->edges;
	fdf->s->triangle = fdf->m->triangle;
	fdf->s->triangles = fdf->m->triangles;
	e = -1;
	while (++e < fdf->s->edges)
	{
		if (fdf->s->edge[e].is_hidden)
			continue ;
		line = fdf_create_line(fdf, fdf->s->edge[e].start, fdf->s->edge[e].end);
		if (line == NULL)
			return (0);
		fdf_draw_line(fdf, line);
	}
	free(line);
	return (1);
}
