#include "philo.h"

long	get_current_timestamp()
{
    struct	timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_safe_atoi(char *str)
{
	size_t	i;

	i = 0;
	if (!str || *str == '\0')
		return (printf("Error: Empty or NULL argument\n"), -1);
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return(printf("Error: Non-numeric argument '%s'\n", str), -1);
		i++;
	}
	return (atoi(str));
}