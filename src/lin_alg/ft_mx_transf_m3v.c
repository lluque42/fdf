/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_transf_m3v.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:51:47 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 13:31:20 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

void	ft_mx_transf_m3v(t_ft_mx *tf_mx, t_ft_mx *col_vectors_mx)
{
	int		col_v;
	double	vector[3];
	int		i;
	int		j;

	if (tf_mx == NULL || col_vectors_mx == NULL)
		return ;
	col_v = 0;
	while (col_v < col_vectors_mx->n)
	{
		ft_bzero(vector, 3 * sizeof (double));
		i = -1;
		while (++i < 3)
		{
			j = -1;
			while (++j < 3)
				vector[i] += tf_mx->d[i * 3 + j] * (col_vectors_mx->d + col_v * 3)[j];
		}
		ft_memmove(col_vectors_mx->d + 3 * col_v, vector, sizeof (double) * 3);
		col_v++;
	}
}
