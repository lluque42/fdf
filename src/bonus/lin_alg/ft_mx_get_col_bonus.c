/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_get_col_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:41:15 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:39:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf_bonus.h"

t_ft_mx	*ft_mx_get_col(t_ft_mx *matrix, int j)
{
	t_ft_mx	*result;
	int		i;

	if (j >= matrix->n)
		return (NULL);
	result = ft_mx_create(matrix->m, 1);
	if (result == NULL)
		return (NULL);
	i = -1;
	while (++i < result->m)
		result->d[i * result->n] = matrix->d[i * matrix->n + j];
	return (result);
}
