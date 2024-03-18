/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_zoom_keys_down.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/18 10:06:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "fdf_features.h"

// key down event is inspected again for simmetry (not needed though)
static void	fdf_user_zoom(t_fdf *fdf)
{
	int	sca_step_x;
	int	sca_step_y;
	int	sca_step_z;

	sca_step_x = 0;
	sca_step_y = 0;
	sca_step_z = 0;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_PAGE_UP))
	{
		sca_step_x++;
		sca_step_y++;
		sca_step_z++;
	}
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_PAGE_DOWN))
	{
		sca_step_x--;
		sca_step_y--;
		sca_step_z--;
	}
	fdf_scale_step(fdf, sca_step_x, sca_step_y, sca_step_z);
}

void	fdf_zoom_keys_down(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_PAGE_DOWN)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_PAGE_UP))
		fdf_user_zoom(fdf);
}
