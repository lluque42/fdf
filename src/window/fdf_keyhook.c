/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:06:57 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 14:11:18 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft.h"

// Supone que en param viene un mlx_t. Esto se logra al registrar este callback
void	fdf_keyhook(mlx_key_data_t keydata, void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		ft_printf("Escape (%p)\n", fdf);
		mlx_close_window(fdf->wlayout->window);
	}
}
