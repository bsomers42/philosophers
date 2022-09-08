/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:59:25 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:20:03 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_input *input, t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->fork_mut = malloc(input->philos * sizeof(pthread_mutex_t));
	while (i < input->philos)
	{
		philo[i].num = i + 1;
		philo[i].last_eaten = 0;
		philo[i].total_eaten = 0;
		philo[i].data = data;
		philo[i].input = input;
		pthread_mutex_init(&data->fork_mut[i], NULL);
		i++;
	}
	data->death = false;
	data->enough_eaten = 0;
	pthread_mutex_init(&data->msg_mut, NULL);
	pthread_mutex_init(&data->death_mut, NULL);
}
