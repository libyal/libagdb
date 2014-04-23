/*
 * Volume information functions
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
#include "libagdb_file_information.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcdata.h"
#include "libagdb_libcerror.h"
#include "libagdb_libcnotify.h"
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
     libagdb_internal_volume_information_t **volume_information,
     libcerror_error_t **error )
{
	static char *function = "libagdb_internal_volume_information_free";
	int result            = 1;

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
		if( ( *volume_information )->device_path != NULL )
		{
			memory_free(
			 ( *volume_information )->device_path );
		}
		if( libcdata_array_free(
		     &( ( *volume_information )->files_array ),
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
		 *volume_information );

		*volume_information = NULL;
	}
	return( result );
}

/* Reads the volume information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize64_t libagdb_volume_information_read(
           libagdb_volume_information_t *volume_information,
           libfdata_stream_t *uncompressed_data_stream,
           libbfio_handle_t *file_io_handle,
           libagdb_io_handle_t *io_handle,
           off64_t file_offset,
           uint32_t volume_index,
           libcerror_error_t **error )
{
	libagdb_file_information_t *file_information                       = NULL;
	libagdb_internal_volume_information_t *internal_volume_information = NULL;
	uint8_t *volume_information_data                                   = NULL;
	static char *function                                              = "libagdb_volume_information_read";
	ssize64_t total_read_count                                         = 0;
	ssize_t read_count                                                 = 0;
	uint32_t file_index                                                = 0;
	uint32_t number_of_files                                           = 0;
	uint16_t device_path_size                                          = 0;
	int entry_index                                                    = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t filetime_string[ 48 ];

	libfdatetime_filetime_t *filetime                                  = NULL;
	libcstring_system_character_t *value_string                        = NULL;
	size_t value_string_size                                           = 0;
	uint64_t value_64bit                                               = 0;
	uint32_t value_32bit                                               = 0;
	uint16_t value_16bit                                               = 0;
	int result                                                         = 0;
#endif

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

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: volume: %" PRIu32 " information data:\n",
		 function,
		 volume_index );
		libcnotify_print_data(
		 volume_information_data,
		 (size_t) io_handle->volume_information_entry_size,
		 0 );
	}
#endif
	if( ( io_handle->volume_information_entry_size != 56 )
	 && ( io_handle->volume_information_entry_size != 72 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported volume information entry size: %" PRIu32 ".",
		 function,
		 io_handle->volume_information_entry_size );

		return( -1 );
	}
	if( io_handle->volume_information_entry_size == 56 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_56_t *) volume_information_data )->number_of_files,
		 number_of_files );

		byte_stream_copy_to_uint64_little_endian(
		 ( (agdb_volume_information_56_t *) volume_information_data )->creation_time,
		 internal_volume_information->creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_56_t *) volume_information_data )->serial_number,
		 internal_volume_information->serial_number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (agdb_volume_information_56_t *) volume_information_data )->device_path_number_of_characters,
		 device_path_size );
	}
	else if( io_handle->volume_information_entry_size == 72 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_72_t *) volume_information_data )->number_of_files,
		 number_of_files );

		byte_stream_copy_to_uint64_little_endian(
		 ( (agdb_volume_information_72_t *) volume_information_data )->creation_time,
		 internal_volume_information->creation_time );

		byte_stream_copy_to_uint32_little_endian(
		 ( (agdb_volume_information_72_t *) volume_information_data )->serial_number,
		 internal_volume_information->serial_number );

		byte_stream_copy_to_uint16_little_endian(
		 ( (agdb_volume_information_72_t *) volume_information_data )->device_path_number_of_characters,
		 device_path_size );
	}

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfdatetime_filetime_initialize(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create filetime.",
			 function );

			goto on_error;
		}
		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown1,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown1,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown2,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown2,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown2\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: number of files\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_files );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown3,
			 value_32bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown3,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown3\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown4,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown4,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown4\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			result = libfdatetime_filetime_copy_from_byte_stream(
			          filetime,
			          ( (agdb_volume_information_56_t *) volume_information_data )->creation_time,
			          8,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			result = libfdatetime_filetime_copy_from_byte_stream(
			          filetime,
			          ( (agdb_volume_information_72_t *) volume_information_data )->creation_time,
			          8,
			          LIBFDATETIME_ENDIAN_LITTLE,
			          error );
		}
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: creation time\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		libcnotify_printf(
		 "%s: serial number\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_volume_information->serial_number );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown5,
			 value_32bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown5,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: unknown5\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown6,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown6,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown6\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "%s: device path number of characters\t: %" PRIu16 "\n",
		 function,
		 device_path_size );

		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown7,
			 value_16bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint16_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown7,
			 value_16bit );
		}
		libcnotify_printf(
		 "%s: unknown7\t\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown8,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown8\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( io_handle->volume_information_entry_size == 56 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_56_t *) volume_information_data )->unknown9,
			 value_64bit );
		}
		else if( io_handle->volume_information_entry_size == 72 )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (agdb_volume_information_72_t *) volume_information_data )->unknown9,
			 value_64bit );
		}
		libcnotify_printf(
		 "%s: unknown9\t\t\t\t: 0x%08" PRIx64 "\n",
		 function,
		 value_64bit );

		libcnotify_printf(
		 "\n" );

		if( libfdatetime_filetime_free(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free filetime.",
			 function );

			goto on_error;
		}
	}
#endif
	memory_free(
	 volume_information_data );

	volume_information_data = NULL;

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
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  internal_volume_information->device_path,
				  internal_volume_information->device_path_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  internal_volume_information->device_path,
				  internal_volume_information->device_path_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine size of volume device path string.",
				 function );

				goto on_error;
			}
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( libcstring_system_character_t ) * value_string_size ) > (size_t) SSIZE_MAX ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid volume device path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = libcstring_system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create volume device path string.",
				 function );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  internal_volume_information->device_path,
				  internal_volume_information->device_path_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  internal_volume_information->device_path,
				  internal_volume_information->device_path_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set volume device path string.",
				 function );

				goto on_error;
			}
			libcnotify_printf(
			 "%s: volume device path\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
			 function,
			 value_string );

			libcnotify_printf(
			 "\n" );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#endif
	}
	file_offset += total_read_count;

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
		              file_information,
		              uncompressed_data_stream,
		              file_io_handle,
		              io_handle,
		              file_offset,
		              file_index,
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
		file_offset      += read_count;
		total_read_count += read_count;

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
#endif
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
