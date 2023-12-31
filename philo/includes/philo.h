/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:44 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/31 09:07:37 by lperroti         ###   ########.fr       */
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
# define CHECK_DEATH_USLEEP 10
# define MS_ARGS_MIN 60
# ifndef MAX_PHILOS
#  define MAX_PHILOS 200
# endif

enum e_philo_status {
	TAKING_A_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philo {
	int					my_index;
	pthread_t			thread;
	pthread_mutex_t		fork_mutex;
	long long			last_meal;
	pthread_mutex_t		last_meal_mutex;
	long long			meal_count;
	enum e_philo_status	status;
	struct s_app		*app;
}	t_philo;

typedef struct s_app {
	pthread_mutex_t	start_mutex;
	long long		start_timestamp;
	int				philo_count;
	t_philo			philo_list[MAX_PHILOS];
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

void		*philo_routine(void *app);
bool		change_status(t_philo *philo, enum e_philo_status status);
bool		check_args(int argc, char const *argv[]);
bool		init_app(t_app *app, int argc, char const *argv[]);
void		destroy_app(t_app *app);
// ====== UTILS =============== //
void		philo_wait(t_philo	*philo, long long ms);
void		set_last_meal(t_philo *philo, long long ms);
void		set_forks(t_philo *philo, pthread_mutex_t **left_fork,
				pthread_mutex_t **right_fork);
// ====== CHECK DEATH ========= //
bool		is_finish(t_philo *philo);
bool		philo_is_starving(t_philo *philo);
void		check_death_while(t_app *app);
// ====== LIBLP =============== //
char		*lp_strchr(char const *s, int c);
char		*lp_strmapi(char const *s, char (*f)(unsigned int, char));
long long	lp_get_timestamp(void);
long long	lp_atol(const char *nptr);

#endif