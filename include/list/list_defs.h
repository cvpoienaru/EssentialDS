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

#ifndef EDS_LIST_DEFS_H_
#define EDS_LIST_DEFS_H_

#include <defs.h>

#define EDS_NO_LIST_TYPE 0
#define EDS_LINKED_LIST_TYPE 1
#define EDS_ARRAY_LIST_TYPE 2

struct eds_list_base {
	int items_used;
	int items_allocated;
};

struct eds_linked_list_node {
	struct eds_linked_list_node *prev;
	struct eds_linked_list_node *next;
	void *data;
};

struct eds_linked_list {
	struct eds_list_base *base;
	struct eds_linked_list_node *start;
	struct eds_linked_list_node *end;
};

struct eds_array_list {
	struct eds_list_base *base;
	void **data;
};

union eds_list_container {
	struct eds_linked_list *linked_list;
	struct eds_array_list *array_list;
};

struct eds_list_base* eds_alloc_list_base(void);
void eds_free_list_base(struct eds_list_base **base);

struct eds_linked_list_node* eds_alloc_linked_list_node(void);
void eds_free_linked_list_node(
	struct eds_linked_list_node **node,
	const eds_free_data free_function);

struct eds_linked_list* eds_alloc_linked_list(void);
void eds_free_linked_list(
	struct eds_linked_list **list,
	const eds_free_data free_function);

struct eds_array_list* eds_alloc_array_list(const int initial_size);
void eds_free_array_list(
	struct eds_array_list **list,
	const int items_allocated,
	const eds_free_data free_function);

union eds_list_container* eds_alloc_list_container(void);
void eds_free_list_container(
	union eds_list_container **container,
	const int list_type,
	const eds_free_data free_function);

const int eds_is_list_type_valid(const int type);

#endif /* EDS_LIST_DEFS_H_ */
