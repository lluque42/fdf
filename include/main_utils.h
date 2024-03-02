/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/03/01 23:55:25 by lluque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main_utils.h
 * Header file for utility functions for program arguments.
*/

#ifndef MAIN_UTILS_H
# define MAIN_UTILS_H
# define FILE_EXTENSION ".fdf"

/**
 * @brief <b>fdf_args_valid</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] argc - TODO.
 *
 * @param [in] argv - TODO.
 *
 * @return Non-zero value if correct.  
 * A value of zero is returned if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int	fdf_args_valid(int argc, char **argv);

/**
 * @brief <b>fdf_filename_valid</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] filename - TODO.
 *
 * @return Non-zero value if correct.  
 * A value of zero is returned if error.
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int	fdf_filename_valid(const char *filename);

#endif
