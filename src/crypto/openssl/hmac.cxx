/*
  Copyright (C) 2005, 2004 Erik Eliasson, Johan Bilien

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */

/*
 * Authors: Erik Eliasson <eliasson@it.kth.se>
 *          Johan Bilien <jobi@via.ecp.fr>
 */

#include <openssl/hmac.h>
#include <crypto/openssl/hmac.h>

void hmac_sha1( uint8 * key, int32 key_length,
		const uint8* data, uint32 data_length,
		uint8* mac, int32* mac_length )
{
    HMAC( EVP_sha1(), key, key_length,
          data, data_length, mac,
          reinterpret_cast<uint32*>(mac_length) );
}

void hmac_sha1( uint8* key, int32 key_length,
		const uint8* data_chunks[],
		uint32 data_chunck_length[],
		uint8* mac, int32* mac_length ){
	HMAC_CTX ctx;
	HMAC_CTX_init( &ctx );
	HMAC_Init_ex( &ctx, key, key_length, EVP_sha1(), NULL );
	while( *data_chunks ){
		HMAC_Update( &ctx, *data_chunks, *data_chunck_length );
		data_chunks ++;
		data_chunck_length ++;
	}
        HMAC_Final( &ctx, mac, reinterpret_cast<uint32*>(mac_length) );
	HMAC_CTX_cleanup( &ctx );
}

