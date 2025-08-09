/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:07:36 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/09 18:08:38 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_data(t_data *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void init_forks(pthread_mutex_t *forks, int philo_num)
{
	int i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void init_input(t_philo *philos, char **av)
{
	philos->num_of_philos = ft_atoi(av[1]);
	philos->time_to_die = ft_atoi(av[2]);
	philos->time_to_eat = ft_atoi(av[3]);
	philos->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos->times_to_eat = ft_atoi(av[5]);
	else
			philos->times_to_eat = -1;
}

void init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks, char **av)
{
	int i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos->id = i + 1;
		philos->eating = 0;
		philos->meals_eaten = 0;
		init_input(philos, av);
		philos->dead = &data->dead_flag;
		philos->start_time = get_time_in_ms();
		philos->last_meal = get_time_in_ms();
		philos->write_lock = &data->write_lock;
		philos->dead_lock = &data->dead_lock;
		philos->meal_lock = &data->meal_lock;
		philos->left_fork = &forks[i];
		if (i == 0)
			philos->right_fork = &forks[philos->num_of_philos - 1];
		else
			philos->right_fork = &forks[i - 1];
	}
}
