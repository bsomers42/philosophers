/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 15:00:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/05 17:02:18 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int    print_msg(char *str, int ret)
{
    printf("%s", str);
    return (ret);
}

void philo_msg(int phil, size_t time, char c, t_philo *philo)
{
	// msg = NULL;
	// pthread_mutex_lock(&philo->death);
	pthread_mutex_lock(&philo->msg);
	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->msg);
		return ;
	}
	if (c == 'l')
		printf("%zu   \033[0;37m%d has taken left fork\033[0m\n", time, phil);
	if (c == 'r')
		printf("%zu   \033[0;37m%d has taken right fork\033[0m\n", time, phil);
	if (c == 'e')
		printf("%zu   \033[0;33m%d is eating\033[0m\n", time, phil);
	if (c == 's')
		printf("%zu   \033[0;34m%d is sleeping\033[0m\n", time, phil);
	if (c == 't')
		printf("%zu   \033[0;32m%d is thinking\033[0m\n", time, phil);
	if (c == 'd')
		printf("%zu   \033[0;31m%d has died\033[0m\n", time, phil);
	pthread_mutex_unlock(&philo->msg);
	// pthread_mutex_unlock(&philo->death);

}

size_t	get_time()
{
    size_t  time;
	struct timeval	current_time;

    gettimeofday(&current_time, NULL);
	// if (gettimeofday(NULL, &current_time) != 0)
    //     hier error messag!?
    time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000; //time is in millisec
	// printf("Time: [%zu]\n", time);
	return (time);
}

// int get_time(size_t start)
// {
// 	return (get_time_start() - start);
// }

void	clean_up(pthread_t *threads, pthread_t	*check_thr, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	(void)threads;
	(void)check_thr;
	while(i < philo->data->philos)
	{
		if (pthread_join(philo[i].data->threads, NULL)) //like a wait function, but for threads
			return ;
		if (philo[i].data->check_t)
		{
			if (pthread_join(philo[i].data->check_t, NULL) != 0)
			{
				return ;
			}
		}
		i++;
	}
	i = 0;
	while(i < philo->data->philos)
	{
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->death_mut);
	pthread_mutex_destroy(&philo->msg);
	free(philo);
	if (data)
		free(data);

}