/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:01 by lperroti          #+#    #+#             */
/*   Updated: 2023/08/01 01:41:46 by lperroti         ###   ########.fr       */
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

	if (!check_args(argc, argv) || !init_app(&app, argc, argv))
	{
		printf("Philosophers\n./philo number_of_philosophers" \
			"time_to_die time_to_eat time_to_sleep" \
			"[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	if (app.philo_count == 1)
	{
		printf("0 1 has taken a fork\n%ld 1 died\n", app.time_to_die);
		return (0);
	}
	if (app.time_to_die < MS_ARGS_MIN || app.time_to_eat < MS_ARGS_MIN
		|| app.time_to_sleep < MS_ARGS_MIN)
	{
		printf("ERROR: no simulation with times below to %dms\n", MS_ARGS_MIN);
		return (0);
	}
	start_philos(&app);
	check_death_while(&app);
	join_philos(&app);
	destroy_app(&app);
	return (0);
}
