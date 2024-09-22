/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/22 07:18:21 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_died(t_philo *philo)
{
    if ((get_current_time() - philo->time_last_eat) > philo->time_of_die)
        return (1);
    return (0);
}

void doing(t_philo *philo, char *str)
{
    pthread_mutex_lock(philo->mutex);
    if (is_died(philo))
        printf("%zu %d is died\n", get_current_time() - philo->time_last_eat, philo->id);
    else
        printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id, str);
    pthread_mutex_unlock(philo->mutex);
}

void *actions(void *arg)
{
    t_philo *philo;
    //static int is_died_verify;

    philo = (t_philo *)arg;
    while (!is_died(philo))
    {
        pthread_mutex_lock(philo->mutex_left);
        pthread_mutex_lock(philo->mutex_right);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            break ;
        }
        doing(philo, "take_fork_left");
        doing(philo, "take_fork_right");
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            break ;
        }
        doing(philo, "is eating");
        philo->time_last_eat = get_current_time();
        usleep(philo->time_of_eat);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            //philo->is_died = 1;
            break ;
        }
        if (is_died(philo))
            break ;
        pthread_mutex_unlock(philo->mutex_left);
        doing(philo, "dropped_fork_left");
        pthread_mutex_unlock(philo->mutex_right);
        doing(philo, "dropped_fork_right");
        if (is_died(philo))
            break ;
        doing(philo, "is sleeping");
        usleep(philo->time_of_sleep);
        if (is_died(philo))
            break ;
        doing(philo, "is thinking");
    }
    if (is_died(philo))
    {
       // is_died_verify = 1;
        printf("Morreu............................\n");
        return (NULL);
    }
    return (NULL);
}
