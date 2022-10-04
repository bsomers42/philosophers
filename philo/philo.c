/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/04 11:50:56 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_death(t_philo *philo, int i)
{
	philo->data->death = true;
	printf("%zu   \033[0;31m%d died\033[0m\n", get_time() - \
	philo->data->start, i + 1);
	pthread_mutex_unlock(&philo->data->death_mut);
	return (NULL);
}

void	*philo_monitor(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mut);
		if (get_time() - philo[i].last_eaten >= (size_t)philo->input->time_die \
		&& philo->data->death != true && philo[i].last_eaten != 0)
			return (handle_death(philo, i));
		if (philo->data->death == true || philo->data->enough_eaten == \
		philo->input->philos)
			break ;
		pthread_mutex_unlock(&philo->data->death_mut);
		i++;
		if (i == philo->input->philos)
			i = 0;
	}
	pthread_mutex_unlock(&philo->data->death_mut);
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->data->death_mut);
	pthread_mutex_unlock(&philo->data->death_mut);
	if (philo->input->philos == 1)
		return (one_philo(philo));
	if (philo->num % 2 == 0)
		ft_usleep_start(100);
	pthread_mutex_lock(&philo->data->death_mut);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->data->death_mut);
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
		philo_msg(philo->num, 't', philo);
	}
}

int	philosophers(t_input *input, t_philo *philo)
{
	int			i;
	pthread_t	*philo_thr;
	pthread_t	mon_thr;

	i = 0;
	philo_thr = malloc(input->philos * sizeof(pthread_t));
	if (philo_thr == NULL)
		return (free_structs(philo));
	pthread_mutex_lock(&philo->data->death_mut);
	while (i < input->philos)
	{
		if (pthread_create(&philo_thr[i], NULL, &philo_routine, &philo[i]) != 0)
			return (clean_up_after_error(philo, philo_thr));
		i++;
	}
	philo->data->start = get_time();
	if (pthread_create(&mon_thr, NULL, &philo_monitor, philo) != 0)
		return (clean_up_after_error(philo, philo_thr));
	pthread_mutex_unlock(&philo->data->death_mut);
	join_threads(philo, philo_thr, mon_thr);
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
