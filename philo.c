/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:49:47 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/26 11:12:58 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	philo_func(void *philo)
{
	(struct t_philo*) philo;
	printf("%d is eating\n", philo->num)
}

void	philosophers(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		pthread_create(philo[i]->philo, NULL, &philo_func, &philo[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	t_data data;

	if (argc > 6 || argc < 5)
	{	
		printf("Wrong number of arguments!\n");
		return (0);
	}
	parse_input(argc, argv, &philo, &data);
	init_data(&philo, data.philos);
	philosophers(&philo, &data);

}