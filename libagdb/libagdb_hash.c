/*
 * Hash functions
 *
 * Copyright (C) 2014-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#include "libagdb_hash.h"
#include "libagdb_libcerror.h"

/* Calculates the hash of the data
 * Returns 1 if successful or -1 on error
 */
int libagdb_hash_calculate(
     uint32_t *hash_value,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libagdb_hash_calculate";
	size_t data_offset    = 0;
	uint32_t value_32bit  = 0;

	if( hash_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hash value.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	*hash_value = 0x00004cb2fUL;

	for( data_offset = 0;
	     ( data_offset + 8 ) < data_size;
	     data_offset += 8 )
	{
		value_32bit  = data[ data_offset + 1 ];
		value_32bit *= 0x25;
		value_32bit += data[ data_offset + 2 ];
		value_32bit *= 0x25;
		value_32bit += data[ data_offset + 3 ];
		value_32bit *= 0x25;
		value_32bit += data[ data_offset + 4 ];
		value_32bit *= 0x25;
		value_32bit += data[ data_offset + 5 ];
		value_32bit *= 0x25;
		value_32bit += data[ data_offset + 6 ];
		value_32bit *= 0x25;

		value_32bit += 0x1a617d0dUL * data[ data_offset ];

		*hash_value = value_32bit - ( 0x2fe8ed1fUL * *hash_value ) + data[ data_offset + 7 ];
	}
	while( data_offset < data_size )
	{
		 *hash_value *= 0x25;
		 *hash_value += data[ data_offset++ ];
	}
	return( 1 );
}

