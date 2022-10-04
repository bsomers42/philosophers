/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:30:55 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/04 10:23:34 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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
	bool			death;
	int				enough_eaten;
	size_t			start;
	pthread_mutex_t	death_mut;
	pthread_mutex_t	*fork_mut;
}	t_data;

typedef struct s_philo
{
	int		num;
	size_t	last_eaten;
	int		total_eaten;
	t_data	*data;
	t_input	*input;
}	t_philo;

//parsing and init
int		parse_input(int argc, char *argv[], t_input *input);
int		init_data(t_input *input, t_philo *philo, t_data *data);

//actions
int		check_death_done(t_philo *philo);
int		philo_take_fork(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
void	*one_philo(t_philo *philo);

//time and print
int		ft_usleep(size_t time, t_philo *philo);
int		ft_usleep_start(size_t time);
size_t	get_time(void);
void	philo_msg(int phil, char c, t_philo *philo);
int		error_input_msg(void);

//utils and cleaning
int		ft_atoi(const char *nptr);
void	destroy_mutexes(t_philo *philo);
int		free_structs(t_philo *philo);
int		clean_up_after_error(t_philo *philo, pthread_t *philo_thr);
int		join_threads(t_philo *philo, pthread_t *philo_thr, pthread_t mon_thr);

#endif