/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:08:53 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 17:41:07 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_swap_doubles(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	fdf_calc_color_m(t_fdf_line *line)
{
	line->red_m = fdf_get_color_comp(line->end_color, RGBA_RED);
	line->red_m -= fdf_get_color_comp(line->start_color, RGBA_RED);
	line->red_m /= line->i_length;
	line->green_m = fdf_get_color_comp(line->end_color, RGBA_GREEN);
	line->green_m -= fdf_get_color_comp(line->start_color, RGBA_GREEN);
	line->green_m /= line->i_length;
	line->blue_m = fdf_get_color_comp(line->end_color, RGBA_BLUE);
	line->blue_m -= fdf_get_color_comp(line->start_color, RGBA_BLUE);
	line->blue_m /= line->i_length;
	line->alpha_m = fdf_get_color_comp(line->end_color, RGBA_ALPHA);
	line->alpha_m -= fdf_get_color_comp(line->start_color, RGBA_ALPHA);
	line->alpha_m /= line->i_length;
}

static t_fdf_line	*fdf_low_slope_line_case(double start_x,
		double start_y, double end_x, double end_y)
{
	t_fdf_line	*line;

	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	line->m = (end_y - start_y) / (end_x - start_x);
	line->b = end_y - line->m * end_x;
	line->first_i = start_x;
	line->last_i = end_x;
	line->i_is_x = 1;
	return (line);
}

static t_fdf_line	*fdf_high_slope_line_case(double start_x,
		double start_y, double end_x, double end_y)
{
	t_fdf_line	*line;

	line = ft_calloc(1, sizeof (t_fdf_line));
	if (line == NULL)
		return (NULL);
	line->m = (end_x - start_x) / (end_y - start_y);
	line->b = end_x - line->m * end_y;
	line->first_i = start_y;
	line->last_i = end_y;
	line->i_is_x = 0;
	return (line);
}

t_fdf_line	*fdf_create_line(t_fdf_object *obj, int e)
{
	t_fdf_line	*line;
	double		start_x;
	double		start_y;
	double		end_x;
	double		end_y;

	start_x = obj->screen_mx->d[obj->edge[e].start];
	start_y = obj->screen_mx->d[obj->screen_mx->n + obj->edge[e].start];
	end_x = obj->screen_mx->d[obj->edge[e].end];
	end_y = obj->screen_mx->d[obj->screen_mx->n + obj->edge[e].end];
	if (fabs((end_y - start_y) / (end_x - start_x)) <= 1)
		line = fdf_low_slope_line_case(start_x, start_y, end_x, end_y);
	else
		line = fdf_high_slope_line_case(start_x, start_y, end_x, end_y);
	line->start_color = obj->edge[e].start_color;
	line->end_color = obj->edge[e].end_color;
	if (line->first_i > line->last_i)
	{
		fdf_swap_doubles(&line->first_i, &line->last_i);
		line->end_color = obj->edge[e].start_color;
		line->start_color = obj->edge[e].end_color;
	}
	line->i_length = line->last_i - line->first_i;
	line->i_base = line->first_i;
	return (fdf_calc_color_m(line), line);
}
