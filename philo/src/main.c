/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:37:01 by lperroti          #+#    #+#             */
/*   Updated: 2023/06/29 00:03:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	start_philos(t_app *app)
{
	long	i;

	i = 0;
	pthread_mutex_init(&(app->start_mutex), NULL);
	pthread_mutex_lock(&(app->start_mutex));
	while (i < app->philo_count)
	{
		if (
			pthread_create(
				&app->philo_list[i].thread, NULL, philo_routine,
				app->philo_list + i)
		)
			return (false);
		i++;
	}
	app->start_timestamp = lp_get_timestamp();
	pthread_mutex_unlock(&(app->start_mutex));
	return (true);
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
	if (!init_app(&app, argc, argv) || !app.philo_count)
	{
		printf("Error\n");
		return (0);
	}
	if (!start_philos(&app))
	{
		printf("WOOOOH TOO MUCH THREADS !!!!!!\n");
		return (0);
	}
	while_check_philos(&app);
	join_philos(&app);
	destroy_all(&app);
	return (0);
}
