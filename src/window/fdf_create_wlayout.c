/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_wlayout.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:49:59 by lluque            #+#    #+#             */
/*   Updated: 2024/03/14 14:40:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

t_fdf_wlayout	*fdf_create_wlayout(int32_t drw_w, int32_t drw_h)
{
	t_fdf_wlayout	*wlayout;

	wlayout = malloc(sizeof (t_fdf_wlayout));
	if (wlayout == NULL)
		return (NULL);
	wlayout->image_w = drw_w;
	wlayout->image_h = drw_h;
	wlayout->window_w = wlayout->image_w * DEF_WLAYOUT_RATIO;
	wlayout->window_h = wlayout->image_h * DEF_WLAYOUT_RATIO;
	wlayout->wintoimg_xoffset = (wlayout->window_w - wlayout->image_w) / 2;
	wlayout->wintoimg_yoffset = (wlayout->window_h - wlayout->image_h) / 2;
	return (wlayout);
}
