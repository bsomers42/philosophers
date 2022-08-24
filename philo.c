/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 10:45:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/24 14:40:12 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggggg
#include <unistd.h> //weegggg

void	*philo_func()
{
	// pthread_mutex_lock(&mutex);
	printf("Test in philo_func\n");
	usleep(300);
	// printf("ending thread\n");
	// pthread_mutex_unlock(&mutex);
	return(NULL);
}

void	philosophers(t_num *num_time)
{
	pthread_t	philo[num_time->philos]; //as much threads as philos
	// pthread_mutex_t	mutex;
	int	i;

	i = 0;
	// pthread_mutex_init(&mutex, NULL);
	while (i < num_time->philos)
	{
		if (pthread_create(&philo[i], NULL, &philo_func, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return ;
		}
		printf("Thread %d started\n", i);
		i++;
	}
	// display_message(i, 'e');
	i = 0;
	while (i < num_time->philos)
	{
		if (pthread_join(philo[i], NULL) != 0) //like a wait function, but for threads
			return ;
		printf("Thread %d closed\n", i);
		i++;
	}
	// pthread_mutex_destroy(&mutex);
}

void	parse_input(char *argv[], int argc, t_num *num_time)
{
	num_time->philos = ft_atoi(argv[1]);
	printf("philos: %d\n", num_time->philos);
	num_time->die_sec = ft_atoi(argv[2]);
	num_time->eat_sec = ft_atoi(argv[3]);
	num_time->sleep_sec = ft_atoi(argv[4]);
	if (argc == 6)
		num_time->times_eat = ft_atoi(argv[5]);
	else
		num_time->times_eat = (int)NULL;
}

int main(int argc, char *argv[])
{
	t_num	num_time;

	if (argc > 6 || argc < 5)
	{	
		printf("Wrong number of arguments!\n");
		return (0);
	}
	parse_input(argv, argc, &num_time);
	philosophers(&num_time);
	return (0);
}