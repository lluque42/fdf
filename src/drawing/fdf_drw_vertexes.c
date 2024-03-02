/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_vertexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:09 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 00:00:16 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"

void	fdf_drw_vertexes(mlx_image_t *img, t_ft_mx *v_mx, uint32_t col)
{
	int			i;
	int			stop;
	uint32_t	pixels;

	pixels = v_mx->n;
	stop = pixels * 3;
	i = 0;
	while (i < stop)
	{
		mlx_put_pixel(img, (uint32_t)v_mx->d[i], (uint32_t)v_mx->d[i + 1], col);
		i += 3;
	}
}
