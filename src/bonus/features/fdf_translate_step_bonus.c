/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translate_step_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:26:28 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:33:56 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_translate_step(t_fdf *fdf, int step_x, int step_y, int step_z)
{
	fdf->object->w2c_tra_par[0] += TRA_STEP * step_x;
	fdf->object->w2c_tra_par[1] += TRA_STEP * step_y;
	fdf->object->w2c_tra_par[2] += TRA_STEP * step_z;
	if (fdf->render_request > FROM_CAMERA)
		fdf->render_request = FROM_CAMERA;
}
	/*
	ft_printf("New translation: (%d, %d, %d)\n",
		(int)fdf->object->w2c_tra_par[0],
		(int)fdf->object->w2c_tra_par[1],
		(int)fdf->object->w2c_tra_par[2]);
	*/
