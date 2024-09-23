/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/23 19:03:20 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "gettimeofday() error\n", 22);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int main(int ac, char **av)
{
    int i;
    int num_thread;
    int fork_right;
    pthread_mutex_t *mutex;
    pthread_t *pthreads;
    t_philo *philos;
    if (ac == 5 || ac == 6)
    {
        num_thread = atoi(av[number_of_philosopher]);
        pthreads = malloc(sizeof(pthread_t) * num_thread);
        if (!pthreads)
            return (0);
        philos = malloc(sizeof(t_philo) * num_thread);
        if (!philos)
            return (0);
        mutex = malloc(sizeof(pthread_mutex_t) * (num_thread + 2));
        if (!mutex)
            return (0);
        i = 0;
        while (i < num_thread)
        {
            pthread_mutex_init(&mutex[i], NULL);
            i++;
        }
        i = 0;
        while (i < num_thread)
        {
            philos[i].id = i + 1;
            if (philos[i].id != 1)
                fork_right = i - 1;
            else
                fork_right = num_thread - 1;
            philos[i].time_of_eat = atoi(av[time_to_eat]) * 1000;
            philos[i].time_of_sleep = atoi(av[time_to_sleep]) * 1000;
            philos[i].time_of_die = atoi(av[time_to_die]);
            philos[i].mutex_left = &mutex[i];
            philos[i].mutex_right = &mutex[fork_right];
            philos[i].mutex_write = &mutex[num_thread + 1];
            philos[i].mutex_died = &mutex[num_thread + 2];
            philos[i].time_last_eat = get_current_time();
            philos[i].start_time = get_current_time();
            pthread_create(&pthreads[i], NULL, (void *)&actions, (void *)&philos[i]);
            i++;
        }
        i = 0;
        while (i < num_thread)
        {
            pthread_join(pthreads[i], NULL);
            i++;
        }
    }
    i = 0;
    while (i < num_thread)
    {
        pthread_mutex_destroy(&mutex[i]);
        i++;
    }
    return (0);
}
