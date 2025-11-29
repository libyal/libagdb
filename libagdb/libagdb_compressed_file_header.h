/*
 * Compressed file header functions
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

#if !defined( _LIBAGDB_COMPRESSED_FILE_HEADER_H )
#define _LIBAGDB_COMPRESSED_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_compressed_file_header libagdb_compressed_file_header_t;

struct libagdb_compressed_file_header
{
	/* The file type
	 */
	uint8_t file_type;

	/* The file size
	 */
	size64_t file_size;

	/* The uncompressed block size
	 */
	uint32_t uncompressed_block_size;

	/* The uncompressed data size
	 */
	uint32_t uncompressed_data_size;
};

int libagdb_compressed_file_header_initialize(
     libagdb_compressed_file_header_t **compressed_file_header,
     libcerror_error_t **error );

int libagdb_compressed_file_header_free(
     libagdb_compressed_file_header_t **compressed_file_header,
     libcerror_error_t **error );

int libagdb_compressed_file_header_read_data(
     libagdb_compressed_file_header_t *compressed_file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libagdb_compressed_file_header_read_file_io_handle(
     libagdb_compressed_file_header_t *compressed_file_header,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_COMPRESSED_FILE_HEADER_H ) */

