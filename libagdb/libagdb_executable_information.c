/*
 * Executable information functions
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

#include "libagdb_definitions.h"
#include "libagdb_executable_information.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_libfdata.h"
#include "libagdb_libuna.h"

#include "agdb_executable_information.h"

/* Creates executable information
 * Make sure the value executable_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_executable_information_initialize(
     libagdb_executable_information_t **executable_information,
     libcerror_error_t **error )
{
	libagdb_internal_executable_information_t *internal_executable_information = NULL;
	static char *function                                                      = "libagdb_executable_information_initialize";

	if( executable_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable information.",
		 function );

		return( -1 );
	}
	if( *executable_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid executable information value already set.",
		 function );

		return( -1 );
	}
	internal_executable_information = memory_allocate_structure(
	                                   libagdb_internal_executable_information_t );

	if( internal_executable_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create executable information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_executable_information,
	     0,
	     sizeof( libagdb_internal_executable_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear executable.",
		 function );

		goto on_error;
	}
	*executable_information = (libagdb_executable_information_t *) internal_executable_information;

	return( 1 );

on_error:
	if( internal_executable_information != NULL )
	{
		memory_free(
		 internal_executable_information );
	}
	return( -1 );
}

/* Frees executable information
 * Returns 1 if successful or -1 on error
 */
int libagdb_executable_information_free(
     libagdb_executable_information_t **executable_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_executable_information_free";

	if( executable_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable information.",
		 function );

		return( -1 );
	}
	if( *executable_information != NULL )
	{
		*executable_information = NULL;
	}
	return( 1 );
}

/* Frees executable information
 * Returns 1 if successful or -1 on error
 */
int libagdb_internal_executable_information_free(
     libagdb_internal_executable_information_t **executable_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_executable_information_free";

	if( executable_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable information.",
		 function );

		return( -1 );
	}
	if( *executable_information != NULL )
	{
		if( ( *executable_information )->filename != NULL )
		{
			memory_free(
			 ( *executable_information )->filename );
		}
		memory_free(
		 *executable_information );

		*executable_information = NULL;
	}
	return( 1 );
}

/* Reads the executable information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t libagdb_executable_information_read(
         libagdb_executable_information_t *executable_information,
         libfdata_stream_t *uncompressed_data_stream,
         libbfio_handle_t *file_io_handle,
         libagdb_io_handle_t *io_handle,
         off64_t file_offset,
         uint32_t executable_index,
         libcerror_error_t **error )
{
	libagdb_internal_executable_information_t *internal_executable_information = NULL;
	uint8_t *executable_information_data                                       = NULL;
	static char *function                                                      = "libagdb_executable_information_read";
	ssize_t read_count                                                         = 0;
	ssize_t total_read_count                                                   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t *value_string                                = NULL;
	size_t value_string_size                                                   = 0;
	uint32_t value_32bit                                                       = 0;
	int result                                                                 = 0;
#endif

	if( executable_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid executable information.",
		 function );

		return( -1 );
	}
	internal_executable_information = (libagdb_internal_executable_information_t *) executable_information;

	if( internal_executable_information->filename != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid executable information - filename value already set.",
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
#if SIZEOF_SIZE_T <= 4
	if( (size_t) io_handle->executable_information_entry_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - executable information entry size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading executable: %" PRIu32 " information at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 executable_index,
		 file_offset,
		 file_offset );
	}
#endif
	if( libfdata_stream_seek_offset(
	     uncompressed_data_stream,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek executable: %" PRIu32 " information offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 executable_index,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	executable_information_data = (uint8_t *) memory_allocate(
	                                           sizeof( uint8_t ) * io_handle->executable_information_entry_size );

	if( executable_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create executable information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              executable_information_data,
	              (size_t) io_handle->executable_information_entry_size,
	              0,
	              error );

	if( read_count != (ssize_t) io_handle->executable_information_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read executable: %" PRIu32 " information data.",
		 function,
		 executable_index );

		goto on_error;
	}
	total_read_count += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: executable: %" PRIu32 " information data:\n",
		 function,
		 executable_index );
		libcnotify_print_data(
		 executable_information_data,
		 (size_t) io_handle->executable_information_entry_size,
		 0 );
	}
#endif
	if( io_handle->executable_information_entry_size != 100 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported executable information entry size: %" PRIu32 ".",
		 function,
		 io_handle->executable_information_entry_size );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown1,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown4,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown5:\n",
		 function );
		libcnotify_print_data(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown5,
		 12,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown6,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown7,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown8,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown8\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown9,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: unknown10:\n",
		 function );
		libcnotify_print_data(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown10,
		 16,
		 0 );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown11,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown11\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown12,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown12\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown13,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown13\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown14,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown14\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown15,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown15\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown16,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown16\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown17,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown17\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown18,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown18\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown19,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown19\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_executable_information_100_t *) executable_information_data )->unknown20,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown20\t\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	memory_free(
	 executable_information_data );

	executable_information_data = NULL;

	return( total_read_count );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	if( internal_executable_information->filename != NULL )
	{
		memory_free(
		 internal_executable_information->filename );

		internal_executable_information->filename = NULL;
	}
	internal_executable_information->filename_size = 0;

	if( executable_information_data != NULL )
	{
		memory_free(
		 executable_information_data );
	}
	return( -1 );
}

