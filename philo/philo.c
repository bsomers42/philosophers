/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/13 12:57:44 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->data->death_mut);
	pthread_mutex_unlock(&philo->data->death_mut);
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

int	join_threads(t_philo *philo, pthread_t *philo_thr)
{
	int	i;

	i = 0;
	while (i < philo->input->philos)
	{
		if (pthread_join(philo_thr[i], NULL) != 0)
			break ;
		i++;
	}
	return (0);
}

int	philosophers(t_input *input, t_philo *philo)
{
	int			i;
	pthread_t	*philo_thr;

	i = 0;
	philo_thr = malloc(input->philos * sizeof(pthread_t));
	if (philo_thr == NULL)
		return (free_structs(philo));
	philo->data->start = get_time();
	pthread_mutex_lock(&philo->data->death_mut);
	while (i < input->philos)
	{
		if (pthread_create(&philo_thr[i], NULL, &philo_routine, &philo[i]) != 0)
		{
			free(philo_thr);
			destroy_mutexes(philo);
			free_structs(philo);
			return (-1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->death_mut);
	join_threads(philo, philo_thr);
	free(philo_thr);
	destroy_mutexes(philo);
	return (free_structs(philo));
}

int	main(int argc, char *argv[])
{
	t_input	*input;
	t_philo	*philo;
	t_data	*data;

	input = (t_input *)malloc(sizeof(t_input));
	if (input == NULL)
		return (0);
	if (argc > 6 || argc < 5 || parse_input(argc, argv, input) < 0)
		return (free(input), error_input_msg());
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
	{
		free(input);
		return (0);
	}
	philo = (t_philo *)malloc(input->philos * sizeof(t_philo));
	if (philo == NULL)
	{
		free(input);
		free(data);
		return (0);
	}
	if (init_data(input, philo, data) < 0)
		return (0);
	philosophers(input, philo);
}
