/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_translate_step.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:26:28 by lluque            #+#    #+#             */
/*   Updated: 2024/03/17 15:17:35 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_translate_step(t_fdf *fdf, int step_x, int step_y, int step_z)
{
	ft_printf("[DUMMY %p]New translation: (%d, %d, %d)\n",
		fdf,
		step_x,
		step_y,
		step_z);
	if (fdf->render_request > FROM_CAMERA)
		fdf->render_request = FROM_CAMERA;
	// DUMMY so far															////////
}
