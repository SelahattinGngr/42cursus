/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocCollector.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segungor <segungor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:36:20 by segungor          #+#    #+#             */
/*   Updated: 2024/01/11 16:36:20 by segungor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOCCOLLECTOR_H
# define MALLOCCOLLECTOR_H

# include <stdlib.h>

typedef struct s_mallocCollector
{
	void						*new_malloc;
	struct s_mallocCollector	*next;
}	t_mallocCollector;

t_mallocCollector	*malloc_start(void);
void				*new_malloc(t_mallocCollector *mc, size_t size);
void				delete_malloc(t_mallocCollector *mc, void *ptr_to_delete);
void				end_malloc(t_mallocCollector *mc);

#endif
