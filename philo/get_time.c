/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_time.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:31:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/03 14:42:43 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	ft_usleep(size_t time, t_philo *philo)
{
	size_t	timesleep;

	timesleep = get_time();
	while (get_time() - timesleep < time)
	{
		usleep(100);
		if (check_death_done(philo) != 0)
			return (1);
	}
	return (0);
}

int	ft_usleep_start(size_t time)
{
	size_t	timesleep;

	timesleep = get_time();
	while (get_time() - timesleep < time)
		usleep(100);
	return (0);
}

size_t	get_time(void)
{
	size_t			time;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
	{
		printf("\033[0;31mgettimeofday error\033[0m\n");
		return (0);
	}
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}
