/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:10:34 by lperroti          #+#    #+#             */
/*   Updated: 2023/05/24 02:57:04 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	init_philos_and_forks(t_app *app)
{
	long	i;

	app->philo_list = (t_philo *)malloc(app->philo_count * sizeof(bool));
	if (app->philo_list)
		return (false);
	i = 0;
	while (i < app->philo_count)
	{
		app->philo_list[i].my_index = i;
		pthread_mutex_init(&app->philo_list[i].fork_mutex, NULL);
	}
	return (true);
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
	pthread_mutex_init(&app->is_finish_mutex, NULL);
	app->is_finish = false;
	pthread_mutex_init(&app->write_mutex, NULL);
	if (!init_philos_and_forks(app))
		return (false);
	return (true);
}
