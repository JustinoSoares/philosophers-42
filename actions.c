/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/28 23:49:05 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL))
        write(2, "Error\n", 6);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void is_doing(t_philo *philo, char *str)
{
    printf("%ld %i %s\n", get_current_time() - philo->time_last_eat, philo->id, str);
}

void    philo_finish(t_philo *philo)
{
    size_t i;
    i = 0;

    while(i < philo->num_philo)
    {
        philo[i].finish = 1;
        i++;
    }
}

int is_died(t_philo *philo)
{
    if (philo->time_last_eat > get_current_time() - philo->time_to_die)
    {
        printf("philo %d is died", philo->id);
        philo_finish(philo);
        return (1);
    }
    return (0);
}

void *action(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        if (philo->finish || is_died(philo))
        {
            printf("Morreuuu\n");
            break ;
        }
           
        pthread_mutex_lock(philo->fork_left);
        pthread_mutex_lock(philo->fork_right);

        is_doing(philo, "take fork left");
        is_doing(philo, "take fork right");
        is_doing(philo, "is eating");

        philo->time_last_eat = get_current_time();
        usleep(philo->time_to_eat * 1000);

        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(philo->fork_right);
        is_doing(philo, "sleeping");
        usleep(philo->time_to_sleep * 1000);

        is_doing(philo, "thinking");
    }

    return (NULL);
}
