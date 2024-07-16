/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:47:23 by lluque            #+#    #+#             */
/*   Updated: 2024/03/05 03:07:23 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

// The formula for the element i,j in matrix result from multiplying the
// matrixes: m1 (size m x n) and m2 (size n x p) is:
//
// 		result_ij = sum_of_every_kth: m1_ik * m2_kj
// 			where:
// 				i from 1 to m
// 				j from 1 to p
// 				k from 1 to n
//
//			thus:
//				m = m1->m;
//				n = m1->n; or the equivalent n = m2->m
//				p = m2->n;
//static double	calculate_rij(double *m1_row, t_ft_mx *m2, int r_i, int r_j)
/*
double	calculate_rij(t_ft_mx *m1, t_ft_mx *m2, int i, int j)
{
	double	rij;
	int		k;

	rij = 0;
	k = -1;
	while (++k < m1->n)
		rij += m1->d[i * m1->n + k] * m2->d[k * m1->n + j];
	return (rij);
}
*/
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
