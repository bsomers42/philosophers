/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:32:27 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:17:34 by bsomers       ########   odam.nl         */
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
	if (((get_time() - philo->last_eaten) > (size_t)philo->input->time_die))
	{
		pthread_mutex_lock(&philo->data->msg_mut);
		printf("%zu   \033[0;31m%d has died\033[0m\n", get_time() - \
		philo->data->start, philo->num);
		pthread_mutex_unlock(&philo->data->msg_mut);
		philo->data->death = true;
		pthread_mutex_unlock(&philo->data->death_mut);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mut);
	return (0);
}

int	philo_take_fork(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	else
		pthread_mutex_lock(&philo->data->fork_mut[philo->num - 1]);
	philo_msg(philo->num, get_time() - philo->data->start, 'f', philo);
	if (check_death_done(philo) != 0)
	{
		pthread_mutex_unlock(&philo->data->fork_mut[philo->num - 1]);
		return (1);
	}
	else
		pthread_mutex_lock(&philo->data->fork_mut[philo->num % \
		philo->input->philos]);
	philo_msg(philo->num, get_time() - philo->data->start, 'f', philo);
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
		philo_msg(philo->num, get_time() - philo->data->start, 'e', philo);
	philo->last_eaten = get_time();
	ft_usleep(philo->input->time_eat);
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
	philo_msg(philo->num, get_time() - philo->data->start, 's', philo);
	ft_usleep(philo->input->time_sleep);
	return (0);
}
