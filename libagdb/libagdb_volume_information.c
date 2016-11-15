/*
 * Volume information functions
 *
 * Copyright (C) 2014-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include "libagdb_file_information.h"
#include "libagdb_hash.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcdata.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdatetime.h"
#include "libagdb_libfdata.h"
#include "libagdb_libuna.h"
#include "libagdb_volume_information.h"

#include "agdb_volume_information.h"

/* Creates volume information
 * Make sure the value volume_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_initialize(
     libagdb_volume_information_t **volume_information,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_initialize";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *volume_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume information value already set.",
		 function );

		return( -1 );
	}
	internal_volume_information = memory_allocate_structure(
	                               libagdb_internal_volume_information_t );

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_volume_information,
	     0,
	     sizeof( libagdb_internal_volume_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear volume.",
		 function );

		goto on_error;
	}
	if( libcdata_array_initialize(
	     &( internal_volume_information->files_array ),
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create files array.",
		 function );

		goto on_error;
	}
	*volume_information = (libagdb_volume_information_t *) internal_volume_information;

	return( 1 );

on_error:
	if( internal_volume_information != NULL )
	{
		memory_free(
		 internal_volume_information );
	}
	return( -1 );
}

/* Frees volume information
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_free(
     libagdb_volume_information_t **volume_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_volume_information_free";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *volume_information != NULL )
	{
		*volume_information = NULL;
	}
	return( 1 );
}

/* Frees volume information
 * Returns 1 if successful or -1 on error
 */
int libagdb_internal_volume_information_free(
     libagdb_internal_volume_information_t **internal_volume_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_volume_information_free";
	int result            = 1;

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( *internal_volume_information != NULL )
	{
		if( ( *internal_volume_information )->device_path != NULL )
		{
			memory_free(
			 ( *internal_volume_information )->device_path );
		}
		if( libcdata_array_free(
		     &( ( *internal_volume_information )->files_array ),
		     (int (*)(intptr_t **, libcerror_error_t **)) &libagdb_internal_file_information_free,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free files array.",
			 function );

			result = -1;
		}
		memory_free(
		 *internal_volume_information );

		*internal_volume_information = NULL;
	}
	return( result );
}

/* Reads the volume information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize64_t libagdb_volume_information_read(
           libagdb_internal_volume_information_t *internal_volume_information,
           libagdb_io_handle_t *io_handle,
           libfdata_stream_t *uncompressed_data_stream,
           libbfio_handle_t *file_io_handle,
           uint32_t volume_index,
           off64_t file_offset,
           libcerror_error_t **error )
{
	uint8_t alignment_padding_data[ 8 ];

	libagdb_file_information_t *file_information = NULL;
	uint8_t *volume_information_data             = NULL;
	static char *function                        = "libagdb_volume_information_read";
	ssize64_t total_read_count                   = 0;
	size_t alignment_padding_size                = 0;
	size_t alignment_size                        = 0;
	ssize_t read_count                           = 0;
	uint32_t calculated_hash_value               = 0;
	uint32_t file_index                          = 0;
	uint32_t number_of_files                     = 0;
	uint16_t device_path_size                    = 0;
	int entry_index                              = 0;

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	if( internal_volume_information->device_path != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid volume information - device path value already set.",
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
	if( (size_t) io_handle->volume_information_entry_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid IO handle - volume information entry size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading volume: %" PRIu32 " information at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 volume_index,
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
		 "%s: unable to seek volume: %" PRIu32 " information offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 volume_index,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	volume_information_data = (uint8_t *) memory_allocate(
	                                       sizeof( uint8_t ) * io_handle->volume_information_entry_size );

	if( volume_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create volume information data.",
		 function );

		goto on_error;
	}
	read_count = libfdata_stream_read_buffer(
	              uncompressed_data_stream,
	              (intptr_t *) file_io_handle,
	              volume_information_data,
	              (size_t) io_handle->volume_information_entry_size,
	              0,
	              error );

	if( read_count != (ssize_t) io_handle->volume_information_entry_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volume: %" PRIu32 " information data.",
		 function,
		 volume_index );

		goto on_error;
	}
	total_read_count += read_count;
	file_offset      += read_count;

	if( libagdb_volume_information_read_data(
	     internal_volume_information,
	     io_handle,
	     volume_information_data,
	     (size_t) io_handle->volume_information_entry_size,
	     &number_of_files,
	     &device_path_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read volume: %" PRIu32 " information.",
		 function,
		 volume_index );

		goto on_error;
	}
	memory_free(
	 volume_information_data );

	volume_information_data = NULL;

	if( io_handle->volume_information_entry_size == 56 )
	{
		alignment_size = 4;
	}
	else if( io_handle->volume_information_entry_size == 72 )
	{
		alignment_size = 8;
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported volume information entry size: %" PRIu32 ".",
		 function,
		 io_handle->volume_information_entry_size );

		goto on_error;
	}
	if( device_path_size != 0 )
	{
		device_path_size += 1;
		device_path_size *= 2;

		internal_volume_information->device_path = (uint8_t *) memory_allocate(
		                                                        sizeof( uint8_t ) * device_path_size );

		if( internal_volume_information->device_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create device path.",
			 function );

			goto on_error;
		}
		internal_volume_information->device_path_size = device_path_size;

		read_count = libfdata_stream_read_buffer(
		              uncompressed_data_stream,
		              (intptr_t *) file_io_handle,
		              internal_volume_information->device_path,
		              internal_volume_information->device_path_size,
		              0,
		              error );

		if( read_count != (ssize_t) internal_volume_information->device_path_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read volume: %" PRIu32 " information data.",
			 function,
			 volume_index );

			goto on_error;
		}
		total_read_count += read_count;
		file_offset      += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: volume: %" PRIu32 " device path data:\n",
			 function,
			 volume_index );
			libcnotify_print_data(
			 internal_volume_information->device_path,
			 internal_volume_information->device_path_size,
			 0 );
		}
#endif
		if( libagdb_hash_calculate(
		     &calculated_hash_value,
		     internal_volume_information->device_path,
		     internal_volume_information->device_path_size - 2,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume: %" PRIu32 " device path hash value.",
			 function,
			 volume_index );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( libagdb_debug_print_utf16_string_value(
			     function,
			     "volume device path\t\t\t",
			     internal_volume_information->device_path,
			     internal_volume_information->device_path_size,
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
			 "%s: volume device path hash value\t\t: 0x%08" PRIx64 "\n",
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
			              uncompressed_data_stream,
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
	for( file_index = 0;
	     file_index < number_of_files;
	     file_index++ )
	{
		if( libagdb_file_information_initialize(
		     &file_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create file: %" PRIu32 " information.",
			 function,
			 file_index );

			goto on_error;
		}
		read_count = libagdb_file_information_read(
		              (libagdb_internal_file_information_t *) file_information,
		              io_handle,
		              uncompressed_data_stream,
		              file_io_handle,
		              file_index,
		              file_offset,
		              error );

		if( read_count == -1 )
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
		total_read_count += read_count;
		file_offset      += read_count;

		if( libcdata_array_append_entry(
		     internal_volume_information->files_array,
		     &entry_index,
		     (intptr_t *) file_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append file: %" PRIu32 " information to array.",
			 function,
			 file_index );

			goto on_error;
		}
		file_information = NULL;
	}
	return( total_read_count );

on_error:
	if( file_information != NULL )
	{
		libagdb_internal_file_information_free(
		 (libagdb_internal_file_information_t **) &file_information,
		 NULL );
	}
	if( internal_volume_information->device_path != NULL )
	{
		memory_free(
		 internal_volume_information->device_path );

		internal_volume_information->device_path = NULL;
	}
	internal_volume_information->device_path_size = 0;

	if( volume_information_data != NULL )
	{
		memory_free(
		 volume_information_data );
	}
	return( -1 );
}

/* Reads the volume information
 * Returns the number of bytes read if successful or -1 on error
 */
int libagdb_volume_information_read_data(
     libagdb_internal_volume_information_t *internal_volume_information,
     libagdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     uint32_t *number_of_files,
     uint16_t *device_path_size,
     libcerror_error_t **error )
{
	static char *function  = "libagdb_volume_information_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint8_t *filetime_data = NULL;
	uint64_t value_64bit   = 0;
	uint32_t value_32bit   = 0;
	uint16_t value_16bit   = 0;
#endif

	if( internal_volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
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
	if( data_size < io_handle->volume_information_entry_size )
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
	if( number_of_files == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of files.",
		 function );

		return( -1 );
	}
	if( device_path_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid device path size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: volume information data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 (size_t) io_handle->volume_information_entry_size,
		 0 );
	}
#endif
	if( io_handle->volume_information_entry_size == 56 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_56_t *) data )->number_of_files,
		 *number_of_files );

		byte_stream_copy_to_uint64_little_endian(
		 ( (agdb_volume_information_56_t *) data )->creation_time,
		 internal_volume_information->creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_56_t *) data )->serial_number,
		 internal_volume_information->serial_number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (agdb_volume_information_56_t *) data )->device_path_number_of_characters,
		 *device_path_size );
	}
	else if( io_handle->volume_information_entry_size == 72 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_72_t *) data )->number_of_files,
		 *number_of_files );

		byte_stream_copy_to_uint64_little_endian(
		 ( (agdb_volume_information_72_t *) data )->creation_time,
		 internal_volume_information->creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_72_t *) data )->serial_number,
		 internal_volume_information->serial_number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (agdb_volume_information_72_t *) data )->device_path_number_of_characters,
		 *device_path_size );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown1,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown1,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown2,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown2,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: number of files\t\t\t: %" PRIu32 "\n",
		 function,
		 *number_of_files );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown3,
			 value_32bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown3,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown4,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown4,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			filetime_data = ( (agdb_volume_information_56_t *) data )->creation_time;
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			filetime_data = ( (agdb_volume_information_72_t *) data )->creation_time;
		}
		if( libagdb_debug_print_filetime_value(
		     function,
		     "creation time\t\t\t\t",
		     filetime_data,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: serial number\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_volume_information->serial_number );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown5,
			 value_32bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown5,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown6,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown6,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: device path number of characters\t: %" PRIu16 "\n",
		 function,
		 *device_path_size );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown7,
			 value_16bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown7,
			 value_16bit );
		}
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown8,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_56_t *) data )->unknown9,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) data )->unknown9,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the volume creation date and time
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_creation_time(
     libagdb_volume_information_t *volume_information,
     uint64_t *creation_time,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_creation_time";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( creation_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid creation time.",
		 function );

		return( -1 );
	}
	*creation_time = internal_volume_information->creation_time;

	return( 1 );
}

/* Retrieves the serial number
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_serial_number(
     libagdb_volume_information_t *volume_information,
     uint32_t *serial_number,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_serial_number";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( serial_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid serial number.",
		 function );

		return( -1 );
	}
	*serial_number = internal_volume_information->serial_number;

	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_utf8_device_path_size(
     libagdb_volume_information_t *volume_information,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_utf8_device_path_size";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( libuna_utf8_string_size_from_utf16_stream(
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve device path UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_utf8_device_path(
     libagdb_volume_information_t *volume_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_utf8_device_path";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( libuna_utf8_string_copy_from_utf16_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy device path to UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded device path
 * The returned size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_utf16_device_path_size(
     libagdb_volume_information_t *volume_information,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_utf16_device_path_size";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( libuna_utf16_string_size_from_utf16_stream(
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve device path UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded device path
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_utf16_device_path(
     libagdb_volume_information_t *volume_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_utf16_device_path";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( libuna_utf16_string_copy_from_utf16_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_volume_information->device_path,
	     internal_volume_information->device_path_size,
	     LIBUNA_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy device path to UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the number of files
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_number_of_files(
     libagdb_volume_information_t *volume_information,
     int *number_of_files,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_number_of_files";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

	if( libcdata_array_get_number_of_entries(
	     internal_volume_information->files_array,
	     number_of_files,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of files.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a specific file information
 * Returns 1 if successful or -1 on error
 */
int libagdb_volume_information_get_file_information(
     libagdb_volume_information_t *volume_information,
     int file_index,
     libagdb_file_information_t **file_information,
     libcerror_error_t **error )
{
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	static char *function                                              = "libagdb_volume_information_get_file_information";

	if( volume_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume information.",
		 function );

		return( -1 );
	}
	internal_volume_information = (libagdb_internal_volume_information_t *) volume_information;

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
	if( libcdata_array_get_entry_by_index(
	     internal_volume_information->files_array,
	     file_index,
	     (intptr_t **) file_information,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file: %d information.",
		 function,
		 file_index );

		return( -1 );
	}
	return( 1 );
}

