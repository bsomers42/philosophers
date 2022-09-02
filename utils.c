/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 15:00:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/02 14:23:01 by bsomers       ########   odam.nl         */
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

void philo_msg(int philo, size_t time, char c, pthread_mutex_t *msg)
{
	msg = NULL;
	// pthread_mutex_lock(msg);
	if (c == 'l')
		printf("%zu   \033[0;37m%d has taken left fork\033[0m\n", time, philo);
	if (c == 'r')
		printf("%zu   \033[0;37m%d has taken right fork\033[0m\n", time, philo);
	if (c == 'e')
		printf("%zu   \033[0;33m%d is eating\033[0m\n", time, philo);
	if (c == 's')
		printf("%zu   \033[0;34m%d is sleeping\033[0m\n", time, philo);
	if (c == 't')
		printf("%zu   \033[0;32m%d is thinking\033[0m\n", time, philo);
	if (c == 'd')
		printf("%zu   \033[0;31m%d has died\033[0m\n", time, philo);
	// pthread_mutex_unlock(msg);
}

int get_time()
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
	while(i < philo->data->philos)
	{
		if (pthread_join(threads[i], NULL) != 0) //like a wait function, but for threads
			return ;
		if (pthread_join(check_thr[i], NULL) != 0) //like a wait function, but for threads
			return ;
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	// pthread_mutex_destroy(philo->msg);
	// pthread_mutex_destroy(philo->death);
	// i = 0;
	// while (i < philo->data->philos)
	// {
	// 	free(&philo[i]);
	// 	i++;
	// }
	free(philo);
	if (data)
		free(data);

}