/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milhan <milhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 01:15:51 by milhan            #+#    #+#             */
/*   Updated: 2023/01/23 01:15:54 by milhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_with_new_line(int fd, char *all_first_left_last)
{
	int		read_bytes;
	char	*buff;

	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_find_new_line(all_first_left_last))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (0 == read_bytes)
			break ;
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		all_first_left_last = ft_strjoin(all_first_left_last, buff);
	}
	free(buff);
	return (all_first_left_last);
}

char	*ft_until_new_line(char *all_first_left_last)
{
	int		i;
	char	*arr;

	i = 0;
	while (!(all_first_left_last[i] == '\n' || all_first_left_last[i] == '\0'))
		i++;
	if (all_first_left_last[i] == '\n')
		arr = (malloc(sizeof(char) * (i + 2)));
	if (all_first_left_last[i] == '\0')
		arr = (malloc(sizeof(char) * (i + 1)));
	if (!arr)
		return (NULL);
	i = 0;
	while (all_first_left_last[i] != '\n' && all_first_left_last[i] != '\0')
	{
		arr[i] = all_first_left_last[i];
		i++;
	}
	if (all_first_left_last[i] == '\n')
		arr[i++] = '\n';
	arr[i] = '\0';
	return (arr);
}

char	*ft_left(char	*all_first_left_last)
{
	int		i;
	int		j;
	int		len;
	char	*arr;

	i = 0;
	j = 0;
	len = ft_strlen(all_first_left_last) + 1;
	while (all_first_left_last[i] != '\n' && all_first_left_last[i] != '\0')
		i++;
	if (all_first_left_last[i] == '\0')
	{
		free(all_first_left_last);
		return (NULL);
	}
	arr = malloc(sizeof(char) * (len - i));
	i++;
	if (!arr)
		return (NULL);
	while (all_first_left_last[i] != '\0')
		arr[j++] = all_first_left_last[i++];
	arr[j] = '\0';
	free(all_first_left_last);
	return (arr);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*all_first_left_last;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	all_first_left_last = ft_with_new_line(fd, all_first_left_last);
	if (all_first_left_last == NULL)
		return (NULL);
	line = ft_until_new_line(all_first_left_last);
	all_first_left_last = ft_left(all_first_left_last);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// int main(void)
// {
// 	int file = open("text.txt", O_RDONLY);
// 	char *line = get_next_line(file);
// 	char *line2 = get_next_line(file);
// 	printf("%s", line);
// 	printf("%s", line2);
// 	free(line);
// 	close(file);
// 	free(line2);
// 	return(0);
// }
