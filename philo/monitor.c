#include "philo.h"

void	*monitor_death_complete(void *arg)
{
	t_philosopher	*philosophers;
	long			current_time;

	philosophers = (t_philosopher *)arg;
	if (!philosophers || !philosophers->sim)
		return (printf("Error: philosophers or sim is NULL\n"), NULL);
	current_time = get_current_timestamp();
	loop_for_monitor(philosophers, current_time);
	return (NULL);
}

void loop_for_monitor(t_philosopher *philo, long current_time)
{
	while (1)
	{
		if (!died_check_and_died(philo, current_time))
			return ;
		if (philo->sim->meal_limit > 0 && completed_check(philo))
			return ;
		usleep(1000);
	}
}

int	died_check_and_died(t_philosopher *philo, long current_time)
{
	size_t 	i;

	i = 0;
	while (i < philo->sim->number_of_philosophers)
	{
		if (current_time - philo[i].last_meal_time > philo->sim->time_to_die)
		{
			philo_died(philo, current_time);
			return (0);
		}
		i++;
	}
	return (1);
}

int	completed_check(t_philosopher *philo)
{
	size_t 	i;

	i = 0;
	if (!philo->sim->meal_limit)
		return (1);
	while (i < philo->sim->number_of_philosophers)
	{
		if (philo[i].meals_eaten < philo->sim->meal_limit)
			return (0);
		i++;
	}
	philo_all_completed(philo);
	return (1);
}
