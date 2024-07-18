/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_transpose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:40:26 by lluque            #+#    #+#             */
/*   Updated: 2024/02/27 18:53:50 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_ft_mx	*ft_mx_transpose(t_ft_mx *matrix)
{
	t_ft_mx	*r;
	int		i;
	int		j;

	if (matrix == NULL)
		return (NULL);
	r = ft_mx_create(matrix->n, matrix->m);
	if (r == NULL)
		return (NULL);
	i = -1;
	while (++i < r->m)
	{
		j = -1;
		while (++j < r->n)
			r->d[i * r->n + j] = matrix->d[j * matrix->n + i];
	}
	return (r);
}