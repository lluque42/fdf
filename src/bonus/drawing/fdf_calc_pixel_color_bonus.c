/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_calc_pixel_color_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:16:19 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:32:24 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "fdf_bonus.h"

static uint32_t	fdf_calc_red(t_fdf_line *line, double i)
{
	uint32_t	start_red;
	double		new_red;

	start_red = fdf_get_color_comp(line->start_color, RGBA_RED);
	new_red = start_red + (line->red_m * (i - line->i_base));
	return ((uint32_t)new_red);
}

static uint32_t	fdf_calc_green(t_fdf_line *line, double i)
{
	uint32_t	start_green;
	double		new_green;

	start_green = fdf_get_color_comp(line->start_color, RGBA_GREEN);
	new_green = start_green + (line->green_m * (i - line->i_base));
	return ((uint32_t)new_green);
}

static uint32_t	fdf_calc_blue(t_fdf_line *line, double i)
{
	uint32_t	start_blue;
	double		new_blue;

	start_blue = fdf_get_color_comp(line->start_color, RGBA_BLUE);
	new_blue = start_blue + (line->blue_m * (i - line->i_base));
	return ((uint32_t)new_blue);
}

static uint32_t	fdf_calc_alpha(t_fdf_line *line, double i)
{
	uint32_t	start_alpha;
	double		new_alpha;

	start_alpha = fdf_get_color_comp(line->start_color, RGBA_ALPHA);
	new_alpha = start_alpha + (line->alpha_m * (i - line->i_base));
	return ((uint32_t)new_alpha);
}

uint32_t	fdf_calc_line_pixel_color(t_fdf_line *line, double i)
{
	uint32_t		color;

	color = fdf_get_color_rgba(fdf_calc_red(line, i),
			fdf_calc_green(line, i),
			fdf_calc_blue(line, i),
			fdf_calc_alpha(line, i));
	return (color);
}
