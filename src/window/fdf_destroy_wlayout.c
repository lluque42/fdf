/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_wlayout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:04:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 16:30:00 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "window.h"

// Apparently mlx_terminate() frees wlayout->window and wlayout->image
// eliminating the need of dealing with them here.
void	fdf_destroy_wlayout(t_fdf_wlayout *wlayout)
{
	free(wlayout);
}
