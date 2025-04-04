/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:15:57 by tstephan          #+#    #+#             */
/*   Updated: 2025/02/07 14:31:00 by tstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

t_bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long long	ft_atoll(const char *s)
{
	long long	nbr;
	int			mult;

	nbr = 0;
	while (ft_isspace(*s))
		s++;
	mult = 1;
	if (*s == '-')
	{
		mult = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		nbr *= 10;
		nbr += *s - '0';
		s++;
	}
	return (nbr * mult);
}

int	ft_atoi(const char *s)
{
	int	nbr;
	int	mult;

	nbr = 0;
	while (ft_isspace(*s))
		s++;
	mult = 1;
	if (*s == '-')
	{
		mult = -1;
		s++;
	}
	while (ft_isdigit(*s))
	{
		nbr *= 10;
		nbr += *s - '0';
		s++;
	}
	return (nbr * mult);
}
