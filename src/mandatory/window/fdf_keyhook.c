/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:06:57 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 13:11:14 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "drawing.h"
#include "libft.h"
#include "fdf_features.h"

void	fdf_keyhook(mlx_key_data_t keydata, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		fdf_exit_program(fdf);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		fdf_toggle_autofit(fdf);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		fdf_toggle_tesselation(fdf);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		fdf_toggle_drw_diags(fdf);
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
		fdf_toggle_drw_hidden(fdf);
}
