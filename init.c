/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:59:25 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/06 18:05:21 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    init_data(t_input *input, t_philo *philo)
{
    int i;

    i = 0;
    philo->mutex = malloc(input->philos * sizeof(pthread_mutex_t));
    while (i < input->philos)
    {
        philo[i].num = i + 1;
        philo[i].last_eaten = 0;
        philo[i].total_eaten = 0;
        philo[i].mutex = philo->mutex;
        pthread_mutex_init(philo[i].mutex, NULL);
        i++;
    }
}