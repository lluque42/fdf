/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_gui_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:22:10 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:45:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf_bonus.h"

// The MLX loop is broken when fdf_exit_program() calls mlx_close_window()
// either on ESCAPE or X button. Then the control is back to fdf_start_gui().
//
// fdf_exit_program() just deletes the image (seemed unnecesary) and closes
// the window by calling mlx_close_window().
//
// A free(fdf->wlayout->window) after mlx_terminate() throws
// errors (double free).
int	fdf_start_gui(t_fdf *fdf)
{
	fdf->wlayout->window = mlx_init(fdf->wlayout->window_w, 
			fdf->wlayout->window_h,
			"lluque's fdf", true);
	if (fdf->wlayout->window == NULL)
		return (perror("fdf"), mlx_terminate(fdf->wlayout->window), 0);
	mlx_resize_hook(fdf->wlayout->window, fdf_resizehook, fdf);
	mlx_key_hook(fdf->wlayout->window, &fdf_keyhook, fdf);
	mlx_close_hook(fdf->wlayout->window, &fdf_closehook, fdf);
	if (!mlx_loop_hook(fdf->wlayout->window, &fdf_generichook, fdf))
		return (perror("fdf"), mlx_terminate(fdf->wlayout->window), 0);
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window,
			fdf->wlayout->image_w,
			fdf->wlayout->image_h);
	if (fdf->wlayout->image == NULL)
		return (perror("fdf"), mlx_terminate(fdf->wlayout->window), 0);
	if (mlx_image_to_window(fdf->wlayout->window,
			fdf->wlayout->image,
			fdf->wlayout->wintoimg_xoffset,
			fdf->wlayout->wintoimg_yoffset) == -1)
		return (perror("fdf"), mlx_terminate(fdf->wlayout->window), 0);
	mlx_loop(fdf->wlayout->window);
	mlx_terminate(fdf->wlayout->window);
	return (1);
}
