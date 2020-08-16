/*
 * Source information functions
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
#include "libagdb_hash.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"
#include "libagdb_libuna.h"
#include "libagdb_source_information.h"

#include "agdb_source_information.h"

/* Creates source information
 * Make sure the value source_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_initialize(
     libagdb_source_information_t **source_information,
     libcerror_error_t **error )
{
	libagdb_internal_source_information_t *internal_source_information = NULL;
	static char *function                                              = "libagdb_source_information_initialize";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	if( *source_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid source information value already set.",
		 function );

		return( -1 );
	}
	internal_source_information = memory_allocate_structure(
	                               libagdb_internal_source_information_t );

	if( internal_source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create source information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_source_information,
	     0,
	     sizeof( libagdb_internal_source_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear source information.",
		 function );

		goto on_error;
	}
	*source_information = (libagdb_source_information_t *) internal_source_information;

	return( 1 );

on_error:
	if( internal_source_information != NULL )
	{
		memory_free(
		 internal_source_information );
	}
	return( -1 );
}

/* Frees source information
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_free(
     libagdb_source_information_t **source_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_source_information_free";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	if( *source_information != NULL )
	{
		*source_information = NULL;
	}
	return( 1 );
}

/* Frees source information
 * Returns 1 if successful or -1 on error
 */
int libagdb_internal_source_information_free(
     libagdb_internal_source_information_t **internal_source_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_source_information_free";

	if( internal_source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	if( *internal_source_information != NULL )
	{
		memory_free(
		 *internal_source_information );

		*internal_source_information = NULL;
	}
	return( 1 );
}

/* Reads the source information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t libagdb_source_information_read(
         libagdb_internal_source_information_t *internal_source_information,
         libagdb_io_handle_t *io_handle,
         libfdata_stream_t *uncompressed_data_stream,
         libbfio_handle_t *file_io_handle,
         uint32_t source_information_index,
         off64_t file_offset,
         libcerror_error_t **error )
{
	uint8_t sub_entry_data[ 32 ];

	uint8_t *source_information_data = NULL;
	static char *function            = "libagdb_source_information_read";
	ssize_t read_count               = 0;
	ssize_t total_read_count         = 0;
	uint32_t entry_index             = 0;
	uint32_t number_of_entries       = 0;
	uint32_t sub_entry_data_size     = 0;

	if( internal_source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
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
	if( ( io_handle->source_information_entry_size == 0 )
	 || ( io_handle->source_information_entry_size > (uint32_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid IO handle - source information entry size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading source: %" PRIu32 " information at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 source_information_index,
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
		 "%s: unable to seek source: %" PRIu32 " information offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 source_information_index,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	source_information_data = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * (size_t) io_handle->source_information_entry_size );

	if( source_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create source information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              source_information_data,
	              (size_t) io_handle->source_information_entry_size,
	              0,
	              error );

	if( read_count != (ssize_t) io_handle->source_information_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read source: %" PRIu32 " information data.",
		 function,
		 source_information_index );

		goto on_error;
	}
	total_read_count += read_count;

	if( libagdb_source_information_read_data(
	     internal_source_information,
	     io_handle,
	     source_information_data,
	     (size_t) io_handle->source_information_entry_size,
	     &number_of_entries,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read source: %" PRIu32 " information.",
		 function,
		 source_information_index );

		goto on_error;
	}
	memory_free(
	 source_information_data );

	source_information_data = NULL;

	if( number_of_entries > 0 )
	{
/* TODO is this the correct sub entry type ? */
		if( ( io_handle->file_information_sub_entry_type2_size != 16 )
		 && ( io_handle->file_information_sub_entry_type2_size != 24 ) )
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
		sub_entry_data_size = io_handle->file_information_sub_entry_type2_size;

		for( entry_index = 0;
		     entry_index < number_of_entries;
		     entry_index++ )
		{
			read_count = libfdata_stream_read_buffer(
				      uncompressed_data_stream,
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
	internal_source_information->executable_filename_size = 0;

	if( source_information_data != NULL )
	{
		memory_free(
		 source_information_data );
	}
	return( -1 );
}

/* Reads the source information
 * Returns the number of bytes read if successful or -1 on error
 */
int libagdb_source_information_read_data(
     libagdb_internal_source_information_t *internal_source_information,
     libagdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     uint32_t *number_of_entries,
     libcerror_error_t **error )
{
	static char *function = "libagdb_source_information_read_data";
	uint8_t mode          = 0;
	int string_index      = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit  = 0;
	uint32_t value_32bit  = 0;
#endif

	if( internal_source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
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
	if( data_size < io_handle->source_information_entry_size )
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
	if( number_of_entries == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of entries.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: source information data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) io_handle->source_information_entry_size,
		 0 );
	}
#endif
	if( ( io_handle->source_information_entry_size == 60 )
	 || ( io_handle->source_information_entry_size == 100 ) )
	{
		mode = 32;
	}
	else if( ( io_handle->source_information_entry_size == 88 )
	      || ( io_handle->source_information_entry_size == 144 ) )
	{
		mode = 64;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported source information entry size: %" PRIu32 ".",
		 function,
		 io_handle->source_information_entry_size );

		return( -1 );
	}
	if( ( io_handle->source_information_entry_size == 60 )
	 || ( io_handle->source_information_entry_size == 88 ) )
	{
		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_60_t *) data )->unknown3,
			 *number_of_entries );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_88_t *) data )->unknown3,
			 *number_of_entries );
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_60_t *) data )->unknown1,
			 value_64bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_source_information_88_t *) data )->unknown1,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_60_t *) data )->name_hash,
			 value_64bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_source_information_88_t *) data )->name_hash,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: name hash\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: number of entries\t\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_entries );

		if( mode == 32 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_60_t *) data )->unknown4,
			 value_32bit );
		}
		else if( mode == 64 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_source_information_88_t *) data )->unknown4,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );
	}
#endif

	if( ( io_handle->source_information_entry_size == 60 )
	 || ( io_handle->source_information_entry_size == 88 ) )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_60_t *) data )->unknown5,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_88_t *) data )->unknown5,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown5\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "%s: unknown6:\n",
			 function );
			if( mode == 32 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_60_t *) data )->unknown6,
				 8,
				 0 );
			}
			else if( mode == 64 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_88_t *) data )->unknown6,
				 16,
				 0 );
			}

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_60_t *) data )->unknown7,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_88_t *) data )->unknown7,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_60_t *) data )->unknown8,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_88_t *) data )->unknown8,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_60_t *) data )->unknown9,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_88_t *) data )->unknown9,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown9\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_60_t *) data )->unknown10,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_88_t *) data )->unknown10,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown10\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "%s: unknown11:\n",
			 function );
			if( mode == 32 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_60_t *) data )->unknown11,
				 8,
				 0 );
			}
			else if( mode == 64 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_88_t *) data )->unknown11,
				 16,
				 0 );
			}
		}
#endif
	}
	else if( ( io_handle->source_information_entry_size == 100 )
	      || ( io_handle->source_information_entry_size == 144 ) )
	{
		if( mode == 32 )
		{
			if( memory_copy(
			     internal_source_information->executable_filename,
			     ( (agdb_source_information_100_t *) data )->executable_filename,
			     (size_t) 16 ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy executable filename.",
				 function );

				return( -1 );
			}
		}
		else if( mode == 64 )
		{
			if( memory_copy(
			     internal_source_information->executable_filename,
			     ( (agdb_source_information_144_t *) data )->executable_filename,
			     (size_t) 16 ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy executable filename.",
				 function );

				return( -1 );
			}
		}
		for( string_index = 0;
		     string_index < 16;
		     string_index++ )
		{
			if( internal_source_information->executable_filename[ string_index ] == 0 )
			{
				break;
			}
		}
		internal_source_information->executable_filename_size = string_index + 1;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unknown5:\n",
			 function );
			if( mode == 32 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_100_t *) data )->unknown5,
				 12,
				 0 );
			}
			else if( mode == 64 )
			{
				libcnotify_print_data(
				 ( (agdb_source_information_144_t *) data )->unknown5,
				 24,
				 0 );
			}

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown6,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown6,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown7,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown7,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->prefetch_hash,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->prefetch_hash,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: prefetch hash\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown9,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown9,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown9\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

/* TODO allow to set codepage */
			if( libagdb_debug_print_string_value(
			     function,
			     "executable filename\t\t\t",
			     internal_source_information->executable_filename,
			     internal_source_information->executable_filename_size,
			     LIBUNA_CODEPAGE_ASCII,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print string value.",
				 function );

				return( -1 );
			}
			libcnotify_printf(
			 "\n" );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown11,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown11,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown11\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown12,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown12,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown12\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown13,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown13,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown13\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown14,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown14,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown14\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown15,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown15,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown15\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown16,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown16,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown16\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown17,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown17,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown17\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown18,
				 value_32bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown18,
				 value_32bit );
			}
			libcnotify_printf(
			 "%s: unknown18\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown19,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown19,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown19\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			if( mode == 32 )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (agdb_source_information_100_t *) data )->unknown20,
				 value_64bit );
			}
			else if( mode == 64 )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (agdb_source_information_144_t *) data )->unknown20,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown20\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "\n" );
		}
#endif
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded executable filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_get_utf8_executable_filename_size(
     libagdb_source_information_t *source_information,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_source_information_t *internal_source_information = NULL;
	static char *function                                              = "libagdb_source_information_get_utf8_executable_filename_size";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	internal_source_information = (libagdb_internal_source_information_t *) source_information;

/* TODO allow to set codepage */
	if( libuna_utf8_string_size_from_byte_stream(
	     internal_source_information->executable_filename,
	     internal_source_information->executable_filename_size,
	     LIBUNA_CODEPAGE_ASCII,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve executable filename UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded executable filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_get_utf8_executable_filename(
     libagdb_source_information_t *source_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_source_information_t *internal_source_information = NULL;
	static char *function                                              = "libagdb_source_information_get_utf8_executable_filename";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	internal_source_information = (libagdb_internal_source_information_t *) source_information;

/* TODO allow to set codepage */
	if( libuna_utf8_string_copy_from_byte_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_source_information->executable_filename,
	     internal_source_information->executable_filename_size,
	     LIBUNA_CODEPAGE_ASCII,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy executable filename to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded executable filename
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_get_utf16_executable_filename_size(
     libagdb_source_information_t *source_information,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_source_information_t *internal_source_information = NULL;
	static char *function                                              = "libagdb_source_information_get_utf16_executable_filename_size";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	internal_source_information = (libagdb_internal_source_information_t *) source_information;

/* TODO allow to set codepage */
	if( libuna_utf16_string_size_from_byte_stream(
	     internal_source_information->executable_filename,
	     internal_source_information->executable_filename_size,
	     LIBUNA_CODEPAGE_ASCII,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve executable filename UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded executable filename
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_source_information_get_utf16_executable_filename(
     libagdb_source_information_t *source_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_source_information_t *internal_source_information = NULL;
	static char *function                                              = "libagdb_source_information_get_utf16_executable_filename";

	if( source_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source information.",
		 function );

		return( -1 );
	}
	internal_source_information = (libagdb_internal_source_information_t *) source_information;

/* TODO allow to set codepage */
	if( libuna_utf16_string_copy_from_byte_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_source_information->executable_filename,
	     internal_source_information->executable_filename_size,
	     LIBUNA_CODEPAGE_ASCII,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy executable filename to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

