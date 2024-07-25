/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:38:28 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:39:32 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
