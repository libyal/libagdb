/*
 * The volume information definitions of a Windows SuperFetch database file
 *
 * Copyright (C) 2014-2018, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _AGDB_VOLUME_INFORMATION_H )
#define _AGDB_VOLUME_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct agdb_volume_information_56 agdb_volume_information_56_t;

struct agdb_volume_information_56
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The number of files
	 * Consists of 4 bytes
	 */
	uint8_t number_of_files[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* The (volume) creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* The (volume) serial number
	 * Consists of 4 bytes
	 */
	uint8_t serial_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* The (volume) device path number of characters
	 * Consists of 2 bytes
	 */
	uint8_t device_path_number_of_characters[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown7[ 2 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];
};

typedef struct agdb_volume_information_72 agdb_volume_information_72_t;

struct agdb_volume_information_72
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown2[ 8 ];

	/* The number of files
	 * Consists of 4 bytes
	 */
	uint8_t number_of_files[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

	/* The (volume) creation time
	 * Consists of 8 bytes
	 */
	uint8_t creation_time[ 8 ];

	/* The (volume) serial number
	 * Consists of 4 bytes
	 */
	uint8_t serial_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown5[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown6[ 8 ];

	/* The (volume) device path number of characters
	 * Consists of 2 bytes
	 */
	uint8_t device_path_number_of_characters[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown7[ 2 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _AGDB_VOLUME_INFORMATION_H ) */

