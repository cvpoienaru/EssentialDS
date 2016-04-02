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

#include <defs.h>
#include <list/list_defs.h>
#include <list/linked_list.h>
#include <list/array_list.h>
#include <list/list.h>

void free_function(void **data)
{
	struct eds_list_base *base = NULL;

	if(!data || !(*data))
		return;

	base = (struct eds_list_base*)*data;
	eds_free_list_base(&base);
}

int main(int argc, char **argv)
{
	int ret = EDS_FAILURE;

	/* Simple list base and linked list node allocs. */
	struct eds_list_base *base_1 = eds_alloc_list_base();
	if(!base_1)
		goto exit;

	struct eds_linked_list_node *node_1 = eds_alloc_linked_list_node();
	if(!node_1)
		goto exit;

	/* Linked list node with list base data. */
	struct eds_list_base *base_2 = eds_alloc_list_base();
	if(!base_2)
		goto exit;

	struct eds_linked_list_node *node_2 = eds_alloc_linked_list_node();
	if(!node_2)
		goto exit;

	node_2->data = (void*)base_2;

	/* Simple linked list with one list base data. */
	struct eds_list_base *base_3 = eds_alloc_list_base();
	if(!base_3)
		goto exit;

	struct eds_linked_list_node *node_3 = eds_alloc_linked_list_node();
	if(!node_3)
		goto exit;

	node_3->data = (void*)base_3;

	struct eds_linked_list *list_1 = eds_alloc_linked_list();
	if(!list_1)
		goto exit;

	list_1->start = node_3;
	list_1->end = node_3;

	/* Simple linked list with two list base data. */
	struct eds_list_base *base_4 = eds_alloc_list_base();
	if(!base_4)
		goto exit;

	struct eds_list_base *base_5 = eds_alloc_list_base();
	if(!base_5)
		goto exit;

	struct eds_linked_list_node *node_4 = eds_alloc_linked_list_node();
	if(!node_4)
		goto exit;

	struct eds_linked_list_node *node_5 = eds_alloc_linked_list_node();
	if(!node_5)
		goto exit;

	node_4->data = (void*)base_4;
	node_5->data = (void*)base_5;

	struct eds_linked_list *list_2 = eds_alloc_linked_list();
	if(!list_1)
		goto exit;

	list_2->start = node_4;
	list_2->end = node_5;
	node_4->next = node_5;
	node_5->prev = node_4;

	ret = EDS_SUCCESS;

exit:
	if(base_1)
		eds_free_list_base(&base_1);
	if(node_1)
		eds_free_linked_list_node(&node_1, NULL);
	if(node_2)
		eds_free_linked_list_node(&node_2, free_function);
	if(list_1)
		eds_free_linked_list(&list_1, free_function);
	if(list_2)
		eds_free_linked_list(&list_2, free_function);
	return ret;
}