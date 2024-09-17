/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/17 19:40:20 by justinosoar      ###   ########.fr       */
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

void thinking(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d is thinking\n", ms, thread_id);
}
void sleeping(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d is sleeping\n", ms, thread_id);
}

void eating(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d is eating\n", ms, thread_id);
}

void take_fork_left(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d take fork left\n", ms, thread_id);
}

void take_fork_right(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d take fork right\n", ms, thread_id);
}

void dropped_fork_right(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d dropped the right fork\n", ms, thread_id);
}

void dropped_fork_left(int thread_id)
{
    struct timeval tv;
    size_t ms;

    // pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%zu %d dropped the left fork\n", ms, thread_id);
}

void *actions(void *arg)
{
    t_philo *philo;
    size_t dif;
    
    while (1)
    {
        philo = (t_philo *)arg;
        pthread_mutex_lock(philo->mutex_left);
        pthread_mutex_lock(philo->mutex_right);
        take_fork_left(philo->id);
        take_fork_right(philo->id);
        dif = get_current_time() - philo->time_last_eat;
        philo->time_last_eat = get_current_time();
        printf("id %d Dif %zu last %zu \n", philo->id, dif, philo->time_last_eat);
        eating(philo->id);
        usleep(philo->time_of_eat);
        pthread_mutex_unlock(philo->mutex_left);
        dropped_fork_left(philo->id);
        pthread_mutex_unlock(philo->mutex_right);
        dropped_fork_right(philo->id);
        sleeping(philo->id);
        usleep(philo->time_of_sleep);
        thinking(philo->id);
    }
    return (NULL);
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
