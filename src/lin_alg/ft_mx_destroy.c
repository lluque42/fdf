/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:03:36 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 13:06:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lin_alg.h"

void	ft_mx_destroy(t_ft_mx *matrix)
{
	free(matrix->d);
	free(matrix);
}
