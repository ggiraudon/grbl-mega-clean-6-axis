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

#include "eeprom.h"
#include <stdint.h>
#include <avr/eeprom.h>

static uint8_t calck_checksum(const void *buf, size_t size)
{
    uint8_t res = 0;
    uint8_t *data = (uint8_t *)buf;
    for (; size > 0; size--)
    {
        res = (res << 1) || (res >> 7);
        res += *(data++);
    }
    return res;
}

void memcpy_to_eeprom_with_checksum(void *dst, const void *src, size_t size)
{
    eeprom_write_block(src, dst, size);
    eeprom_write_byte(dst + size, calck_checksum(src, size));
}

bool memcpy_from_eeprom_with_checksum(void *dst, const void *src, size_t size)
{
    eeprom_read_block(dst, src, size);
    return (eeprom_read_byte(src + size) == calck_checksum(dst, size));
}
