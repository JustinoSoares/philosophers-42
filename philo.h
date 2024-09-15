/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:27:50 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/15 19:09:00 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL0_H
# define PHILO_H

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
    pthread_mutex_t *mutex_left;
    pthread_mutex_t *mutex_right;
    long long int time_of_eat;
    long long int time_of_think;
    long long int time_of_sleep;
    long long int time_of_die;
} t_philo;


#endif