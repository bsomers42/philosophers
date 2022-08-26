/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:50:57 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/26 10:11:09 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    parse_input(int argc, char *argv[], t_philo *philo, t_data *data)
{
	data->philos = ft_atoi(argv[1]);
	data->die_sec = ft_atoi(argv[2]);
	data->eat_sec = ft_atoi(argv[3]);
	data->sleep_sec = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_eat = ft_atoi(argv[5]);
	else
		data->times_eat = (int)NULL;
	philo = malloc(data->philos * sizeof(t_philo *));
}

void	init_data(t_philo *philo, int total)
{
	int	i

	i = 0;
	while (i < total)
	{
		philo[i]->l_fork = (i - 1)%total;
		philo[i]->r_fork = i;
		philo[i]->die_sec = 0;
		philo[i]->eat_sec = 0;
		philo[i]->sleep_sec = 0;
		philo[i]->times_eat = 0;
		philo[i]->num = i;
		philo[i]->philo = philo;
		i++;
	}
}