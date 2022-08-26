/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:16:28 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/26 10:11:33 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <pthread.h>

typedef struct	s_philo
{
	int		num;
	int		l_fork;
	int		r_fork;
	int		die_sec;
    int     eat_sec;
	int		sleep_sec;
	int		times_eat;
	pthread_t	philo;
}				t_philo;

typedef struct	s_data
{
	int		philos;
	int		die_sec;
    int     eat_sec;
	int		sleep_sec;
	int		times_eat;
	pthread_mutex_t	*mutex;
}				t_data;


int	ft_atoi(const char *nptr);
void	display_message(int	i, char c);
void	init_data(t_philo *philo, int total);
void    parse_input(int argc, char *argv[], t_philo *philo, t_data *data);

#endif