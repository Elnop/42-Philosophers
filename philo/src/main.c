/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:01 by lperroti          #+#    #+#             */
/*   Updated: 2023/07/21 03:02:12 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	start_philos(t_app *app)
{
	long	i;

	i = 0;
	pthread_mutex_init(&app->start_mutex, NULL);
	pthread_mutex_lock(&app->start_mutex);
	while (i < app->philo_count)
	{
		pthread_create(
			&app->philo_list[i].thread, NULL, philo_routine,
			app->philo_list + i);
		i++;
	}
	app->start_timestamp = lp_get_timestamp();
	pthread_mutex_unlock(&app->start_mutex);
}

static void	destroy_forks_mutex(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
		pthread_mutex_destroy(&app->philo_list[i++].fork_mutex);
}

static void	destroy_all(t_app *app)
{
	destroy_forks_mutex(app);
	free(app->philo_list);
	pthread_mutex_destroy(&app->is_finish_mutex);
	pthread_mutex_destroy(&app->write_mutex);
}

static void	join_philos(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->philo_count)
		pthread_join(app->philo_list[i++].thread, NULL);
}

int	main(int argc, char const *argv[])
{
	t_app	app;

	if (!check_args(argc, argv))
	{
		printf("Philosophers\n./philo number_of_philosophers ");
		printf("time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (!init_app(&app, argc, argv) || app.philo_count < 2)
	{
		printf("0 1 died\nERROR: philo 1 died in deep loneliness :/\n");
		return (0);
	}
	if (app.time_to_die < 60 || app.time_to_eat < 60 || app.time_to_sleep < 60)
	{
		printf("ERROR: no simulation with times below to 60ms\n");
		return (0);
	}
	start_philos(&app);
	check_death_while(&app);
	join_philos(&app);
	destroy_all(&app);
	return (0);
}
