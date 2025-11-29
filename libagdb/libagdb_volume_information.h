/*
 * Volume information functions
 *
 * Copyright (C) 2014-2025, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBAGDB_INTERNAL_VOLUME_INFORMATION_H )
#define _LIBAGDB_INTERNAL_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libagdb_extern.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcdata.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"
#include "libagdb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_internal_volume_information libagdb_internal_volume_information_t;

struct libagdb_internal_volume_information
{
	/* The volume device path
	 */
	uint8_t *device_path;

	/* The volume device path size
	 */
	uint32_t device_path_size;

	/* The volume creation time
	 */
	uint64_t creation_time;

	/* The volume serial number
	 */
	uint32_t serial_number;

	/* The number of files
	 */
	uint32_t number_of_files;

	/* The files array
	 */
	libcdata_array_t *files_array;
};

int libagdb_volume_information_initialize(
     libagdb_volume_information_t **volume_information,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_free(
     libagdb_volume_information_t **volume_information,
     libcerror_error_t **error );

int libagdb_internal_volume_information_free(
     libagdb_internal_volume_information_t **internal_volume_information,
     libcerror_error_t **error );

int libagdb_internal_volume_information_read_data(
     libagdb_internal_volume_information_t *internal_volume_information,
     libagdb_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libagdb_internal_volume_information_read_device_path_data(
     libagdb_internal_volume_information_t *internal_volume_information,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

ssize64_t libagdb_internal_volume_information_read_file_io_handle(
           libagdb_internal_volume_information_t *internal_volume_information,
           libagdb_io_handle_t *io_handle,
           libfdata_stream_t *data_stream,
           libbfio_handle_t *file_io_handle,
           off64_t file_offset,
           uint32_t volume_index,
           libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_creation_time(
     libagdb_volume_information_t *volume_information,
     uint64_t *creation_time,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_serial_number(
     libagdb_volume_information_t *volume_information,
     uint32_t *serial_number,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_utf8_device_path_size(
     libagdb_volume_information_t *volume_information,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_utf8_device_path(
     libagdb_volume_information_t *volume_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_utf16_device_path_size(
     libagdb_volume_information_t *volume_information,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_utf16_device_path(
     libagdb_volume_information_t *volume_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_number_of_files(
     libagdb_volume_information_t *volume_information,
     int *number_of_files,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_file_information(
     libagdb_volume_information_t *volume_information,
     int file_index,
     libagdb_file_information_t **file_information,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_INTERNAL_VOLUME_INFORMATION_H ) */

