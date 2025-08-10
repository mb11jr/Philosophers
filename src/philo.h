/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:56:10 by mbentale          #+#    #+#             */
/*   Updated: 2025/08/10 08:39:56 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				*dead;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			last_meal;
	int				num_of_philos;
	int				meals_to_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	t_philo			*philos;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}					t_data;

// initialization
void				init_data(t_data *data, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philos, t_data *data,
						pthread_mutex_t *forks, char **av);

// thread creation
void				create_thread(t_data *data, pthread_mutex_t *forks);
void				ft_destroy(char *str, t_data *data, pthread_mutex_t *forks);

// philo routine
void				*philo_routine(void *ptr);
void				thinking(t_philo *philo);
void				sleeping(t_philo *philo);
void				eating(t_philo *philo);
int					check_dead_flag(t_philo *philo);

// checker
void				*checker(void *ptr);
int					dead_philo(t_philo *philo);
int					death_state(t_philo *philo);
int					everyone_ate(t_philo *philo);
void				print_state_msg(t_philo *philo, char *str);

// utils
int					ft_atoi(const char *str);
int					ft_strlen(char *str);
int					is_all_numeric(char *str);
int					is_valid_input(int ac, char **av);
size_t				get_time_in_ms(void);
int					ft_usleep(size_t ms);

#endif
