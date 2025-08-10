/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:19:58 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/09 23:06:31 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	unsigned long long	value;
	int					sign;
	int					i;

	value = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		value = value * 10 + str[i] - 48;
		i++;
	}
	return (value * sign);
}

int	is_all_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

int	is_valid_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "Number of arguments required is 4 or 5\n", 39), 0);
	if (ft_atoi(av[1]) > PHILO_MAX || ft_atoi(av[1]) <= 0
		|| !is_all_numeric(av[1]))
		return (write(2, "Wrong number of philosophers\n", 29), 0);
	if (ft_atoi(av[2]) <= 0 || !is_all_numeric(av[2]))
		return (write(2, "Invalid time to die\n", 20), 0);
	if (ft_atoi(av[3]) <= 0 || !is_all_numeric(av[3]))
		return (write(2, "Invalid time to eat\n", 20), 0);
	if (ft_atoi(av[4]) <= 0 || !is_all_numeric(av[4]))
		return (write(2, "Invalid time to sleep\n", 22), 0);
	if (av[5] && (ft_atoi(av[5]) < 0 || !is_all_numeric(av[5])))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				50), 0);
	return (1);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() failed!\n", 23);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
