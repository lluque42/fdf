/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:05:34 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 19:11:04 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

unsigned char	fdf_get_color_comp(uint32_t color, int rgba_color_mask)
{
	int				right_shift;
	int				temp;
	unsigned char	color_component;

	right_shift = 32;
	temp = rgba_color_mask;
	while (temp != 0)
	{
		temp <<= 1;
		right_shift--;
	}
	color_component = (color & rgba_color_mask) >> right_shift;
	return (color_component);
}	

uint32_t	fdf_get_color_rgba(unsigned char red,
				unsigned char green,
				unsigned char blue,
				unsigned char alpha)
{
	uint32_t	color;

	color = red << 24;
	color += (green << 16);
	color += (blue << 8);
	color += alpha;
	return (color);
}
