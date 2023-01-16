/*
 * Library file_information type test program
 *
 * Copyright (C) 2014-2023, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "agdb_test_functions.h"
#include "agdb_test_libagdb.h"
#include "agdb_test_libbfio.h"
#include "agdb_test_libcerror.h"
#include "agdb_test_libfdata.h"
#include "agdb_test_macros.h"
#include "agdb_test_memory.h"
#include "agdb_test_unused.h"

#include "../libagdb/libagdb_file_information.h"
#include "../libagdb/libagdb_io_handle.h"

uint8_t agdb_test_file_information_data1[ 276 ] = {
	0x69, 0x1a, 0xf9, 0x02, 0xa6, 0xa7, 0x28, 0xa1, 0x01, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00,
	0xa8, 0x9a, 0xf9, 0x02, 0x04, 0x00, 0x00, 0x21, 0x00, 0x00, 0x80, 0x00, 0x9c, 0x01, 0x00, 0x00,
	0x60, 0x1a, 0xf9, 0x02, 0x68, 0x01, 0xc0, 0x00, 0x03, 0x00, 0x09, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x5c, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x44, 0x00, 0x4f, 0x00,
	0x57, 0x00, 0x53, 0x00, 0x5c, 0x00, 0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x53, 0x00, 0x58, 0x00,
	0x53, 0x00, 0x5c, 0x00, 0x46, 0x00, 0x49, 0x00, 0x4c, 0x00, 0x45, 0x00, 0x4d, 0x00, 0x41, 0x00,
	0x50, 0x00, 0x53, 0x00, 0x5c, 0x00, 0x50, 0x00, 0x52, 0x00, 0x4f, 0x00, 0x47, 0x00, 0x52, 0x00,
	0x41, 0x00, 0x4d, 0x00, 0x5f, 0x00, 0x46, 0x00, 0x49, 0x00, 0x4c, 0x00, 0x45, 0x00, 0x53, 0x00,
	0x5f, 0x00, 0x43, 0x00, 0x4f, 0x00, 0x4d, 0x00, 0x4d, 0x00, 0x4f, 0x00, 0x4e, 0x00, 0x5f, 0x00,
	0x46, 0x00, 0x49, 0x00, 0x4c, 0x00, 0x45, 0x00, 0x53, 0x00, 0x5f, 0x00, 0x4d, 0x00, 0x49, 0x00,
	0x43, 0x00, 0x52, 0x00, 0x4f, 0x00, 0x53, 0x00, 0x4f, 0x00, 0x46, 0x00, 0x54, 0x00, 0x5f, 0x00,
	0x53, 0x00, 0x48, 0x00, 0x41, 0x00, 0x52, 0x00, 0x45, 0x00, 0x44, 0x00, 0x5f, 0x00, 0x53, 0x00,
	0x54, 0x00, 0x41, 0x00, 0x54, 0x00, 0x49, 0x00, 0x4f, 0x00, 0x4e, 0x00, 0x45, 0x00, 0x52, 0x00,
	0x59, 0x00, 0x5f, 0x00, 0x33, 0x00, 0x46, 0x00, 0x36, 0x00, 0x43, 0x00, 0x32, 0x00, 0x31, 0x00,
	0x45, 0x00, 0x42, 0x00, 0x34, 0x00, 0x41, 0x00, 0x43, 0x00, 0x36, 0x00, 0x36, 0x00, 0x41, 0x00,
	0x35, 0x00, 0x36, 0x00, 0x2e, 0x00, 0x43, 0x00, 0x44, 0x00, 0x46, 0x00, 0x2d, 0x00, 0x4d, 0x00,
	0x53, 0x00, 0x00, 0x00, 0xc1, 0x29, 0xf7, 0x02, 0x81, 0x00, 0x00, 0x00, 0xaa, 0x01, 0x09, 0x01,
        0x0f, 0x00, 0x67, 0x06 };

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

/* Reads data from the current offset into a buffer
 * Callback for the compressed block descriptor data stream
 * Returns the number of bytes read or -1 on error
 */
ssize_t agdb_test_file_information_read_segment_data(
         intptr_t *data_handle AGDB_TEST_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index AGDB_TEST_ATTRIBUTE_UNUSED,
         int segment_file_index AGDB_TEST_ATTRIBUTE_UNUSED,
         uint8_t *segment_data,
         size_t segment_data_size,
         uint32_t segment_flags AGDB_TEST_ATTRIBUTE_UNUSED,
         uint8_t read_flags AGDB_TEST_ATTRIBUTE_UNUSED,
         libcerror_error_t **error )
{
	static char *function = "agdb_test_file_information_read_segment_data";
	ssize_t read_count    = 0;

	AGDB_TEST_UNREFERENCED_PARAMETER( data_handle )
	AGDB_TEST_UNREFERENCED_PARAMETER( segment_index )
	AGDB_TEST_UNREFERENCED_PARAMETER( segment_file_index )
	AGDB_TEST_UNREFERENCED_PARAMETER( segment_flags )
	AGDB_TEST_UNREFERENCED_PARAMETER( read_flags )

	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              segment_data,
	              segment_data_size,
	              error );

	if( read_count != (ssize_t) segment_data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read segment data.",
		 function );

		return( -1 );
	}
	return( read_count );
}

/* Seeks a certain offset of the data
 * Callback for the cluster block stream
 * Returns the offset if seek is successful or -1 on error
 */
off64_t agdb_test_file_information_seek_segment_offset(
         intptr_t *data_handle AGDB_TEST_ATTRIBUTE_UNUSED,
         libbfio_handle_t *file_io_handle,
         int segment_index AGDB_TEST_ATTRIBUTE_UNUSED,
         int segment_file_index AGDB_TEST_ATTRIBUTE_UNUSED,
         off64_t segment_offset,
         libcerror_error_t **error )
{
	static char *function = "agdb_test_file_information_seek_segment_offset";

	AGDB_TEST_UNREFERENCED_PARAMETER( data_handle )
	AGDB_TEST_UNREFERENCED_PARAMETER( segment_index )
	AGDB_TEST_UNREFERENCED_PARAMETER( segment_file_index )

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     segment_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek segment offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 segment_offset,
		 segment_offset );

		return( -1 );
	}
	return( segment_offset );
}

/* Tests the libagdb_file_information_initialize function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_initialize(
     void )
{
	libagdb_file_information_t *file_information = NULL;
	libcerror_error_t *error                     = NULL;
	int result                                   = 0;

#if defined( HAVE_AGDB_TEST_MEMORY )
	int number_of_malloc_fail_tests              = 1;
	int number_of_memset_fail_tests              = 1;
	int test_number                              = 0;
#endif

	/* Test regular cases
	 */
	result = libagdb_file_information_initialize(
	          &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_internal_file_information_free(
	          (libagdb_internal_file_information_t **) &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libagdb_file_information_initialize(
	          NULL,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file_information = (libagdb_file_information_t *) 0x12345678UL;

	result = libagdb_file_information_initialize(
	          &file_information,
	          &error );

	file_information = NULL;

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_AGDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libagdb_file_information_initialize with malloc failing
		 */
		agdb_test_malloc_attempts_before_fail = test_number;

		result = libagdb_file_information_initialize(
		          &file_information,
		          &error );

		if( agdb_test_malloc_attempts_before_fail != -1 )
		{
			agdb_test_malloc_attempts_before_fail = -1;

			if( file_information != NULL )
			{
				libagdb_internal_file_information_free(
				 (libagdb_internal_file_information_t **) &file_information,
				 NULL );
			}
		}
		else
		{
			AGDB_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			AGDB_TEST_ASSERT_IS_NULL(
			 "file_information",
			 file_information );

			AGDB_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libagdb_file_information_initialize with memset failing
		 */
		agdb_test_memset_attempts_before_fail = test_number;

		result = libagdb_file_information_initialize(
		          &file_information,
		          &error );

		if( agdb_test_memset_attempts_before_fail != -1 )
		{
			agdb_test_memset_attempts_before_fail = -1;

			if( file_information != NULL )
			{
				libagdb_internal_file_information_free(
				 (libagdb_internal_file_information_t **) &file_information,
				 NULL );
			}
		}
		else
		{
			AGDB_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			AGDB_TEST_ASSERT_IS_NULL(
			 "file_information",
			 file_information );

			AGDB_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_AGDB_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_information != NULL )
	{
		libagdb_internal_file_information_free(
		 (libagdb_internal_file_information_t **) &file_information,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

/* Tests the libagdb_file_information_free function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libagdb_file_information_free(
	          NULL,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

/* Tests the libagdb_internal_file_information_free function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_internal_file_information_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libagdb_internal_file_information_free(
	          NULL,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libagdb_internal_file_information_read_data function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_internal_file_information_read_data(
     void )
{
	libagdb_file_information_t *file_information = NULL;
	libagdb_io_handle_t *io_handle               = NULL;
	libcerror_error_t *error                     = NULL;
	int result                                   = 0;

	/* Initialize test
	 */
	result = libagdb_io_handle_initialize(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->file_information_entry_size = 52;

	result = libagdb_file_information_initialize(
	          &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          io_handle,
	          agdb_test_file_information_data1,
	          52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libagdb_internal_file_information_read_data(
	          NULL,
	          io_handle,
	          agdb_test_file_information_data1,
	          52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          NULL,
	          agdb_test_file_information_data1,
	          52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          io_handle,
	          NULL,
	          52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          io_handle,
	          agdb_test_file_information_data1,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          io_handle,
	          agdb_test_file_information_data1,
	          0,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libagdb_internal_file_information_free(
	          (libagdb_internal_file_information_t **) &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_io_handle_free(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_information != NULL )
	{
		libagdb_internal_file_information_free(
	         (libagdb_internal_file_information_t **) &file_information,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libagdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_internal_file_information_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_internal_file_information_read_file_io_handle(
     void )
{
	libagdb_file_information_t *file_information = NULL;
	libagdb_io_handle_t *io_handle               = NULL;
	libbfio_handle_t *file_io_handle             = NULL;
	libcerror_error_t *error                     = NULL;
	libfdata_stream_t *data_stream               = NULL;
	ssize64_t read_count                         = 0;
	int element_index                            = 0;
	int result                                   = 0;

	/* Initialize test
	 */
	result = libagdb_io_handle_initialize(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->file_information_entry_size           = 52;
	io_handle->file_information_sub_entry_type1_size = 16;
	io_handle->file_information_sub_entry_type2_size = 20;

	result = libfdata_stream_initialize(
	          &data_stream,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          (ssize_t (*)(intptr_t *, intptr_t *, int, int, uint8_t *, size_t, uint32_t, uint8_t, libcerror_error_t **)) &agdb_test_file_information_read_segment_data,
	          NULL,
	          (off64_t (*)(intptr_t *, intptr_t *, int, int, off64_t, libcerror_error_t **)) &agdb_test_file_information_seek_segment_offset,
	          0,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "data_stream",
	 data_stream );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_append_segment(
	          data_stream,
	          &element_index,
	          0,
	          0,
	          276,
	          0,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_file_information_initialize(
	          &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = agdb_test_open_file_io_handle(
	          &file_io_handle,
	          agdb_test_file_information_data1,
	          276,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              io_handle,
	              data_stream,
	              file_io_handle,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) 276 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libagdb_internal_file_information_read_file_io_handle(
	              NULL,
	              io_handle,
	              data_stream,
	              file_io_handle,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              NULL,
	              data_stream,
	              file_io_handle,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              io_handle,
	              NULL,
	              file_io_handle,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              io_handle,
	              data_stream,
	              NULL,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              io_handle,
	              data_stream,
	              file_io_handle,
	              -1,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up file IO handle
	 */
	result = agdb_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test data too small
	 */
	result = agdb_test_open_file_io_handle(
	          &file_io_handle,
	          agdb_test_file_information_data1,
	          8,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	read_count = libagdb_internal_file_information_read_file_io_handle(
	              (libagdb_internal_file_information_t *) file_information,
	              io_handle,
	              data_stream,
	              file_io_handle,
	              0,
	              1,
	              &error );

	AGDB_TEST_ASSERT_EQUAL_INT64(
	 "read_count",
	 read_count,
	 (int64_t) -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = agdb_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libagdb_internal_file_information_free(
	          (libagdb_internal_file_information_t **) &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libfdata_stream_free(
	          &data_stream,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "data_stream",
	 data_stream );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_io_handle_free(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( file_information != NULL )
	{
		libagdb_internal_file_information_free(
		 (libagdb_internal_file_information_t **) &file_information,
		 NULL );
	}
	if( data_stream != NULL )
	{
		libfdata_stream_free(
		 &data_stream,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libagdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_file_information_get_utf8_path_size function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_get_utf8_path_size(
     libagdb_file_information_t *file_information )
{
	libcerror_error_t *error  = NULL;
	size_t utf8_path_size     = 0;
	int result                = 0;
	int utf8_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = libagdb_file_information_get_utf8_path_size(
	          file_information,
	          &utf8_path_size,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_path_size_is_set = result;

	/* Test error cases
	 */
	result = libagdb_file_information_get_utf8_path_size(
	          NULL,
	          &utf8_path_size,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_path_size_is_set != 0 )
	{
		result = libagdb_file_information_get_utf8_path_size(
		          file_information,
		          NULL,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libagdb_file_information_get_utf8_path function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_get_utf8_path(
     libagdb_file_information_t *file_information )
{
	uint8_t utf8_path[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;
	int utf8_path_is_set     = 0;

	/* Test regular cases
	 */
	result = libagdb_file_information_get_utf8_path(
	          file_information,
	          utf8_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_path_is_set = result;

	/* Test error cases
	 */
	result = libagdb_file_information_get_utf8_path(
	          NULL,
	          utf8_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf8_path_is_set != 0 )
	{
		result = libagdb_file_information_get_utf8_path(
		          file_information,
		          NULL,
		          512,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libagdb_file_information_get_utf8_path(
		          file_information,
		          utf8_path,
		          0,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libagdb_file_information_get_utf8_path(
		          file_information,
		          utf8_path,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libagdb_file_information_get_utf16_path_size function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_get_utf16_path_size(
     libagdb_file_information_t *file_information )
{
	libcerror_error_t *error   = NULL;
	size_t utf16_path_size     = 0;
	int result                 = 0;
	int utf16_path_size_is_set = 0;

	/* Test regular cases
	 */
	result = libagdb_file_information_get_utf16_path_size(
	          file_information,
	          &utf16_path_size,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_path_size_is_set = result;

	/* Test error cases
	 */
	result = libagdb_file_information_get_utf16_path_size(
	          NULL,
	          &utf16_path_size,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_path_size_is_set != 0 )
	{
		result = libagdb_file_information_get_utf16_path_size(
		          file_information,
		          NULL,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libagdb_file_information_get_utf16_path function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_file_information_get_utf16_path(
     libagdb_file_information_t *file_information )
{
	uint16_t utf16_path[ 512 ];

	libcerror_error_t *error = NULL;
	int result               = 0;
	int utf16_path_is_set    = 0;

	/* Test regular cases
	 */
	result = libagdb_file_information_get_utf16_path(
	          file_information,
	          utf16_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_path_is_set = result;

	/* Test error cases
	 */
	result = libagdb_file_information_get_utf16_path(
	          NULL,
	          utf16_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( utf16_path_is_set != 0 )
	{
		result = libagdb_file_information_get_utf16_path(
		          file_information,
		          NULL,
		          512,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libagdb_file_information_get_utf16_path(
		          file_information,
		          utf16_path,
		          0,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );

		result = libagdb_file_information_get_utf16_path(
		          file_information,
		          utf16_path,
		          (size_t) SSIZE_MAX + 1,
		          &error );

		AGDB_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		AGDB_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc AGDB_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] AGDB_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc AGDB_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] AGDB_TEST_ATTRIBUTE_UNUSED )
#endif
{
#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

	libagdb_file_information_t *file_information = NULL;
	libagdb_io_handle_t *io_handle               = NULL;
	libcerror_error_t *error                     = NULL;
	int result                                   = 0;

#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

	AGDB_TEST_UNREFERENCED_PARAMETER( argc )
	AGDB_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

	AGDB_TEST_RUN(
	 "libagdb_file_information_initialize",
	 agdb_test_file_information_initialize );

#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

	AGDB_TEST_RUN(
	 "libagdb_file_information_free",
	 agdb_test_file_information_free );

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

	AGDB_TEST_RUN(
	 "libagdb_internal_file_information_free",
	 agdb_test_internal_file_information_free );

	AGDB_TEST_RUN(
	 "libagdb_internal_file_information_read_data",
	 agdb_test_internal_file_information_read_data );

	AGDB_TEST_RUN(
	 "libagdb_internal_file_information_read_file_io_handle",
	 agdb_test_internal_file_information_read_file_io_handle );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize file_information for tests
	 */
	result = libagdb_io_handle_initialize(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	io_handle->file_information_entry_size = 52;

	result = libagdb_file_information_initialize(
	          &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_internal_file_information_read_data(
	          (libagdb_internal_file_information_t *) file_information,
	          io_handle,
	          agdb_test_file_information_data1,
	          52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_internal_file_information_read_path_data(
	          (libagdb_internal_file_information_t *) file_information,
	          &( agdb_test_file_information_data1[ 52 ] ),
	          276 - 52,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Run tests
	 */
	AGDB_TEST_RUN_WITH_ARGS(
	 "libagdb_file_information_get_utf8_path_size",
	 agdb_test_file_information_get_utf8_path_size,
	 file_information );

	AGDB_TEST_RUN_WITH_ARGS(
	 "libagdb_file_information_get_utf8_path",
	 agdb_test_file_information_get_utf8_path,
	 file_information );

	AGDB_TEST_RUN_WITH_ARGS(
	 "libagdb_file_information_get_utf16_path_size",
	 agdb_test_file_information_get_utf16_path_size,
	 file_information );

	AGDB_TEST_RUN_WITH_ARGS(
	 "libagdb_file_information_get_utf16_path",
	 agdb_test_file_information_get_utf16_path,
	 file_information );

	/* Clean up
	 */
	result = libagdb_internal_file_information_free(
	          (libagdb_internal_file_information_t **) &file_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "file_information",
	 file_information );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_io_handle_free(
	          &io_handle,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */
#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_information != NULL )
	{
		libagdb_internal_file_information_free(
		 (libagdb_internal_file_information_t **) &file_information,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libagdb_io_handle_free(
		 &io_handle,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

