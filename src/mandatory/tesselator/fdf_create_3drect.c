/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_3drect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:58:23 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:02:49 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"

t_fdf_3drect	*fdf_create_3drect(t_ft_mx *v1, t_ft_mx *v2)
{
	t_fdf_3drect	*rect;

	rect = ft_calloc(1, sizeof (t_fdf_3drect));
	if (rect == NULL)
		return (NULL);
	rect->x1 = v1->d[0];
	rect->y1 = v1->d[1];
	rect->z1 = v1->d[2];
	rect->x2 = v2->d[0];
	rect->y2 = v2->d[1];
	rect->z2 = v2->d[2];
	rect->parallel_to_xy = v1->d[2] == v2->d[2];
	rect->parallel_to_yz = v1->d[0] == v2->d[0];
	rect->parallel_to_xz = v1->d[1] == v2->d[1];
	if (rect->parallel_to_xy && rect->parallel_to_yz && rect->parallel_to_xz)
		return (free(rect), NULL);
	if (rect->parallel_to_xy)
		rect->parallel_to_xy_at_z = v1->d[2];
	if (rect->parallel_to_yz)
		rect->parallel_to_yz_at_x = v1->d[0];
	if (rect->parallel_to_xz)
		rect->parallel_to_xz_at_y = v1->d[1];
	return (rect);
}
