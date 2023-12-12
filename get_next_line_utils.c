/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:01:28 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/12 17:25:20 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	size1;
	size_t	size2;
	size_t	newsize;
	size_t	i;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	newsize = size1 + size2;
	join = (char *)malloc(sizeof(char) * (newsize + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (i < newsize)
	{
		if (i < size1)
			join[i] = s1[i];
		else
			join[i] = s2[i - size1];
		i++;
	}
	join[i] = '\0';
	return (join);
}

/*			Libera la memoria de las cadenas
 * Verifica si la cadena hay mem asignada, y luego la libera
*/
char	*ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}
