/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_toggle_drw_hidden.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:52:45 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 13:11:02 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_features.h"

void	fdf_toggle_drw_hidden(t_fdf *fdf)
{
	if (fdf->drw_hidden_edges)
		fdf->drw_hidden_edges = 0;
	else
		fdf->drw_hidden_edges = 1;
	if (fdf->render_request > FROM_IMAGE)
		fdf->render_request = FROM_IMAGE;
}
