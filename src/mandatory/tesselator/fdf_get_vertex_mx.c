/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_mx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:44:48 by lluque            #+#    #+#             */
/*   Updated: 2024/07/21 15:46:20 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lin_alg.h"
#include "tesselator.h"

t_ft_mx	*fdf_get_vertex_mx(t_ft_mx **map_mx)
{
	t_ft_mx	*v_mx;
	int		i;
	int		j;
	int		v;

	v_mx = ft_mx_create(4, map_mx[Z]->m * map_mx[Z]->n);
	if (v_mx == NULL)
		return (NULL);
	v = -1;
	i = 0;
	j = 0;
	while (++v < map_mx[Z]->m * map_mx[Z]->n)
	{
		v_mx->d[v] = j;
		v_mx->d[map_mx[Z]->m * map_mx[Z]->n + v] = i;
		v_mx->d[2 * map_mx[Z]->m * map_mx[Z]->n + v] = map_mx[Z]->d[i * map_mx[Z]->n + j];
		v_mx->d[3 * map_mx[Z]->m * map_mx[Z]->n + v] = 1;
		if (++j == map_mx[Z]->n)
		{
			j = 0;
			if (++i == map_mx[Z]->m)
				i = 0;
		}
	}
	return (v_mx);
}
