/*
** options.c for  in /home/mart_4/rendu/PSU_2015_myftp/src/parsing
**
** Made by Thomas Martins
** Login   <mart_4@epitech.net>
**
** Started on  Sun May 15 11:16:52 2016 Thomas Martins
** Last update Sun May 15 11:18:38 2016 Thomas Martins
*/

#include "../struct.h"

int		(*get_matchs(const char *find, t_list
			     *list))(t_cmd *, t_server *)
{
  t_list	*tmp;

  tmp = list;
  while (tmp->next != list)
    {
      if ((strcmp(find, tmp->next->name)) == 0)
	{
	  return (tmp->next->func);
	}
      tmp = tmp->next;
    }
  return (NULL);
}

int		init_value(t_val *val)
{
  val->i = 0;
  val->b = 0;
  val->a = 0;
  return (0);
}
