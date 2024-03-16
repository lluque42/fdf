/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:32 by lluque            #+#    #+#             */
/*   Updated: 2024/03/14 14:27:51 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
static t_fdf_line	*fdf_vertical_line(double start_y,
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
static t_fdf_line	*fdf_create_line(t_fdf_object *object, int start, int end)
{
	t_fdf_line	*line;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;

	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	start_x = object->screen_mx->d[start];
	start_y = object->screen_mx->d[object->screen_mx->n + start];
	end_x = object->screen_mx->d[end];
	end_y = object->screen_mx->d[object->screen_mx->n + end];
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

static void	fdf_draw_line(mlx_image_t *image, t_fdf_line *line)
{
	uint32_t	pixel_x;
	uint32_t	pixel_y;

	if (!line->m_is_infinite)
	{
		pixel_x = line->first_x - 1;
		while (++pixel_x <= line->last_x)
		{
			pixel_y = (int)(pixel_x * line->m + line->b);
			if (pixel_y > (uint32_t)image->height)
				pixel_y = image->height;
			mlx_put_pixel(image, pixel_x, pixel_y, 0xFFFFFFFF);
		}
		return ;
	}
	pixel_y = line->first_x - 1;
	while (++pixel_y <= line->last_x)
		mlx_put_pixel(image,
			line->vertical_line_x,
			pixel_y, 0xFFFFFFFF);
	return ;
}

int	fdf_drw_edges(mlx_image_t *image, t_fdf_object *object)
{
	int			e;
	t_fdf_line	*line;

	e = -1;
	while (++e < object->edges)
	{
		if (object->edge[e].is_hidden)
			continue ;
		line = fdf_create_line(object,
				object->edge[e].start,
				object->edge[e].end);
		if (line == NULL)
			return (0);
		fdf_draw_line(image, line);
	}
	free(line);
	return (1);
}
	/*
	ft_printf("[fdf_drw_edges] The edges from world\n");
	fdf_print_edges(NULL, fdf->object, fdf->object->world_mx);
	ft_printf("[fdf_drw_edges] The edges from camera\n");
	fdf_print_edges(NULL, fdf->object, fdf->object->camera_mx);
	ft_printf("[fdf_drw_edges] The edges from screen\n");
	fdf_print_edges(NULL, fdf->object, fdf->object->screen_mx);
	*/
	// Por ahora...
		/*
		printf("[fdf_drw_edges] Drawing line %d, m = %f, b = %f, first_x = %d, last_x = %d, m_is_infinite = %d, vertical_line_x = %f\n",
			e,
			line->m,
			line->b,
			line->first_x,
			line->last_x,
			line->m_is_infinite,
			line->vertical_line_x);
	*/
