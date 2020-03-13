/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:53:48 by delacourt         #+#    #+#             */
/*   Updated: 2019/10/16 14:58:19 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstadd_back(t_list **alst, t_list *new)
{
  t_list  *temp;

  if (alst && new)
  {
    temp = *alst;
    if (temp)
    {
      while (temp->next)
        temp = temp->next;
      temp->next = new;
      new->next = NULL;
    }
    else
      temp = new;
  }
}
