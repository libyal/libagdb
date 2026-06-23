/*
 * File header functions
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

#if !defined( _LIBAGDB_FILE_HEADER_H )
#define _LIBAGDB_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_file_header libagdb_file_header_t;

struct libagdb_file_header
{
	/* The size
	 */
	uint32_t size;

	/* The number of volumes
	 */
	uint32_t number_of_volumes;

	/* The number of sources
	 */
	uint32_t number_of_sources;
};

int libagdb_file_header_initialize(
     libagdb_file_header_t **file_header,
     libcerror_error_t **error );

int libagdb_file_header_free(
     libagdb_file_header_t **file_header,
     libcerror_error_t **error );

int libagdb_file_header_read_stream(
     libagdb_file_header_t *file_header,
     libagdb_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_FILE_HEADER_H ) */

