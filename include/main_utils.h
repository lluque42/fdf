/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluque <lluque@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:55:20 by lluque            #+#    #+#             */
/*   Updated: 2024/02/26 21:25:30 by lluque           ###   ########.fr       */
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
 * @brief <b>args_valid</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] c - TODO.
 *
 * @return TODO..
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int	args_valid(int argc, char **argv);

/**
 * @brief <b>filename_valid</b> -- TODO.
 *
 * @details TODO.
 *
 * @param [in] c - TODO.
 *
 * @return TODO..
 *
 * @warning TODO.
 *
 * @remark Implementation notes:
 * TODO.
*/
int	filename_valid(const char *filename);

#endif
