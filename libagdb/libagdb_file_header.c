/*
 * File header functions
 *
 * Copyright (C) 2014-2026, Joachim Metz <joachim.metz@gmail.com>
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

#include "libagdb_database_header.h"
#include "libagdb_file_header.h"
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"

#include "agdb_file_header.h"

/* Creates a file header
 * Make sure the value file_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_header_initialize(
     libagdb_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_file_header_initialize";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file header value already set.",
		 function );

		return( -1 );
	}
	*file_header = memory_allocate_structure(
	                libagdb_file_header_t );

	if( *file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_header,
	     0,
	     sizeof( libagdb_file_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( -1 );
}

/* Frees a file header
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_header_free(
     libagdb_file_header_t **file_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_file_header_free";

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		memory_free(
		 *file_header );

		*file_header = NULL;
	}
	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_header_read_stream(
     libagdb_file_header_t *file_header,
     libagdb_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ sizeof( agdb_file_header_t ) ];

	libagdb_database_header_t *database_header = NULL;
	static char *function                      = "libagdb_file_header_read_stream";
	size_t database_header_size                = 0;
	ssize_t read_count                         = 0;
	uint32_t data_size                         = 0;
	int result                                 = 0;

	if( file_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file header.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	read_count = libfdata_stream_read_buffer_at_offset(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              file_header_data,
	              sizeof( agdb_file_header_t ),
	              0,
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( agdb_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header data offset: 0 (0x00000000).",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header data:\n",
		 function );
		libcnotify_print_data(
		 file_header_data,
		 sizeof( agdb_file_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_file_header_t *) file_header_data )->data_size,
	 data_size );

/* TODO improve detection */
	if( io_handle->uncompressed_data_size != (size64_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: uncompressed data size mismatch.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_file_header_t *) file_header_data )->signature,
	 file_header->signature );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->signature );
	}
#endif
	if( io_handle->file_type == LIBAGDB_FILE_TYPE_UNCOMPRESSED )
	{
		if( ( file_header->signature == 0x00000005UL )
		 || ( file_header->signature == 0x0000000eUL )
		 || ( file_header->signature == 0x0000000fUL ) )
		{
			result = 1;
		}
	}
	else if( ( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
	      || ( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
	{
		if( file_header->signature == 0x0000000eUL )
		{
			result = 1;
		}
	}
	else if( ( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8_0 )
	      || ( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8_1 ) )
	{
		if( file_header->signature == 0x00000003UL )
		{
			result = 1;
		}
	}
	if( result == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported signature.",
		 function );

		goto on_error;
	}
	if( ( file_header->signature == 0x00000003UL )
	 || ( file_header->signature == 0x0000000eUL )
	 || ( file_header->signature == 0x0000000fUL ) )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_header_t *) file_header_data )->header_size,
		 file_header->size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 data_size );

			libcnotify_printf(
			 "%s: header size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 file_header->size );

			libcnotify_printf(
			 "\n" );
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

		if( (size_t) file_header->size < sizeof( agdb_file_header_t ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid file header size value out of bounds.",
			 function );

			goto on_error;
		}
		database_header_size = (size_t) file_header->size - sizeof( agdb_file_header_t );

		if( libagdb_database_header_initialize(
		     &database_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create database header.",
			 function );

			goto on_error;
		}
		if( libagdb_database_header_read_stream(
		     database_header,
		     io_handle,
		     uncompressed_data_stream,
		     file_io_handle,
		     database_header_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read database header.",
			 function );

			goto on_error;
		}
		file_header->number_of_volumes = database_header->number_of_volumes;
		file_header->number_of_sources = database_header->number_of_sources;

		if( libagdb_database_header_free(
		     &database_header,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free database header.",
			 function );

			goto on_error;
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );

on_error:
	if( database_header != NULL )
	{
		libagdb_database_header_free(
		 &database_header,
		 NULL );
	}
	return( -1 );
}

