/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:13:28 by jsoares           #+#    #+#             */
/*   Updated: 2024/10/07 08:04:16 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/time.h"
#include "unistd.h"
#include "stdio.h"

int main(void)
{
    struct  timeval start, end;

    gettimeofday(&start, NULL);

    long time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
    printf("%ld\n", time);

}