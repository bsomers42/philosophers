/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:32:27 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/06 18:04:07 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_done(t_philo *philo)
{
	if (philo->data->death == true)
		return (1);
	if (philo->data->enough_eaten == philo->data->input->must_eat)
		return (1);
	if ((get_time() - philo->last_eaten) > (size_t)philo->data->input->time_die)
	{
		printf("%zu   \033[0;31m%d has died\033[0m\n", get_time() - philo->data->start, philo->num);
		philo->data->death = true;
		return (1);
	}
	return (0);
}

int    philo_take_fork(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	check_death_done(philo);
	pthread_mutex_lock(&philo->mutex[philo->num - 1]);
	pthread_mutex_lock(&philo->mutex[philo->num % philo->data->input->philos]);
	philo_msg(philo->num, get_time() - philo->data->start, 'r', philo);
	philo_msg(philo->num, get_time() - philo->data->start, 'l', philo);
	return (0);
}

int    philo_eat(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	philo_msg(philo->num, get_time() - philo->data->start, 'e', philo);
	philo->last_eaten = get_time();
	ft_usleep(philo->data->input->time_eat);
	pthread_mutex_unlock(&philo->mutex[philo->num % philo->data->input->philos]);
	pthread_mutex_unlock(&philo->mutex[philo->num - 1]);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return (1);
	philo_msg(philo->num, get_time() - philo->data->start, 's', philo);
	ft_usleep(philo->data->input->time_sleep);
	return (0);
}
