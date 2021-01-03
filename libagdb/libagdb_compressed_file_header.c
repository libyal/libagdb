/*
 * Compressed file header functions
 *
 * Copyright (C) 2014-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libagdb_compressed_file_header.h"
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"

/* Creates compressed file header
 * Make sure the value compressed_file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_file_header_initialize(
     libagdb_compressed_file_header_t **compressed_file_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_file_header_initialize";

	if( compressed_file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed file header.",
		 function );

		return( -1 );
	}
	if( *compressed_file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed file header value already set.",
		 function );

		return( -1 );
	}
	*compressed_file_header = memory_allocate_structure(
	                           libagdb_compressed_file_header_t );

	if( *compressed_file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *compressed_file_header,
	     0,
	     sizeof( libagdb_compressed_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *compressed_file_header != NULL )
	{
		memory_free(
		 *compressed_file_header );

		*compressed_file_header = NULL;
	}
	return( -1 );
}

/* Frees compressed file header
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_file_header_free(
     libagdb_compressed_file_header_t **compressed_file_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_file_header_free";

	if( compressed_file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed file header.",
		 function );

		return( -1 );
	}
	if( *compressed_file_header != NULL )
	{
		memory_free(
		 *compressed_file_header );

		*compressed_file_header = NULL;
	}
	return( 1 );
}

/* Reads the compressed file header data
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_file_header_read_data(
     libagdb_compressed_file_header_t *compressed_file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libagdb_compressed_file_header_read_data";
	uint32_t value_32bit  = 0;

	if( compressed_file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed file header.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < 8 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compressed file header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 8,
		 0 );
	}
#endif
	if( memory_compare(
	     data,
	     agdb_mem_file_signature_vista,
	     4 ) == 0 )
	{
		compressed_file_header->file_type               = LIBAGDB_FILE_TYPE_COMPRESSED_VISTA;
		compressed_file_header->uncompressed_block_size = 4096;
	}
	else if( memory_compare(
	          data,
	          agdb_mem_file_signature_win7,
	          4 ) == 0 )
	{
		compressed_file_header->file_type               = LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7;
		compressed_file_header->uncompressed_block_size = 65536;
	}
	else if( memory_compare(
	          data,
	          agdb_mam_file_signature_win8,
	          4 ) == 0 )
	{
		compressed_file_header->file_type               = LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8;
		compressed_file_header->uncompressed_block_size = 65536;
	}
	else
	{
		compressed_file_header->file_type = LIBAGDB_FILE_TYPE_UNCOMPRESSED;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
		 || ( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
		{
			libcnotify_printf(
			 "%s: signature\t\t\t: %c%c%c%c\n",
			 function,
			 data[ 0 ],
			 data[ 1 ],
			 data[ 2 ],
			 data[ 3 ] );
		}
		else if( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8 )
		{
			libcnotify_printf(
			 "%s: signature\t\t\t: %c%c%c\\x%02x\n",
			 function,
			 data[ 0 ],
			 data[ 1 ],
			 data[ 2 ],
			 data[ 3 ] );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( ( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_UNCOMPRESSED )
	 || ( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
	 || ( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 &( data[ 0 ] ),
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( data[ 4 ] ),
		 compressed_file_header->uncompressed_data_size );

		if( compressed_file_header->file_type == LIBAGDB_FILE_TYPE_UNCOMPRESSED )
		{
/* TODO improve detection */
			if( ( ( value_32bit != 0x00000005UL )
			  &&  ( value_32bit != 0x0000000eUL )
			  &&  ( value_32bit != 0x0000000fUL ) )
			 || ( compressed_file_header->file_size != (size64_t) compressed_file_header->uncompressed_data_size ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: invalid signature.",
				 function );

				return( -1 );
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: uncompressed data size\t: %" PRIu32 "\n",
			 function,
			 compressed_file_header->uncompressed_data_size );
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads the compressed file header data
 * Returns 1 if successful or -1 on error
 */
int libagdb_compressed_file_header_read_file_io_handle(
     libagdb_compressed_file_header_t *compressed_file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t compressed_file_header_data[ 8 ];

	static char *function = "libagdb_compressed_file_header_read_file_io_handle";
	ssize_t read_count    = 0;

	if( compressed_file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed file header.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( compressed_file_header->file_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              compressed_file_header_data,
	              8,
	              0,
	              error );

	if( read_count != (ssize_t) 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed file header data at offset: 0 (0x00000000).",
		 function );

		return( -1 );
	}
/* TODO pass file_size as an argument ? */
	if( libagdb_compressed_file_header_read_data(
	     compressed_file_header,
	     compressed_file_header_data,
	     8,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed file header.",
		 function );

		return( -1 );
	}
	return( 1 );
}

