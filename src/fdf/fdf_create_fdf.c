/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:06:09 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 13:38:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

t_fdf	*fdf_create_fdf(int32_t drawing_w, int32_t drawing_h)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof (t_fdf));
	if (fdf == NULL)
		return (NULL);
	fdf->wlayout = fdf_create_wlayout(drawing_w, drawing_h);
	if (fdf->wlayout == NULL)
		return (fdf_destroy_fdf(fdf), NULL);
	return (fdf);
}
