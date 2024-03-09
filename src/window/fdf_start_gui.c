/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 21:37:07 by lluque           ###   ########.fr       */
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
	mlx_resize_hook(fdf->wlayout->window, fdf_resizehook, fdf);
	mlx_key_hook(fdf->wlayout->window, &fdf_keyhook, fdf);
	mlx_close_hook(fdf->wlayout->window, &fdf_closehook, fdf);
	if (!mlx_loop_hook(fdf->wlayout->window, &fdf_generichook, fdf))
		return (mlx_terminate(fdf->wlayout->window), 0);
	if (!fdf_render(fdf, FROM_WORLD))
		return (mlx_terminate(fdf->wlayout->window), 0);
	mlx_loop(fdf->wlayout->window);
	ft_printf("[fdf_start_gui] Sale del loop\n");
	mlx_terminate(fdf->wlayout->window);
	ft_printf("[fdf_start_gui] Hizo el terminate\n");
	return (1);
}
