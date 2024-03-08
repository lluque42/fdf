/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_generichook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:56:31 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 18:27:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing.h"
#include "window.h"
#include "fdf_features.h"

void	fdf_generichook(void *f)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)f;
	fdf_rotation_keys_down(fdf);
	fdf_translation_keys_down(fdf);
	fdf_zoom_keys_down(fdf);
	if (fdf->render_needed)
	{
		if (!fdf_render(fdf, FROM_CAMERA))
			fdf_exit_program(fdf);
	}
}
