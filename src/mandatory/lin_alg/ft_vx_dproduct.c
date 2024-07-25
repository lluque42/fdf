/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vx_dproduct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:16:12 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 02:17:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

// This function exploits the linear storage of values inside a matrix, making
// irrelevant if we're dealing with row-vectors or col-vectors. Once checked
// that both matrixes are vectors (1xn, mx1, doesn't matter), and of the same
// size (the other non 1 size is the same); and since every element is linearly
// storaged inside the matrix's ->d[] array, the addressing is very simple. 
int	ft_vx_dproduct(t_ft_mx *a, t_ft_mx *b, double *result)
{
	int	elements;
	int	i;

	elements = a->m * a->n;
	if (elements != b->m * b-> n)
		return (0);
	if (a->m * b->m != 1
		&& a->n * b->n != 1
		&& a->m * b->n != 1
		&& a->n * b->m != 1)
		return (0);
	*result = 0;
	i = -1;
	while (++i < elements)
	{
		*result = *result + (a->d[i] * b->d[i]);
	}
	return (1);
}
