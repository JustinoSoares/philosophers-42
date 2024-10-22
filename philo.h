/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:27:50 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/22 14:22:46 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct s_rules;

typedef struct s_philosopher
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	struct s_rules	*rules;
	pthread_t		thread_id;
}					t_philosopher;

typedef struct s_rules
{
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				died;
	int				all_ate;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	m_died;
	pthread_mutex_t	m_eat_all;
	pthread_mutex_t	m_waiting;
	pthread_mutex_t	m_all_ate;
	t_philosopher	philosophers[250];
}					t_rules;

int					write_error(char *str);
int					error_manager(int error);

int					init_all(t_rules *rules, char **argv);

int					ft_atoi(const char *str);
void				action_write(t_rules *rules, int id, char *string);
size_t				timestamp(void);
long long			time_diff(long long past, long long pres);
void				waiting(long long time, t_rules *rules);

int					launcher(t_rules *rules);
void				exit_program(t_rules *rules, t_philosopher *philos);

#endif
