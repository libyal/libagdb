/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBAGDB_IO_HANDLE_H )
#define _LIBAGDB_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const char *agdb_mem_file_signature_vista;
extern const char *agdb_mem_file_signature_win7;
extern const char *agdb_mam_file_signature_win8;

typedef struct libagdb_io_handle libagdb_io_handle_t;

struct libagdb_io_handle
{
	/* The file type
	 */
	uint8_t file_type;

	/* The file size
	 */
	size64_t file_size;

	/* The uncompressed data size
	 */
	uint32_t uncompressed_data_size;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int libagdb_io_handle_initialize(
     libagdb_io_handle_t **io_handle,
     libcerror_error_t **error );

int libagdb_io_handle_free(
     libagdb_io_handle_t **io_handle,
     libcerror_error_t **error );

int libagdb_io_handle_clear(
     libagdb_io_handle_t *io_handle,
     libcerror_error_t **error );

int libagdb_io_handle_read_compressed_file_header(
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libagdb_io_handle_read_compressed_blocks(
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_t *compressed_blocks_list,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

