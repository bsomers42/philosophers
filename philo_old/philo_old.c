/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 10:45:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/25 14:46:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggggg
#include <unistd.h> //weegggg

void	*philo_func(void *count)
{
	// pthread_mutex_t	fork[5];//num_time->philos];
	int 	i;
	int		j;
	i = *(int*)count;
	j = 0;

	// while (j < 5)
	// {
	// 	pthread_mutex_init(&fork[j], NULL);
	// 	j++;
	// }
	printf("Philosopher %d is thinking\n", i);
	// pthread_mutex_lock(&fork[i]);
	// pthread_mutex_lock(&fork[i + 1]);
	// printf("Philosopher %d is eating\n", i);
	sleep(3);
	// pthread_mutex_unlock(&fork[i]);
	// pthread_mutex_unlock(&fork[i + 1]);
	printf("Philo %d finished eating\n", i);
	return(NULL);
}

void	philosophers(t_num *num_time)
{
	pthread_t	philo[num_time->philos]; //as much threads as philos
	// pthread_mutex_t	fork[num_time->philos];
	int	i;
	int *a = NULL;

	i = 0;
	*a = i;
	// while (i < num_time->philos)
	// {
	// 	pthread_mutex_init(&fork[i], NULL);
	// 	i++;
	// }
	while (i < num_time->philos)
	{
		*a = i;
		if (pthread_create(&philo[i], NULL, &philo_func, a) != 0)
		{
			perror("Failed to create thread\n");
			return ;
		}
		printf("Thread %d started\n", i);
		i++;
	}
	// display_message(i, 'e');/watch
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