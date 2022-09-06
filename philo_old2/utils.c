/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 15:00:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/06 15:55:47 by bsomers       ########   odam.nl         */
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
	pthread_mutex_lock(&philo->data->death_mut);

	if (philo->data->death == true)
	{
		pthread_mutex_unlock(&philo->data->death_mut);
		pthread_mutex_unlock(&philo->msg);
		printf("this?\n");
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mut);

	pthread_mutex_lock(&philo->msg);
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

void	clean_up(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while(i < philo->data->philos)
	{
		// if (pthread_join(philo[i].data->threads, NULL) != 0) //like a wait function, but for threads
		// 	return ;
		// if (pthread_join(philo[i].data->check_t, NULL) != 0)
		// 	return ;
		pthread_join(philo[i].data->threads, NULL);
		pthread_join(philo[i].data->check_t, NULL);
		// printf("Joined threads %d. philos: %d\n", i, philo->data->philos);
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