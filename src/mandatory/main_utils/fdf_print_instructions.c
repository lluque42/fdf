/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_print_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:29:33 by lluque            #+#    #+#             */
/*   Updated: 2024/07/18 04:00:53 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fdf_print_instructions(void)
{
	ft_printf("lluque's fdf instructions:\n");
	ft_printf("\t* Press ESCAPE key or clic the window's X button to exit.\n");
	ft_printf("\t* Press I, K, J, L, U, O keys to rotate along each axis.\n");
	ft_printf("\t* Press the T key to cycle through ");
	ft_printf("planar/spherical/cylindrical projections.\n");
	ft_printf("\t* Press TAB key to turn on/off the ");
	ft_printf("autofit and center feature.\n");
	ft_printf("\t* With autofit disabled:\n");
	ft_printf("\t\t* Press W or S keys to change the scale/zoom.\n");
	ft_printf("\t\t* Use the arrow keys to translate (displace) the model:\n");
	ft_printf("\t\t\t* UP/DOWN to move the camera perspective along Z axis.\n");
	ft_printf("\t\t\t* LEFT/RIGHT to move the camera in each direction.\n");
	ft_printf("\t\t\t* LEFT/RIGHT simultanously with UP/DOWN to move the\n");
	ft_printf("\t\t\tcamera perspective along X and Y axis.\n");
}
