/*
 * OSS-Fuzz target for libagdb compressed block (de)compression
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

#include <stddef.h>
#include <stdint.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libagdb.h"
#include "ossfuzz_libbfio.h"

#include <libagdb_compressed_block.h>
#include <libagdb_io_handle.h>

int LLVMFuzzerTestOneInput(
      const uint8_t *data,
      size_t size )
{
	libbfio_handle_t *file_io_handle             = NULL;
	libagdb_compressed_block_t *compressed_block = NULL;
	libagdb_io_handle_t *io_handle               = NULL;
	uint32_t expected_data_size                  = 0;

	if( size < 6 )
	{
		return( 0 );
	}
	if( libagdb_io_handle_initialize(
	     &io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	/* The first byte of the input selects the compression algorithm:
	 * 0: LZNT1 ( compressed blocks of a Windows Vista AGDB file )
	 * 1: LZXpress Huffman ( compressed blocks of a Windows 7 AGDB file )
	 * 2: LZXpress Huffman ( compressed blocks of a Windows 8.0 AGDB file )
	 * 3: LZXpress Huffman ( compressed blocks of a Windows 8.1 AGDB file )
	 * The next four bytes are the size of the expected uncompressed data
	 * (little-endian) and the remainder is the compressed block.
	 */
	if( data[ 0 ] == 0 )
	{
		io_handle->file_type = LIBAGDB_FILE_TYPE_COMPRESSED_VISTA;
	}
	else if( data[ 0 ] == 1 )
	{
		io_handle->file_type = LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS7;
	}
	else if( data[ 0 ] == 2 )
	{
		io_handle->file_type = LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8_0;
	}
	else
	{
		io_handle->file_type = LIBAGDB_FILE_TYPE_COMPRESSED_WINDOWS8_1;
	}
	expected_data_size  = (uint32_t) data[ 1 ];
	expected_data_size |= ( (uint32_t) data[ 2 ] ) << 8;
	expected_data_size |= ( (uint32_t) data[ 3 ] ) << 16;
	expected_data_size |= ( (uint32_t) data[ 4 ] ) << 24;

	/* Limit the size to keep the allocation size within bounds
	 */
	if( expected_data_size > ( 8 * 1024 * 1024 ) )
	{
		expected_data_size = ( 8 * 1024 * 1024 );
	}
	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		goto on_error_io_handle;
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libbfio_handle_open(
	     file_io_handle,
	     LIBBFIO_OPEN_READ,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( libagdb_compressed_block_initialize(
	     &compressed_block,
	     expected_data_size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	libagdb_compressed_block_read(
	 compressed_block,
	 io_handle,
	 file_io_handle,
	 5,
	 size - 5,
	 NULL );
	libagdb_compressed_block_free(
	 &compressed_block,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

on_error_io_handle:
	libagdb_io_handle_free(
	 &io_handle,
	 NULL );

	return( 0 );
}

} /* extern "C" */
