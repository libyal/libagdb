/*
 * Input/Output (IO) handle functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libagdb_debug.h"
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"
#include "libagdb_unused.h"

#include "agdb_file_header.h"

const char *agdb_mem_file_signature_vista = "MEMO";
const char *agdb_mem_file_signature_win7  = "MEM0";
const char *agdb_mam_file_signature_win8  = "MAM\x84";

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
	size_t read_size                 = 0;
	ssize_t read_count               = 0;
	uint32_t compressed_block_size   = 0;
	uint32_t uncompressed_data_size  = 0;
	uint32_t uncompressed_block_size = 0;
	int compressed_block_index       = 0;
	int element_index                = 0;

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
	if( ( io_handle->file_type != LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
	 && ( io_handle->file_type != LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 )
	 && ( io_handle->file_type != LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
	{
		file_offset = 8;
		read_size   = 2;
	}
	else if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 )
	{
		file_offset = 8;
		read_size   = 4;
	}
	else if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8 )
	{
/* TODO implement */
		file_offset = 4;
		read_size   = 4;
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
			 "%s: unable to seek compressed data block offset: %" PRIi64 ".",
			 function,
			 file_offset );

			return( -1 );
		}
		read_count = libbfio_handle_read_buffer(
		              file_io_handle,
		              compressed_block_data,
		              read_size,
		              error );

		if( read_count != (ssize_t) read_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read compressed block data.",
			 function );

			return( -1 );
		}
		if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_VISTA )
		{
			byte_stream_copy_to_uint16_little_endian(
			 compressed_block_data,
			 compressed_block_size );

			compressed_block_size &= 0x0fff;
			compressed_block_size += 3;
		}
		else if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 compressed_block_data,
			 compressed_block_size );

			file_offset += 4;
		}
		else if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8 )
		{
/* TODO implement read the block and determine the range */
		}
		if( uncompressed_data_size < io_handle->uncompressed_block_size )
		{
			uncompressed_block_size = uncompressed_data_size;
		}
		else
		{
			uncompressed_block_size = io_handle->uncompressed_block_size;
		}
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
		if( compressed_block_size == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid compressed block size value out of bounds.",
			 function );

			return( -1 );
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

		compressed_block_index++;
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
     uint32_t *number_of_sources,
     libcerror_error_t **error )
{
	agdb_file_header_t file_header_data;

	uint8_t *database_header_data = NULL;
	static char *function         = "libagdb_io_handle_read_uncompressed_file_header";
	size64_t data_stream_size     = 0;
	size_t database_header_size   = 0;
	ssize_t read_count            = 0;
	uint32_t data_size            = 0;
	uint32_t header_size          = 0;
	uint32_t unknown1             = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit          = 0;
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
	if( number_of_volumes == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of volumes.",
		 function );

		return( -1 );
	}
	if( number_of_sources == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sources.",
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

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading uncompressed file header at offset: 0 (0x00000000)\n",
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

		goto on_error;
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
		 "%s: unable to read file header data.",
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

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.unknown1,
	 unknown1 );

	if( unknown1 != 0x0000000eUL )
	{
/* TODO add support for AgAppLaunch.db unknown1: 5 */
		return( 1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.header_size,
	 header_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unknown1\t\t: %" PRIu32 "\n",
		 function,
		 unknown1 );

		libcnotify_printf(
		 "%s: data size\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		libcnotify_printf(
		 "%s: header size\t\t: %" PRIi64 "\n",
		 function,
		 header_size );

		libcnotify_printf(
		 "\n" );
	}
#endif
	if( (size_t) header_size < sizeof( agdb_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid header size value out of bounds.",
		 function );

		goto on_error;
	}
	database_header_size = (size_t) header_size - sizeof( agdb_file_header_t );

	if( ( database_header_size < 60 )
	 || ( database_header_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid database header size value out of bounds.",
		 function );

		goto on_error;
	}
	database_header_data = (uint8_t *) memory_allocate(
	                                    sizeof( uint8_t ) * database_header_size );

	if( database_header_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create database header data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              database_header_data,
	              database_header_size,
	              0,
	              error );

	if( read_count != (ssize_t) database_header_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read database header data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: database header data:\n",
		 function );
		libcnotify_print_data(
	         database_header_data,
	         database_header_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) database_header_data )->database_type,
	 io_handle->database_type );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 0 ] ),
	 io_handle->volume_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 4 ] ),
	 io_handle->file_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 8 ] ),
	 io_handle->source_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 12 ] ),
	 io_handle->file_information_sub_entry_type1_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 16 ] ),
	 io_handle->file_information_sub_entry_type2_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) database_header_data )->number_of_volumes,
	 *number_of_volumes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) database_header_data )->number_of_sources,
	 *number_of_sources );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: database type\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->database_type );

		libcnotify_printf(
		 "%s: database parameters\t: ",
		 function );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 0 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 4 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 8 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 12 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 16 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 20 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 24 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 28 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) database_header_data )->database_parameters[ 32 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 "\n",
		 value_32bit );

		libcnotify_printf(
		 "%s: number of volumes\t: %" PRIu32 "\n",
		 function,
		 *number_of_volumes );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->number_of_files,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of files\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sources\t: %" PRIu32 "\n",
		 function,
		 *number_of_sources );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( database_header_size == 116 )
		 || ( database_header_size == 228 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown6,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown6\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown7,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown8,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown8\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown9,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown9\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown10,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown10\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown11,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown11\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown12,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown12\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown13,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown13\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown14,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown14\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown15,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown15\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( database_header_size == 116 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown16\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown17,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown17\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown18,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown18\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( database_header_size == 228 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: number of time values\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: time values data:\n",
			 function );
			libcnotify_print_data(
		         ( (agdb_database_header_228_t *) database_header_data )->unknown17,
		         120,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	memory_free(
	 database_header_data );

	database_header_data = NULL;

	*volumes_information_offset = header_size;

	return( 1 );

on_error:
	if( database_header_data != NULL )
	{
		memory_free(
		 database_header_data );
	}
	return( -1 );
}

/* Reads data from the current offset into a buffer
 * Callback for the uncompressed block stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t libagdb_io_handle_read_segment_data(
         intptr_t *data_handle LIBAGDB_ATTRIBUTE_UNUSED,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBAGDB_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags LIBAGDB_ATTRIBUTE_UNUSED,
         uint8_t read_flags LIBAGDB_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "libagdb_io_handle_read_segment_data";
	ssize_t read_count    = 0;

	LIBAGDB_UNREFERENCED_PARAMETER( data_handle )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_file_index )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_flags )
	LIBAGDB_UNREFERENCED_PARAMETER( read_flags )

	if( segment_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid segment data size value out of bounds.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              (libbfio_handle_t *) file_io_handle,
	              segment_data,
	              segment_data_size,
	              error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment: %d data.",
		 function,
		 segment_index );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Callback for the uncompressed block stream
 * Returns the offset if seek is successful or -1 on error
 */
off64_t libagdb_io_handle_seek_segment_offset(
         intptr_t *data_handle LIBAGDB_ATTRIBUTE_UNUSED,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index LIBAGDB_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "libagdb_io_handle_seek_segment_offset";

	LIBAGDB_UNREFERENCED_PARAMETER( data_handle )
	LIBAGDB_UNREFERENCED_PARAMETER( segment_file_index )

	if( libbfio_handle_seek_offset(
	     (libbfio_handle_t *) file_io_handle,
	     segment_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek segment: %d offset: %" PRIi64 ".",
		 function,
		 segment_index,
		 segment_offset );

		return( -1 );
	}
	return( segment_offset );
}

