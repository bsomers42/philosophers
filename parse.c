/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:50:57 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/02 14:53:22 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggg
#include <stdlib.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (str[i] == '\0' && (str[i - 1] == '-' || str[i - 1] == '+'))
		return (0);
	return (1);
}

static int	check_empty(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		min;
	size_t	num;

	i = check_empty(nptr);
	min = 1;
	num = 0;
	if (nptr[i] == '-')
	{
		if (nptr[i + 1] == '+' || nptr[i + 1] == '-')
			return (0);
		min = -1;
		i++;
	}
	if (nptr[i] == '+')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(num * min));
}


int	check_input(int argc, char *argv[])
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_isnumber(argv[i]) == 0)
			return (-1);
		// printf("Arg checked: %d, [%s] (= TO CHECK COUNTER)\n", i, argv[i]);
		i++;
	}
	return (0);
}

int    parse_input(int argc, char *argv[], t_data *data)
{
	if (check_input(argc, argv) < 0)
		return (-1);
	data->times_eaten = 0;
	data->how_much_eat = 0;
	data->time = get_time();
	data->start = get_time();
	data->philos = ft_atoi(argv[1]);
	data->die_sec = ft_atoi(argv[2]);
	data->eat_sec = ft_atoi(argv[3]);
	data->sleep_sec = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->times_eaten = ft_atoi(argv[5]);
		if (data->times_eaten <= 0)
			return (-1);
	}
	else
		data->times_eaten = (int)NULL;
	if (data->philos <= 0 || data->die_sec <=0 || data->eat_sec <= 0 || \
		data->sleep_sec <= 0)
		return (-1);
	return (0);
}

void	init_data(t_philo *philo, t_data *data)
{
	int	i;
	pthread_mutex_t *mutex;
	// pthread_mutex_t msg;
	// pthread_mutex_t death;



	i = 0;
	// msg = malloc(sizeof(pthread_mutex_t));
	// death = malloc(sizeof(pthread_mutex_t));
	mutex = malloc(data->philos * sizeof(pthread_mutex_t));
	//malloc check inbouwen!
	pthread_mutex_init(&philo->msg, NULL);
	pthread_mutex_init(&philo->death, NULL);

	while (i < data->philos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		// pthread_mutex_init(&msg[i], NULL);
		philo[i].num = i + 1;
		philo[i].eaten = 0;
		philo[i].mutex = mutex;
		philo[i].data = data;
		philo[i].last_time_eaten = 0;
		i++;
	}
}