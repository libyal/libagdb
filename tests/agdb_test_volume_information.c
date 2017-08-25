/*
 * Library volume_information type test program
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

	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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
				libagdb_internal_volume_information_free(
				 (libagdb_internal_volume_information_t **) &volume_information,
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
				libagdb_internal_volume_information_free(
				 (libagdb_internal_volume_information_t **) &volume_information,
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
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
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

#if defined( __GNUC__ )

/* Tests the libagdb_volume_information_get_creation_time function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_creation_time(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	uint64_t creation_time                           = 0;
	int creation_time_is_set                         = 0;
	int result                                       = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_creation_time(
	          volume_information,
	          &creation_time,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	creation_time_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_creation_time(
	          NULL,
	          &creation_time,
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

	if( creation_time_is_set != 0 )
	{
		result = libagdb_volume_information_get_creation_time(
		          volume_information,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_serial_number function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_serial_number(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	uint32_t serial_number                           = 0;
	int result                                       = 0;
	int serial_number_is_set                         = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_serial_number(
	          volume_information,
	          &serial_number,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	serial_number_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_serial_number(
	          NULL,
	          &serial_number,
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

	if( serial_number_is_set != 0 )
	{
		result = libagdb_volume_information_get_serial_number(
		          volume_information,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_utf8_device_path_size function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_utf8_device_path_size(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	size_t utf8_device_path_size                     = 0;
	int result                                       = 0;
	int utf8_device_path_size_is_set                 = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_utf8_device_path_size(
	          volume_information,
	          &utf8_device_path_size,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_device_path_size_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_utf8_device_path_size(
	          NULL,
	          &utf8_device_path_size,
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

	if( utf8_device_path_size_is_set != 0 )
	{
		result = libagdb_volume_information_get_utf8_device_path_size(
		          volume_information,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_utf8_device_path function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_utf8_device_path(
     void )
{
	uint8_t utf8_device_path[ 512 ];

	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;
	int utf8_device_path_is_set                      = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_utf8_device_path(
	          volume_information,
	          utf8_device_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf8_device_path_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_utf8_device_path(
	          NULL,
	          utf8_device_path,
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

	if( utf8_device_path_is_set != 0 )
	{
		result = libagdb_volume_information_get_utf8_device_path(
		          volume_information,
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

		result = libagdb_volume_information_get_utf8_device_path(
		          volume_information,
		          utf8_device_path,
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

		result = libagdb_volume_information_get_utf8_device_path(
		          volume_information,
		          utf8_device_path,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_utf16_device_path_size function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_utf16_device_path_size(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	size_t utf16_device_path_size                    = 0;
	int result                                       = 0;
	int utf16_device_path_size_is_set                = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_utf16_device_path_size(
	          volume_information,
	          &utf16_device_path_size,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_device_path_size_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_utf16_device_path_size(
	          NULL,
	          &utf16_device_path_size,
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

	if( utf16_device_path_size_is_set != 0 )
	{
		result = libagdb_volume_information_get_utf16_device_path_size(
		          volume_information,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_utf16_device_path function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_utf16_device_path(
     void )
{
	uint16_t utf16_device_path[ 512 ];

	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	int result                                       = 0;
	int utf16_device_path_is_set                     = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_utf16_device_path(
	          volume_information,
	          utf16_device_path,
	          512,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	utf16_device_path_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_utf16_device_path(
	          NULL,
	          utf16_device_path,
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

	if( utf16_device_path_is_set != 0 )
	{
		result = libagdb_volume_information_get_utf16_device_path(
		          volume_information,
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

		result = libagdb_volume_information_get_utf16_device_path(
		          volume_information,
		          utf16_device_path,
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

		result = libagdb_volume_information_get_utf16_device_path(
		          volume_information,
		          utf16_device_path,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

/* Tests the libagdb_volume_information_get_number_of_files function
 * Returns 1 if successful or 0 if not
 */
int agdb_test_volume_information_get_number_of_files(
     void )
{
	libagdb_volume_information_t *volume_information = NULL;
	libcerror_error_t *error                         = NULL;
	int number_of_files                              = 0;
	int number_of_files_is_set                       = 0;
	int result                                       = 0;

	/* Initialize test
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

	/* Test regular cases
	 */
	result = libagdb_volume_information_get_number_of_files(
	          volume_information,
	          &number_of_files,
	          &error );

	AGDB_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	AGDB_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_files_is_set = result;

	/* Test error cases
	 */
	result = libagdb_volume_information_get_number_of_files(
	          NULL,
	          &number_of_files,
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

	if( number_of_files_is_set != 0 )
	{
		result = libagdb_volume_information_get_number_of_files(
		          volume_information,
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
	/* Clean up
	 */
	result = libagdb_internal_volume_information_free(
	          (libagdb_internal_volume_information_t **) &volume_information,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume_information != NULL )
	{
		libagdb_internal_volume_information_free(
		 (libagdb_internal_volume_information_t **) &volume_information,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) */

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

#if defined( __GNUC__ ) && defined( TODO )

	/* TODO: add tests for libagdb_volume_information_read */

	/* TODO: add tests for libagdb_volume_information_read_data */

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_creation_time",
	 agdb_test_volume_information_get_creation_time );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_serial_number",
	 agdb_test_volume_information_get_serial_number );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_utf8_device_path_size",
	 agdb_test_volume_information_get_utf8_device_path_size );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_utf8_device_path",
	 agdb_test_volume_information_get_utf8_device_path );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_utf16_device_path_size",
	 agdb_test_volume_information_get_utf16_device_path_size );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_utf16_device_path",
	 agdb_test_volume_information_get_utf16_device_path );

	AGDB_TEST_RUN(
	 "libagdb_volume_information_get_number_of_files",
	 agdb_test_volume_information_get_number_of_files );

	/* TODO: add tests for libagdb_volume_information_get_file_information */

#endif /* defined( __GNUC__ ) && defined( TODO ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

