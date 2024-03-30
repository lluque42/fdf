/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:06:09 by lluque            #+#    #+#             */
/*   Updated: 2024/03/27 10:01:32 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

t_fdf	*fdf_create_fdf(int32_t drawing_w, int32_t drawing_h, t_ft_mx *map_mx)
{
	t_fdf	*fdf;

	fdf = ft_calloc(1, sizeof (t_fdf));
	if (fdf == NULL)
		return (NULL);
	fdf->wlayout = fdf_create_wlayout(drawing_w, drawing_h);
	if (fdf->wlayout == NULL)
		return (fdf_destroy_fdf(fdf), NULL);
	fdf->object = fdf_create_object(map_mx);
	if (fdf->object == NULL)
		return (fdf_destroy_fdf(fdf), free(fdf->wlayout), NULL);
	fdf->render_request = FROM_MODEL;
	fdf->autofit = 1;
	return (fdf);
}
