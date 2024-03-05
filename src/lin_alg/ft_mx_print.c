/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:09:46 by lluque            #+#    #+#             */
/*   Updated: 2024/03/04 13:33:15 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>														///////////
//#include "libft.h"
#include "lin_alg.h"

void	ft_mx_print(t_ft_mx *matrix, char separator)
{
	int	i;
	int	j;

	i = -1;
	while (++i < matrix->m)
	{
		j = -1;
		while (++j < matrix->n)
			printf("% 12f%c", matrix->d[i * matrix->n + j], separator);
		printf("\n");
	}
}
