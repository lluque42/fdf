/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_edges_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:32 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:32:03 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf_bonus.h"

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
static void	fdf_line_abscissa_clipping(mlx_image_t *image, t_fdf_line *line)
{
	if (line->i_is_x)
	{
		if (round(line->last_i) >= image->width)
			line->last_i = image->width - 1;
		if (round(line->first_i) < 0)
			line->first_i = 0;
	}
	else
	{
		if (round(line->last_i) >= image->height)
			line->last_i = image->height - 1;
		if (round(line->first_i) < 0)
			line->first_i = 0;
	}
}

// This function performs clipping on the ordinate just before mlx_put_pixel.
// The abscissa is clipped in fdf_line_abscissa_clipping().
static void	fdf_draw_line(mlx_image_t *image, t_fdf_line *line, int no_color)
{
	double		pixel_x;
	double		pixel_y;
	uint32_t	color;

	fdf_line_abscissa_clipping(image, line);
	line->first_i--;
	while (++line->first_i < line->last_i)
	{
		if (line->i_is_x)
			pixel_y = round(line->first_i * line->m + line->b);
		else
			pixel_x = round(line->first_i * line->m + line->b);
		if ((line->i_is_x && (pixel_y < 0 || pixel_y >= image->height))
			|| (!line->i_is_x && (pixel_x < 0 || pixel_x >= image->width)))
			continue ;
		color = 0xFFFFFFFF;
		if (no_color)
			color = fdf_calc_line_pixel_color(line, line->first_i); 
		if (line->i_is_x && pixel_y < image->height)
			mlx_put_pixel(image, round(line->first_i), pixel_y, color);
		if (!line->i_is_x && pixel_x < image->width)
			mlx_put_pixel(image, pixel_x, round(line->first_i), color);
	}
}

int	fdf_drw_edges(mlx_image_t *image,
		t_fdf_object *object,
		int drw_hidden_edges,
		int drw_valid_diag_edges)
{
	int			e;
	t_fdf_line	*line;
	int			skip;

	e = -1;
	while (++e < object->edges)
	{
		skip = object->edge[e].is_hidden & !drw_hidden_edges;
		skip = skip & !(object->edge[e].is_valid_diag & drw_valid_diag_edges);
		if (skip)
			continue ;
		line = fdf_create_line(object, e);
		if (line == NULL)
			return (0);
		if (object->map_mx[C] != NULL && !object->force_monochromatic)
			fdf_draw_line(image, line, 1);
		else
			fdf_draw_line(image, line, 0);
		free(line);
	}
	return (1);
}
