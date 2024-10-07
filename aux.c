/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 00:53:25 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/07 11:11:38 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(const char *str)
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

void		smart_sleep(long long time, t_rules *rules)
{
	long long i;

	i = timestamp();
	while (!(rules->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		//usleep(50);
	}
}

void		action_print(t_rules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded))
	{
		printf("%lld ", timestamp() - rules->first_timestamp);
		printf("%d ", id);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->writing));
	return ;
}