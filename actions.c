/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/20 08:51:02 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *actions(void *arg)
{
    t_philo *philo;
    // size_t dif;
    philo = (t_philo *)arg;
    while (!is_died(philo))
    {
        
        pthread_mutex_lock(philo->mutex_left);
        pthread_mutex_lock(philo->mutex_right);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            philo->is_died = 1;
            break ;
        }
        take_fork_left(philo);
        take_fork_right(philo);
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            philo->is_died = 1;
            break ;
        }
        eating(philo);
        philo->time_last_eat = get_current_time();
        if (is_died(philo))
        {
            pthread_mutex_unlock(philo->mutex_left);
            pthread_mutex_unlock(philo->mutex_right);
            philo->is_died = 1;
            break ;
        }
       
        // printf("id %d Dif %zu last %zu \n", philo->id, dif, philo->time_last_eat);
        if (is_died(philo))
            break ;
        pthread_mutex_unlock(philo->mutex_left);
        dropped_fork_left(philo);
        pthread_mutex_unlock(philo->mutex_right);
        dropped_fork_right(philo);
        if (is_died(philo))
            break ;
        sleeping(philo);
        if (is_died(philo))
            break ;
        thinking(philo);
    }
    if (philo->is_died == 1)
    {
        printf("id %d Dif %zu\n", philo->id, get_current_time() - philo->time_last_eat);
    }
    return (NULL);
}