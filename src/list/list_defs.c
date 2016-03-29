/**
 * Copyright (c) 2016, Codrin-Victor Poienaru <cvpoienaru@gmail.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * This software is provided by the copyright holders and contributors "as is"
 * and any express or implied warranties, including, but not limited to, the
 * implied warranties of merchantability and fitness for a particular purpose
 * are disclaimed. In no event shall the copyright holder or contributors be
 * liable for any direct, indirect, incidental, special, exemplary, or
 * consequential damages (including, but not limited to, procurement of
 * substitute goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether in
 * contract, strict liability, or tort (including negligence or otherwise)
 * arising in any way out of the use of this software, even if advised of the
 * possibility of such damage.
 */

#include <list/list_defs.h>
#include <defs.h>

struct eds_linked_list_node* alloc_eds_linked_list_node(void)
{
	struct eds_linked_list_node *node = NULL;

	node = (struct eds_linked_list_node*)malloc(
		sizeof(struct eds_linked_list_node));
	if(!node)
		return node;

	node->next = NULL;
	node->prev = NULL;
	node->data = NULL;

	return node;
}

void free_eds_linked_list_node(
	struct eds_linked_list_node **node,
	const free_eds_data free_function)
{
	if(!node || !(*node))
		return;

	if(free_function)
		free_function(&(*node)->data);

	free(*node);
	*node = NULL;
}

struct eds_linked_list* alloc_eds_linked_list(void)
{
	struct eds_linked_list *list = NULL;

	list = (struct eds_linked_list*)malloc(sizeof(struct eds_linked_list));
	if(!list)
		return list;

	list->start = NULL;
	list->end = NULL;

	return list;
}

void free_eds_linked_list(
	struct eds_linked_list **list,
	const free_eds_data free_function)
{
	struct eds_linked_list_node *crt = NULL;
	struct eds_linked_list_node *tmp = NULL;

	if(!list || !(*list))
		return;

	if((*list)->start && (*list)->end) {
		crt = (*list)->start;
		while(crt != (*list)->end) {
			tmp = crt;
			crt = crt->next;
			free_eds_linked_list_node(&tmp, free_function);
		}

		free_eds_linked_list_node(&crt, free_function);
	}

	free(*list);
	*list = NULL;
}

struct eds_array_list* alloc_eds_array_list(const int initial_size)
{
	int status = EDS_FAILURE;
	struct eds_array_list *list = NULL;

	if(initial_size < 0)
		goto exit;

	list = (struct eds_array_list*)malloc(sizeof(struct eds_array_list));
	if(!list)
		goto exit;

	list->data = (void**)malloc(initial_size * sizeof(void*));
	if(!list->data)
		goto exit;

	status = EDS_SUCCESS;

exit:
	if(status == EDS_FAILURE)
		free_eds_array_list(&list, initial_size, NULL);
	return list;
}

void free_eds_array_list(
	struct eds_array_list **list,
	const int size,
	const free_eds_data free_function)
{
	int i;

	if(!list || !(*list))
		return;

	if((*list)->data) {
		if(free_function) {
			for(i = 0; i < size; ++i) {
				if((*list)->data[i])
					free_function((*list)->data[i]);
			}
		}

		free((*list)->data);
	}

	free(*list);
	*list = NULL;
}
