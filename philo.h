/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:27:50 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/28 23:36:22 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL0_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define number_philo 1
#define time_die 2
#define time_eat 3
#define time_sleep 4
#define number_must_eat 5

typedef struct s_philo
{
    int id;
    int finish;
    pthread_t *threads;
    pthread_mutex_t *fork_left;
    pthread_mutex_t *fork_right;
    pthread_mutex_t *mutex;
    pthread_mutex_t mutex_died;
    size_t num_philo;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t time_start;
    size_t time_last_eat;
} t_philo;

void *action(void *arg);
size_t get_current_time(void);

#endif
