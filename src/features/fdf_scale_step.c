/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_scale_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:32:30 by lluque            #+#    #+#             */
/*   Updated: 2024/03/18 10:08:43 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_scale_step(t_fdf *fdf, int step_x, int step_y, int step_z)
{
	fdf->object->w2c_sca_par[0] += SCA_STEP * step_x;
	fdf->object->w2c_sca_par[1] += SCA_STEP * step_y;
	fdf->object->w2c_sca_par[2] += SCA_STEP * step_z;
	ft_printf("New scale: (%d, %d, %d)\n",
		(int)fdf->object->w2c_sca_par[0],
		(int)fdf->object->w2c_sca_par[1],
		(int)fdf->object->w2c_sca_par[2]);
	if (fdf->render_request > FROM_CAMERA)
		fdf->render_request = FROM_CAMERA;
}
