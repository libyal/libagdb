/*
 * The source information definitions of a Windows SuperFetch database file
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

#if !defined( _AGDB_EXECUTABLE_INFORMATION_H )
#define _AGDB_EXECUTABLE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct agdb_source_information_60 agdb_source_information_60_t;

struct agdb_source_information_60
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

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
	 * Consists of 8 bytes
	 */
	uint8_t unknown6[ 8 ];

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
	 * Consists of 16 bytes
	 */
	uint8_t unknown11[ 16 ];
};

typedef struct agdb_source_information_88 agdb_source_information_88_t;

struct agdb_source_information_88
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown6[ 16 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown10[ 8 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown11[ 16 ];
};

typedef struct agdb_source_information_100 agdb_source_information_100_t;

struct agdb_source_information_100
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The name hash
	 * Consists of 4 bytes
	 */
	uint8_t name_hash[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 12 bytes
	 */
	uint8_t unknown5[ 12 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* The prefetch hash
	 * Consists of 4 bytes
	 */
	uint8_t prefetch_hash[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* The executable filename
	 * Consists of 16 bytes
	 */
	uint8_t executable_filename[ 16 ];

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

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown19[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown20[ 4 ];
};

typedef struct agdb_source_information_144 agdb_source_information_144_t;

struct agdb_source_information_144
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The name hash
	 * Consists of 8 bytes
	 */
	uint8_t name_hash[ 8 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 24 bytes
	 */
	uint8_t unknown5[ 24 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* The prefetch hash
	 * Consists of 8 bytes
	 */
	uint8_t prefetch_hash[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* The executable filename
	 * Consists of 16 bytes
	 */
	uint8_t executable_filename[ 16 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown11[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown12[ 8 ];

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

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown19[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown20[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _AGDB_EXECUTABLE_INFORMATION_H ) */

