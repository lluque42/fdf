/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_is_in_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:12:26 by lluque            #+#    #+#             */
/*   Updated: 2024/03/19 17:17:03 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tesselator.h"

int	fdf_is_in_plane(t_ft_mx *v, t_fdf_plane *plane)
{
	double	temp;

	temp = plane->a * v->d[0];
	temp += plane->b * v->d[1];
	temp += plane->c * v->d[2];
	temp += plane->k;
	return (temp == 0);
}
