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

#include <list/array_list.h>
#include <defs.h>
#include <list/list_defs.h>

#include <stdlib.h>
#include <math.h>

static void eds_shift_right_overwrite_unbounded(
	void **data,
	const int start,
	const int end)
{
	int i;

	if(start == end) {
		data[end + 1] = data[end];
		data[end] = NULL;
		return;
	}

	for(i = end; i > start; --i) {
		data[i] = data[i - 1];
	}

	data[i] = NULL;
}

static void eds_compute_first_null_sequence(
	void **data,
	const int start,
	const int end,
	int *sequence_end,
	int *null_count)
{
	int i;

	*sequence_end = EDS_NO_LIST_INDEX;
	*null_count = 0;

	for(i = start; i < end; ++i) {
		if(data[i] && *null_count == 0)
			continue;

		if(data[i])
			break;

		(*null_count)++;
		*sequence_end = i;
	}
}

static void eds_collapse_left_range(
	void **data,
	const int start,
	const int end,
	int *new_end)
{
	int i;
	int start_index;
	int difference;

	*new_end = EDS_NO_LIST_INDEX;

	eds_compute_first_null_sequence(
		data,
		start,
		end,
		&start_index,
		&difference);
	if(start_index == EDS_NO_LIST_INDEX)
		return;

	for(i = start_index + 1; i < end; ++i) {
		if(!data[i]) {
			++difference;
			continue;
		}

		data[i - difference] = data[i];
	}

	for(i = end - 1; i >= end - difference; --i) {
		data[i] = NULL;
	}

	*new_end = end - difference;
}

const int eds_add_array_list_range(
	struct eds_array_list *list,
	struct eds_list_range_item **items,
	const int items_allocated)
{
	int i;
	int ret = EDS_FAILURE;
	long resize_length = 0;
	void *new_data_array = NULL;

	if(!list)
		goto exit;

	if(!items || !(*items))
		goto exit;

	if(items_allocated < 0)
		goto exit;

	for(i = 0; i < items_allocated; ++i) {
		if(items[i]->index < 0)
			goto exit;
	}

	if(items_allocated > 1) {
		qsort(
			(void**)items,
			items_allocated,
			sizeof(struct eds_list_range_item*),
			eds_compare_list_range_item);
	}

	for(i = items_allocated - 1; i >= 0; --i) {
		if(items[i]->index >= list->base->items_allocated
			|| (list->data[items[i]->index]
				&& list->base->last_item == list->base->items_allocated)) {
			resize_length = (long)pow(2, floor(log2(items[i]->index)) + 1);
			new_data_array = realloc(list->data, resize_length);
			if(!new_data_array)
				goto exit;

			list->data = new_data_array;
			list->base->items_allocated = resize_length;
		}

		if(list->data[items[i]->index]) {
			eds_shift_right_overwrite_unbounded(
				list->data,
				items[i]->index,
				list->base->last_item);

			list->data[items[i]->index] = items[i]->data;
		}

		if(items[i]->index > list->base->last_item)
			list->base->last_item = items[i]->index;
	}

	ret = EDS_SUCCESS;

exit:
	return ret;
}

const int eds_add_array_list_index(
	struct eds_array_list *list,
	const int index,
	void *data)
{
	int ret = EDS_FAILURE;
	struct eds_list_range_item **items = NULL;

	if(!list)
		goto exit;

	if(index < 0)
		goto exit;

	items = (struct eds_list_range_item**)malloc(
		sizeof(struct eds_list_range_item*));
	if(!items)
		goto exit;

	items[0] = eds_alloc_list_range_item(index, data);
	if(!items[0])
		goto exit;

	ret = eds_add_array_list_range(list, items, 1);
	if(ret != EDS_SUCCESS)
		goto exit;

exit:
	if(items) {
		if(items[0])
			eds_free_list_range_item(&items[0], NULL);

		free(items);
	}
	return ret;
}

const int eds_add_first_array_list(
	struct eds_array_list *list,
	void *data)
{
	if(!list)
		return EDS_FAILURE;

	return eds_add_array_list_index(list, 0, data);
}

const int eds_add_last_array_list(
	struct eds_array_list *list,
	void  *data)
{
	int new_end = EDS_NO_LIST_INDEX;

	if(!list)
		return EDS_FAILURE;

	if(list->base->last_item >= list->base->items_allocated - 1
			&& !list->is_compact) {
		eds_collapse_left_range(
			list->data,
			0,
			list->base->last_item,
			&new_end);

		list->base->last_item = new_end;
		list->is_compact = TRUE;
	}

	return eds_add_array_list_index(list, list->base->last_item, data);
}
