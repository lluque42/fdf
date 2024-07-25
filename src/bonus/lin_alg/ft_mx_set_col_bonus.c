/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_set_col_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:41:15 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:37:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf_bonus.h"

int	ft_mx_set_col(t_ft_mx *matrix, int j, t_ft_mx *col)
{
	int		i;

	if (j >= matrix->n || col->m != matrix->m)
		return (0);
	i = -1;
	while (++i < matrix->m)
		matrix->d[i * matrix->n + j] = col->d[i * matrix->n];
	return (1);
}
