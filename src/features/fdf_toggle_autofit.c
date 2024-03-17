/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_autofit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/03/17 15:18:36 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_toggle_autofit(t_fdf *fdf)
{
	if (fdf->autofit)
	{
		fdf->autofit = 0;
		ft_printf("Autofit disabled\n");
	}
	else
	{
		fdf->autofit = 1;
		ft_printf("Autofit enabled\n");
		if (fdf->render_request > FROM_SCREEN)
			fdf->render_request = FROM_SCREEN;
	}
}
