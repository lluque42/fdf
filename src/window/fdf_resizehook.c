/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_resizehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:11:50 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 01:47:59 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "drawing.h"
#include "libft.h"

void	fdf_resizehook(int32_t width, int32_t height, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	ft_printf("Window (%p) resize detected, ", fdf);
	ft_printf("new size: width = %d and height = %d\n", width, height);
	fdf_recalc_wlayout(fdf, width, height);
	if (!fdf_render(fdf, FROM_SCREEN))
	{
		ft_printf("Error while rendering from resize event\n");
		mlx_close_window(fdf->wlayout->window);
	}
}
