/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_plane_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:48:56 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:58:54 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf_bonus.h"

t_fdf_plane	*fdf_create_plane(t_ft_mx *a, t_ft_mx *b, t_ft_mx *c)
{
	t_fdf_plane	*pl;
	t_ft_mx		*v1;
	t_ft_mx		*v2;
	t_ft_mx		*normal;

	pl = ft_calloc(1, sizeof (t_fdf_plane));
	if (pl == NULL)
		return (NULL);
	v1 = ft_vx_substract(a, b);
	v2 = ft_vx_substract(b, c);
	if (v1 == NULL || v2 == NULL)
		return (free(pl), ft_mx_destroy(v1), ft_mx_destroy(v2), NULL);
	normal = ft_vx_xproduct(v1, v2);
	if (normal == NULL)
		return (free(pl), ft_mx_destroy(v1), ft_mx_destroy(v2), NULL);
	pl->a = normal->d[0];
	pl->b = normal->d[1];
	pl->c = normal->d[2];
	pl->k = -1 * pl->a * a->d[0] - pl->b * a->d[1] - pl->c * a->d[2];
	return (ft_mx_destroy(normal), ft_mx_destroy(v1), ft_mx_destroy(v2), pl);
}
