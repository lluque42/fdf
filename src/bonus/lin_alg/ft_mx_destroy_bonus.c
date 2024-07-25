/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_destroy_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:03:36 by lluque            #+#    #+#             */
/*   Updated: 2024/07/25 18:39:52 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf_bonus.h"

void	ft_mx_destroy(t_ft_mx *matrix)
{
	if (matrix == NULL)
		return ;
	free(matrix->d);
	free(matrix);
}
