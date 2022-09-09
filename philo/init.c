/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:59:25 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/09 10:39:52 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->philos)
	{
		if (pthread_mutex_init(&data->fork_mut[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->msg_mut, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->death_mut, NULL) != 0)
		return (-1);
	return (0);
}

int	init_data(t_input *input, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->fork_mut = malloc(input->philos * sizeof(pthread_mutex_t));
	if (data->fork_mut == NULL)
	{
		free(data);
		free(input);
		free(philo);
		return (-1);
	}
	while (i < input->philos)
	{
		philo[i].num = i + 1;
		philo[i].last_eaten = 0;
		philo[i].total_eaten = 0;
		philo[i].data = data;
		philo[i].input = input;
		i++;
	}
	data->death = false;
	data->enough_eaten = 0;
	if (init_mutexes(data, input) != 0)
		return (free_structs(philo));
	return (0);
}
