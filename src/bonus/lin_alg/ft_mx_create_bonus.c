/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:55:15 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:40:11 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "fdf_bonus.h"

t_ft_mx	*ft_mx_create(int m, int n)
{
	t_ft_mx	*matrix;

	if (m == 0 || n == 0)
		return (NULL);
	matrix = malloc(sizeof (t_ft_mx));
	if (matrix == NULL)
		return (NULL);
	matrix->d = calloc(m * n, sizeof (double));
	if (matrix->d == NULL)
		return (free(matrix), NULL);
	matrix->m = m;
	matrix->n = n;
	matrix->is_sqr = m == n;
	return (matrix);
}
