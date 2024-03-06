/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:06:09 by lluque            #+#    #+#             */
/*   Updated: 2024/03/06 18:02:04 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

static void	init_mtow_settings(t_fdf *fdf)
{
	fdf->w_deg_x = 0;
	fdf->w_deg_y = 0;
	fdf->w_deg_z = 0;
	fdf->w_offset_x = 0;
	fdf->w_offset_y = 0;
	fdf->w_offset_z = 0;
	fdf->w_sca_x = 1;
	fdf->w_sca_y = 1;
	fdf->w_sca_z = 1;
}

/*
	fdf->c_deg_x = 0;
	fdf->c_deg_y = 0;
	fdf->c_deg_z = 0;

	fdf->c_deg_x = 35.264;
	fdf->c_deg_y = 45;
	fdf->c_deg_z = 0;

	fdf->c_deg_x = 45;
	fdf->c_deg_y = 90 - 35.264;
	fdf->c_deg_z = 45;
 */
static void	init_wtoc_settings(t_fdf *fdf)
{
	fdf->c_deg_x = 45;
	fdf->c_deg_y = 90 - 35.264;
	fdf->c_deg_z = 45;
	fdf->c_offset_x = 0;
	fdf->c_offset_y = 0;
	fdf->c_offset_z = 0;
	fdf->c_sca_x = 1;
	fdf->c_sca_y = 1;
	fdf->c_sca_z = 1;
}

t_fdf	*fdf_create_fdf(int32_t drawing_w, int32_t drawing_h)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof (t_fdf));
	if (fdf == NULL)
		return (NULL);
	fdf->wlayout = fdf_create_wlayout(drawing_w, drawing_h);
	if (fdf->wlayout == NULL)
		return (fdf_destroy_fdf(fdf), NULL);
	init_mtow_settings(fdf);
	init_wtoc_settings(fdf);
	return (fdf);
}
