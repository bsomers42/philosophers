/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:36:29 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:12:24 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_msg(int phil, size_t time, char c, t_philo *philo)
{
	if (check_death_done(philo) != 0)
		return ;
	pthread_mutex_lock(&philo->data->msg_mut);
	if (c == 'f')
		printf("%zu   \033[0;37m%d has taken a fork\033[0m\n", time, phil);
	if (c == 'e')
		printf("%zu   \033[0;33m%d is eating\033[0m\n", time, phil);
	if (c == 's')
		printf("%zu   \033[0;34m%d is sleeping\033[0m\n", time, phil);
	if (c == 't')
		printf("%zu   \033[0;32m%d is thinking\033[0m\n", time, phil);
	pthread_mutex_unlock(&philo->data->msg_mut);
}
