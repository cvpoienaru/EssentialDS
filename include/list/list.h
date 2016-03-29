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

#ifndef EDS_LIST_H_
#define EDS_LIST_H_

#include <list/list_defs.h>
#include <defs.h>

#define EDS_INITIAL_SIZE 0

#define EDS_NO_LIST_TYPE 0
#define EDS_LINKED_LIST_TYPE 1
#define EDS_ARRAY_LIST_TYPE 2

struct eds_list {
	int type;
	int items_used;
	int items_allocated;
	free_eds_data free_function;
	union eds_list_container *container;
};

const int is_eds_list_type_valid(const int type);

struct eds_list* alloc_eds_list(const int type);
void free_eds_list(struct eds_list **list);

#endif /* EDS_LIST_H_ */
