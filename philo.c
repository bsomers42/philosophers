/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:49:47 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/01 12:25:35 by bsomers       ########   odam.nl         */
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
		philo_msg(philo->num, get_time(), 'l');
		pthread_mutex_lock(&philo->mutex[philo->num]);// % philo->data->philos]);
		philo_msg(philo->num, get_time(), 'r');
		philo_msg(philo->num, get_time(), 'e');
		philo->eaten = philo->eaten + 1;
		// if (philo->eaten == philo->data->wants_eat)
		if (philo->eaten == philo->data->how_much_eat)
			philo->data->times_eaten = philo->data->times_eaten + 1;
		// usleep(philo->data->times_eaten * 1000);
		usleep(philo->data->eat_sec * 1000);
		philo->last_time_eaten = get_time();
		pthread_mutex_unlock(&philo->mutex[philo->num - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->num]);// % philo->data->philos]);
		philo_msg(philo->num, get_time(), 's');
		usleep(philo->data->sleep_sec * 1000);
		philo_msg(philo->num, get_time(), 't');
	}
	return ((void *)0);
}

void	*check_philosophers(void *ptr)
{
	int	i;
	t_philo *philo;

	philo = (t_philo *)ptr;
	i = 0;
	printf("Here................................................................???\n");
	while (1)
	{
		if (philo[i].data->times_eaten == philo[i].data->philos)
			return ((void *)1);
		if ((get_time() - philo[i].last_time_eaten) > (size_t)philo->data->die_sec)
		{
			// usleep(100);
			philo_msg(philo->num, get_time(), 'd');
			return ((void *)1);
		}
		i = (i + 1) % philo->data->philos;
		usleep(500);
	}
	return ((void *)0);
}

void	init_philosophers(t_philo *philo, t_data *data)
{
	int	i;
	pthread_t	threads[philo->data->philos];
	pthread_t	check_thr[philo->data->philos];

	i = 0;
	while (i < philo->data->philos)
	{
		// printf("Here?\n");
		pthread_create(&threads[i], NULL, &philo_func, &philo[i]);
		if (pthread_create(&check_thr[i], NULL, &check_philosophers, &philo[i]) == 1)
			break ;
		// usleep(100);
		i++;
	}
	// check_philosophers(philo, data);
	i = 0;
	while (i < philo->data->philos)
	{
		if (pthread_join(threads[i], NULL) != 0) //like a wait function, but for threads
			return ;
		i++;
	}
	clean_up(threads, philo, data);
}

int	main(int argc, char *argv[])
{
	t_philo	*philo;
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	// philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	if (argc > 6 || argc < 5 || parse_input(argc, argv, data) < 0)
		return (print_msg("Wrong arguments!\n", 1));
	// data = (t_data *)malloc(sizeof(t_data));
	philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	init_data(philo, data);
	init_philosophers(philo, data);
}