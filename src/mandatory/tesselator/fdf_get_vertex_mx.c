/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_get_vertex_mx.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:44:48 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:00:52 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf.h"

t_ft_mx	*fdf_get_vertex_mx(t_ft_mx *z_mx)
{
	t_ft_mx	*v_mx;
	int		i;
	int		j;
	int		v;

	v_mx = ft_mx_create(4, z_mx->m * z_mx->n);
	if (v_mx == NULL)
		return (NULL);
	v = -1;
	i = 0;
	j = 0;
	while (++v < z_mx->m * z_mx->n)
	{
		v_mx->d[v] = j;
		v_mx->d[z_mx->m * z_mx->n + v] = i;
		v_mx->d[2 * z_mx->m * z_mx->n + v] = z_mx->d[i * z_mx->n + j];
		v_mx->d[3 * z_mx->m * z_mx->n + v] = 1;
		if (++j == z_mx->n)
		{
			j = 0;
			if (++i == z_mx->m)
				i = 0;
		}
	}
	return (v_mx);
}
