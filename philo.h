/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:55 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/08 15:08:37 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_input
{
	int	philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}	t_input;

typedef struct s_data
{
	bool	death;
	int		enough_eaten;
	size_t	start;
	pthread_mutex_t	msg_mut;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	*fork_mut;
}	t_data;

typedef struct s_philo
{
	int	num;
	size_t	last_eaten;
	int	total_eaten;
	t_data	*data;
	t_input *input;
}	t_philo;


//parsing and init
int		parse_input(int argc, char *argv[], t_input *input);
void	init_data(t_input *input, t_philo *philo, t_data *data);

//actions
int		check_death_done(t_philo *philo);
int		philo_take_fork(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);

//time and print
void	ft_usleep(size_t time);
size_t	get_time();
void	philo_msg(int phil, size_t time, char c, t_philo *philo);

//utils
int		ft_isnumber(char *str);
int		ft_atoi(const char *nptr);
void	destroy_and_free(t_philo *philo);

#endif