/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:01:11 by yanaranj          #+#    #+#             */
/*   Updated: 2023/12/11 15:54:51 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*Libera la memoria asignada en las cadenas.
 * Primero verifica su hay memoria asignada y luego la libera
*/
static char	*ft_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

char	ft_next()
{
}
/* Leera la linea que debe retornar
 * *line: cadena a devolver
 * i: iterador de la cadena
 * si el buffer tiene contenido y es distinto a \n, itera en el buffer
 * Asigna memoria en line.
 * while(): lee el buffer y comprueba si es diferente a '\n'
 * 			sigue leyendo los caracteres del archivo.
 * Asigna memoria en line y verifica en caso de error.
 * while(): lee el buffer y comprueba si es diferente a '\n'
 * 			copia el buffer en line.
 * if(): cuando el buffer sea '\n'
 * 		 se mueve en la pos de line y agrega el '\n' 
*/
char	ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
//	while (buffer[i] && buffer[i] != '\n')
//		i++;
	line = malloc (size(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

/* Leera en el FD y concatena las cadenas en el
 * STRG y devuelve el resultado de la cadena(strg).
 * *buffer: almacena datos leido de manera temp.
 * byte: num de bytes que ira contando. Se inicia en 1 para entrar en
 *		 el bucle
 * malloc: para asignar memoria en el buffer.
 * while(): bucle que busca el caracter '\n' o hasta el final de linea
 * 			primero lee los bytes desde el fd al BS
 * 			Si se leyeron, primero asegura que que no termina en nulo.
 * 			Concatena el buffer a una cadena existente y lo almacena en
 * 			strg. Si falla, return NULL.
 * 			Else (si no ha leido bytes), libera los datos.
 * Al salir del bucle, libera la memoria de buffer despues de leer las lineas
 */
static char	*read_file(int fd, char *strg)
{
	char	*buffer;
	int		bytes;

	byte = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(NULL, strg));
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';//iguala a nulo para que sea una cadena ok
			strg = ft_strjoin(strg, buffer);
			if (!strg)
				return (NULL);
		}
		else if (bytes < 0)
			return (ft_free(strg, buffer));
	}
	free(buffer);
	return (strg);	
}

char	*get_next_line(int fd)
{
	static char	*strg = NULL;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	strg = read_line(fd, strg);
	if (!strg)
		return (NULL);
	line = ft_line(strg);
	strg = ft_next(strg);
	return (line);
}
