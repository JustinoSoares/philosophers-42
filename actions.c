/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:50:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/27 16:48:08 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time_stamp()
{
    //
}

void is_doing(t_philo *philo, char *str)
{
    printf("philo %i %s\n", philo->id, str);
}

void    *action (void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    is_doing(philo, "take fork left");
    is_doing(philo, "take fork right");
    is_doing(philo, "sleeping");
    is_doing(philo, "thinking");
    return (NULL);
}
