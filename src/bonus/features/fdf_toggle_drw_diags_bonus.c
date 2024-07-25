/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_drw_diags_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:34:18 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	fdf_toggle_drw_diags(t_fdf *fdf)
{
	if (fdf->drw_valid_diag_edges)
		fdf->drw_valid_diag_edges = 0;
	else
		fdf->drw_valid_diag_edges = 1;
	if (fdf->render_request > FROM_IMAGE)
		fdf->render_request = FROM_IMAGE;
}
