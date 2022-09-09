/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:58:07 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/09 10:39:06 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_destroy(&philo->data->msg_mut) != 0)
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

static int	check_empty(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		min;
	size_t	num;

	i = check_empty(nptr);
	min = 1;
	num = 0;
	if (nptr[i] == '-')
	{
		if (nptr[i + 1] == '+' || nptr[i + 1] == '-')
			return (0);
		min = -1;
		i++;
	}
	if (nptr[i] == '+')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(num * min));
}
