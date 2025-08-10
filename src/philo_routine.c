/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 19:12:53 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/09 23:52:33 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	thinking(t_philo *philo)
{
	print_state_msg(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_state_msg(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state_msg(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_state_msg(philo, "has taken a fork");
	philo->eating = 1;
	print_state_msg(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!check_dead_flag(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ptr);
}
