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

#ifndef EDS_DEFS_LIST_H_
#define EDS_DEFS_LIST_H_

typedef (*free_eds_data)(void **data);

struct eds_linked_list_node {
	struct eds_linked_list_node *prev;
	struct eds_linked_list_node *next;
	void *data;
};

struct eds_linked_list {
	struct eds_linked_list_node *start;
	struct eds_linked_list_node *end;
};

struct eds_array_list {
	void **data;
};

union eds_list_container {
	struct eds_linked_list *linked_list;
	struct eds_array_list *array_list;
};

struct eds_linked_list_node* alloc_eds_linked_list_node(void);
void free_eds_linked_list_node(
	struct eds_linked_list_node **node,
	const free_eds_data free_function);

struct eds_linked_list* alloc_eds_linked_list(void);
void free_eds_linked_list(
	struct eds_linked_list **list,
	const free_eds_data free_function);

struct eds_array_list* alloc_eds_array_list(const int initial_size);
void free_eds_array_list(
	struct eds_array_list **list,
	const int size,
	const free_eds_data free_function);

#endif /* EDS_DEFS_LIST_H_ */
