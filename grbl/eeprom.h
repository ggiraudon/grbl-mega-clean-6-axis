/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdbool.h>
#include <stddef.h>

void memcpy_to_eeprom_with_checksum(void *dst, const void *src, size_t size);

bool memcpy_from_eeprom_with_checksum(void *dst, const void *src, size_t size);

#endif /* EEPROM_H_ */
