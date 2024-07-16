/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_resizehook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:11:50 by lluque            #+#    #+#             */
/*   Updated: 2024/03/17 19:52:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "drawing.h"
#include "fdf_features.h"
#include "libft.h"

void	fdf_resizehook(int32_t width, int32_t height, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	fdf_window_resize(fdf, width, height);
}
/*
	ft_printf("Window (%p) resize detected, ", fdf);
	ft_printf("new size: width = %d and height = %d\n", width, height);
	fdf_recalc_wlayout(fdf, width, height);
//	fdf->render_needed = 1;
	//ft_printf("[fdf_resizehook]Image to be deleted %p\n", fdf->wlayout->image);
	mlx_delete_image(fdf->wlayout->window, fdf->wlayout->image);
	fdf->wlayout->image = mlx_new_image(fdf->wlayout->window,
			fdf->wlayout->image_w,
			fdf->wlayout->image_h);
	//ft_printf("[fdf_resizehook]New image %p\n", fdf->wlayout->image);
	// Aqui hay problemas... No hay retorno en los hooks... Hay que cerrar
	// la ventana antes de terminar...
//	if (fdf->wlayout->image == NULL)
//		return (mlx_terminate(fdf->wlayout->window), 0);
	mlx_image_to_window(fdf->wlayout->window,
		fdf->wlayout->image,
		fdf->wlayout->wintoimg_xoffset,
		fdf->wlayout->wintoimg_yoffset);
	if (fdf->render_request < FROM_SCREEN)
		fdf->render_request = FROM_SCREEN;
	if (!fdf_render(fdf))
	{
		ft_printf("Error while rendering from resize event\n");
		mlx_close_window(fdf->wlayout->window);
	}
}
*/
