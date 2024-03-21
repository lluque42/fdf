/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotation_keys_down.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/19 00:18:35 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "fdf_features.h"

// key down event is inspected again to allow simultaneous transformation
// in more than one axis.
static void	fdf_user_rotate(t_fdf *fdf)
{
	int	rot_step_x;
	int	rot_step_y;
	int	rot_step_z;

	rot_step_x = 0;
	rot_step_y = 0;
	rot_step_z = 0;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_I))
		rot_step_x++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_O))
		rot_step_y++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_J))
		rot_step_z++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_K))
		rot_step_x--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_U))
		rot_step_y--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_L))
		rot_step_z--;
	fdf_rotate_step(fdf, rot_step_x, rot_step_y, rot_step_z);
}

void	fdf_rotation_keys_down(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_I)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_O)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_J)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_K)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_U)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_L))
		fdf_user_rotate(fdf);
}
