/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:07:59 by lluque            #+#    #+#             */
/*   Updated: 2024/03/09 22:51:48 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tesselator.h"

static void	init_m2w_settings(t_fdf_object *object)
{
	object->m2w_rot_par[0] = 0;
	object->m2w_rot_par[1] = 0;
	object->m2w_rot_par[2] = 0;
	object->m2w_tra_par[0] = 0;
	object->m2w_tra_par[1] = 0;
	object->m2w_tra_par[2] = 0;
	object->m2w_sca_par[0] = 1;
	object->m2w_sca_par[1] = 1;
	object->m2w_sca_par[2] = 1;
}

static void	init_w2c_settings(t_fdf_object *object)
{
	object->w2c_rot_par[0] = 90 - 35.264;
	object->w2c_rot_par[1] = 0;
	object->w2c_rot_par[2] = 360 - 45;
	object->w2c_tra_par[0] = 0;
	object->w2c_tra_par[1] = 0;
	object->w2c_tra_par[2] = 0;
	object->w2c_sca_par[0] = 1;
	object->w2c_sca_par[1] = 1;
	object->w2c_sca_par[2] = 1;
}

static void	init_c2s_settings(t_fdf_object *object)
{
	object->c2s_rot_par[0] = 0;
	object->c2s_rot_par[1] = 0;
	object->c2s_rot_par[2] = 0;
	object->c2s_tra_par[0] = 0;
	object->c2s_tra_par[1] = 0;
	object->c2s_tra_par[2] = 0;
	object->c2s_sca_par[0] = 1;
	object->c2s_sca_par[1] = 1;
	object->c2s_sca_par[2] = 1;
}

t_fdf_object	*fdf_create_object(void)
{
	t_fdf_object	*object;

	object = ft_calloc(1, sizeof(t_fdf_object));
	if (object == NULL)
		return (NULL);
	init_m2w_settings(object);
	init_w2c_settings(object);
	init_c2s_settings(object);
	return (object);
}
