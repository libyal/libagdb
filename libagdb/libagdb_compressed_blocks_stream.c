/*
 * The compressed blocks stream functions
 *
 * Copyright (C) 2014-2025, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#include "libagdb_compressed_blocks_stream.h"
#include "libagdb_compressed_blocks_stream_data_handle.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"

/* Creates a compressed block stream
 * Make sure the value compressed_blocks_stream is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_blocks_stream_initialize(
     libfdata_stream_t **compressed_blocks_stream,
     libfdata_list_t *compressed_blocks_list,
     libfcache_cache_t *compressed_blocks_cache,
     libcerror_error_t **error )
{
	libagdb_compressed_blocks_stream_data_handle_t *data_handle = NULL;
	static char *function                                       = "libagdb_compressed_blocks_stream_initialize";
	off64_t segment_offset                                      = 0;
	size64_t segment_size                                       = 0;
	int element_index                                           = 0;
	int number_of_elements                                      = 0;
	int segment_index                                           = 0;

	if( compressed_blocks_stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed block stream.",
		 function );

		return( -1 );
	}
	if( compressed_blocks_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed blocks list.",
		 function );

		return( -1 );
	}
	if( libagdb_compressed_blocks_stream_data_handle_initialize(
	     &data_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data handle.",
		 function );

		goto on_error;
	}
	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing data handle.",
		 function );

		goto on_error;
	}
	data_handle->compressed_blocks_list  = compressed_blocks_list;
	data_handle->compressed_blocks_cache = compressed_blocks_cache;

	if( libfdata_stream_initialize(
	     compressed_blocks_stream,
	     (intptr_t *) data_handle,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libagdb_compressed_blocks_stream_data_handle_free,
	     NULL,
	     NULL,
	     (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &libagdb_compressed_blocks_stream_data_handle_read_segment_data,
	     NULL,
	     (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &libagdb_compressed_blocks_stream_data_handle_seek_segment_offset,
	     LIBFDATA_DATA_HANDLE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create stream.",
		 function );

		goto on_error;
	}
	if( libfdata_list_get_number_of_elements(
	     compressed_blocks_list,
	     &number_of_elements,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of compressed blocks list elements.",
		 function );

		data_handle = NULL;

		goto on_error;
	}
	for( element_index = 0;
	     element_index < number_of_elements;
	     element_index++ )
	{
		if( libfdata_list_get_mapped_size_by_index(
		     compressed_blocks_list,
		     element_index,
		     &segment_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve compressed blocks list element: %d mapped size.",
			 function,
			 element_index );

			data_handle = NULL;

			goto on_error;
		}
		if( libfdata_stream_append_segment(
		     *compressed_blocks_stream,
		     &segment_index,
		     0,
		     segment_offset,
		     segment_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append compressed blocks stream segment: %d.",
			 function,
			 element_index );

			data_handle = NULL;

			goto on_error;
		}
		segment_offset += segment_size;
	}
	return( 1 );

on_error:
	if( *compressed_blocks_stream != NULL )
	{
		libfdata_stream_free(
		 compressed_blocks_stream,
		 NULL );
	}
	if( data_handle != NULL )
	{
		libagdb_compressed_blocks_stream_data_handle_free(
		 &data_handle,
		 NULL );
	}
	return( -1 );
}

