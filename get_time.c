/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_time.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:31:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:15:42 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	ft_usleep(size_t time)
{
	size_t	timesleep;

	timesleep = get_time();
	while (get_time() - timesleep < time)
		usleep(100);
}

size_t	get_time(void)
{
	size_t			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
    //     hier error messag!?
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}
