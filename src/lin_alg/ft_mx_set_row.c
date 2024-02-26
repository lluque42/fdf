/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_set_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:09:39 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 20:53:01 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lin_alg.h"

int	ft_mx_set_row(t_ft_mx *matrix, int i, t_ft_mx *row)
{
	double	*dst;

	if (i > matrix->m || row->n != matrix->n)
		return (0);
	dst = matrix->d + i * matrix->n;
	ft_memmove(dst, row, matrix->n);
	return (1);
}
