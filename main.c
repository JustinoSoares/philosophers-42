/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/20 08:50:31 by jsoares          ###   ########.fr       */
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

int is_died(t_philo *philo)
{
    if ((get_current_time() - philo->time_last_eat) > philo->time_of_die)
    {
         printf("%zu %d is died\n", get_current_time() - philo->start_time, philo->id);
         return (1);
    }
    return (0);
}

void thinking(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d is thinking\n", get_current_time() - philo->start_time, philo->id);
}
void sleeping(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
    usleep(philo->time_of_sleep);
}

void eating(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d is eating\n", get_current_time() - philo->start_time, philo->id);
    usleep(philo->time_of_eat);
}

void take_fork_left(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d take fork left\n", get_current_time() - philo->start_time, philo->id);
}

void take_fork_right(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d take fork right\n", get_current_time() - philo->start_time, philo->id);
}

void dropped_fork_right(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d dropped the right fork\n", get_current_time() - philo->start_time, philo->id);
}

void dropped_fork_left(t_philo *philo)
{
    if (is_died(philo))
        return ;
    printf("%zu %d dropped the left fork\n", get_current_time() - philo->start_time, philo->id);
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
        mutex = malloc(sizeof(pthread_mutex_t) * num_thread);
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
            philos[i].mutex_left = &mutex[i];
            philos[i].mutex_right = &mutex[fork_right];
            philos[i].time_last_eat = get_current_time();
            philos[i].start_time = get_current_time();
            philos[i].is_died = 0;
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
