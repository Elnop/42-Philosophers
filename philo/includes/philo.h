/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/29 00:22:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>

# define CHECK_PHILOS_USLEEP 5
# define PHILO_WAIT_USLEEP 5

enum e_philo_status {
	TAKING_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_app {
	long long		start_timestamp;
	long			philo_count;
	struct s_philo	*philo_list;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	pthread_mutex_t	is_finish_mutex;
	bool			is_finish;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	start_mutex;
}	t_app;

typedef struct s_philo {
	int					my_index;
	pthread_t			thread;
	pthread_mutex_t		fork_mutex;
	long long			last_meal;
	pthread_mutex_t		meal_count_mutex;
	long long			meal_count;
	enum e_philo_status	status;
	t_app				*app;
}	t_philo;

bool		check_args(int argc, char const *argv[]);
bool		init_app(t_app *app, int argc, char const *argv[]);
void		*philo_routine(void *app);
void		change_status(t_philo *philo, enum e_philo_status status);
bool		check_all_philo_eat_enough(t_philo *philo);
char		*lp_strchr(char const *s, int c);
char		*lp_strmapi(char const *s, char (*f)(unsigned int, char));
long long	lp_get_timestamp(void);
void		destroy_all(t_app *app);
void		while_check_philos(t_app *app);
bool		is_finish(t_app	*app);

#endif