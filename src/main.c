/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:03:20 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/10 08:39:56 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t ms)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < ms)
		usleep(500);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!is_valid_input(ac, av))
		return (1);
	init_data(&data, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, &data, forks, av);
	create_thread(&data, forks);
	ft_destroy(NULL, &data, forks);
}
