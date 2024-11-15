/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_step_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:44 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:35:28 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	fdf_round_cdegrees(t_fdf *fdf)
{
	if (fdf->object->w2c_rot_par[0] >= 360)
		fdf->object->w2c_rot_par[0] -= 360;
	if (fdf->object->w2c_rot_par[1] >= 360)
		fdf->object->w2c_rot_par[1] -= 360;
	if (fdf->object->w2c_rot_par[2] >= 360)
		fdf->object->w2c_rot_par[2] -= 360;
	if (fdf->object->w2c_rot_par[0] < 0)
		fdf->object->w2c_rot_par[0] += 360;
	if (fdf->object->w2c_rot_par[1] < 0)
		fdf->object->w2c_rot_par[1] += 360;
	if (fdf->object->w2c_rot_par[2] < 0)
		fdf->object->w2c_rot_par[2] += 360;
}

void	fdf_rotate_step(t_fdf *fdf, int step_x, int step_y, int step_z)
{
	fdf->object->w2c_rot_par[0] += DEG_STEP * step_x;
	fdf->object->w2c_rot_par[1] += DEG_STEP * step_y;
	fdf->object->w2c_rot_par[2] += DEG_STEP * step_z;
	fdf_round_cdegrees(fdf);
	if (fdf->render_request > FROM_CAMERA)
		fdf->render_request = FROM_CAMERA;
}
