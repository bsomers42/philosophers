/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:36:29 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/06 17:37:20 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_msg(int phil, size_t time, char c, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->msg);
	if (c == 'l')
		printf("%zu   \033[0;37m%d has taken left fork\033[0m\n", time, phil);
	if (c == 'r')
		printf("%zu   \033[0;37m%d has taken right fork\033[0m\n", time, phil);
	if (c == 'e')
		printf("%zu   \033[0;33m%d is eating\033[0m\n", time, phil);
	if (c == 's')
		printf("%zu   \033[0;34m%d is sleeping\033[0m\n", time, phil);
	if (c == 't')
		printf("%zu   \033[0;32m%d is thinking\033[0m\n", time, phil);
	if (c == 'd')
		printf("%zu   \033[0;31m%d has died\033[0m\n", time, phil);
	pthread_mutex_unlock(&philo->data->msg);
}