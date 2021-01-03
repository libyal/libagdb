/*
 * Compressed block functions
 *
 * Copyright (C) 2014-2021, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBAGDB_COMPRESSED_BLOCK_H )
#define _LIBAGDB_COMPRESSED_BLOCK_H

#include <common.h>
#include <types.h>

#include "libagdb_io_handle.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfcache.h"
#include "libagdb_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_compressed_block libagdb_compressed_block_t;

struct libagdb_compressed_block
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int libagdb_compressed_block_initialize(
     libagdb_compressed_block_t **compressed_block,
     size_t data_size,
     libcerror_error_t **error );

int libagdb_compressed_block_free(
     libagdb_compressed_block_t **compressed_block,
     libcerror_error_t **error );

int libagdb_compressed_block_read(
     libagdb_compressed_block_t *compressed_block,
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t compressed_block_offset,
     size_t compressed_block_size,
     libcerror_error_t **error );

int libagdb_compressed_block_read_element_data(
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfcache_cache_t *cache,
     int element_file_index,
     off64_t compressed_block_offset,
     size64_t compressed_block_size,
     uint32_t compressed_block_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_COMPRESSED_BLOCK_H ) */

