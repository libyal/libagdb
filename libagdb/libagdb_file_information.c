/*
 * File information functions
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
#include "libagdb_file_information.h"
#include "libagdb_hash.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"
#include "libagdb_libuna.h"

#include "agdb_file_information.h"

/* Creates file information
 * Make sure the value file_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_initialize(
     libagdb_file_information_t **file_information,
     libcerror_error_t **error )
{
	libagdb_internal_file_information_t *internal_file_information = NULL;
	static char *function                                          = "libagdb_file_information_initialize";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file information value already set.",
		 function );

		return( -1 );
	}
	internal_file_information = memory_allocate_structure(
	                             libagdb_internal_file_information_t );

	if( internal_file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file_information,
	     0,
	     sizeof( libagdb_internal_file_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	*file_information = (libagdb_file_information_t *) internal_file_information;

	return( 1 );

on_error:
	if( internal_file_information != NULL )
	{
		memory_free(
		 internal_file_information );
	}
	return( -1 );
}

/* Frees file information
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_free(
     libagdb_file_information_t **file_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_file_information_free";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *file_information != NULL )
	{
		*file_information = NULL;
	}
	return( 1 );
}

/* Frees file information
 * Returns 1 if successful or -1 on error
 */
int libagdb_internal_file_information_free(
     libagdb_internal_file_information_t **internal_file_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_file_information_free";

	if( internal_file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( *internal_file_information != NULL )
	{
		if( ( *internal_file_information )->path != NULL )
		{
			memory_free(
			 ( *internal_file_information )->path );
		}
		memory_free(
		 *internal_file_information );

		*internal_file_information = NULL;
	}
	return( 1 );
}

/* Reads the file information path data
 * Note that this function is mainly used for the tests
 * Returns the number of bytes read if successful or -1 on error
 */
int libagdb_internal_file_information_read_path_data(
     libagdb_internal_file_information_t *internal_file_information,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function  = "libagdb_internal_file_information_read_path_data";

	if( internal_file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( internal_file_information->path != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file information - path value already set.",
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
	if( ( data_size < internal_file_information->path_size )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file information path data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) internal_file_information->path_size,
		 0 );
	}
#endif
	if( internal_file_information->path_size > 0 )
	{
		if( internal_file_information->path_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid file information - path size value exceeds maximum allocation size.",
			 function );

			goto on_error;
		}
		internal_file_information->path = (uint8_t *) memory_allocate(
		                                               sizeof( uint8_t ) * internal_file_information->path_size );

		if( internal_file_information->path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     internal_file_information->path,
		     data,
		     sizeof( uint8_t ) * internal_file_information->path_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy path.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( internal_file_information->path != NULL )
	{
		memory_free(
		 internal_file_information->path );

		internal_file_information->path = NULL;
	}
	internal_file_information->path_size = 0;

	return( -1 );
}

/* Reads the file information
 * Returns the number of bytes read if successful or -1 on error
 */
int libagdb_internal_file_information_read_data(
     libagdb_internal_file_information_t *internal_file_information,
     libagdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_file_information_read_data";
	uint32_t flags        = 0;
	uint8_t mode          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( internal_file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
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
	if( data_size < io_handle->file_information_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file information data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) io_handle->file_information_entry_size,
		 0 );
	}
#endif
	if( ( io_handle->file_information_entry_size == 36 )
	 || ( io_handle->file_information_entry_size == 52 )
	 || ( io_handle->file_information_entry_size == 56 )
	 || ( io_handle->file_information_entry_size == 72 ) )
	{
		mode = 32;
	}
	else if( ( io_handle->file_information_entry_size == 64 )
	      || ( io_handle->file_information_entry_size == 88 )
	      || ( io_handle->file_information_entry_size == 112 ) )
	{
		mode = 64;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file information entry size: %" PRIu32 ".",
		 function,
		 io_handle->file_information_entry_size );

		return( -1 );
	}
	if( mode == 32 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_36_t *) data )->number_of_entries,
		 internal_file_information->number_of_entries );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_36_t *) data )->flags,
		 flags );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_36_t *) data )->path_number_of_characters,
		 internal_file_information->path_size );
	}
	else if( mode == 64 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_64_t *) data )->number_of_entries,
		 internal_file_information->number_of_entries );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_64_t *) data )->flags,
		 flags );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_file_information_64_t *) data )->path_number_of_characters,
		 internal_file_information->path_size );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_36_t *) data )->unknown1,
			 value_64bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_64_t *) data )->unknown1,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_36_t *) data )->name_hash,
			 value_64bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_64_t *) data )->name_hash,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: name hash\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: number of entries\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_file_information->number_of_entries );

		libcnotify_printf(
		 "%s: flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 flags );

		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_36_t *) data )->unknown4a,
			 value_64bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_64_t *) data )->unknown4a,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown4a\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->file_information_entry_size == 52 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown4b,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown4b\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown4c,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown4c\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
		}
		else if( io_handle->file_information_entry_size == 88 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown4b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown4b\t\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown4c,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown4c\t\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_36_t *) data )->unknown4b,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_64_t *) data )->unknown4b,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown4b\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		if( io_handle->file_information_entry_size == 52 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown5a,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown5a\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown5b,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown5b\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
		}
		else if( ( io_handle->file_information_entry_size == 64 )
		      || ( io_handle->file_information_entry_size == 88 ) )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_64_t *) data )->unknown5a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5a\t\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_64_t *) data )->unknown5b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown5b\t\t\t\t: 0x%04" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_36_t *) data )->unknown5,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_112_t *) data )->unknown5,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown5\t\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: path number of characters\t\t: 0x%08" PRIx32 " (number of characters: %" PRIu32 ", lower bits: 0x%02" PRIx32 ")\n",
		 function,
		 internal_file_information->path_size,
		 internal_file_information->path_size >> 2,
		 internal_file_information->path_size & 0x00000001UL );

		if( mode == 64 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_64_t *) data )->unknown6,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( io_handle->file_information_entry_size <= 52 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_36_t *) data )->unknown7,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( io_handle->file_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown7a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown7b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown7b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( io_handle->file_information_entry_size >= 56 )
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_56_t *) data )->unknown7,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_88_t *) data )->unknown7,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		if( io_handle->file_information_entry_size == 52 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown8,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown9,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown9\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown10,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown10\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown11,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown11\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown12,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown12\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_52_t *) data )->unknown13,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( io_handle->file_information_entry_size == 88 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown8a,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown8a\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown8b,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown8b\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown8c,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown8c\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );

			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown8d,
			 value_16bit );
			libcnotify_printf(
			 "%s: unknown8d\t\t\t\t: 0x%04" PRIx16 "\n",
			 function,
			 value_16bit );
		}
		else if( ( io_handle->file_information_entry_size == 56 )
		      || ( io_handle->file_information_entry_size >= 72 ) )
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_56_t *) data )->unknown8a,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_72_t *) data )->unknown8a,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown8a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_56_t *) data )->unknown8b,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_file_information_72_t *) data )->unknown8b,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown8b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( ( io_handle->file_information_entry_size == 56 )
		 || ( io_handle->file_information_entry_size >= 88 ) )
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_56_t *) data )->file_reference,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_file_information_88_t *) data )->unknown9,
				 value_64bit );
			}
			if( value_64bit == 0 )
			{
				libcnotify_printf(
				 "%s: file reference\t\t\t\t: %" PRIu64 "\n",
				 function,
				 value_64bit );
			}
			else
			{
				libcnotify_printf(
				 "%s: file reference\t\t\t\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
				 function,
				 value_64bit & 0xffffffffffffUL,
				 value_64bit >> 48 );
			}
		}
		if( io_handle->file_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown9a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown9a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown9b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown9b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown10a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown10a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown10b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown10b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown11a,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown11a\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_file_information_72_t *) data )->unknown11b,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown11b\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		else if( io_handle->file_information_entry_size >= 88 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_88_t *) data )->unknown10,
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown10\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		if( io_handle->file_information_entry_size == 112 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_112_t *) data )->unknown11,
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown11\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_112_t *) data )->unknown12,
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown12\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_file_information_112_t *) data )->unknown13,
			 value_64bit );
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	if( internal_file_information->path_size != 0 )
	{
		internal_file_information->path_size >>= 2;
		internal_file_information->path_size <<= 1;
		internal_file_information->path_size  += 2;
	}
	return( 1 );
}

/* Reads the file information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t libagdb_internal_file_information_read_file_io_handle(
         libagdb_internal_file_information_t *internal_file_information,
         libagdb_io_handle_t *io_handle,
         libfdata_stream_t *data_stream,
         libbfio_handle_t *file_io_handle,
         off64_t file_offset,
         uint32_t file_index,
         libcerror_error_t **error )
{
	uint8_t alignment_padding_data[ 8 ];
	uint8_t sub_entry_data[ 32 ];

	uint8_t *file_information_data = NULL;
	static char *function          = "libagdb_internal_file_information_read_file_io_handle";
	size_t alignment_padding_size  = 0;
	size_t alignment_size          = 0;
	ssize_t read_count             = 0;
	ssize_t total_read_count       = 0;
	uint32_t calculated_hash_value = 0;
	uint32_t entry_index           = 0;
	uint32_t sub_entry_data_size   = 0;

	if( internal_file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( internal_file_information->path != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file information - path value already set.",
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
	if( ( io_handle->file_information_entry_size == 0 )
	 || ( io_handle->file_information_entry_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - file information entry size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file: %" PRIu32 " information at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_index,
		 file_offset,
		 file_offset );
	}
#endif
	if( libfdata_stream_seek_offset(
	     data_stream,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file: %" PRIu32 " information offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_index,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	file_information_data = (uint8_t *) memory_allocate(
	                                     sizeof( uint8_t ) * (size_t) io_handle->file_information_entry_size );

	if( file_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              data_stream,
	              (intptr_t *) file_io_handle,
	              file_information_data,
	              (size_t) io_handle->file_information_entry_size,
	              0,
	              error );

	if( read_count != (ssize_t) io_handle->file_information_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file: %" PRIu32 " information data.",
		 function,
		 file_index );

		goto on_error;
	}
	total_read_count += read_count;
	file_offset      += read_count;

	if( libagdb_internal_file_information_read_data(
	     internal_file_information,
	     io_handle,
	     file_information_data,
	     (size_t) io_handle->file_information_entry_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file: %" PRIu32 " information.",
		 function,
		 file_index );

		goto on_error;
	}
	memory_free(
	 file_information_data );

	file_information_data = NULL;

	if( ( io_handle->file_information_entry_size == 36 )
	 || ( io_handle->file_information_entry_size == 52 )
	 || ( io_handle->file_information_entry_size == 56 )
	 || ( io_handle->file_information_entry_size == 72 ) )
	{
		alignment_size = 4;
	}
	else if( ( io_handle->file_information_entry_size == 64 )
	      || ( io_handle->file_information_entry_size == 88 )
	      || ( io_handle->file_information_entry_size == 112 ) )
	{
		alignment_size = 8;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file information entry size: %" PRIu32 ".",
		 function,
		 io_handle->file_information_entry_size );

		goto on_error;
	}
	if( internal_file_information->path_size > 0 )
	{
		if( internal_file_information->path_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid file information - path size value exceeds maximum allocation size.",
			 function );

			goto on_error;
		}
		internal_file_information->path = (uint8_t *) memory_allocate(
		                                               sizeof( uint8_t ) * internal_file_information->path_size );

		if( internal_file_information->path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create path.",
			 function );

			goto on_error;
		}
		read_count = libfdata_stream_read_buffer(
		              data_stream,
		              (intptr_t *) file_io_handle,
		              internal_file_information->path,
		              internal_file_information->path_size,
		              0,
		              error );

		if( read_count != (ssize_t) internal_file_information->path_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read file: %" PRIu32 " path data.",
			 function,
			 file_index );

			goto on_error;
		}
		total_read_count += read_count;
		file_offset      += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: file: %" PRIu32 " path data:\n",
			 function,
			 file_index );
			libcnotify_print_data(
			 internal_file_information->path,
			 internal_file_information->path_size,
			 0 );
		}
#endif
		if( libagdb_hash_calculate(
		     &calculated_hash_value,
		     internal_file_information->path,
		     internal_file_information->path_size - 2,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve path hash value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libagdb_debug_print_utf16_string_value(
			     function,
			     "file path\t\t\t\t",
			     internal_file_information->path,
			     internal_file_information->path_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print UTF-16 string value.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: file path hash value\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 calculated_hash_value );

			libcnotify_printf(
			 "\n" );
		}
#endif
		alignment_padding_size = (size_t) ( file_offset % alignment_size );

		if( alignment_padding_size != 0 )
		{
			alignment_padding_size = alignment_size - alignment_padding_size;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: alignment padding size\t\t\t: %" PRIzd "\n",
				 function,
				 alignment_padding_size );
			}
#endif
			read_count = libfdata_stream_read_buffer(
			              data_stream,
			              (intptr_t *) file_io_handle,
			              alignment_padding_data,
			              alignment_padding_size,
			              0,
			              error );

			if( read_count != (ssize_t) alignment_padding_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read file: %" PRIu32 " alignment padding data.",
				 function,
				 file_index );

				goto on_error;
			}
			total_read_count += read_count;
			file_offset      += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: file: %" PRIu32 " alignment padding data:\n",
				 function,
				 file_index );
				libcnotify_print_data(
				 alignment_padding_data,
				 alignment_padding_size,
				 0 );
			}
#endif
		}
	}
	if( internal_file_information->number_of_entries > 0 )
	{
		if( ( io_handle->file_information_sub_entry_type1_size != 16 )
		 && ( io_handle->file_information_sub_entry_type1_size != 24 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported file information sub entry type 1 size: %" PRIu32 ".",
			 function,
			 io_handle->file_information_sub_entry_type1_size );

			return( -1 );
		}
		if( ( io_handle->file_information_sub_entry_type2_size != 16 )
		 && ( io_handle->file_information_sub_entry_type2_size != 20 )
		 && ( io_handle->file_information_sub_entry_type2_size != 24 )
		 && ( io_handle->file_information_sub_entry_type2_size != 32 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported file information sub entry type 2 size: %" PRIu32 ".",
			 function,
			 io_handle->file_information_sub_entry_type2_size );

			return( -1 );
		}
		sub_entry_data_size = io_handle->file_information_sub_entry_type1_size;

		for( entry_index = 0;
		     entry_index < internal_file_information->number_of_entries;
		     entry_index++ )
		{
			read_count = libfdata_stream_read_buffer(
				      data_stream,
				      (intptr_t *) file_io_handle,
				      sub_entry_data,
				      (size_t) sub_entry_data_size,
				      0,
				      error );

			if( read_count != (ssize_t) sub_entry_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read sub entry: %" PRIu32 " data.",
				 function,
				 entry_index );

				goto on_error;
			}
			total_read_count += read_count;
			file_offset      += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: sub entry: %" PRIu32 " data:\n",
				 function,
				 entry_index );
				libcnotify_print_data(
				 sub_entry_data,
				 (size_t) sub_entry_data_size,
				 0 );
			}
#endif
		}
	}
	return( total_read_count );

on_error:
	if( internal_file_information->path != NULL )
	{
		memory_free(
		 internal_file_information->path );

		internal_file_information->path = NULL;
	}
	internal_file_information->path_size = 0;

	if( file_information_data != NULL )
	{
		memory_free(
		 file_information_data );
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 encoded path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_get_utf8_path_size(
     libagdb_file_information_t *file_information,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_file_information_t *internal_file_information = NULL;
	static char *function                                          = "libagdb_file_information_get_utf8_path_size";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	internal_file_information = (libagdb_internal_file_information_t *) file_information;

	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_file_information->path,
	     internal_file_information->path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve path UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_get_utf8_path(
     libagdb_file_information_t *file_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_file_information_t *internal_file_information = NULL;
	static char *function                                          = "libagdb_file_information_get_utf8_path";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	internal_file_information = (libagdb_internal_file_information_t *) file_information;

	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_file_information->path,
	     internal_file_information->path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy path to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_get_utf16_path_size(
     libagdb_file_information_t *file_information,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_file_information_t *internal_file_information = NULL;
	static char *function                                          = "libagdb_file_information_get_utf16_path_size";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	internal_file_information = (libagdb_internal_file_information_t *) file_information;

	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_file_information->path,
	     internal_file_information->path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve path UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_file_information_get_utf16_path(
     libagdb_file_information_t *file_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_file_information_t *internal_file_information = NULL;
	static char *function                                          = "libagdb_file_information_get_utf16_path";

	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	internal_file_information = (libagdb_internal_file_information_t *) file_information;

	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_file_information->path,
	     internal_file_information->path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy path to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

