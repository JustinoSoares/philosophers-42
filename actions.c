/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/23 20:42:49 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_died(t_philo *philo)
{
    if ((get_current_time() - philo->time_last_eat) > philo->time_of_die)
    {
        pthread_mutex_lock(philo->mutex_write);
        printf("%zu %d is died \n", get_current_time() - philo->time_last_eat, philo->id);
        pthread_mutex_unlock(philo->mutex_write);
        return (1);
    }
    return (0);
}

void doing(t_philo *philo, char *str)
{
    if (is_died(philo))
    {
        pthread_mutex_lock(philo->mutex_write);
        printf("%zu %d is died\n", get_current_time() - philo->time_last_eat, philo->id);
        pthread_mutex_unlock(philo->mutex_write);
    }
    else
    {
        pthread_mutex_lock(philo->mutex_write);
        printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id, str);
        pthread_mutex_unlock(philo->mutex_write);
    }
        
}

void *actions(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    
    while (!is_died(philo))
    {
        if (is_died(philo))
            pthread_mutex_lock(philo->mutex_died);
        pthread_mutex_lock(philo->mutex_left);
        pthread_mutex_lock(philo->mutex_right);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            break;
        }
        doing(philo, "take_fork_left");
        doing(philo, "take_fork_right");
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            break;
        }
        doing(philo, "is eating");
        philo->time_last_eat = get_current_time();
        usleep(philo->time_of_eat);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            break;
        }
        if (is_died(philo))
        {
            break ;
        }  
        pthread_mutex_unlock(philo->mutex_left);
        doing(philo, "dropped_fork_left");
        pthread_mutex_unlock(philo->mutex_right);
        doing(philo, "dropped_fork_right");
        if (is_died(philo))
        {
            break ;   
        }
        doing(philo, "is sleeping");
        usleep(philo->time_of_sleep);
        if (is_died(philo))
        {
            break ;
        }
        doing(philo, "is thinking");
        if (is_died(philo))
            pthread_mutex_unlock(philo->mutex_died);
    }
    return (NULL);
}
