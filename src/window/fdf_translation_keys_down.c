/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translation_keys_down.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 18:36:16 by lluque           ###   ########.fr       */
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
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_R))
		tra_step_x++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_T))
		tra_step_y++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_Y))
		tra_step_z++;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_F))
		tra_step_x--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_G))
		tra_step_y--;
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_H))
		tra_step_z--;
	fdf_translate_step(fdf, tra_step_x, tra_step_y, tra_step_z);
	fdf->render_needed = 1;
}

void	fdf_translation_keys_down(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->wlayout->window, MLX_KEY_R)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_T)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_Y)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_F)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_G)
		|| mlx_is_key_down(fdf->wlayout->window, MLX_KEY_H))
		fdf_user_translate(fdf);
}
