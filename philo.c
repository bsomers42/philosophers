/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:19:55 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->num % 2 == 0)
		usleep(250);
	philo->last_eaten = get_time();
	while (1)
	{
		if (philo_take_fork(philo) != 0)
			return (NULL);
		if (philo_eat(philo) != 0)
			return (NULL);
		if (philo_sleep(philo) != 0)
			return (NULL);
		if (check_death_done(philo) != 0)
			return (NULL);
		philo_msg(philo->num, get_time() - philo->data->start, 't', philo);
	}
}

void	philosophers(t_input *input, t_philo *philo)
{
	int			i;
	pthread_t	philo_thr[input->philos];

	i = 0;
	philo->data->start = get_time();
	while (i < input->philos)
	{
		pthread_create(&philo_thr[i], NULL, &philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < input->philos)
	{
		pthread_join(philo_thr[i], NULL);
		i++;
	}
	destroy_and_free(philo);
}

int	main(int argc, char *argv[])
{
	t_input	*input;
	t_philo	*philo;
	t_data	*data;

	input = (t_input *)malloc(sizeof(t_input));
	data = (t_data *)malloc(sizeof(t_data));
	if (argc > 6 || argc < 5 || parse_input(argc, argv, input) < 0)
	{
		printf("Wrong arguments!\nUsage: ./philo a b c d e \n\
		a = <number of philos*>\n \
		b = <time to die>\n \
		c = <time to eat>\n \
		d = <time to sleep>\n \
		e = <optional: number of times each philo must eat>\n \
		*should be at least two, because everyone needs two forks to eat!\n");
		return (0);
	}
	philo = (t_philo *)malloc(input->philos * sizeof(t_philo));
	init_data(input, philo, data);
	philosophers(input, philo);
}
