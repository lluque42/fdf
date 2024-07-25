/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_autofit_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:34:32 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
