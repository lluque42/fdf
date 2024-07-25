/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_tesselation_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:34:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_toggle_tesselation(t_fdf *fdf)
{
	if (fdf->object->tesselation_type == PLANE_TESSELATION)
		fdf->object->tesselation_type = SPHERICAL_TESSELATION;
	else if (fdf->object->tesselation_type == SPHERICAL_TESSELATION)
		fdf->object->tesselation_type = CYLINDRICAL_TESSELATION;
	else if (fdf->object->tesselation_type == CYLINDRICAL_TESSELATION)
		fdf->object->tesselation_type = PLANE_TESSELATION;
	if (fdf->render_request > FROM_MODEL)
		fdf->render_request = FROM_MODEL;
}
