/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_tesselation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 09:58:13 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_toggle_tesselation(t_fdf *fdf)
{
	if (fdf->object->tesselation_type == PLANE_TESSELATION)
	{
		fdf->object->tesselation_type = SPHERICAL_TESSELATION;
		ft_printf("Tesselation changed from plane to spherical\n");
	}
	else if (fdf->object->tesselation_type == SPHERICAL_TESSELATION)
	{
		fdf->object->tesselation_type = CYLINDRICAL_TESSELATION;
		ft_printf("Tesselation changed from spherical to cylindrical\n");
	}
	else if (fdf->object->tesselation_type == CYLINDRICAL_TESSELATION)
	{
		fdf->object->tesselation_type = PLANE_TESSELATION;
		ft_printf("Tesselation changed from cylindrical to plane\n");
	}
	if (fdf->render_request > FROM_MODEL)
		fdf->render_request = FROM_MODEL;
}
