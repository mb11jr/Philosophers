/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:34:12 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/09 23:06:54 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_msg(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time_in_ms() - philo->start_time;
	if (!check_dead_flag(philo))
		printf("%zu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	dead_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_in_ms() - philo->last_meal >= philo->time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	death_state(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (dead_philo(&philo[i]))
		{
			print_state_msg(philo, "died");
			pthread_mutex_lock(philo[0].dead_lock);
			*philo[i].dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	everyone_ate(t_philo *philo)
{
	int	i;
	int	done_eating;

	i = 0;
	done_eating = 0;
	if (philo[0].meals_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].meals_to_eat)
			done_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (done_eating == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*checker(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (death_state(philo) || everyone_ate(philo))
			break ;
	}
	return (ptr);
}
