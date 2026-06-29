/*
 * Database header functions
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
#include "libagdb_definitions.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"

#include "agdb_database_header.h"

/* Creates a database header
 * Make sure the value database_header is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_database_header_initialize(
     libagdb_database_header_t **database_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_database_header_initialize";

	if( database_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid database header.",
		 function );

		return( -1 );
	}
	if( *database_header != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid database header value already set.",
		 function );

		return( -1 );
	}
	*database_header = memory_allocate_structure(
	                    libagdb_database_header_t );

	if( *database_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create database header.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *database_header,
	     0,
	     sizeof( libagdb_database_header_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear database header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *database_header != NULL )
	{
		memory_free(
		 *database_header );

		*database_header = NULL;
	}
	return( -1 );
}

/* Frees a database header
 * Returns 1 if successful or -1 on error
 */
int libagdb_database_header_free(
     libagdb_database_header_t **database_header,
     libcerror_error_t **error )
{
	static char *function = "libagdb_database_header_free";

	if( database_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid database header.",
		 function );

		return( -1 );
	}
	if( *database_header != NULL )
	{
		memory_free(
		 *database_header );

		*database_header = NULL;
	}
	return( 1 );
}

/* Reads the database header
 * Returns 1 if successful or -1 on error
 */
int libagdb_database_header_read_stream(
     libagdb_database_header_t *database_header,
     libagdb_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     size_t data_size,
     libcerror_error_t **error )
{
	uint8_t *data         = NULL;
	static char *function = "libagdb_database_header_read_stream";
	ssize_t read_count    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
#endif

	if( database_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid database header.",
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
	if( ( data_size < 60 )
	 || ( data_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid database header size value out of bounds.",
		 function );

		goto on_error;
	}
	data = (uint8_t *) memory_allocate(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              data,
	              data_size,
	              0,
	              error );

	if( read_count != (ssize_t) data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data.",
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
	         data,
	         data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) data )->database_type,
	 io_handle->database_type );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) data )->database_parameters[ 0 ] ),
	 io_handle->volume_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) data )->database_parameters[ 4 ] ),
	 io_handle->file_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) data )->database_parameters[ 8 ] ),
	 io_handle->source_information_entry_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) data )->database_parameters[ 12 ] ),
	 io_handle->file_information_sub_entry_type1_size );

	byte_stream_copy_to_uint32_little_endian(
	 &( ( (agdb_database_header_t *) data )->database_parameters[ 16 ] ),
	 io_handle->file_information_sub_entry_type2_size );

	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) data )->number_of_volumes,
	 database_header->number_of_volumes );

	byte_stream_copy_to_uint32_little_endian(
	 ( (agdb_database_header_t *) data )->number_of_sources,
	 database_header->number_of_sources );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: database type\t\t\t: %" PRIu32 "\n",
		 function,
		 io_handle->database_type );

		libcnotify_printf(
		 "%s: database parameters\t\t: ",
		 function );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 0 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 4 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 8 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 12 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 16 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 20 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 24 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 28 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 ", ",
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 &( ( (agdb_database_header_t *) data )->database_parameters[ 32 ] ),
		 value_32bit );
		libcnotify_printf(
		 "%" PRIu32 "\n",
		 value_32bit );

		libcnotify_printf(
		 "%s: number of volumes\t\t\t: %" PRIu32 "\n",
		 function,
		 database_header->number_of_volumes );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) data )->number_of_files,
		 value_32bit );
		libcnotify_printf(
		 "%s: number of files\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: number of sources\t\t\t: %" PRIu32 "\n",
		 function,
		 database_header->number_of_sources );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_database_header_t *) data )->unknown5,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( ( data_size == 116 )
		 || ( data_size == 228 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown6,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown7,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown8,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown9,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown9\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown10,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown10\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown11,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown11\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown12,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown12\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown13,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown14,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown14\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown15,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown15\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( data_size == 116 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown16\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown17,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown17\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown18,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown18\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( data_size == 228 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_database_header_116_t *) data )->unknown16,
			 value_32bit );
			libcnotify_printf(
			 "%s: number of time values\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: time values data:\n",
			 function );
			libcnotify_print_data(
		         ( (agdb_database_header_228_t *) data )->unknown17,
		         120,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	memory_free(
	 data );

	data = NULL;

	return( 1 );

on_error:
	if( data != NULL )
	{
		memory_free(
		 data );
	}
	return( -1 );
}

