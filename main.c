/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:36:29 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/15 19:16:12 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void    thinking(int thread_id)
{
    struct timeval tv;
    long long ms;

    //pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%lld %d is thinking\n", ms, thread_id);
}
void    sleeping(int thread_id)
{
    struct timeval tv;
    long long ms;

    //pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%lld %d is sleeping\n", ms, thread_id);
}

void    eating(int thread_id)
{
    struct timeval tv;
    long long ms;

    //pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%lld %d is eating\n", ms, thread_id);
}

void    take_fork(int thread_id)
{
    struct timeval tv;
    long long ms;

    //pegar po tempo actual
    gettimeofday(&tv, NULL);
    ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    printf("%lld %d take fork left\n", ms, thread_id);
    printf("%lld %d take fork right\n", ms, thread_id);
}

void *actions(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id  == 1)
    {
        pthread_mutex_lock(philo->mutex_right);
        pthread_mutex_lock(philo->mutex_left);
    }
    else
    {
        pthread_mutex_lock(philo->mutex_left);
        pthread_mutex_lock(philo->mutex_right);
    }
    take_fork(philo->id);
    eating(philo->id);
    usleep(philo->time_of_eat);

    sleeping(philo->id);
    usleep(philo->time_of_sleep);
    pthread_mutex_unlock(philo->mutex_left);
    pthread_mutex_unlock(philo->mutex_right);
    return (NULL);
}

int main(int ac, char **av)
{
    int i;
    int num_thread;
    pthread_mutex_t *mutex;
    pthread_t *pthreads;
    t_philo *philos;

    if (ac ==  5 || ac == 6)
    {
        num_thread = atoi(av[number_of_philosopher]);
        pthreads = malloc(sizeof(pthread_t) * num_thread);
        if (!pthreads)
            return (0);
        philos = malloc(sizeof(t_philo) * num_thread);
        if (!philos)
            return (0);
        mutex = malloc(sizeof(pthread_mutex_t) * num_thread);
        i = 0;
        while(i < num_thread)
        {
             pthread_mutex_init(&mutex[i], NULL);
             i++;
        }
        i = 0;
        while(i < num_thread)
        {
            philos[i].id = i + 1;
            philos[i].time_of_eat = atoi(av[time_to_eat]) * 1000;
            philos[i].mutex_left = &mutex[i];
            philos[i].mutex_right = &mutex[(i + 1) % num_thread];
            pthread_create(&pthreads[i], NULL, actions, &philos[i]);
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
    while(i < num_thread)
    {
         pthread_mutex_destroy(&mutex[i]);
        i++;
    }
    return (0);
}
