/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 16:58:07 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/04 11:46:11 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_empty(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == '\n' || nptr[i] == ' ' || nptr[i] == '\t'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		min;
	size_t	num;

	i = check_empty(nptr);
	min = 1;
	num = 0;
	if (nptr[i] == '-')
	{
		if (nptr[i + 1] == '+' || nptr[i + 1] == '-')
			return (0);
		min = -1;
		i++;
	}
	if (nptr[i] == '+')
		i++;
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(num * min));
}
