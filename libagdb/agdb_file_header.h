/*
 * The file header definition of a Windows SuperFetch database file
 *
 * Copyright (C) 2014-2015, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _AGDB_FILE_HEADER_H )
#define _AGDB_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct agdb_file_header agdb_file_header_t;

struct agdb_file_header
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* The header size
	 * Consists of 4 bytes
	 */
	uint8_t header_size[ 4 ];
};

typedef struct agdb_database_header agdb_database_header_t;

struct agdb_database_header
{
	/* The database type
	 * Consists of 4 bytes
	 */
	uint8_t database_type[ 4 ];

	/* The database parameters
	 * Consists of 36 bytes
	 */
	uint8_t database_parameters[ 36 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The number of files
	 * Consists of 4 bytes
	 */
	uint8_t number_of_files[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* The number of sources
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sources[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];
};

typedef struct agdb_database_header_116 agdb_database_header_116_t;

struct agdb_database_header_116
{
	/* The database type
	 * Consists of 4 bytes
	 */
	uint8_t database_type[ 4 ];

	/* The database parameters
	 * Consists of 36 bytes
	 */
	uint8_t database_parameters[ 36 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The number of files
	 * Consists of 4 bytes
	 */
	uint8_t number_of_files[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* The number of sources
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sources[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

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
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown11[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown12[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown13[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown14[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown15[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown16[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown17[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown18[ 4 ];
};

typedef struct agdb_database_header_228 agdb_database_header_228_t;

struct agdb_database_header_228
{
	/* The database type
	 * Consists of 4 bytes
	 */
	uint8_t database_type[ 4 ];

	/* The database parameters
	 * Consists of 36 bytes
	 */
	uint8_t database_parameters[ 36 ];

	/* The number of volumes
	 * Consists of 4 bytes
	 */
	uint8_t number_of_volumes[ 4 ];

	/* The number of files
	 * Consists of 4 bytes
	 */
	uint8_t number_of_files[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* The number of sources
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sources[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

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
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown11[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown12[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown13[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown14[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown15[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown16[ 4 ];

	/* Unknown
	 * Consists of 120 bytes
	 */
	uint8_t unknown17[ 120 ];
};

#if defined( __cplusplus )
}
#endif

#endif

