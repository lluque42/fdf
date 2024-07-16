/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mx_get_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:24:05 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 20:52:05 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

double	ft_mx_get_element(t_ft_mx *matrix, int i, int j)
{
	return (matrix->d[i * matrix->n + j]);
}
