/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/22 14:23:50 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	lock_forks(t_philosopher *p, t_rules *r, int f_l, int f_r)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(&(r->forks[f_l]));
		pthread_mutex_lock(&(r->forks[f_r]));
	}
	else
	{
		pthread_mutex_lock(&(r->forks[f_r]));
		pthread_mutex_lock(&(r->forks[f_l]));
	}
}

void	philo_eats(t_philosopher *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->m_died));
	if (!(rules->died))
	{
		pthread_mutex_unlock(&(rules->m_died));
		lock_forks(philo, rules, philo->left_fork_id, philo->right_fork_id);
		action_write(rules, philo->id, "has taken a fork");
		action_write(rules, philo->id, "has taken a fork");
		pthread_mutex_lock(&(rules->meal_check));
		philo->t_last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		action_write(rules, philo->id, "is eating");
		waiting(rules->time_eat, rules);
		pthread_mutex_lock(&(rules->m_all_ate));
		(philo->x_ate)++;
		pthread_mutex_unlock(&(rules->m_all_ate));
		pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
		pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	}
	else
		pthread_mutex_unlock(&(rules->m_died));
}

void	*p_thread(void *my_philo)
{
	t_philosopher	*philo;
	t_rules			*rules;

	philo = (t_philosopher *)my_philo;
	rules = philo->rules;
	while (1)
	{
		pthread_mutex_lock(&(rules->m_died));
		if (rules->died)
		{
			pthread_mutex_unlock(&(rules->m_died));
			return (NULL);
		}
		pthread_mutex_unlock(&(rules->m_died));
		if (rules->all_ate)
			break ;
		philo_eats(philo);
		if (rules->all_ate)
			break ;
		action_write(rules, philo->id, "is sleeping");
		waiting(rules->time_sleep, rules);
		action_write(rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	exit_program(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = 0;
	while (++i <= rules->nb_philo)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
	}
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->m_died));
	pthread_mutex_destroy(&(rules->m_eat_all));
	pthread_mutex_destroy(&(rules->m_waiting));
	pthread_mutex_destroy(&(rules->m_all_ate));
}

void	death_checker_aux(t_rules *r, t_philosopher *p, int i)
{
	pthread_mutex_lock(&(r->meal_check));
	if (time_diff(p[i].t_last_meal, timestamp()) > r->time_death)
	{
		action_write(r, i + 1, "died");
		pthread_mutex_lock(&(r->m_died));
		r->died = 1;
		pthread_mutex_unlock(&(r->m_died));
	}
	pthread_mutex_unlock(&(r->meal_check));
}

void	death_checker(t_rules *r, t_philosopher *p)
{
	int	i;

	pthread_mutex_lock(&(r->m_eat_all));
	while (!(r->all_ate))
	{
		i = -1;
		while (++i < r->nb_philo && !(r->died))
			death_checker_aux(r, p, i);
		pthread_mutex_lock(&(r->m_died));
		if (r->died)
		{
			pthread_mutex_unlock(&(r->m_died));
			break ;
		}
		else
			pthread_mutex_unlock(&(r->m_died));
		i = 0;
		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
	pthread_mutex_unlock(&(r->m_eat_all));
}

int	launcher(t_rules *rules)
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
	death_checker(rules, rules->philosophers);
	exit_program(rules, phi);
	return (0);
}
