/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_destroy_fdf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:07:42 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 18:26:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

void	fdf_destroy_fdf(t_fdf *fdf)
{
	fdf_destroy_model(fdf->model);
	fdf_destroy_wlayout(fdf->wlayout);
	free(fdf);
}
