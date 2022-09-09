/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:52:35 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/09 10:06:42 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (str[i] == '\0' && (str[i - 1] == '-' || str[i - 1] == '+'))
		return (0);
	return (1);
}

int	check_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isnumber(argv[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int	parse_input(int argc, char *argv[], t_input *input)
{
	if (check_input(argc, argv) < 0)
		return (-1);
	input->philos = ft_atoi(argv[1]);
	input->time_die = ft_atoi(argv[2]);
	input->time_eat = ft_atoi(argv[3]);
	input->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		input->must_eat = ft_atoi(argv[5]);
		if (input->must_eat <= 0)
			return (-1);
	}
	else
		input->must_eat = 0;
	if (input->philos <= 0 || input->time_die <= 0 || input->time_eat <= 0 || \
		input->time_sleep <= 0)
		return (-1);
	return (0);
}
