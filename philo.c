/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:49:47 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/02 15:30:00 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*philo_func(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		usleep(10);
	philo->last_time_eaten = get_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[philo->num - 1]);
		pthread_mutex_lock(&philo->mutex[philo->num]);// % philo->data->philos]);
		// pthread_mutex_lock(philo->msg);
		philo_msg(philo->num, get_time() - philo->data->start, 'l', &philo->msg);
		philo_msg(philo->num, get_time() - philo->data->start, 'r', &philo->msg);
		philo->last_time_eaten = get_time(philo->data->start); //protect mutex!
		philo_msg(philo->num, get_time() - philo->data->start, 'e', &philo->msg);
		// pthread_mutex_unlock(philo->msg);
		philo->eaten = philo->eaten + 1;
		// pthread_mutex_lock(&philo->msg[philo->num]);
		if (philo->eaten == philo->data->how_much_eat) //protect mutex!
			philo->data->times_eaten = philo->data->times_eaten + 1;
		usleep(philo->data->eat_sec * 1000);
		printf("Last time eaten: [%zu]\n", get_time() - philo->last_time_eaten);
		// pthread_mutex_unlock(&philo->msg[philo->num]);
		// pthread_mutex_unlock(philo->msg);
		pthread_mutex_unlock(&philo->mutex[philo->num - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->num]);// % philo->data->philos]);
		philo_msg(philo->num, get_time() - philo->data->start, 's', &philo->msg);
		usleep(philo->data->sleep_sec * 1000);
		philo_msg(philo->num, get_time() - philo->data->start, 't', &philo->msg);
	}
	return ((void *)0);
}

void	*check_philosophers(void *ptr)
{
	// int	i;
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		usleep(10);

	//i = 0;
	// printf("Here................................................................???\n");
	while (1)
	{
		if (philo->data->times_eaten == philo->data->philos)
			return ((void *)1);
		if ((get_time() - philo->last_time_eaten) > (size_t)philo->data->die_sec)
		{
			printf("[%lu], [%zu], [%zu]\n", get_time() - philo->data->start, philo->last_time_eaten, (size_t)philo->data->die_sec);
			// usleep(100);
			// pthread_mutex_lock(philo->msg);
			// pthread_mutex_lock(philo->death);
			philo->data->death = true;
			printf("Here................................................................???\n");
			philo_msg(philo->num, get_time() - philo->data->start, 'd', &philo->msg);
			// pthread_mutex_unlock(philo->msg);
			// pthread_mutex_unlock(philo->death);
			return ((void *)1);
		}
		// i = (i + 1) % philo->data->philos;
		usleep(500);
	}
	// printf("Here................................................................???\n");
	// philo_msg(philo->num, get_time(), 'd');//, philo->msg);

	return ((void *)0);
}

void	init_philosophers(t_philo *philo, t_data *data)
{
	int	i;
	pthread_t	threads[philo->data->philos];
	pthread_t	check_thr[philo->data->philos];

	i = 0;
	data->start = get_time();
	while (i < philo->data->philos)
	{
		printf("Here?\n");
		pthread_create(&threads[i], NULL, &philo_func, &philo[i]);
		if (pthread_create(&check_thr[i], NULL, &check_philosophers, &philo[i]))
			return ;
		// usleep(100);
		i++;
	}
	// check_philosophers(philo, data);
	// i = 0;
	// while (i < philo->data->philos)
	// {
	// 	if (pthread_join(threads[i], NULL) != 0) //like a wait function, but for threads
	// 		return ;
	// 	i++;
	// }
	clean_up(threads, check_thr, philo, data);
}

void	func_atexit(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_data *data;

	// atexit(func_atexit);
	data = (t_data *)malloc(sizeof(t_data));
	// philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	if (argc > 6 || argc < 5 || parse_input(argc, argv, data) < 0)
		return (print_msg("Wrong arguments!\n", 1));
	// data = (t_data *)malloc(sizeof(t_data));
	philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	init_data(philo, data);
	init_philosophers(philo, data);
	printf("--END--\n");
}