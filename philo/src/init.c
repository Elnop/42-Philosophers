/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:10:34 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/31 07:49:00 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	init_philos_and_forks(t_app *app)
{
	long	i;

	i = 0;
	while (i < app->philo_count)
	{
		app->philo_list[i].my_index = i;
		app->philo_list[i].app = app;
		app->philo_list[i].meal_count = 0;
		app->philo_list[i].last_meal = 0;
		pthread_mutex_init(&(app->philo_list[i].fork_mutex), NULL);
		pthread_mutex_init(&(app->philo_list[i].last_meal_mutex), NULL);
		i++;
	}
}

bool	init_app(t_app *app, int argc, char const *argv[])
{
	app->philo_count = lp_atol(argv[1]);
	if (app->philo_count > MAX_PHILOS)
	{
		printf("ERROR: number of philo greater than %d\n", MAX_PHILOS);
		return (false);
	}
	if (app->philo_count < 1)
		return (false);
	app->time_to_die = lp_atol(argv[2]);
	app->time_to_eat = lp_atol(argv[3]);
	app->time_to_sleep = lp_atol(argv[4]);
	if (argc == 6)
		app->max_meal = lp_atol(argv[5]);
	else
		app->max_meal = -1;
	app->is_finish = false;
	pthread_mutex_init(&(app->is_finish_mutex), NULL);
	pthread_mutex_init(&(app->write_mutex), NULL);
	pthread_mutex_init(&app->total_satiated_mutex, NULL);
	app->total_satiated = 0;
	init_philos_and_forks(app);
	return (true);
}
