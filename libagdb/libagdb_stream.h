/*
 * Section functions
 *
 * Copyright (c) 2014, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBAGDB_INTERNAL_STREAM_H )
#define _LIBAGDB_INTERNAL_STREAM_H

#include <common.h>
#include <types.h>

#include "libagdb_extern.h"
#include "libagdb_io_handle.h"
#include "libagdb_libbfio.h"
#include "libagdb_libcerror.h"
#include "libagdb_stream_descriptor.h"
#include "libagdb_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_internal_stream libagdb_internal_stream_t;

struct libagdb_internal_stream
{
	/* The IO handle
	 */
	libagdb_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The stream descriptor
	 */
	libagdb_stream_descriptor_t *stream_descriptor;
};

int libagdb_stream_initialize(
     libagdb_stream_t **stream,
     libagdb_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libagdb_stream_descriptor_t *stream_descriptor,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_free(
     libagdb_stream_t **stream,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_get_type(
     libagdb_stream_t *stream,
     uint32_t *type,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
ssize_t libagdb_stream_read_buffer(
         libagdb_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBAGDB_EXTERN \
ssize_t libagdb_stream_read_buffer_at_offset(
         libagdb_stream_t *stream,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBAGDB_EXTERN \
off64_t libagdb_stream_seek_offset(
         libagdb_stream_t *stream,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_get_offset(
     libagdb_stream_t *stream,
     off64_t *offset,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_get_size(
     libagdb_stream_t *stream,
     size64_t *size,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_get_start_offset(
     libagdb_stream_t *stream,
     off64_t *start_offset,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_stream_get_data_file_io_handle(
     libagdb_stream_t *stream,
     libbfio_handle_t **file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

