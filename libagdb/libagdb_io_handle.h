/*
 * Input/Output (IO) handle functions
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

#if !defined( _LIBAGDB_IO_HANDLE_H )
#define _LIBAGDB_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_libfcache.h"
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

	/* The uncompressed block size
	 */
	uint32_t uncompressed_block_size;

	/* The uncompressed data size
	 */
	uint32_t uncompressed_data_size;

	/* The database type
	 */
	uint32_t database_type;

	/* The volume information entry size
	 */
	uint32_t volume_information_entry_size;

	/* The file information entry size
	 */
	uint32_t file_information_entry_size;

	/* The source information entry size
	 */
	uint32_t source_information_entry_size;

	/* The file information sub entry type 1 size
	 */
	uint32_t file_information_sub_entry_type1_size;

	/* The file information sub entry type 2 size
	 */
	uint32_t file_information_sub_entry_type2_size;

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

int libagdb_io_handle_read_uncompressed_file_header(
     libagdb_io_handle_t *io_handle,
     libfdata_stream_t *uncompressed_data_stream,
     libbfio_handle_t *file_io_handle,
     off64_t *volumes_information_offset,
     uint32_t *number_of_volumes,
     uint32_t *number_of_sources,
     libcerror_error_t **error );

ssize_t libagdb_io_handle_read_segment_data(
         intptr_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags,
         uint8_t read_flags,
         libcerror_error_t **error );

off64_t libagdb_io_handle_seek_segment_offset(
         intptr_t *data_handle,
         intptr_t *file_io_handle,
         int segment_index,
         int segment_file_index,
         off64_t segment_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_IO_HANDLE_H ) */

