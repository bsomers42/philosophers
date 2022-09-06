/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:52 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/06 18:10:30 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2 == 0)
		usleep(80);
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

// void	*philo_check(void *ptr)
// {
// 	t_data *data;

// 	data = (t_philo *)ptr;
// 	while (1)
// 	{
		// if (data->death == true)
		// 	return ;
// 		if (data->enough_eaten == data->input->must_eat)
// 			return ;
// 	}
// }

void	philosophers(t_input *input, t_philo *philo)
{
	int i;

	i = 0;
	// pthread_create(&philo[i].data->check_thr, NULL, &philo_check, &data);
	// philo->data->start = get_time();
	while (i < input->philos)
    {
        pthread_create(&philo[i].data->philo_thr, NULL, &philo_routine, &philo[i]);
        i++;
    }
	i = 0;
	while(i < input->philos)
	{
		pthread_join(philo[i].data->philo_thr, NULL);
		pthread_mutex_destroy(&philo->mutex[i]);
		i++;
	}
	free (philo);
}

int main(int argc, char *argv[])
{
	t_input	*input;
	t_philo *philo;

	input = (t_input *)malloc(sizeof(t_input));
   	if (argc > 6 || argc < 5 || parse_input(argc, argv, input) < 0)
	{
		printf("Wrong arguments!\n");
		return (0);
	}
	philo = (t_philo *)malloc(input->philos * sizeof(t_philo));
	init_data(input, philo);
	philosophers(input, philo);
}