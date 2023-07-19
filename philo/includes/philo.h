/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/20 00:53:38 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libs/liblp_c/liblp.h"
# include <pthread.h>

# define PHILO_WAIT_USLEEP 120

enum e_philo_status {
	TAKING_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_app {
	pthread_mutex_t	start_mutex;
	long long		start_timestamp;
	long			philo_count;
	struct s_philo	*philo_list;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	pthread_mutex_t	total_satiated_mutex;
	long long		total_satiated;
	pthread_mutex_t	is_finish_mutex;
	bool			is_finish;
	pthread_mutex_t	write_mutex;
}	t_app;

typedef struct s_philo {
	int					my_index;
	pthread_t			thread;
	pthread_mutex_t		fork_mutex;
	long long			last_meal;
	long long			meal_count;
	enum e_philo_status	status;
	t_app				*app;
}	t_philo;

bool	check_args(int argc, char const *argv[]);
bool	init_app(t_app *app, int argc, char const *argv[]);
void	*philo_routine(void *app);
void	change_status(t_philo *philo, enum e_philo_status status);
bool	is_finish(t_app	*app);
void	philo_wait(t_philo	*philo, long long ms);

#endif