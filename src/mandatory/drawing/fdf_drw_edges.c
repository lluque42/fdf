/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:32 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 22:56:39 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>															////////////
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
static void	fdf_swap_doubles(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	fdf_calc_color_m(t_fdf_line *line)
{
	line->red_m = (fdf_get_color_comp(line->end_color, RGBA_RED)
		- fdf_get_color_comp(line->start_color, RGBA_RED)) / line->i_length;
	line->green_m = (fdf_get_color_comp(line->end_color, RGBA_GREEN)
		- fdf_get_color_comp(line->start_color, RGBA_GREEN)) / line->i_length;
	line->blue_m = (fdf_get_color_comp(line->end_color, RGBA_BLUE)
		- fdf_get_color_comp(line->start_color, RGBA_BLUE)) / line->i_length;
	line->alpha_m = (fdf_get_color_comp(line->end_color, RGBA_ALPHA)
		- fdf_get_color_comp(line->start_color, RGBA_ALPHA)) / line->i_length;
}

static t_fdf_line	*fdf_create_line(t_fdf_object *object, int e)
{
	t_fdf_line	*line;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;


	start_x = object->screen_mx->d[object->edge[e].start];
	start_y = object->screen_mx->d[object->screen_mx->n + object->edge[e].start];
	end_x = object->screen_mx->d[object->edge[e].end];
	end_y = object->screen_mx->d[object->screen_mx->n + object->edge[e].end];


	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	line->m = (end_y - start_y) / (end_x - start_x);
	if (fabs(line->m) <= 1)
	{
		line->b = end_y - line->m * end_x;
		line->first_i = start_x;
		line->last_i = end_x;
		line->i_is_x = 1;
	}
	else
	{
		line->m = (end_x - start_x) / (end_y - start_y);
		line->b = end_x - line->m * end_y;
		line->first_i = start_y;
		line->last_i = end_y;
		line->i_is_x = 0;
		line->start_color = object->edge[e].start_color;
		line->end_color = object->edge[e].end_color;
	}
	line->start_color = object->edge[e].start_color;
	line->end_color = object->edge[e].end_color;
	if (line->first_i > line->last_i)
	{
		fdf_swap_doubles(&line->first_i, &line->last_i);
		line->end_color = object->edge[e].start_color;
		line->start_color = object->edge[e].end_color;
	}
	
	line->i_length = line->last_i - line->first_i;
	line->i_base = line->first_i;
	fdf_calc_color_m(line);
	/*
	printf("start_color = %X end_color = %X red_m = %f green_m = %f  blue_m = %f  alpha_m = %f\n",
			line->start_color,
			line->end_color,
			line->red_m,
			line->green_m,
			line->blue_m,
			line->alpha_m);
	*/



	return (line);
}

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
	while (line->first_i < line->last_i)
	{
		if (line->i_is_x)
			pixel_y = round(line->first_i * line->m + line->b);
		else
			pixel_x = round(line->first_i * line->m + line->b);
		if ((line->i_is_x && (pixel_y < 0 || pixel_y >= image->height))
			|| (!line->i_is_x && (pixel_x < 0 || pixel_x >= image->width)))
		{
			line->first_i++;
			continue ;
		}
		if (no_color)
			color = fdf_calc_line_pixel_color(line, line->first_i); 
		else
			color = 0xFFFFFFFF;
		if (line->i_is_x && pixel_y < image->height)
		{
			//printf("[fdf_draw_line] i is XXX\n");
			//if (fabs(line->m) <= 1)
		//	printf("[fdf_draw_line] fabs(line->m) = %f\n", line->m);
			mlx_put_pixel(image, round(line->first_i), pixel_y, color);
			//mlx_put_pixel(image, round(line->first_i), pixel_y, 0xFFFFFFFF);
		}
		if (!line->i_is_x && pixel_x < image->width)
		{
		//	printf("[fdf_draw_line] i is YYY\n");
			//if (fabs(line->m) <= 1)
			//	printf("[fdf_draw_line] fabs(line->m) <= 1\n");
		//	printf("[fdf_draw_line] fabs(line->m) = %f\n", line->m);
			mlx_put_pixel(image, pixel_x, round(line->first_i), color);
			//mlx_put_pixel(image, pixel_x, round(line->first_i), 0xFFFFFFFF);
		}
		line->first_i++;
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
		if (object->map_mx[C] != NULL && !object->force_monochromatic)  // aquí la opción de feature de quitar o poner color
			fdf_draw_line(image, line, 1);
		else
			fdf_draw_line(image, line, 0);
		free(line);
	}
	return (1);
}
/*
static t_fdf_line	*fdf_create_line(double start_x,
		double start_y,
		double end_x,
		double end_y)
{
	t_fdf_line	*line;

	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	line->m = (end_y - start_y) / (end_x - start_x);
	if (fabs(line->m) <= 1)
	{
		line->b = end_y - line->m * end_x;
		line->first_i = start_x;
		line->last_i = end_x;
		line->i_is_x = 1;
	}
	else
	{
		line->m = (end_x - start_x) / (end_y - start_y);
		line->b = end_x - line->m * end_y;
		line->first_i = start_y;
		line->last_i = end_y;
		line->i_is_x = 0;
	}
	if (line->first_i > line->last_i)
		fdf_swap_doubles(&line->first_i, &line->last_i);
	line->i_length = line->last_i - line->first_i;
	return (line);
}
*/
