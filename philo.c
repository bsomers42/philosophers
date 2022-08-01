/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 10:45:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/08/01 12:02:54 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggggg
#include <unistd.h> //weegggg

void	*philo_func()
{
	printf("Test in philo_func\n");
	usleep(300);
	printf("ending thread\n");
	return(NULL);
}

void	philosophers(t_num *num_time)
{
	pthread_t	philo[num_time->philos]; //as much threads as philos
	int	i;

	i = 0;
	while (i < num_time->philos)
	{
		pthread_create(&philo[i], NULL, &philo_func, NULL);
		i++;
	}
	display_message(3, 'e');
	i = 0;
	while (i < num_time->philos)
	{
		pthread_join(philo[i], NULL); //like a wait function, but for threads
		i++;
	}
}

void	parse_input(char *argv[], int argc, t_num *num_time)
{
	num_time->philos = ft_atoi(argv[1]);
	printf("philos: %d\n", num_time->philos);
	num_time->die_sec = ft_atoi(argv[2]);
	num_time->eat_sec = ft_atoi(argv[3]);
	num_time->sleep_sec = ft_atoi(argv[4]);
	if (argc == 6)
		num_time->times_eat = ft_atoi(argv[5]);
	else
		num_time->times_eat = (int)NULL;
}

int main(int argc, char *argv[])
{
	t_num	num_time;

	if (argc > 6 || argc < 5)
	{	
		printf("Wrong number of arguments!\n");
		return (0);
	}
	parse_input(argv, argc, &num_time);
	philosophers(&num_time);
	return (0);
}