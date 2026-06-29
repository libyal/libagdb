/*
 * The file information definitions of a Windows SuperFetch database file
 *
 * Copyright (C) 2014-2026, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _AGDB_FILE_INFORMATION_H )
#define _AGDB_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct agdb_file_information_36_32bit agdb_file_information_36_32bit_t;

struct agdb_file_information_36_32bit
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
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

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

typedef struct agdb_file_information_48_32bit agdb_file_information_48_32bit_t;

struct agdb_file_information_48_32bit
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

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

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];
};

typedef struct agdb_file_information_52_32bit agdb_file_information_52_32bit_t;

struct agdb_file_information_52_32bit
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
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

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
};

typedef struct agdb_file_information_64_64bit agdb_file_information_64_64bit_t;

struct agdb_file_information_64_64bit
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
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

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
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];
};

typedef struct agdb_file_information_72_32bit agdb_file_information_72_32bit_t;

struct agdb_file_information_72_32bit
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
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

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
};

typedef struct agdb_file_information_80_64bit agdb_file_information_80_64bit_t;

struct agdb_file_information_80_64bit
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* The (file) path number of characters
	 * Consists of 4 bytes
	 */
	uint8_t path_number_of_characters[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown10[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];
};

typedef struct agdb_file_information_88_64bit agdb_file_information_88_64bit_t;

struct agdb_file_information_88_64bit
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
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

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
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];

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
};

typedef struct agdb_file_information_112_64bit agdb_file_information_112_64bit_t;

struct agdb_file_information_112_64bit
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
	uint8_t unknown3[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

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
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown8[ 8 ];

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

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown14[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _AGDB_FILE_INFORMATION_H ) */

