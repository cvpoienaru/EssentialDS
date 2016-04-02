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

#include <list/linked_list.h>
#include <defs.h>
#include <list/list_defs.h>

#include <stdlib.h>

static const int eds_add_general_linked_list(
	struct eds_linked_list *list,
	struct eds_linked_list_node *node,
	void *data,
	const int add_mode)
{
	int ret = EDS_FAILURE;
	struct eds_linked_list_node *crt = NULL;

	crt = eds_alloc_linked_list_node();
	if(!crt)
		goto exit;

	crt->data = data;

	if(!list->start && !list->end) {
		list->start = crt;
		list->end = crt;
		goto first_node_exit;
	}

	switch(add_mode) {
		case EDS_ADD_BEFORE_LIST_MODE:
			if(list->start == node)
				list->start = crt;

			crt->prev = node->prev;
			crt->next = node;
			node->prev = crt;
			if(crt->prev)
				crt->prev->next = crt;
			break;

		case EDS_ADD_AFTER_LIST_MODE:
			if(list->end == node)
				list->end = crt;

			crt->next = node->next;
			crt->prev = node;
			node->next = crt;
			if(crt->next)
				crt->next->prev = crt;
			break;

		default:
			goto exit;
	}

first_node_exit:
	++(list->base->items_allocated);
	list->base->items_used = list->base->items_allocated;

	ret = EDS_SUCCESS;

exit:
	return ret;
}

const int eds_add_before_linked_list(
	struct eds_linked_list *list,
	struct eds_linked_list_node *node,
	void *data)
{
	if(!list)
		return EDS_FAILURE;

	if(!node)
		return EDS_FAILURE;

	return eds_add_general_linked_list(
		list,
		node,
		data,
		EDS_ADD_BEFORE_LIST_MODE);
}

const int eds_add_after_linked_list(
	struct eds_linked_list *list,
	struct eds_linked_list_node *node,
	void *data)
{
	if(!list)
		return EDS_FAILURE;

	if(!node)
		return EDS_FAILURE;

	return eds_add_general_linked_list(
		list,
		node,
		data,
		EDS_ADD_AFTER_LIST_MODE);
}

const int eds_add_first_linked_list(
	struct eds_linked_list *list,
	void *data)
{
	if(!list)
		return EDS_FAILURE;

	return eds_add_before_linked_list(list, list->start, data);
}

const int eds_add_last_linked_list(
	struct eds_linked_list *list,
	void  *data)
{
	return eds_add_after_linked_list(list, list->end, data);
}
