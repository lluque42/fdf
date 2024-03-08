/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:12:44 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 15:20:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"
#include "drawing.h"

static void	fdf_round_cdegrees(t_fdf *fdf)
{
	if (fdf->c_deg_x >= 360)
		fdf->c_deg_x -= 360;
	if (fdf->c_deg_y >= 360)
		fdf->c_deg_y -= 360;
	if (fdf->c_deg_z >= 360)
		fdf->c_deg_z -= 360;
	if (fdf->c_deg_x < 0)
		fdf->c_deg_x += 360;
	if (fdf->c_deg_y < 0)
		fdf->c_deg_y += 360;
	if (fdf->c_deg_z < 0)
		fdf->c_deg_z += 360;
}

void	fdf_rotate_step(t_fdf *fdf, int step_x, int step_y, int step_z)
{
	fdf->c_deg_x += DEG_STEP * step_x;
	fdf->c_deg_y += DEG_STEP * step_y;
	fdf->c_deg_z += DEG_STEP * step_z;
	fdf_round_cdegrees(fdf);
	ft_printf("New rotation angle: (%d, %d, %d)\n",
		(int)fdf->c_deg_x,
		(int)fdf->c_deg_y,
		(int)fdf->c_deg_z);
}
