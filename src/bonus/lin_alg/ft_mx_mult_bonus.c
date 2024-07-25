/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_mult_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:47:23 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:38:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_ft_mx	*ft_mx_mult(t_ft_mx *m1, t_ft_mx *m2)
{
	t_ft_mx	*vx1;
	t_ft_mx	*vx2;
	t_ft_mx	*result;
	int		i;
	int		j;

	result = ft_mx_create(m1->m, m2->n);
	if (result == NULL || m1->n != m2->m)
		return (ft_mx_destroy(result), NULL);
	i = -1;
	while (++i < m1->m)
	{
		j = -1;
		vx1 = ft_mx_get_row(m1, i);
		while (++j < m2->n)
		{
			vx2 = ft_mx_get_col(m2, j);
			if (!ft_vx_dproduct(vx1, vx2, result->d + (i * (m2->n) + j)))
				return (ft_mx_destroy(result), ft_mx_destroy(vx1),
					ft_mx_destroy(vx2), NULL);
			ft_mx_destroy(vx2);
		}
		ft_mx_destroy(vx1);
	}
	return (result);
}
/*
 * OLD BUGGY but more efficient
t_ft_mx	*ft_mx_mult(t_ft_mx *m1, t_ft_mx *m2)
{
	t_ft_mx	*r;
	int		v;
	int		i;
	int		j;
	int		n;

	if (m1->n != m2->m)
		return (NULL);
	r = ft_mx_create(m1->m, m2->n);
	if (r == NULL)
		return (NULL);
	n = m1->n;
	v = -1;
	while (++v < m2->n)
	{
		i = -1;
		while (++i < n)
		{
			j = -1;
			while (++j < n)
				r->d[i * r->n + v] += m1->d[i * n + j] * m2->d[j * m2->n + v];
		}
	}
	return (r);
}
*/
