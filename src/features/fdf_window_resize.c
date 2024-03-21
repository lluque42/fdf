/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window_resize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:24:29 by lluque            #+#    #+#             */
/*   Updated: 2024/03/21 12:54:25 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"

static void	fdf_recalc_wlayout(t_fdf *fdf, int32_t win_w, int32_t win_h)
{
	t_fdf_wlayout	*wlayout;

	wlayout = fdf->wlayout;
	wlayout->window_w = win_w;
	wlayout->window_h = win_h;
	wlayout->image_w = wlayout->window_w / DEF_WLAYOUT_RATIO;
	wlayout->image_h = wlayout->window_h / DEF_WLAYOUT_RATIO;
	wlayout->wintoimg_xoffset = (wlayout->window_w - wlayout->image_w) / 2;
	wlayout->wintoimg_yoffset = (wlayout->window_h - wlayout->image_h) / 2;
}

void	fdf_window_resize(t_fdf *fdf, int32_t width, int32_t height)
{
	fdf_recalc_wlayout(fdf, width, height);
	if (fdf->wlayout->image_w <= 0 || fdf->wlayout->image_h <= 0)
		return ;
	mlx_delete_image(fdf->wlayout->window, fdf->wlayout->image);
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window,
			fdf->wlayout->image_w,
			fdf->wlayout->image_h);
	mlx_image_to_window(fdf->wlayout->window,
		fdf->wlayout->image,
		fdf->wlayout->wintoimg_xoffset,
		fdf->wlayout->wintoimg_yoffset);
	if (fdf->render_request > FROM_SCREEN)
		fdf->render_request = FROM_SCREEN;
}
	//ft_printf("Window (%p) resize detected, ", fdf);
	//ft_printf("new size: width = %d and height = %d\n", width, height);
