/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 15:00:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/01 14:40:34 by bsomers       ########   odam.nl         */
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

void philo_msg(int philo, size_t time, char c)
{
	if (c == 'l')
		printf("%zu   %d has taken left fork\n", time, philo);
	if (c == 'r')
		printf("%zu   %d has taken right fork\n", time, philo);
	if (c == 'e')
		printf("%zu   %d is eating\n", time, philo);
	if (c == 's')
		printf("%zu   %d is sleeping\n", time, philo);
	if (c == 't')
		printf("%zu   %d is thinking\n", time, philo);
	if (c == 'd')
		printf("%zu   %d has died\n", time, philo);
}

int get_time()
{
    size_t  time;
	struct timeval	current_time;

    gettimeofday(&current_time, NULL);
	// if (gettimeofday(NULL, &current_time) != 0)
    //     hier error messag!?
    time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000; //time is in millisec
	printf("Time: [%zu]\n", time);
	return (time);
}

void	clean_up(pthread_t *threads, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while(i < philo->data->philos)
	{
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	if (threads)
		free(threads);
	free(data);
	free(philo);

}