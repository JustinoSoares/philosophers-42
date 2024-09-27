/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/27 16:36:41 by jsoares          ###   ########.fr       */
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
