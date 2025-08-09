/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:25:36 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/09 23:36:34 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(char *str, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	create_thread(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	tracker;
	int			i;

	if (pthread_create(&tracker, NULL, &checker, data->philos) != 0)
		destroy_all("pthread_create error!", data, forks);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			destroy_all("pthread_create error!", data, forks);
		i++;
	}
	if (pthread_join(tracker, NULL) != 0)
		destroy_all("pthread_join error!", data, forks);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_all("pthread_join error!", data, forks);
		i++;
	}
}
