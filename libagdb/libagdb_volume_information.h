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

#if !defined( _LIBAGDB_INTERNAL_VOLUME_INFORMATION_H )
#define _LIBAGDB_INTERNAL_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libagdb_extern.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcdata.h"
#include "libagdb_libcerror.h"
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
     libagdb_internal_volume_information_t **volume_information,
     libcerror_error_t **error );

ssize64_t libagdb_volume_information_read(
           libagdb_volume_information_t *volume_information,
           libfdata_stream_t *uncompressed_data_stream,
           libbfio_handle_t *file_io_handle,
           libagdb_io_handle_t *io_handle,
           off64_t file_offset,
           uint32_t volume_index,
           libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_volume_information_get_serial_number(
     libagdb_volume_information_t *volume_information,
     uint32_t *serial_number,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

