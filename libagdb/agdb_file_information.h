/*
 * The file information definitions of a Windows SuperFetch database file
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

#if !defined( _AGDB_FILE_INFORMATION_H )
#define _AGDB_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct agdb_file_information_36 agdb_file_information_36_t;

struct agdb_file_information_36
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];
};

typedef struct agdb_file_information_52 agdb_file_information_52_t;

struct agdb_file_information_52
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown8[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown9[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown10[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown11[ 2 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown12[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown13[ 4 ];
};

typedef struct agdb_file_information_56 agdb_file_information_56_t;

struct agdb_file_information_56
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown11[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown12[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown13[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif

