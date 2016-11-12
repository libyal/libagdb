/*
 * Library volume_information type testing program
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "agdb_test_libagdb.h"
#include "agdb_test_libcerror.h"
#include "agdb_test_macros.h"
#include "agdb_test_memory.h"
#include "agdb_test_unused.h"

#include "../libagdb/libagdb_volume_information.h"

#if defined( __GNUC__ )

/* Tests the libagdb_volume_information_initialize function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_initialize(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;

#if defined( HAVE_AGDB_TEST_MEMORY )
	int number_of_malloc_fail_tests                  = 1;
	int number_of_memset_fail_tests                  = 1;
	int test_number                                  = 0;
#endif

	/* Test regular cases
	 */
	result = libagdb_volume_information_initialize(
	          &volume_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        AGDB_TEST_ASSERT_IS_NOT_NULL(
         "volume_information",
         volume_information );

        AGDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libagdb_volume_information_free(
	          &volume_information,
	          &error );

	AGDB_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        AGDB_TEST_ASSERT_IS_NULL(
         "volume_information",
         volume_information );

        AGDB_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libagdb_volume_information_initialize(
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

	volume_information = (libagdb_volume_information_t *) 0x12345678UL;

	result = libagdb_volume_information_initialize(
	          &volume_information,
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

	volume_information = NULL;

#if defined( HAVE_AGDB_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libagdb_volume_information_initialize with malloc failing
		 */
		agdb_test_malloc_attempts_before_fail = test_number;

		result = libagdb_volume_information_initialize(
		          &volume_information,
		          &error );

		if( agdb_test_malloc_attempts_before_fail != -1 )
		{
			agdb_test_malloc_attempts_before_fail = -1;

			if( volume_information != NULL )
			{
				libagdb_volume_information_free(
				 &volume_information,
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
			 "volume_information",
			 volume_information );

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
		/* Test libagdb_volume_information_initialize with memset failing
		 */
		agdb_test_memset_attempts_before_fail = test_number;

		result = libagdb_volume_information_initialize(
		          &volume_information,
		          &error );

		if( agdb_test_memset_attempts_before_fail != -1 )
		{
			agdb_test_memset_attempts_before_fail = -1;

			if( volume_information != NULL )
			{
				libagdb_volume_information_free(
				 &volume_information,
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
			 "volume_information",
			 volume_information );

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
	if( volume_information != NULL )
	{
		libagdb_volume_information_free(
		 &volume_information,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

/* Tests the libagdb_volume_information_free function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libagdb_volume_information_free(
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

#if defined( __GNUC__ )

	AGDB_TEST_RUN(
	 "libagdb_volume_information_initialize",
	 agdb_test_volume_information_initialize );

#endif /* defined( __GNUC__ ) */

	AGDB_TEST_RUN(
	 "libagdb_volume_information_free",
	 agdb_test_volume_information_free );

#if defined( __GNUC__ )

	/* TODO: add tests for libagdb_volume_information_read */

#endif /* defined( __GNUC__ ) */

	/* TODO: add tests for libagdb_volume_information_get_creation_time */

	/* TODO: add tests for libagdb_volume_information_get_serial_number */

	/* TODO: add tests for libagdb_volume_information_get_utf8_device_path_size */

	/* TODO: add tests for libagdb_volume_information_get_utf8_device_path */

	/* TODO: add tests for libagdb_volume_information_get_utf16_device_path_size */

	/* TODO: add tests for libagdb_volume_information_get_utf16_device_path */

	/* TODO: add tests for libagdb_volume_information_get_number_of_files */

	/* TODO: add tests for libagdb_volume_information_get_file_information */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

