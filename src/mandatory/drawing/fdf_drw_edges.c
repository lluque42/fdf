/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_edges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:31:32 by lluque            #+#    #+#             */
/*   Updated: 2024/07/17 16:53:36 by lluque           ###   ########.fr       */
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
static void	fdf_swap_doubles(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

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
static void	fdf_draw_line(mlx_image_t *image, t_fdf_line *line)
{
	double	pixel_x;
	double	pixel_y;

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
		if (line->i_is_x && pixel_y < image->height)
			mlx_put_pixel(image, round(line->first_i), pixel_y, 0xFFFFFFFF);
		if (!line->i_is_x && pixel_x < image->width)
			mlx_put_pixel(image, pixel_x, round(line->first_i), 0xFFFFFFFF);
		line->first_i++;
	}
}

int	fdf_drw_edges(mlx_image_t *image, t_fdf_object *object)
{
	int			e;
	t_fdf_line	*line;
	t_ft_mx		*s_mx;

	s_mx = object->screen_mx;
	e = -1;
	while (++e < object->edges)
	{
		if (object->edge[e].is_hidden)
			continue ;
		line = fdf_create_line(s_mx->d[object->edge[e].start],
				s_mx->d[object->screen_mx->n + object->edge[e].start],
				s_mx->d[object->edge[e].end],
				s_mx->d[object->screen_mx->n + object->edge[e].end]);
		if (line == NULL)
			return (0);
		fdf_draw_line(image, line);
		free(line);
	}
	return (1);
}
/*
static void fdf_out_of_boundary_pixel(mlx_image_t *image, t_fdf_line *line)
{
		if (line->i_is_x)
		{
			if (round(line->first_i) >= image->width
					|| round(line->first_i) < 0
					|| pixel_y >= image->height
					|| pixel_y < 0)
			{
				printf("[fdf_draw_line] WARNING! PIXEL OUT OF RANGE\n");
				printf("\t i is x!!!\n");
				printf("\timage->width = %d\n", image->width);
				printf("\tround(line->first_i) = %f\n", round(line->first_i));
				printf("\timage->height = %d\n", image->height);
				printf("\tpixel_y = %f\n", pixel_y);
			}
		}
		else
		{
			if (pixel_x >= image->width
					|| pixel_x < 0
					|| round(line->first_i) >= image->height
					|| round(line->first_i) < 0)
			{
				printf("[fdf_draw_line] WARNING! PIXEL OUT OF RANGE\n");
				printf("\t i is y!!!\n");
				printf("\timage->width = %d\n", image->width);
				printf("\tpixel_x = %f\n", pixel_x);
				printf("\timage->height = %d\n", image->height);
				printf("\tround(line->first_i) = %f\n", round(line->first_i));
			}
		}
}
*/
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
	printf("[fdf_drw_edges] Drawing line %d, 
		m = %f, b = %f, first_x = %f, last_x = %f,
		m_is_infinite = %d, vertical_line_x = %f\n",
		e,
		line->m,
		line->b,
		line->first_x,
		line->last_x,
		line->m_is_infinite,
		line->vertical_line_x);
	*/
