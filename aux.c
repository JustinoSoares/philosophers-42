/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 00:53:25 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/22 14:12:40 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

size_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	waiting(long long time, t_rules *rules)
{
	long long	now;

	now = timestamp();
	while (1)
	{
		pthread_mutex_lock(&(rules->m_died));
		if (rules->died)
		{
			pthread_mutex_unlock(&(rules->m_died));
			return ;
		}
		pthread_mutex_unlock(&(rules->m_died));
		if (time_diff(now, timestamp()) >= time)
			break ;
	}
}

void	action_write(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	pthread_mutex_lock(&(rules->m_died));
	if (!(rules->died))
	{
		printf("%lld ", timestamp() - rules->first_timestamp);
		printf("%d ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->m_died));
	pthread_mutex_unlock(&(rules->writing));
	return ;
}
