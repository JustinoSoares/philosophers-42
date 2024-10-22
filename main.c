/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/21 15:24:51 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		res;

	if (argc != 5 && argc != 6)
		return (write_error("Invalid number of parameters"));
	res = init_all(&rules, argv);
	if (res == 3)
		return (write(1, "0 1 is_died\n", 12));
	if (res == 1)
		return (error_manager(res));
	if (launcher(&rules))
		return (write_error("There was an error creating the threads"));
	return (0);
}
