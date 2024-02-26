/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:55:15 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 13:02:41 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lin_alg.h"
#include <stdlib.h>

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
