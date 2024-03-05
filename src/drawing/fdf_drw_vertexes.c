/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_drw_vertexes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:36:09 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 01:37:31 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"

void	fdf_drw_vertexes(mlx_image_t *img, t_ft_mx *v_mx, uint32_t col)
{
	int			col_v;
	uint32_t	pix_x;
	uint32_t	pix_y;

	col_v = 0;
	while (col_v < v_mx->n)
	{
		pix_x = v_mx->d[col_v];
		pix_y = v_mx->d[v_mx->n + col_v];
		mlx_put_pixel(img, pix_x, pix_y, col);
		col_v++;
	}
}
