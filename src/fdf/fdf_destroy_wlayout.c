/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_wlayout.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:04:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 14:14:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//#include "fdf.h"
#include "window.h"

void	fdf_destroy_wlayout(t_fdf_wlayout *wlayout)
{
	// falta destruir
	// wlayout->window
	// wlayout->image
	free(wlayout);
}
