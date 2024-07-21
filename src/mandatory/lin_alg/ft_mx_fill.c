/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:28 by lluque            #+#    #+#             */
/*   Updated: 2024/07/21 13:45:46 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

void	ft_mx_fill(t_ft_mx *matrix, double element_value)
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix->m)
	{
		j = -1;
		while (++j < matrix->n)
			ft_mx_set_element(matrix, element_value, i, j);
	}
}
