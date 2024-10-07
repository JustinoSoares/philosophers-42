/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 00:51:15 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/07 00:54:57 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 7);
	write(2, str, len);
	write(2, "\n", 1);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("At least one wrong argument"));
	if (error == 2)
		return (write_error("Fatal error when intializing mutex"));
	return (1);
}