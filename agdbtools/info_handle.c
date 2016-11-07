/*
 * Info handle
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "agdbinput.h"
#include "agdbtools_libcerror.h"
#include "agdbtools_libfdatetime.h"
#include "agdbtools_libagdb.h"
#include "info_handle.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libagdb_file_initialize(
	     &( ( *info_handle )->input_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file.",
		 function );

		goto on_error;
	}
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_file != NULL )
		{
			if( libagdb_file_free(
			     &( ( *info_handle )->input_file ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input file.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_file != NULL )
	{
		if( libagdb_file_signal_abort(
		     info_handle->input_file,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_ascii_codepage";
	int result            = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = agdbinput_determine_ascii_codepage(
	          string,
	          &( info_handle->ascii_codepage ),
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libagdb_file_open_wide(
	     info_handle->input_file,
	     filename,
	     LIBAGDB_OPEN_READ,
	     error ) != 1 )
#else
	if( libagdb_file_open(
	     info_handle->input_file,
	     filename,
	     LIBAGDB_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libagdb_file_close(
	     info_handle->input_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input file.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the file information
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	system_character_t filetime_string[ 48 ];

	libagdb_source_information_t *source_information = NULL;
	libagdb_file_information_t *file_information     = NULL;
	libagdb_volume_information_t *volume_information = NULL;
	system_character_t *value_string                 = NULL;
	libfdatetime_filetime_t *filetime                = NULL;
	static char *function                            = "info_handle_file_fprint";
	size_t value_string_size                         = 0;
	uint64_t value_64bit                             = 0;
	uint32_t value_32bit                             = 0;
	int file_index                                   = 0;
	int number_of_files                              = 0;
	int number_of_sources                            = 0;
	int number_of_volumes                            = 0;
	int result                                       = 0;
	int source_index                                 = 0;
	int volume_index                                 = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
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
	fprintf(
	 info_handle->notify_stream,
	 "Windows SuperFetch database file information:\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "Volumes:\n" );

	if( libagdb_file_get_number_of_volumes(
	     info_handle->input_file,
	     &number_of_volumes,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of volumes.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of volumes\t\t: %d\n",
	 number_of_volumes );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( volume_index = 0;
	     volume_index < number_of_volumes;
	     volume_index++ )
	{
		if( libagdb_file_get_volume_information(
		     info_handle->input_file,
		     volume_index,
		     &volume_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve volume information.",
			 function );

			return( -1 );
		}
		fprintf(
		 info_handle->notify_stream,
		 "Volume: %d information:\n",
		 volume_index + 1 );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libagdb_volume_information_get_utf16_device_path_size(
			  volume_information,
			  &value_string_size,
			  error );
#else
		result = libagdb_volume_information_get_utf8_device_path_size(
			  volume_information,
			  &value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve device path size.",
			 function );

			goto on_error;
		}
		if( value_string_size > 0 )
		{
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create value string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libagdb_volume_information_get_utf16_device_path(
				  volume_information,
				  (uint16_t *) value_string,
				  value_string_size,
				  error );
#else
			result = libagdb_volume_information_get_utf8_device_path(
				  volume_information,
				  (uint8_t *) value_string,
				  value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve device path.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tDevice path\t\t\t: %" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
		if( libagdb_volume_information_get_creation_time(
		     volume_information,
		     &value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve creation time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		fprintf(
		 info_handle->notify_stream,
		 "\tCreation time\t\t\t: %" PRIs_SYSTEM " UTC\n",
		 filetime_string );

		if( libagdb_volume_information_get_serial_number(
		     volume_information,
		     &value_32bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve serial number.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tSerial number\t\t\t: 0x%08" PRIx32 "\n",
		 value_32bit );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		fprintf(
		 info_handle->notify_stream,
		 "Files:\n" );

		if( libagdb_volume_information_get_number_of_files(
		     volume_information,
		     &number_of_files,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of files.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tNumber of files\t\t\t: %d\n",
		 number_of_files );

		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		for( file_index = 0;
		     file_index < number_of_files;
		     file_index++ )
		{
			if( libagdb_volume_information_get_file_information(
			     volume_information,
			     file_index,
			     &file_information,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve file information.",
				 function );

				return( -1 );
			}
			fprintf(
			 info_handle->notify_stream,
			 "File: %d information:\n",
			 file_index + 1 );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libagdb_file_information_get_utf16_path_size(
				  file_information,
				  &value_string_size,
				  error );
#else
			result = libagdb_file_information_get_utf8_path_size(
				  file_information,
				  &value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve path size.",
				 function );

				goto on_error;
			}
			if( value_string_size > 0 )
			{
				value_string = system_string_allocate(
						value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libagdb_file_information_get_utf16_path(
					  file_information,
					  (uint16_t *) value_string,
					  value_string_size,
					  error );
#else
				result = libagdb_file_information_get_utf8_path(
					  file_information,
					  (uint8_t *) value_string,
					  value_string_size,
					  error );
#endif
				if( result != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve path.",
					 function );

					goto on_error;
				}
				fprintf(
				 info_handle->notify_stream,
				 "\tPath\t\t\t\t: %" PRIs_SYSTEM "\n",
				 value_string );

				memory_free(
				 value_string );

				value_string = NULL;
			}
			if( libagdb_file_information_free(
			     &file_information,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free file information.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\n" );
		}
		if( libagdb_volume_information_free(
		     &volume_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free volume information.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Sources:\n" );

	if( libagdb_file_get_number_of_sources(
	     info_handle->input_file,
	     &number_of_sources,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sources.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of sources\t\t: %d\n",
	 number_of_sources );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	for( source_index = 0;
	     source_index < number_of_sources;
	     source_index++ )
	{
		if( libagdb_file_get_source_information(
		     info_handle->input_file,
		     source_index,
		     &source_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve source information.",
			 function );

			return( -1 );
		}
		fprintf(
		 info_handle->notify_stream,
		 "Source: %d information:\n",
		 source_index + 1 );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libagdb_source_information_get_utf16_executable_filename_size(
			  source_information,
			  &value_string_size,
			  error );
#else
		result = libagdb_source_information_get_utf8_executable_filename_size(
			  source_information,
			  &value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve executable filename size.",
			 function );

			goto on_error;
		}
		if( value_string_size > 0 )
		{
			value_string = system_string_allocate(
					value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create value string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libagdb_source_information_get_utf16_executable_filename(
				  source_information,
				  (uint16_t *) value_string,
				  value_string_size,
				  error );
#else
			result = libagdb_source_information_get_utf8_executable_filename(
				  source_information,
				  (uint8_t *) value_string,
				  value_string_size,
				  error );
#endif
			if( result != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve executable filename.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tExecutable filename\t\t: %" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
		if( libagdb_source_information_free(
		     &source_information,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free source information.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( source_information != NULL )
	{
		libagdb_source_information_free(
		 &source_information,
		 NULL );
	}
	if( volume_information != NULL )
	{
		libagdb_volume_information_free(
		 &volume_information,
		 NULL );
	}
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
	return( -1 );
}

