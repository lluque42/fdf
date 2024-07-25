/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_print_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:09:46 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:38:06 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "fdf_bonus.h"

// WARNING, uses printf, only for debugging
void	ft_mx_print(t_ft_mx *matrix, char separator)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	printf("As matrix format:\n");
	while (++i < matrix->m)
	{
		j = -1;
		while (++j < matrix->n)
			printf("% 12f%c", matrix->d[i * matrix->n + j], separator);
		printf("\n");
	}
	printf("As it is actually storaged in memory as a unidimensional array ");
	printf("using the row-major order ");
	printf("(aka lexicographic order; aka row-by-row):\n");
	k = -1;
	while (++k < matrix->m * matrix->n)
		printf("% 12f%c", matrix->d[k], separator);
	printf("\n");
}
