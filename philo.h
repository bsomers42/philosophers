/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:16:28 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/01 11:58:57 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <pthread.h>

typedef struct	s_num
{
	int		philos;
	int		die_sec;
    int     eat_sec;
	int		sleep_sec;
	int		times_eat;
}				t_num;

int	ft_atoi(const char *nptr);
void	display_message(int	i, char c);

#endif