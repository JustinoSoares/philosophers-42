/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/22 14:52:30 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(t_rules *rules)
{
	t_philosopher	*phi;
	int				i;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		pthread_mutex_lock(&(rules->meal_check));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		i++;
	}
	death_verify(rules, rules->philosophers);
	exit_program(rules, phi);
	return (0);
}

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
	if (create_thread(&rules))
		return (write_error("There was an error creating the threads"));
	return (0);
}
