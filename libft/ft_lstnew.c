/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:30:04 by delacourt         #+#    #+#             */
/*   Updated: 2019/10/16 14:44:12 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(void *content)
{
  t_list  *list;
  if (!(list = (t_list *)malloc(sizeof(t_list))))
    return (NULL);
  if (!content)
  {
    list->content = NULL;
    list->next = NULL;
  }
  else
  {
    list->content = content;
    list->next = NULL;
  }
  return (list);
}
