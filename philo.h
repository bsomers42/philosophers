/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:16:28 by bsomers       #+#    #+#                 */
/*   Updated: 2022/06/15 13:34:02 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <pthread.h>

typedef struct s_philo
{
	int		philos;
	int		sleep_sec;
	int		die_sec;
    int     eat_sec;
}		t_philo;

int	ft_atoi(const char *nptr);

#endif