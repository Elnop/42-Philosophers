/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/21 04:53:20 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/time.h>
# include <unistd.h>

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
	int				philo_count;
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
	long long			start_timestamp;
	long long			last_meal;
	pthread_mutex_t		last_meal_mutex;
	long long			meal_count;
	enum e_philo_status	status;
	t_app				*app;
}	t_philo;

bool		check_args(int argc, char const *argv[]);
bool		init_app(t_app *app, int argc, char const *argv[]);
void		*philo_routine(void *app);
bool		change_status(t_philo *philo, enum e_philo_status status);
bool		check_all_philo_eat_enough(t_philo *philo);
char		*lp_strchr(char const *s, int c);
char		*lp_strmapi(char const *s, char (*f)(unsigned int, char));
long long	lp_get_timestamp(void);
long long	lp_atol(const char *nptr);
void		philo_wait(t_philo	*philo, long long ms);
bool		philo_is_starving(t_philo *philo);
bool		is_finish(t_philo *philo);
void    	check_death_while(t_app *app);

#endif