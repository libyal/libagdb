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

#include "libagdb_file_header.h"
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"

#include "agdb_file_header.h"

/* Creates compressed file header
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
		 "%s: invalid compressed file header.",
		 function );

		return( -1 );
	}
	if( *file_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed file header value already set.",
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
		 "%s: unable to create compressed file header.",
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
		 "%s: unable to clear compressed file header.",
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

/* Frees compressed file header
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
		 "%s: invalid compressed file header.",
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
	agdb_file_header_t file_header_data;

	uint8_t *database_header_data = NULL;
	static char *function         = "libagdb_file_header_read_stream";
	size_t database_header_size   = 0;
	ssize_t read_count            = 0;
	uint32_t data_size            = 0;
	uint32_t unknown1             = 0;
	int result                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit          = 0;
#endif

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
	              (uint8_t *) &file_header_data,
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
		 "%s: unable to read file header data offset: %" PRIi64 " (0x%08" PRIx64 ").",
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
	 file_header_data.unknown1,
	 unknown1 );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: %" PRIu32 "\n",
		 function,
		 unknown1 );
	}
#endif
	if( io_handle->file_type == LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8 )
	{
		if( unknown1 == 0x00000003UL )
		{
			result = 1;
		}
	}
	else
	{
		/* TODO add support for:
		 * AgAppLaunch.db unknown1: 5
		 */
		if( ( unknown1 == 0x0000000eUL )
		 || ( unknown1 == 0x0000000fUL ) )
		{
			result = 1;
		}
	}
	if( result == 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "\n" );
		}
#endif
		return( 1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header_data.header_size,
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
#endif
	if( (size_t) file_header->size < sizeof( agdb_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid header size value out of bounds.",
		 function );

		goto on_error;
	}
	database_header_size = (size_t) file_header->size - sizeof( agdb_file_header_t );

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
	 file_header->number_of_volumes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) database_header_data )->number_of_sources,
	 file_header->number_of_sources );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: database type\t\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->database_type );

		libcnotify_printf(
		 "%s: database parameters\t\t\t: ",
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
		 "%s: number of volumes\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_volumes );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->number_of_files,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of files\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sources\t\t\t: %" PRIu32 "\n",
		 function,
		 file_header->number_of_sources );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) database_header_data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( database_header_size == 116 )
		 || ( database_header_size == 228 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown6,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown7,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown8,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown9,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown9\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown10,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown10\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown11,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown11\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown12,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown12\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown13,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown14,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown14\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown15,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown15\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( database_header_size == 116 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown16\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown17,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown17\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown18,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown18\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( database_header_size == 228 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) database_header_data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: number of time values\t\t\t: %" PRIu32 "\n",
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

	return( 1 );

on_error:
	if( database_header_data != NULL )
	{
		memory_free(
		 database_header_data );
	}
	return( -1 );
}

