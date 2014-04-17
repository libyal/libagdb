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
#include "libagdb_libfdata.h"
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

	static char *function = "libagdb_io_handle_read_compressed_file_header";
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
		 "%s: unable to read file header data.",
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
		io_handle->file_type = LIBFWNT_FILE_TYPE_COMPRESSED_VISTA;
	}
	else if( memory_compare(
	          file_header_data,
	          agdb_mem_file_signature_win7,
	          4 ) == 0 )
	{
		io_handle->file_type = LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7;
	}
	else if( memory_compare(
	          file_header_data,
	          agdb_mam_file_signature_win8,
	          4 ) == 0 )
	{
		io_handle->file_type = LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8;
	}
	else
	{
		io_handle->file_type = LIBFWNT_FILE_TYPE_UNCOMPRESSED;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( io_handle->file_type == LIBFWNT_FILE_TYPE_COMPRESSED_VISTA )
		 || ( io_handle->file_type == LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 ) )
		{
			libcnotify_printf(
			 "%s: signature\t\t: %c%c%c%c\n",
			 function,
			 file_header_data[ 0 ],
			 file_header_data[ 1 ],
			 file_header_data[ 2 ],
			 file_header_data[ 3 ] );
		}
		else if( io_handle->file_type == LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8 )
		{
			libcnotify_printf(
			 "%s: signature\t\t: %c%c%c\\x%02x\n",
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
		byte_stream_copy_to_uint32_little_endian(
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
				 "%s: invalid uncompressed data size.",
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
			 io_handle->uncompressed_data_size );
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

	static char *function            = "libagdb_io_handle_read_compressed_blocks";
	off64_t file_offset              = 0;
	ssize_t read_count               = 0;
	uint32_t compressed_block_size   = 0;
	uint32_t uncompressed_data_size  = 0;
	uint32_t uncompressed_block_size = 0;
	int element_index                = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	int compressed_block_index       = 0;
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
	 && ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS7 )
	 && ( io_handle->file_type != LIBFWNT_FILE_TYPE_COMPRESSED_WINDOWS8 ) )
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
	uncompressed_data_size = io_handle->uncompressed_data_size;

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

		byte_stream_copy_to_uint32_little_endian(
		 compressed_block_data,
		 compressed_block_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: compressed block: %d size\t: %" PRIu32 "\n",
			 function,
			 compressed_block_index,
			 compressed_block_size );
		}
#endif
		uncompressed_block_size = 65536;

		if( uncompressed_block_size > uncompressed_data_size )
		{
			uncompressed_block_size = uncompressed_data_size;
		}
		if( libfdata_list_append_element_with_mapped_size(
		     compressed_blocks_list,
		     &element_index,
		     0,
		     file_offset,
		     (size64_t) compressed_block_size,
		     LIBFDATA_RANGE_FLAG_IS_COMPRESSED,
		     uncompressed_block_size,
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
		file_offset            += compressed_block_size;
		uncompressed_data_size -= uncompressed_block_size;

#if defined( HAVE_DEBUG_OUTPUT )
		compressed_block_index++;
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( (size64_t) file_offset < io_handle->file_size )
		{
			libcnotify_printf(
			 "%s: trailing data size\t: %" PRIu64 "\n",
			 function,
			 io_handle->file_size - (size64_t) file_offset );
		}
	}
#endif
	return( 1 );
}

/* Reads the uncompressed file header
 * Returns 1 if successful or -1 on error
 */
int libagdb_io_handle_read_uncompressed_file_header(
     libagdb_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     off64_t *volumes_information_offset,
     uint32_t *number_of_volumes,
     libcerror_error_t **error )
{
	agdb_file_header_t file_header_data;

	static char *function           = "libagdb_io_handle_read_uncompressed_file_header";
	size64_t data_stream_size       = 0;
	ssize_t read_count              = 0;
	uint32_t alignment_padding_size = 0;
	uint32_t data_size              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit            = 0;
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
	if( volumes_information_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volumes information offset.",
		 function );

		return( -1 );
	}
	if( libfdata_stream_get_size(
	     uncompressed_data_stream,
	     &data_stream_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve uncompressed data stream size.",
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
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
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
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              (uint8_t *) &file_header_data,
	              sizeof( agdb_file_header_t ),
	              0,
	              error );

	if( read_count != (ssize_t) sizeof( agdb_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to readfile header data.",
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
		 (uint8_t *) &file_header_data,
		 sizeof( agdb_file_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.data_size,
	 data_size );

/* TODO improve detection */
	if( data_stream_size != (size64_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.header_size,
	 *volumes_information_offset );

	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.database_type,
	 io_handle->database_type );

	byte_stream_copy_to_uint32_little_endian(
	 &( file_header_data.database_parameters[ 0 ] ),
	 io_handle->volume_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( file_header_data.database_parameters[ 4 ] ),
	 io_handle->file_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.number_of_volumes,
	 *number_of_volumes );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		libcnotify_printf(
		 "%s: header size\t\t: %" PRIi64 "\n",
		 function,
		 *volumes_information_offset );

		libcnotify_printf(
		 "%s: database type\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->database_type );

		libcnotify_printf(
		 "%s: database parameters:\t: ",
		 function );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 0 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 4 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 8 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 12 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 16 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 20 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 24 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 28 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( file_header_data.database_parameters[ 32 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 "\n",
		 value_32bit );

		libcnotify_printf(
		 "%s: number of volumes\t: %" PRIu32 "\n",
		 function,
		 *number_of_volumes );

		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.number_of_files,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of files\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.number_of_executables,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of executables\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header_data.unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	alignment_padding_size = (size_t) ( *volumes_information_offset % 8 );

	if( alignment_padding_size != 0 )
	{
		alignment_padding_size = 8 - alignment_padding_size;
/* Read and print the alignment padding
 */
		*volumes_information_offset += alignment_padding_size;
	}

#ifdef TODO
/* TODO testing */
uint8_t buffer[ 512 ];
size_t read_size = 0;
data_size -= 512;
while( data_size > 0 )
{
	read_size = 512;

	if( read_size > data_size )
	{
		read_size = data_size;
	}

	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              buffer,
	              read_size,
	              0,
	              error );

	if( read_count == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to readfile header data.",
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
		 buffer,
		 read_size,
		 0 );
	}
#endif
	data_size -= read_count;
}
#endif /* TODO */
	return( 1 );
}

