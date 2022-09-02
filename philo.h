/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:16:28 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/02 14:41:06 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

#include <pthread.h>
#include <stdbool.h>

typedef struct	s_data
{
	int		philos;
	int		die_sec;
    int     eat_sec;
	int		sleep_sec;
	int		how_much_eat;
	int		times_eaten;
	bool	death;
	size_t	start;
	size_t	time;
}				t_data;

typedef struct	s_philo
{
	int	num;
	int	eaten;
	t_data	*data;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	msg;
	pthread_mutex_t death;
	size_t	last_time_eaten;
}				t_philo;

/*parsing functions*/
int	ft_atoi(const char *nptr);
int	ft_isnumber(char *str);
int	check_input(int argc, char *argv[]);
int    parse_input(int argc, char *argv[], t_data *data);
void	init_data(t_philo *philo, t_data *data);

/*time and message functions*/
int get_time();
void philo_msg(int philo, size_t time, char c, pthread_mutex_t *msg);
int    print_msg(char *str, int ret);

void	clean_up(pthread_t *threads, pthread_t	*check_thr, t_philo *philo, t_data *data);

#endif