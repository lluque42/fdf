/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generichook_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:46:16 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fdf_bonus.h"

void	fdf_generichook(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	fdf_rotation_keys_down(fdf);
	fdf_translation_keys_down(fdf);
	fdf_zoom_keys_down(fdf);
	if (!fdf_render(fdf))
	{
		ft_putendl_fd("fdf: error while rendering", STDERR_FILENO);
		fdf_exit_program(fdf);
	}
}
