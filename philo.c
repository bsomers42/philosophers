/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:15:30 by bsomers       #+#    #+#                 */
/*   Updated: 2022/06/15 14:21:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggggg
#include <unistd.h> //wegggg

// void	*thread_test()
// {
// 	printf("Threading around\n");
// 	usleep(60);
// 	printf("Ending thread\n");
// 	return (0);
// }

void	down_chopsticks(int c1, int c2, pthread_mutex_t *chopstick)
{
	pthread_mutex_unlock(&chopstick[c1]);
	pthread_mutex_unlock(&chopstick[c2]);

}

void	grab_chopstick(int phil, int c, char *hand, pthread_mutex_t *chopstick)
{
	pthread_mutex_lock(&chopstick[c]);
	printf("Philo %d: took %s chopstick %d\n", phil, hand, c);
}

int	food_on_table(t_philo *str_philo, pthread_mutex_t *food_lock)
{
	static int	food;
	int			myfood;

	food = 10 * str_philo->philos;
	myfood = 0;
	pthread_mutex_lock(food_lock);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock(food_lock);
	return(myfood);
}

void	*philosopher(void *num, t_philo *str_philo, pthread_mutex_t *chopstick, pthread_mutex_t *food_lock)
{
	int	id;
	// int	i;
	int	left_chopstick;
	int	right_chopstick;
	int	f;

	id = (int)num;
	printf("Philo %d stops thinking and starts eating.\n", id);
	right_chopstick = id;
	left_chopstick = id + 1;
	if (left_chopstick == str_philo->philos)
		left_chopstick = 0;
	while (((f) = (food_on_table(str_philo, food_lock))))
	{
		if (id == 1)
			usleep(str_philo->sleep_sec); //If philo 1 takes a nap before picking up the fork, the other philo's can eat and not deadlock.
		grab_chopstick(id, right_chopstick, "right", chopstick);
		grab_chopstick(id, left_chopstick, "left", chopstick);
		printf("Philo %d: eating.\n", id);
		usleep(str_philo->sleep_sec * ((str_philo->philos * 10) - f + 1));
		down_chopsticks(left_chopstick, right_chopstick, chopstick);
	}
	printf("Philosopher %d is done eating. \n", id);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	philo[(ft_atoi(argv[1]))];
	pthread_mutex_t	chopstick[(ft_atoi(argv[1]))];
	pthread_mutex_t food_lock;
	t_philo	str_philo;
	int	i;

	// Arg 1 = number of philos
	// Arg 2 = time to die 
	// Arg 3 = time to eat 
	// Arg 4 = time to sleep
	i = 0;
	str_philo.sleep_sec = ft_atoi(argv[4]);
	str_philo.philos = ft_atoi(argv[1]);
	if (argc < 3)
		return (0);
	pthread_mutex_init(&food_lock, NULL);
	while (i < str_philo.philos)
	{
		pthread_mutex_init(&chopstick[i], NULL);
		i++;
	}
	i = 0;
	while (i < str_philo.philos)
	{
		
		pthread_create(&philo[i], NULL, philosopher, (*void)i, &str_philo, &chopstick, &food_lock);
		i++;
	}
	i = 0;
	while (i < str_philo.philos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	// pthread_create(&t0, NULL, &thread_test, NULL);
	// pthread_create(&t1, NULL, &thread_test, NULL);
	// pthread_join(t0, NULL);//kindof a waitpid function
	// pthread_join(t1, NULL);//kindof a waitpid function
	return (0);
}
