/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:27:50 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/20 16:40:05 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL0_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define number_of_philosopher 1
#define time_to_die 2
#define time_to_eat 3
#define time_to_sleep 4
#define number_of_times_each_philosopher_must_eat 5

typedef struct s_philo
{
    int id;
    int is_died;
    pthread_mutex_t *mutex_left;
    pthread_mutex_t *mutex_right;
    pthread_mutex_t *mutex;
    size_t time_of_eat;
    size_t time_of_think;
    size_t time_of_sleep;
    size_t time_of_die;
    size_t time_last_eat;
    size_t start_time;
} t_philo;


typedef struct s_current
{
    int id;
    size_t time;   
} t_current;

void *actions(void *arg);j

#endif