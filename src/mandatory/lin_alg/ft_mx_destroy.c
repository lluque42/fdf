/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:03:36 by lluque            #+#    #+#             */
/*   Updated: 2024/03/11 13:30:21 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lin_alg.h"

void	ft_mx_destroy(t_ft_mx *matrix)
{
	if (matrix == NULL)
		return ;
	free(matrix->d);
	free(matrix);
}
