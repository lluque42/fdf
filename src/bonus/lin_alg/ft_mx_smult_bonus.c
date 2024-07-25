/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_smult_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 23:39:51 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:37:23 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	ft_mx_smult(t_ft_mx *matrix, double scalar)
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix->m)
	{
		j = -1;
		while (++j < matrix->n)
			matrix->d[i * matrix->n + j] *= scalar;
	}
}