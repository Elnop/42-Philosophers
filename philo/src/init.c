/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:10:34 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/29 00:24:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_philos_and_forks(t_app *app)
{
	long	i;

	app->philo_list = (t_philo *)malloc(app->philo_count * sizeof(t_philo));
	if (!app->philo_list)
		return (false);
	i = 0;
	while (i < app->philo_count)
	{
		app->philo_list[i].my_index = i;
		app->philo_list[i].app = app;
		app->philo_list[i].meal_count = 0;
		pthread_mutex_init(&(app->philo_list[i].fork_mutex), NULL);
		pthread_mutex_init(&(app->philo_list[i].meal_count_mutex), NULL);
		i++;
	}
	return (true);
}

long long	lp_atol(const char *nptr)
{
	long long	num;
	long long	sign;

	num = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	return (num * sign);
}

bool	init_app(t_app *app, int argc, char const *argv[])
{
	app->philo_count = lp_atol(argv[1]);
	app->time_to_die = lp_atol(argv[2]);
	app->time_to_eat = lp_atol(argv[3]);
	app->time_to_sleep = lp_atol(argv[4]);
	if (argc == 6)
		app->max_meal = lp_atol(argv[5]);
	else
		app->max_meal = -1;
	pthread_mutex_init(&(app->is_finish_mutex), NULL);
	app->is_finish = false;
	pthread_mutex_init(&(app->write_mutex), NULL);
	if (!init_philos_and_forks(app))
		return (false);
	return (true);
}
