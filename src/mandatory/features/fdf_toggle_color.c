/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:44:59 by lluque            #+#    #+#             */
/*   Updated: 2024/07/23 22:55:07 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_toggle_color(t_fdf *fdf)
{
	if (fdf->object->force_monochromatic)
		fdf->object->force_monochromatic = 0;
	else
		fdf->object->force_monochromatic = 1;
	if (fdf->render_request > FROM_IMAGE)
		fdf->render_request = FROM_IMAGE;
}
