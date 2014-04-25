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

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

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

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4a[ 4 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown4b[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown4c[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown5a[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown5b[ 2 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

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

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8b[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];
};

typedef struct agdb_file_information_64 agdb_file_information_64_t;

struct agdb_file_information_64
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4a[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4b[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5b[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];
};

typedef struct agdb_file_information_72 agdb_file_information_72_t;

struct agdb_file_information_72
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

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10b[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown11[ 8 ];
};

typedef struct agdb_file_information_88 agdb_file_information_88_t;

struct agdb_file_information_88
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4a[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4b[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4c[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5b[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown8a[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown8b[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown8c[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown8d[ 2 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown10[ 8 ];
};

typedef struct agdb_file_information_112 agdb_file_information_112_t;

struct agdb_file_information_112
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* The flags
	 * Consists of 4 bytes
	 */
	uint8_t flags[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4a[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4b[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown7[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8a[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8b[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown10[ 8 ];

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

