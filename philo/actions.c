/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:32:27 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/04 10:03:25 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mut);
	if (philo->data->death == true || philo->data->enough_eaten == \
	philo->input->philos)
	{
		pthread_mutex_unlock(&philo->data->death_mut);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mut);
	return (0);
}

void	*one_philo(t_philo *philo)
{
	philo->last_eaten = get_time();
	pthread_mutex_lock(&philo->data->fork_mut[philo->num - 1]);
	philo_msg(philo->num, 'f', philo);
	while (1)
	{
		if (check_death_done(philo) == 1)
			break ;
	}
	pthread_mutex_unlock(&philo->data->fork_mut[philo->num - 1]);
	return (NULL);
}

int	philo_take_fork(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	else
		pthread_mutex_lock(&philo->data->fork_mut[philo->num - 1]);
	philo_msg(philo->num, 'f', philo);
	if (check_death_done(philo) != 0)
	{
		pthread_mutex_unlock(&philo->data->fork_mut[philo->num - 1]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->fork_mut[philo->num % \
	philo->input->philos]);
	philo_msg(philo->num, 'f', philo);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_death_done(philo) != 0)
	{
		pthread_mutex_unlock(&philo->data->fork_mut[philo->num % \
		philo->input->philos]);
		pthread_mutex_unlock(&philo->data->fork_mut[philo->num - 1]);
		return (1);
	}
	else
		philo_msg(philo->num, 'e', philo);
	pthread_mutex_lock(&philo->data->death_mut);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->data->death_mut);
	ft_usleep(philo->input->time_eat, philo);
	philo->total_eaten++;
	if (philo->total_eaten == philo->input->must_eat)
	{
		pthread_mutex_lock(&philo->data->death_mut);
		philo->data->enough_eaten++;
		pthread_mutex_unlock(&philo->data->death_mut);
	}
	pthread_mutex_unlock(&philo->data->fork_mut[philo->num % \
	philo->input->philos]);
	pthread_mutex_unlock(&philo->data->fork_mut[philo->num - 1]);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	philo_msg(philo->num, 's', philo);
	if (ft_usleep(philo->input->time_sleep, philo) == 1)
		return (1);
	return (0);
}
