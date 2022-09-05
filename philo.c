/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:49:47 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/05 17:03:30 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_usleep(size_t time)
{
    size_t timesleep;
	
	timesleep = get_time();
	while (get_time() - timesleep < time)
		usleep(100);
}

void	*philo_func(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		usleep(250);
	// philo->last_time_eaten = get_time();
	while (1)
	{
		if (philo->data->death == true)
			break ;
		pthread_mutex_lock(&philo->mutex[philo->right]);
		pthread_mutex_lock(&philo->mutex[philo->left]);
		printf("lock:  left = %i and right = %i\n", philo->left, philo->right);
		philo_msg(philo->num, get_time() - philo->data->start, 'r', philo);
		philo_msg(philo->num, get_time() - philo->data->start, 'l', philo);
		philo_msg(philo->num, get_time() - philo->data->start, 'e', philo);
		pthread_mutex_lock(&philo->msg);
		philo->last_time_eaten = get_time(); //protect mutex!
		ft_usleep(philo->data->eat_sec);
		printf("Last time eaten: [%zu]\n", get_time() - philo->last_time_eaten);
		philo->eaten = philo->eaten + 1;
		if (philo->eaten == philo->data->how_much_eat) //protect mutex!
			philo->data->times_eaten = philo->data->times_eaten + 1;
		pthread_mutex_unlock(&philo->msg);
		pthread_mutex_unlock(&philo->mutex[philo->right]);// % philo->data->philos]);
		pthread_mutex_unlock(&philo->mutex[philo->left]);
		printf("unlock in loop:  left = %i and right = %i\n", philo->left, philo->right);
		philo_msg(philo->num, get_time() - philo->data->start, 's', philo);
		ft_usleep(philo->data->sleep_sec);
		philo_msg(philo->num, get_time() - philo->data->start, 't', philo);
	}
	// printf("unlock:  left = %i and right = %i\n", philo->left, philo->right);
		// pthread_mutex_unlock(&philo->mutex[philo->right]);// % philo->data->philos]);
		// pthread_mutex_unlock(&philo->mutex[philo->left]);
	pthread_mutex_unlock(&philo->msg);
	printf("TEST\n");
	return ((void *)0);
}

void	*check_philosophers(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	printf("print-----------------------------\n");
	while (1)
	{
		// pthread_mutex_lock(&philo->msg);
		pthread_mutex_lock(&philo->data->death_mut);

		if (philo->data->times_eaten == philo->data->philos)
			return ((void *)1);
		if ((get_time() - philo->last_time_eaten) > (size_t)philo->data->die_sec && philo->data->death == false)
		{
		printf("philo bool %i\n", philo->data->death);
			philo->data->death = true;
			printf("%zu   \033[0;31m%d has died\033[0m\n", get_time() - philo->data->start, philo->num);
			pthread_mutex_unlock(&philo->data->death_mut);
			return (NULL);
			// pthread_mutex_unlock(&philo->death);
			// pthread_mutex_unlock(&philo->msg);

			// return ((void *)0);
		}
		// pthread_mutex_unlock(&philo->data->msg);
		pthread_mutex_unlock(&philo->data->death_mut);
	}
	// pthread_mutex_unlock(&philo->data->msg);
	pthread_mutex_unlock(&philo->data->death_mut);
	return (0);
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
		if (pthread_create(&philo[i].data->threads, NULL, &philo_func, &philo[i]) != 0) 
			return ;
		if (pthread_create(&philo[i].data->check_t, NULL, &check_philosophers, &philo[i]) != 0)
			return ;
		// usleep(100);
		i++;
	}
	printf("last test %i\n", i);
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
	if (argc > 6 || argc < 5 || parse_input(argc, argv, data) < 0)
		return (print_msg("Wrong arguments!\n", 1));
	philo = (t_philo *)malloc(data->philos * sizeof(t_philo));
	init_data(philo, data);
	init_philosophers(philo, data);
	printf("--END--\n");
}