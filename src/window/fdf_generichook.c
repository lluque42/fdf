/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generichook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/07 22:12:24 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"
#include "window.h"

void			fdf_generichook(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_X))
	{
		fdf->c_deg_x++;
		if (fdf->c_deg_x > 360)
			fdf->c_deg_x -= 360;
		ft_printf("New X rotation angle: (%d, %d, %d)\n", (int)fdf->c_deg_x, (int)fdf->c_deg_y, (int)fdf->c_deg_z);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_Y))
	{
		fdf->c_deg_y++;
		if (fdf->c_deg_y > 360)
			fdf->c_deg_y -= 360;
		ft_printf("New Y rotation angle: (%d, %d, %d)\n", (int)fdf->c_deg_x, (int)fdf->c_deg_y, (int)fdf->c_deg_z);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_Z))
	{
		fdf->c_deg_z++;
		if (fdf->c_deg_z > 360)
			fdf->c_deg_z -= 360;
		ft_printf("New Z rotation angle: (%d, %d, %d)\n", (int)fdf->c_deg_x, (int)fdf->c_deg_y, (int)fdf->c_deg_z);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
}
