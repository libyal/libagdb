/*
 * File functions
 *
 * Copyright (C) 2014-2017, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBAGDB_FILE_H )
#define _LIBAGDB_FILE_H

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

#if defined( _MSC_VER ) || defined( __BORLANDC__ ) || defined( __MINGW32_VERSION ) || defined( __MINGW64_VERSION_MAJOR )

/* This inclusion is needed otherwise some linkers mess up exporting functions
 */
#include "libagdb_source_information.h"

#endif

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libagdb_internal_file libagdb_internal_file_t;

struct libagdb_internal_file
{
	/* The IO handle
	 */
	libagdb_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The compressed blocks list
	 */
	libfdata_list_t *compressed_blocks_list;

	/* The compressed blocks cache
	 */
	libfcache_cache_t *compressed_blocks_cache;

	/* The uncompressed data stream
	 */
	libfdata_stream_t *uncompressed_data_stream;

	/* The volumes array
	 */
	libcdata_array_t *volumes_array;

	/* The sources array
	 */
	libcdata_array_t *sources_array;
};

LIBAGDB_EXTERN \
int libagdb_file_initialize(
     libagdb_file_t **file,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_free(
     libagdb_file_t **file,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_signal_abort(
     libagdb_file_t *file,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_open(
     libagdb_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBAGDB_EXTERN \
int libagdb_file_open_wide(
     libagdb_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBAGDB_EXTERN \
int libagdb_file_open_file_io_handle(
     libagdb_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_close(
     libagdb_file_t *file,
     libcerror_error_t **error );

int libagdb_file_open_read(
     libagdb_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_get_number_of_volumes(
     libagdb_file_t *file,
     int *number_of_volumes,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_get_volume_information(
     libagdb_file_t *file,
     int volume_index,
     libagdb_volume_information_t **volume_information,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_get_number_of_sources(
     libagdb_file_t *file,
     int *number_of_sources,
     libcerror_error_t **error );

LIBAGDB_EXTERN \
int libagdb_file_get_source_information(
     libagdb_file_t *file,
     int source_index,
     libagdb_source_information_t **source_information,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBAGDB_FILE_H ) */

