/*
 * Library compressed_file_header type test program
 *
 * Copyright (C) 2014-2024, Joachim Metz <joachim.metz@gmail.com>
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
#include "agdb_test_macros.h"
#include "agdb_test_memory.h"
#include "agdb_test_unused.h"

#include "../libagdb/libagdb_compressed_file_header.h"

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

/* Tests the libagdb_compressed_file_header_initialize function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_compressed_file_header_initialize(
     void )
{
	libagdb_compressed_file_header_t *compressed_file_header = NULL;
	libcerror_error_t *error                                 = NULL;
	int result                                               = 0;

#if defined( HAVE_AGDB_TEST_MEMORY )
	int number_of_malloc_fail_tests                          = 1;
	int number_of_memset_fail_tests                          = 1;
	int test_number                                          = 0;
#endif

	/* Test regular cases
	 */
	result = libagdb_compressed_file_header_initialize(
	          &compressed_file_header,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NOT_NULL(
	 "compressed_file_header",
	 compressed_file_header );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libagdb_compressed_file_header_free(
	          &compressed_file_header,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "compressed_file_header",
	 compressed_file_header );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libagdb_compressed_file_header_initialize(
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

	compressed_file_header = (libagdb_compressed_file_header_t *) 0x12345678UL;

	result = libagdb_compressed_file_header_initialize(
	          &compressed_file_header,
	          &error );

	compressed_file_header = NULL;

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
		/* Test libagdb_compressed_file_header_initialize with malloc failing
		 */
		agdb_test_malloc_attempts_before_fail = test_number;

		result = libagdb_compressed_file_header_initialize(
		          &compressed_file_header,
		          &error );

		if( agdb_test_malloc_attempts_before_fail != -1 )
		{
			agdb_test_malloc_attempts_before_fail = -1;

			if( compressed_file_header != NULL )
			{
				libagdb_compressed_file_header_free(
				 &compressed_file_header,
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
			 "compressed_file_header",
			 compressed_file_header );

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
		/* Test libagdb_compressed_file_header_initialize with memset failing
		 */
		agdb_test_memset_attempts_before_fail = test_number;

		result = libagdb_compressed_file_header_initialize(
		          &compressed_file_header,
		          &error );

		if( agdb_test_memset_attempts_before_fail != -1 )
		{
			agdb_test_memset_attempts_before_fail = -1;

			if( compressed_file_header != NULL )
			{
				libagdb_compressed_file_header_free(
				 &compressed_file_header,
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
			 "compressed_file_header",
			 compressed_file_header );

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
	if( compressed_file_header != NULL )
	{
		libagdb_compressed_file_header_free(
		 &compressed_file_header,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_compressed_file_header_free function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_compressed_file_header_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libagdb_compressed_file_header_free(
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
	AGDB_TEST_UNREFERENCED_PARAMETER( argc )
	AGDB_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT )

	AGDB_TEST_RUN(
	 "libagdb_compressed_file_header_initialize",
	 agdb_test_compressed_file_header_initialize );

	AGDB_TEST_RUN(
	 "libagdb_compressed_file_header_free",
	 agdb_test_compressed_file_header_free );

	/* TODO: add tests for libagdb_compressed_file_header_read_data */

	/* TODO: add tests for libagdb_compressed_file_header_read_file_io_handle */

#endif /* defined( __GNUC__ ) && !defined( LIBAGDB_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

