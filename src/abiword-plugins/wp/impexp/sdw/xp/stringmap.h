/* Abiword
 * Copyright (C) 2002 Christian Biesinger <cbiesinger@web.de>
 * Idea by Joaquín Cuenca Abela <cuenca@pacaterie.u-psud.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 */

/** @file
 * header file for stringmap */

#include "ut_pair.h"
#include "ut_map.h"

#ifndef STRINGMAP_H_
#define STRINGMAP_H_

/** Maps ints to UT_UCS4Char* and frees the latter on destruction */
class ABI_EXPORT StringMap {
	public:
		StringMap() {}
		/** Destructs StringMap by free'ing all elements */
		~StringMap() {
			UT_Map::Iterator end(mMap.end());
			for (UT_Map::Iterator it(mMap.begin()); it != end; ++it)
				free(const_cast<void*>(static_cast<const UT_Pair*>(it.value())->second()));

		}
		/** Inserts a new entry into the map.
		 * @param key An integer used to find the data later
		 * @param data The string which belongs to the integer.
		 * Must be freeable using free. 
		 * @throw std::bad_alloc if out of memory */
		void insert(UT_uint16 key, UT_UCS4Char* data) {
			mMap.insert(reinterpret_cast<UT_Map::key_t>(key), static_cast<UT_Map::data_t>(data));
		}
		/** Gets a string given its identifier
		 * @param key The identifier of the string
		 * @return The string, or NULL if not found */
		const UT_UCS4Char* find(UT_uint16 key) {
			UT_Map::Iterator it = mMap.find(reinterpret_cast<UT_Map::key_t>(key));
			if (it == mMap.end())
				return NULL;
			return static_cast<const UT_UCS4Char*>(static_cast<const UT_Pair*>(it.value())->second());
		}

	private:
		/** the map where the data is stored in */
		UT_Map mMap;
};


#endif
