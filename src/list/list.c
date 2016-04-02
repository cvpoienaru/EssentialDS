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

#include <list/list.h>
#include <defs.h>
#include <list/array_list.h>
#include <list/linked_list.h>
#include <list/list_defs.h>

#include <stdlib.h>

struct eds_list* eds_alloc_list(const int type)
{
	int status = EDS_FAILURE;
	struct eds_list *list = NULL;

	if(!eds_is_list_type_valid(type))
		goto exit;

	list = (struct eds_list*)malloc(sizeof(struct eds_list));
	if(!list)
		goto exit;

	list->container = eds_alloc_list_container();
	if(!list->container)
		goto exit;

	switch(type) {
		case EDS_LINKED_LIST_TYPE:
			list->container->linked_list = eds_alloc_linked_list();
			if(!list->container->linked_list)
				goto exit;
			break;

		case EDS_ARRAY_LIST_TYPE:
			list->container->array_list = eds_alloc_array_list(
				EDS_LIST_INITIAL_SIZE);
			if(!list->container->array_list)
				goto exit;
			break;
	}

	list->type = type;
	list->free_function = NULL;

	status = EDS_SUCCESS;

exit:
	if(list && status == EDS_FAILURE)
		eds_free_list(&list);
	return list;
}

void eds_free_list(struct eds_list **list)
{
	if(!list || !(*list))
		return;

	if((*list)->container)
		eds_free_list_container(
			&(*list)->container,
			(*list)->type,
			(*list)->free_function);

	free(*list);
	*list = NULL;
}
