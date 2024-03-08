/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_autofit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/03/08 18:46:00 by lluque           ###   ########.fr       */
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
		fdf->render_needed = 1;
	}
}
