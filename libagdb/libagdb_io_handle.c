/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2014, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libagdb_debug.h"
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_stream_descriptor.h"
#include "libagdb_unused.h"

#include "agdb_file_header.h"

const char *agdb_mem_file_signature_vista = "MEMO";
const char *agdb_mem_file_signature_win7  = "MEM0";
const char *agdb_mam_file_signature_win8  = "MAM\x87";

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_initialize(
     libagdb_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libagdb_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libagdb_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libagdb_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees a IO handle
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_free(
     libagdb_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libagdb_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_clear(
     libagdb_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libagdb_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libagdb_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the compressed file header
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_read_compressed_file_header(
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t file_header_data[ 8 ];

	static char *function = "libagdb_io_handle_read_file_header";
	ssize_t read_count    = 0;

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
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( io_handle->file_size ),
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
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              file_header_data,
	              8,
	              error );

	if( read_count != (ssize_t) 8 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read signature data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header data:\n",
		 function );
		libcnotify_print_data(
		 file_header_data,
		 8,
		 0 );
	}
#endif
	if( memory_compare(
	     file_header_data,
	     agdb_mem_file_signature_vista,
	     4 ) == 0 )
	{
		io_handle->file_handle = LIBFWNT_FILE_TYPE_COMPRESSED_VISTA;
	}
	else if( memory_compare(
	          file_header_data,
	          agdb_mem_file_signature_win7,
	          4 ) == 0 )
	{
		io_handle->file_handle = LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7;
	}
	else if( memory_compare(
	          file_header_data,
	          agdb_mam_file_signature_win8,
	          4 ) == 0 )
	{
		io_handle->file_handle = LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8;
	}
	else
	{
		io_handle->file_handle = LIBFWNT_FILE_TYPE_UNCOMPRESSED;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( io_handle->file_handle == LIBFWNT_FILE_TYPE_COMPRESSED_VISTA )
		 || ( io_handle->file_handle == LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
		{
			libcnotify_printf(
			 "%s: signature\t\t\t\t: %c%c%c%c\n",
			 function,
			 file_header_data[ 0 ],
			 file_header_data[ 1 ],
			 file_header_data[ 2 ],
			 file_header_data[ 3 ] );
		}
		else if( io_handle->file_handle == LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8 )
		{
			libcnotify_printf(
			 "%s: signature\t\t\t\t: %c%c%c\x%02x\n",
			 function,
			 file_header_data[ 0 ],
			 file_header_data[ 1 ],
			 file_header_data[ 2 ],
			 file_header_data[ 3 ] );
		}
	}
#endif
	if( ( io_handle->file_type == LIBFWNT_FILE_TYPE_UNCOMPRESSED )
	 || ( io_handle->file_type == LIBFWNT_FILE_TYPE_COMPRESSED_VISTA )
	 || ( io_handle->file_type == LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
	{
		byte_stream_copy_to_uint16_little_endian(
		 &( file_header_data[ 4 ] ),
		 io_handle->uncompressed_data_size );

		if( io_handle->file_type == LIBFWNT_FILE_TYPE_UNCOMPRESSED )
		{
/* TODO improve detection */
			if( io_handle->file_size != (size64_t) io_handle->uncompressed_data_size )
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
			 "%s: uncompressed data size\t\t: %" PRIu32 "\n",
			 function,
			 uncompressed_data_size->encompressed_data_size );
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

/* Reads the compressed blocks
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_read_compressed_blocks(
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_t *compressed_blocks_list,
     libcerror_error_t **error )
{
	uint8_t compressed_block_data[ 4 ];

	static char *function          = "libagdb_io_handle_read_compressed_blocks";
	off64_t file_offset            = 0;
	ssize_t read_count             = 0;
	uint32_t compressed_block_size = 0;
	int element_index              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	int compressed_block_index     = 0;
#endif

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
	if( ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_VISTA )
	 || ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 )
	 || ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_VISTA )
	 || ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
	{
		file_offset = 8;
	}
	else if( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8 )
	{
		file_offset = 4;
	}
	while( (size64_t) file_offset < io_handle->file_size )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: reading compressed data block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
			 function,
			 file_offset,
			 file_offset );
		}
#endif
		if( libbfio_handle_seek_offset(
		     file_io_handle,
		     file_offset,
		     SEEK_SET,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek file header offset: %" PRIi64 ".",
			 function,
			 file_offset );

			return( -1 );
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              compressed_block_data,
		              4,
		              error );

		if( read_count != (ssize_t) 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed block data.",
			 function );

			return( -1 );
		}
		file_offset += 4;

		byte_stream_copy_to_uint16_little_endian(
		 compressed_block_data,
		 compressed_block_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compressed block: %d size\t\t: %" PRIu32 "\n",
			 function,
			 compressed_block_index,
			 compressed_block_size );
		}
#endif
		if( libfdata_list_append_element(
		     records_list,
		     &element_index,
		     0,
		     file_offset,
		     (size64_t) compressed_block_size,
		     0,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append compressed block: %d to list.",
			 function,
			 compressed_block_index );

			return( -1 );
		}
		file_offset += compressed_block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		compressed_block_index++;
#endif
	}
	return( 1 );
}

