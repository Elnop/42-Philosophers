#include "../includes/philo.h"

static bool	print_status(t_philo *philo)
{
	if (philo->status == TAKING_A_FORK)
		printf("%lld %d has taken a fork\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == EATING)
		printf("%lld %d is eating\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == SLEEPING)
		printf("%lld %d is sleeping\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == THINKING)
		printf("%lld %d is thinking\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	if (philo->status == DIED)
		printf("%lld %d died\n",
			lp_get_timestamp() - philo->app->start_timestamp,
			philo->my_index + 1);
	return (true);
}

bool	change_status(t_philo *philo, enum e_philo_status status)
{
	if (is_finish(philo))
		return (false);
	pthread_mutex_lock(&philo->app->write_mutex);
	if (is_finish(philo))
	{
		pthread_mutex_unlock(&philo->app->write_mutex);
		return (false);
	}
	philo->status = status;
	if (!print_status(philo))
		return (false);
	if (status == DIED)
	{
		pthread_mutex_lock(&(philo->app->is_finish_mutex));
		philo->app->is_finish = true;
		pthread_mutex_unlock(&(philo->app->is_finish_mutex));
	}
	pthread_mutex_unlock(&philo->app->write_mutex);
	if (status == EATING)
		set_last_meal(philo, lp_get_timestamp());
	return (true);
}
