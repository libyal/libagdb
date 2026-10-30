/*
 * OSS-Fuzz target for libagdb file type
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

#include <stddef.h>
#include <stdint.h>

#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libagdb.h"
#include "ossfuzz_libbfio.h"

#if !defined( LIBAGDB_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBAGDB_EXTERN \
int libagdb_file_open_file_io_handle(
      libagdb_file_t *file,
      libbfio_handle_t *file_io_handle,
      int access_flags,
      libagdb_error_t **error );

#endif /* !defined( LIBAGDB_HAVE_BFIO ) */

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libbfio_handle_t *file_io_handle                 = NULL;
	libagdb_file_t *file                             = NULL;
	libagdb_volume_information_t *volume_information = NULL;
	libagdb_file_information_t *file_information     = NULL;
	libagdb_source_information_t *source_information = NULL;
	size_t value_string_size                         = 0;
	uint64_t value_64bit                             = 0;
	uint32_t value_32bit                             = 0;
	uint8_t *value_string                            = NULL;
	int number_of_files                              = 0;
	int number_of_sources                            = 0;
	int number_of_volumes                            = 0;
	int source_index                                 = 0;
	int volume_index                                 = 0;

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libagdb_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libagdb_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     LIBAGDB_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libagdb;
	}
	if( libagdb_file_get_number_of_volumes(
	     file,
	     &number_of_volumes,
	     NULL ) == 1 )
	{
		for( volume_index = 0;
		     volume_index < number_of_volumes
		 && volume_index < 8;
		     volume_index++ )
		{
			if( libagdb_file_get_volume_information(
			     file,
			     volume_index,
			     &volume_information,
			     NULL ) != 1 )
			{
				continue;
			}
			libagdb_volume_information_get_creation_time(
			 volume_information,
			 &value_64bit,
			 NULL );

			libagdb_volume_information_get_serial_number(
			 volume_information,
			 &value_32bit,
			 NULL );

			if( ( libagdb_volume_information_get_utf8_device_path_size(
			      volume_information,
			      &value_string_size,
			      NULL ) == 1 )
			 && ( value_string_size > 0 )
			 && ( value_string_size <= (size_t) ( 1 << 16 ) ) )
			{
				value_string = (uint8_t *) malloc(
				                            value_string_size );

				if( value_string != NULL )
				{
					libagdb_volume_information_get_utf8_device_path(
					 volume_information,
					 value_string,
					 value_string_size,
					 NULL );
					free( value_string );

					value_string = NULL;
				}
			}
			if( ( libagdb_volume_information_get_utf16_device_path_size(
			      volume_information,
			      &value_string_size,
			      NULL ) == 1 )
			 && ( value_string_size > 0 )
			 && ( value_string_size <= ( (size_t) ( 1 << 16 ) / sizeof( uint16_t ) ) ) )
			{
				value_string = (uint8_t *) malloc(
				                            value_string_size * sizeof( uint16_t ) );

				if( value_string != NULL )
				{
					libagdb_volume_information_get_utf16_device_path(
					 volume_information,
					 (uint16_t *) value_string,
					 value_string_size,
					 NULL );
					free( value_string );

					value_string = NULL;
				}
			}
			if( ( libagdb_volume_information_get_number_of_files(
			      volume_information,
			      &number_of_files,
			      NULL ) == 1 )
			 && ( number_of_files > 0 ) )
			{
				if( libagdb_volume_information_get_file_information(
				     volume_information,
				     0,
				     &file_information,
				     NULL ) == 1 )
				{
					if( ( libagdb_file_information_get_utf8_path_size(
					      file_information,
					      &value_string_size,
					      NULL ) == 1 )
					 && ( value_string_size > 0 )
					 && ( value_string_size <= (size_t) ( 1 << 16 ) ) )
					{
						value_string = (uint8_t *) malloc(
						                            value_string_size );

						if( value_string != NULL )
						{
							libagdb_file_information_get_utf8_path(
							 file_information,
							 value_string,
							 value_string_size,
							 NULL );
							free( value_string );

							value_string = NULL;
						}
					}
					if( ( libagdb_file_information_get_utf16_path_size(
					      file_information,
					      &value_string_size,
					      NULL ) == 1 )
					 && ( value_string_size > 0 )
					 && ( value_string_size <= ( (size_t) ( 1 << 16 ) / sizeof( uint16_t ) ) ) )
					{
						value_string = (uint8_t *) malloc(
						                            value_string_size * sizeof( uint16_t ) );

						if( value_string != NULL )
						{
							libagdb_file_information_get_utf16_path(
							 file_information,
							 (uint16_t *) value_string,
							 value_string_size,
							 NULL );
							free( value_string );

							value_string = NULL;
						}
					}
					libagdb_file_information_free(
					 &file_information,
					 NULL );
				}
			}
			libagdb_volume_information_free(
			 &volume_information,
			 NULL );
		}
	}
	if( libagdb_file_get_number_of_sources(
	     file,
	     &number_of_sources,
	     NULL ) == 1 )
	{
		for( source_index = 0;
		     source_index < number_of_sources
		 && source_index < 8;
		     source_index++ )
		{
			if( libagdb_file_get_source_information(
			     file,
			     source_index,
			     &source_information,
			     NULL ) != 1 )
			{
				continue;
			}
			if( ( libagdb_source_information_get_utf8_executable_filename_size(
			      source_information,
			      &value_string_size,
			      NULL ) == 1 )
			 && ( value_string_size > 0 )
			 && ( value_string_size <= (size_t) ( 1 << 16 ) ) )
			{
				value_string = (uint8_t *) malloc(
				                            value_string_size );

				if( value_string != NULL )
				{
					libagdb_source_information_get_utf8_executable_filename(
					 source_information,
					 value_string,
					 value_string_size,
					 NULL );
					free( value_string );

					value_string = NULL;
				}
			}
			if( ( libagdb_source_information_get_utf16_executable_filename_size(
			      source_information,
			      &value_string_size,
			      NULL ) == 1 )
			 && ( value_string_size > 0 )
			 && ( value_string_size <= ( (size_t) ( 1 << 16 ) / sizeof( uint16_t ) ) ) )
			{
				value_string = (uint8_t *) malloc(
				                            value_string_size * sizeof( uint16_t ) );

				if( value_string != NULL )
				{
					libagdb_source_information_get_utf16_executable_filename(
					 source_information,
					 (uint16_t *) value_string,
					 value_string_size,
					 NULL );
					free( value_string );

					value_string = NULL;
				}
			}
			libagdb_source_information_free(
			 &source_information,
			 NULL );
		}
	}
	libagdb_file_close(
	 file,
	 NULL );

on_error_libagdb:
	libagdb_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
