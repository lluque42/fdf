/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/03/13 14:50:44 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "tesselator.h"
#include "drawing.h"
#include "lin_alg.h"
#include "fdf.h"

int	fdf_start_gui(t_fdf *fdf)
{
	ft_printf("[fdf_start_gui] w: %d h:%d\n",
		fdf->wlayout->window_w,
		fdf->wlayout->window_h);
	fdf->wlayout->window = mlx_init(fdf->wlayout->window_w, 
			fdf->wlayout->window_h,
			"lluque's fdf", true);
	if (fdf->wlayout->window == NULL)
		return (mlx_terminate(fdf->wlayout->window), 0);
	ft_printf("[fdf_start_gui] mlx_init OK\n");
	mlx_resize_hook(fdf->wlayout->window, fdf_resizehook, fdf);
	mlx_key_hook(fdf->wlayout->window, &fdf_keyhook, fdf);
	mlx_close_hook(fdf->wlayout->window, &fdf_closehook, fdf);
	if (!mlx_loop_hook(fdf->wlayout->window, &fdf_generichook, fdf))
		return (mlx_terminate(fdf->wlayout->window), 0);
	ft_printf("[fdf_start_gui] Ahora a renderizar\n");
	if (!fdf_render(fdf, FROM_WORLD))
		return (mlx_terminate(fdf->wlayout->window), 0);
	ft_printf("[fdf_start_gui] Primer renderizado OK\n");
	mlx_loop(fdf->wlayout->window);
	ft_printf("[fdf_start_gui] Sale del loop\n");
	mlx_terminate(fdf->wlayout->window);
	ft_printf("[fdf_start_gui] Hizo el terminate\n");
	return (1);
}
