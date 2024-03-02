/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_transf_v3m.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 11:54:07 by lluque            #+#    #+#             */
/*   Updated: 2024/03/02 13:40:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

void	ft_mx_transf_v3m(t_ft_mx *row_vectors_mx, t_ft_mx *tf_mx)
{
	int		row_v;
	double	vector[3];
	int		i;
	int		j;

	if (tf_mx == NULL || row_vectors_mx == NULL)
		return ;
	row_v = 0;
	ft_printf("row_vectors_mx->m = %d\n", row_vectors_mx->m);
	while (row_v < row_vectors_mx->m)
	{
		// para cada vector fila
		ft_bzero(vector, 3 * sizeof (double));
		i = -1;
		while (++i < 3)
		{
			//Para cada fila en la matriz
			j = -1;
			while (++j < 3)
				// Para cada columna en la matriz (fila i fija)
				vector[i] += (row_vectors_mx->d + row_v * 3)[j] * tf_mx->d[i * 3 + j];
		}
		ft_memmove(row_vectors_mx->d + 3 * row_v, vector, sizeof (double) * 3);
		row_v++;
	}
}
/*

	double	vector[3];
	int		j;
	int		i;

	if (matrix == NULL || row_vector == NULL)
		return ;
	ft_bzero(vector, 3 * sizeof (double));
	j = -1;
	while (++j < 3)
	{
		i = -1;
		while (++i < 3)
			vector[j] += row_vector[i] * matrix[i * 3 + j];
	}
	ft_memmove(row_vector, vector, sizeof (double) * 3);

}
*/
