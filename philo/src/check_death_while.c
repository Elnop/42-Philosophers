#include "../includes/philo.h"

bool	philo_is_starving(t_philo *philo)
{
	if (is_finish(philo))
		return (true);
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (lp_get_timestamp() - philo->last_meal >= philo->app->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		change_status(philo, DIED);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (false);
}

bool	is_finish(t_philo *philo)
{
	bool	out;

	pthread_mutex_lock(&(philo->app->is_finish_mutex));
	out = philo->app->is_finish;
	pthread_mutex_unlock(&(philo->app->is_finish_mutex));
	return (out);
}

void    check_death_while(t_app *app)
{
	int		i;

	usleep(10000);
    while (true)
    {
		usleep(1000);
		i = 0;
        while (i < app->philo_count)
		{
			if (philo_is_starving(app->philo_list + i))
				return ;
			i++;
		}
    }
}