/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_recalc_wlayout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:50:39 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 01:01:04 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_recalc_wlayout(t_fdf *fdf, int32_t win_w, int32_t win_h)
{
	t_fdf_wlayout	*wlayout;

	wlayout = fdf->wlayout;
	wlayout->window_w = win_w;
	wlayout->window_h = win_h;
	wlayout->image_w = wlayout->window_w / DEF_WLAYOUT_RATIO;
	wlayout->image_h = wlayout->window_h / DEF_WLAYOUT_RATIO;
	wlayout->drawing_w = wlayout->image_w / DEF_WLAYOUT_RATIO;
	wlayout->drawing_h = wlayout->image_h / DEF_WLAYOUT_RATIO;
	wlayout->imgtodrw_xoffset = (wlayout->image_w - wlayout->drawing_w) / 2;
	wlayout->imgtodrw_yoffset = (wlayout->image_h - wlayout->drawing_h) / 2;
	wlayout->wintoimg_xoffset = (wlayout->window_w - wlayout->image_w) / 2;
	wlayout->wintoimg_yoffset = (wlayout->window_h - wlayout->image_h) / 2;
}