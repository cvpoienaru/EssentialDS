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

#ifndef EDS_LINKED_LIST_H_
#define EDS_LINKED_LIST_H_

#include <list/list_defs.h>

#define EDS_ADD_BEFORE_LIST_MODE 0
#define EDS_ADD_AFTER_LIST_MODE 1

const int eds_add_before_linked_list(
	struct eds_linked_list *list,
	struct eds_linked_list_node *node,
	void *data);
const int eds_add_after_linked_list(
	struct eds_linked_list *list,
	struct eds_linked_list_node *node,
	void *data);
const int eds_add_first_linked_list(
	struct eds_linked_list *list,
	void *data);
const int eds_add_last_linked_list(
	struct eds_linked_list *list,
	void  *data);

#endif /* EDS_LINKED_LIST_H_ */
