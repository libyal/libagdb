/*
 * File information functions
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

#if !defined( _LIBAGDB_INTERNAL_FILE_INFORMATION_H )
#define _LIBAGDB_INTERNAL_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#include "libagdb_extern.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"
#include "libagdb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_internal_file_information libagdb_internal_file_information_t;

struct libagdb_internal_file_information
{
	/* The file path
	 */
	uint8_t *path;

	/* The file path size
	 */
	uint32_t path_size;
};

int libagdb_file_information_initialize(
     libagdb_file_information_t **file_information,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_information_free(
     libagdb_file_information_t **file_information,
     libcerror_error_t **error );

int libagdb_internal_file_information_free(
     libagdb_internal_file_information_t **file_information,
     libcerror_error_t **error );

ssize_t libagdb_file_information_read(
         libagdb_file_information_t *file_information,
         libfdata_stream_t *uncompressed_data_stream,
         libbfio_handle_t *file_io_handle,
         libagdb_io_handle_t *io_handle,
         off64_t file_offset,
         uint32_t file_index,
         libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_information_get_utf8_path_size(
     libagdb_file_information_t *file_information,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_information_get_utf8_path(
     libagdb_file_information_t *file_information,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_information_get_utf16_path_size(
     libagdb_file_information_t *file_information,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_information_get_utf16_path(
     libagdb_file_information_t *file_information,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

