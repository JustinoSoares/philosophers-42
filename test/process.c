/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:23:22 by jsoares           #+#    #+#             */
/*   Updated: 2024/09/16 09:01:37 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    int pid  = fork();
    if (pid == -1)
        return (1);
    printf("process id %d\n", getpid());
    if (pid != 0)
        wait(NULL); //Espera o processo filho terminar
    return (0);
}