/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/28 23:38:41 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int veri_params(int ac)
{
    if (ac != 5 && ac != 6)
    {
        printf("Rule:\n\t ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (0);
    }
    return (1);
}

int main(int ac, char **av)
{
    t_philo *philo;
    pthread_t *threads;
    pthread_mutex_t *mutex;
    int fork_right;
    int i = 0;
    
    if (!veri_params(ac))
        return (1);
    philo = malloc(sizeof(t_philo) * atoi(av[number_philo]));
    if (!philo)
        return (1);
    threads = malloc(sizeof(pthread_t) * atoi(av[number_philo]));
    if (!threads)
        return (1);
    mutex = malloc(sizeof(pthread_mutex_t) * atoi(av[number_philo]));
    if (!mutex)
        return (1);
    while (i < atoi(av[number_philo]))
    {
        pthread_mutex_init(&mutex[i], NULL);
        i++;
    }
    
    i = 0;
    while (i < atoi(av[number_philo]))
    {
        philo[i].id = i + 1;
        if (philo[i].id == 1)
            fork_right = number_philo - 1;
        else
            fork_right = philo[i].id - 1;
        philo[i].fork_left = &mutex[i];
        philo[i].fork_right = &mutex[fork_right];
        philo[i].time_to_eat = atoi(av[time_eat]);
        philo[i].time_to_sleep = atoi(av[time_sleep]);
        philo[i].num_philo = atoi(av[number_philo]);
        philo[i].time_start = get_current_time();
        philo[i].time_last_eat = get_current_time();
        philo[i].finish = 0;
        pthread_create(&threads[i], NULL, action, (void *)&philo[i]); 
        i++;
    }
    i = 0;
    while (i < atoi(av[number_philo]))
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    i = 0;
    while (i < atoi(av[number_philo]))
    {
        pthread_mutex_destroy(&mutex[i]);
        i++;
    }
    return(0);
}
