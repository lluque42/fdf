/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 16:11:34 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

int	fdf_start_gui(t_fdf *fdf)
{
	fdf->wlayout->window = mlx_init(fdf->wlayout->window_w, 
			fdf->wlayout->window_h,
			"lluque's fdf", true);
	if (fdf->wlayout->window == NULL)
		return (mlx_terminate(fdf->wlayout->window), 0);
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window,
			fdf->wlayout->window_w,
			fdf->wlayout->window_h);
	if (fdf->wlayout->image == NULL)
		return (mlx_terminate(fdf->wlayout->window), 0);
	mlx_image_to_window(fdf->wlayout->window,
		fdf->wlayout->image,
		fdf->wlayout->wintoimg_xoffset,
		fdf->wlayout->wintoimg_yoffset);
	mlx_resize_hook(fdf->wlayout->window, fdf_resizehook, fdf);
	mlx_key_hook(fdf->wlayout->window, &fdf_keyhook, fdf);
	mlx_close_hook(fdf->wlayout->window, &fdf_closehook, fdf);
	if (!fdf_render(fdf, FROM_WORLD))
		return (mlx_terminate(fdf->wlayout->window), 0);
	mlx_loop(fdf->wlayout->window);
	mlx_terminate(fdf->wlayout->window);
	return (1);
}
