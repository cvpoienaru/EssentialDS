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

#include <stdlib.h>

struct eds_list_base* eds_alloc_list_base(void)
{
	struct eds_list_base *base = NULL;

	base = (struct eds_list_base*)malloc(sizeof(struct eds_list_base));
	if(!base)
		return base;

	base->items_used = 0;
	base->items_allocated = 0;

	return base;
}

void eds_free_list_base(struct eds_list_base **base)
{
	if(!base || !(*base))
		return;

	free(*base);
	*base = NULL;
}

struct eds_linked_list_node* eds_alloc_linked_list_node(void)
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

void eds_free_linked_list_node(
	struct eds_linked_list_node **node,
	const eds_free_data free_function)
{
	if(!node || !(*node))
		return;

	if(free_function && (*node)->data)
		free_function(&(*node)->data);

	free(*node);
	*node = NULL;
}

struct eds_linked_list* eds_alloc_linked_list(void)
{
	int status = EDS_FAILURE;
	struct eds_linked_list *list = NULL;

	list = (struct eds_linked_list*)malloc(sizeof(struct eds_linked_list));
	if(!list)
		goto exit;

	list->base = eds_alloc_list_base();
	if(!list->base)
		goto exit;

	list->start = NULL;
	list->end = NULL;

	status = EDS_SUCCESS;

exit:
	if(list && status == EDS_FAILURE)
		eds_free_linked_list(&list, NULL);
	return list;
}

void eds_free_linked_list(
	struct eds_linked_list **list,
	const eds_free_data free_function)
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
			eds_free_linked_list_node(&tmp, free_function);
		}

		eds_free_linked_list_node(&crt, free_function);
	}

	if((*list)->base)
		eds_free_list_base(&(*list)->base);

	free(*list);
	*list = NULL;
}

struct eds_array_list* eds_alloc_array_list(const int initial_size)
{
	int status = EDS_FAILURE;
	struct eds_array_list *list = NULL;

	if(initial_size < 0)
		goto exit;

	list = (struct eds_array_list*)malloc(sizeof(struct eds_array_list));
	if(!list)
		goto exit;

	list->base = eds_alloc_list_base();
	if(!list->base)
		goto exit;

	list->data = (void**)malloc(initial_size * sizeof(void*));
	if(!list->data)
		goto exit;

	list->base->items_allocated = initial_size;

	status = EDS_SUCCESS;

exit:
	if(list && status == EDS_FAILURE)
		eds_free_array_list(&list, initial_size, NULL);
	return list;
}

void eds_free_array_list(
	struct eds_array_list **list,
	const int items_allocated,
	const eds_free_data free_function)
{
	int i;

	if(!list || !(*list))
		return;

	if((*list)->data) {
		if(free_function) {
			for(i = 0; i < items_allocated; ++i) {
				if((*list)->data[i])
					free_function((*list)->data[i]);
			}
		}

		free((*list)->data);
	}

	if((*list)->base)
		eds_free_list_base(&(*list)->base);

	free(*list);
	*list = NULL;
}

union eds_list_container* eds_alloc_list_container(void)
{
	union eds_list_container *container = NULL;

	container = (union eds_list_container*)malloc(
		sizeof(union eds_list_container));
	if(!container)
		return container;

	container->linked_list = NULL;
	container->array_list = NULL;

	return container;
}

void eds_free_list_container(
	union eds_list_container **container,
	const int list_type,
	const eds_free_data free_function)
{
	if(!container || !(*container))
		return;

	if(!eds_is_list_type_valid(list_type))
		return;

	switch(list_type) {
		case EDS_LINKED_LIST_TYPE:
			if((*container)->linked_list)
				eds_free_linked_list(&(*container)->linked_list, free_function);
			break;

		case EDS_ARRAY_LIST_TYPE:
			if((*container)->array_list)
				eds_free_array_list(
					&(*container)->array_list,
					(*container)->array_list->base->items_allocated,
					free_function);
			break;
	}

	free(*container);
	*container = NULL;
}

const int eds_is_list_type_valid(const int type)
{
	switch(type) {
		case EDS_NO_LIST_TYPE:
		case EDS_LINKED_LIST_TYPE:
		case EDS_ARRAY_LIST_TYPE:
			return TRUE;

		default:
			break;
	}

	return FALSE;
}
