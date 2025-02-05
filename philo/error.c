#include "philo.h"

void	error_sel(int sign)
{
	if (sign == 0)
	{
		printf("Usage: ./philo [num_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] [meal_limit(optional)]\n");
	}
	if (sign == 1)
		printf("Error: Memory allocation failed\n");
}
