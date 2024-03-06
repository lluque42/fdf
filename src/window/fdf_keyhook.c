/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:06:57 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 02:01:34 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "drawing.h"
#include "libft.h"

void	fdf_keyhook(mlx_key_data_t keydata, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		ft_printf("Escape (%p)\n", fdf);
		mlx_close_window(fdf->wlayout->window);
	}
	if (keydata.key == MLX_KEY_X && keydata.action == MLX_RELEASE)
	{
		fdf->c_deg_x += 5;
		if (fdf->c_deg_x > 360)
			fdf->c_deg_x -= 360;
		ft_printf("New X rotation angle: %d\n", (int)fdf->c_deg_x);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
	if (keydata.key == MLX_KEY_Y && keydata.action == MLX_RELEASE)
	{
		fdf->c_deg_y += 5;
		if (fdf->c_deg_y > 360)
			fdf->c_deg_y -= 360;
		ft_printf("New Y rotation angle: %d\n", (int)fdf->c_deg_y);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
	if (keydata.key == MLX_KEY_Z && keydata.action == MLX_RELEASE)
	{
		fdf->c_deg_z += 5;
		if (fdf->c_deg_z > 360)
			fdf->c_deg_z -= 360;
		ft_printf("New Z rotation angle: %d\n", (int)fdf->c_deg_z);
		if (!fdf_render(fdf, FROM_CAMERA))
		{
			ft_printf("Error while rendering from rotate-X event\n");
			mlx_close_window(fdf->wlayout->window);
		}
	}
}
