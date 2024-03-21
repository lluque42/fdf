/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translation_keys_down.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/19 00:38:09 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "fdf_features.h"

// key down event is inspected again to allow simultaneous transformation
// in more than one axis.
static void	fdf_user_translate(t_fdf *fdf)
{
	int	tra_step_x;
	int	tra_step_y;
	int	tra_step_z;

	tra_step_x = 0;
	tra_step_y = 0;
	tra_step_z = 0;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_LEFT))
		tra_step_x++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_LEFT))
		tra_step_y++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_DOWN))
		tra_step_z++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_RIGHT))
		tra_step_x--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_RIGHT))
		tra_step_y--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_UP))
		tra_step_z--;
	fdf_translate_step(fdf, tra_step_x, tra_step_y, tra_step_z);
}

void	fdf_translation_keys_down(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_RIGHT)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_RIGHT)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_UP)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_LEFT)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_LEFT)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_DOWN))
		fdf_user_translate(fdf);
}
