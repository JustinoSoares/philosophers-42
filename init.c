/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 00:50:27 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/07 11:14:03 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_mutex(t_rules *rules)
{
	int i;

	i = rules->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (1);
	return (0);
}

int init_philosophers(t_rules *rules)
{
	int i;
	int right;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philosophers[i].id = i + 1;
		if (rules->philosophers[i].id == 1)
			right = rules->nb_philo;
		else
			right = rules->philosophers[i].id - 1;
		rules->philosophers[i].x_ate = 0;
		rules->philosophers[i].left_fork_id = i + 1;
		rules->philosophers[i].right_fork_id = right;
		rules->philosophers[i].t_last_meal = 0;
		rules->philosophers[i].rules = rules;
		i++;
	}
	return (0);
}

int init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->dieded = 0;
	if (rules->nb_philo < 2 || rules->time_death < 0 || rules->time_eat < 0 || rules->time_sleep < 0 || rules->nb_philo > 200)
		return (1);
	if (argv[5])
	{
		rules->nb_eat = ft_atoi(argv[5]);
		if (rules->nb_eat <= 0)
			return (1);
	}
	else
		rules->nb_eat = -1;
	if (init_mutex(rules))
		return (2);
	init_philosophers(rules);
	return (0);
}