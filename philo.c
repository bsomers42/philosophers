/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/11 11:15:30 by bsomers       #+#    #+#                 */
/*   Updated: 2022/06/11 11:32:36 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h> //weggggg
#include <unistd.h> //wegggg

void	*thread_test()
{
	printf("Threading around\n");
	usleep(30);
	printf("Ending thread\n");
	return (0);
}

int	main()//int argc, char *argv[])
{
	pthread_t	t0, t1;

	pthread_create(&t0, NULL, &thread_test, NULL);
	pthread_create(&t1, NULL, &thread_test, NULL);
	pthread_join(t0, NULL);//kindof a waitpid function
	pthread_join(t1, NULL);//kindof a waitpid function

	return (0);
}
