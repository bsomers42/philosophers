/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_time.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 11:54:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/01 12:00:51 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h> //voor gettimeofday
#include <stdio.h>

void	display_message(int	i, char c)
{
    size_t  time;
	struct timeval	current_time;

    gettimeofday(&current_time, NULL);
	// if (gettimeofday(NULL, &current_time) != 0)
    //     hier error messag!?
    time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	printf("%zu ", time);
	if (c == 'f')
		printf("%d has taken a fork\n", i);
	if (c == 'e')
		printf("%d is eating\n", i);
	if (c == 's')
		printf("%d is sleeping\n", i);
	if (c == 't')
		printf("%d is thinking\n", i);
	if (c == 'd')
		printf("%d died\n", i);
}