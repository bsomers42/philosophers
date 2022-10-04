/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:58:07 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/04 11:46:20 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_philo *philo, pthread_t *philo_thr, pthread_t mon_thr)
{
	int	i;

	i = 0;
	while (i < philo->input->philos)
	{
		if (pthread_join(philo_thr[i], NULL) != 0)
			break ;
		i++;
	}
	pthread_join(mon_thr, NULL);
	free(philo_thr);
	destroy_mutexes(philo);
	return (0);
}

int	clean_up_after_error(t_philo *philo, pthread_t *philo_thr)
{
	pthread_mutex_unlock(&philo->data->death_mut);
	free(philo_thr);
	destroy_mutexes(philo);
	free_structs(philo);
	return (-1);
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->input->philos)
	{
		if (pthread_mutex_destroy(&philo->data->fork_mut[i]) != 0)
			return ;
		i++;
	}
	if (pthread_mutex_destroy(&philo->data->death_mut) != 0)
		return ;
}

int	free_structs(t_philo *philo)
{
	if (philo->data->fork_mut)
		free (philo->data->fork_mut);
	if (philo->data)
		free (philo->data);
	if (philo->input)
		free (philo->input);
	free (philo);
	return (-1);
}
