/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:23:24 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/16 09:01:38 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int x = 2; 
void *rotina(void)
{
    sleep(1);
    printf("x -> %d\n", x);
    return (NULL);
}

void *rotina2(void)
{
    x += 10;
    sleep(1);
    printf("x -> %d\n", x);
    return (NULL);
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, (void *)&rotina, NULL);
    pthread_create(&t2, NULL, (void *)&rotina2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}