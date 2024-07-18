/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_autofit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 03:53:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_toggle_autofit(t_fdf *fdf)
{
	if (fdf->autofit)
		fdf->autofit = 0;
	else
	{
		fdf->autofit = 1;
		if (fdf->render_request > FROM_SCREEN)
			fdf->render_request = FROM_SCREEN;
	}
}
