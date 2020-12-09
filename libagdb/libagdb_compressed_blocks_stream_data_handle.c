/*
 * The compressed blocks stream data handle functions
 *
 * Copyright (C) 2014-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libagdb_compressed_block.h"
#include "libagdb_compressed_blocks_stream_data_handle.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfdata.h"
#include "libagdb_unused.h"

/* Creates a data handle
 * Make sure the value data_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_blocks_stream_data_handle_initialize(
     libagdb_compressed_blocks_stream_data_handle_t **data_handle,
     libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_blocks_stream_data_handle_initialize";

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( *data_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data handle value already set.",
		 function );

		return( -1 );
	}
	*data_handle = memory_allocate_structure(
	                libagdb_compressed_blocks_stream_data_handle_t );

	if( *data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_handle,
	     0,
	     sizeof( libagdb_compressed_blocks_stream_data_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data handle.",
		 function );

		memory_free(
		 *data_handle );

		*data_handle = NULL;

		return( -1 );
	}
	return( 1 );

on_error:
	if( *data_handle != NULL )
	{
		memory_free(
		 *data_handle );

		*data_handle = NULL;
	}
	return( -1 );
}

/* Frees a data handle
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_blocks_stream_data_handle_free(
     libagdb_compressed_blocks_stream_data_handle_t **data_handle,
     libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_blocks_stream_data_handle_free";
	int result            = 1;

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( *data_handle != NULL )
	{
		/* The compressed_blocks_list and compressed_blocks_cache values are referenced and freed elsewhere
		 */
		memory_free(
		 *data_handle );

		*data_handle = NULL;
	}
	return( result );
}

/* Reads data from the current offset into a buffer
 * Callback for the compressed block stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libagdb_compressed_blocks_stream_data_handle_read_segment_data(
         libagdb_compressed_blocks_stream_data_handle_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBAGDB_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBAGDB_ATTRIBUTE_UNUSED,
         uint8_t read_flags,
         libcerror_error_t **error )
{
	libagdb_compressed_block_t *compressed_block = NULL;
	static char *function                        = "libagdb_compressed_blocks_stream_data_handle_read_segment_data";
	off64_t segment_data_offset                  = 0;
	ssize_t read_count                           = 0;

	LIBAGDB_UNREFERENCED_PARAMETER( segment_file_index )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_flags )

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( segment_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid segment data.",
		 function );

		return( -1 );
	}
	if( segment_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid segment data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_element_value_at_offset(
	     data_handle->compressed_blocks_list,
	     (intptr_t *) file_io_handle,
	     (libfdata_cache_t *) data_handle->compressed_blocks_cache,
	     data_handle->current_offset,
	     &segment_index,
	     &segment_data_offset,
	     (intptr_t **) &compressed_block,
	     read_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve compressed block: %d from list.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( compressed_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing compressed block: %d.",
		 function,
		 segment_index );

		return( -1 );
	}
	if( ( segment_data_offset < 0 )
	 || ( segment_data_offset >= (off64_t) compressed_block->data_size ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid segment data offset value out of bounds.",
		 function );

		return( -1 );
	}
	if( (off64_t) ( segment_data_offset + segment_data_size ) > (off64_t) compressed_block->data_size )
	{
		read_count = (ssize_t) ( compressed_block->data_size - segment_data_offset );
	}
	else
	{
		read_count = (ssize_t) segment_data_size;
	}
	if( memory_copy(
	     segment_data,
	     &( compressed_block->data[ segment_data_offset ] ),
	     (size_t) read_count ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy compressed block data.",
		 function );

		return( -1 );
	}
	data_handle->current_offset += read_count;

	return( read_count );
}

/* Seeks a certain offset of the data
 * Callback for the compressed block stream
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libagdb_compressed_blocks_stream_data_handle_seek_segment_offset(
         libagdb_compressed_blocks_stream_data_handle_t *data_handle,
         intptr_t *file_io_handle LIBAGDB_ATTRIBUTE_UNUSED,
         int segment_index LIBAGDB_ATTRIBUTE_UNUSED,
         int segment_file_index LIBAGDB_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_blocks_stream_data_handle_seek_segment_offset";

	LIBAGDB_UNREFERENCED_PARAMETER( file_io_handle )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_index )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_file_index )

	if( data_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data handle.",
		 function );

		return( -1 );
	}
	if( segment_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment offset value out of bounds.",
		 function );

		return( -1 );
	}
	data_handle->current_offset = segment_offset;

	return( segment_offset );
}

