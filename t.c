/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-cha <aben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:20:31 by aben-cha          #+#    #+#             */
/*   Updated: 2024/01/16 19:21:01 by aben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "pipex.h"

int main(int ac, char **av)
{
	char *s = "ls '-l'a'";
	char **res;
	if(ft_check(s, 39))
	{
		printf("h1.\n");
		res = ft_split(s,39);
	}
	else 
	{
		printf("h2.\n");
		res = ft_split(s,' ');

	}
	// while(*res)
	// {
	// 	// if(!(s[i] == 39))
	// 	// // res = strcpy("", &s[i]);
	// 	printf("%s\n", *res);
	// 	res++;	
	// }
	// 	// printf("%s\n", *res);

	int i = 0;
	// char *res;
	while(s[i])
	{
		if((s[i] != 39) && (s[i + 1] != 0) && (s[i + 1] != 39))
			printf("%c", s[i]);
		// // res = strcpy("", &s[i]);
		i++;	
	}
	return (0);
}
//"ls     '-''la' "       == > "ls -la"