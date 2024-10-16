/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/16 11:46:11 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_waiting (long long unsigned int time)
{
	long long time_init;

	time_init = timestamp();
	while (time_init - timestamp() < time)
		usleep(100);
}

void philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	if ((rules->died))
	{
		pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	}
	else
	{
		action_write(rules, philo->id, "has taken a fork");
		action_write(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->meal_check));
		philo->t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		action_write(rules, philo->id, "is eating");
		sleeping(rules->time_eat, rules);
		ft_waiting((rules->time_death - rules->time_eat - rules->time_sleep) / 2);
		(philo->x_ate)++;
		pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	}
}

void *p_thread(void *void_philosopher)
{
	int i;
	t_philosopher *philo;
	t_rules *rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	while (!(rules->died))
	{
		if (rules->all_ate)
			break;
		philo_eats(philo);
		if (rules->all_ate)
			break;
		action_write(rules, philo->id, "is sleeping");
		sleeping(rules->time_sleep, rules);
		action_write(rules, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void exit_launcher(t_rules *rules, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = 0;
	while (++i <= rules->nb_philo)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
	}
	pthread_mutex_destroy(&(rules->writing));
}

void death_checker(t_rules *r, t_philosopher *p)
{
	int i;

	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->died))
		{
			pthread_mutex_lock(&(r->meal_check));
			if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
			{
				action_write(r, i + 1, "died");
				r->died = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			ft_waiting(1);
		}
		if (r->died)
			break;
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

int launcher(t_rules *rules)
{
	int i;
	t_philosopher *phi;

	i = 0;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(rules, rules->philosophers);
	exit_launcher(rules, phi);
	return (0);
}