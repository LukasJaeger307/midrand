/*
 * This file is part of midrand.
 * 
 * midrand is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * midrand is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Grave.  If not, see <http://www.gnu.org/licenses/>. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define MACHINE_ID_SIZE (16)
#define HEX_STRING_SIZE (MACHINE_ID_SIZE * 2 + 1)
#define HEX_STRING_LAST (MACHINE_ID_SIZE * 2)

int main(){
	// Seeding the random number generator
	srand(time(NULL));

	// Generating a new machine ID
	uint8_t machine_id[MACHINE_ID_SIZE] = {0};
	for (size_t i = 0; i < MACHINE_ID_SIZE; i++){
		machine_id[i] = (uint8_t) (rand() & 0xFF);
	}

	// Extrapolating the hex string
	uint8_t hex_string[HEX_STRING_SIZE] = {0};
	for (size_t i = 0; i < MACHINE_ID_SIZE; i++){
		snprintf(hex_string + i*2, 3, "%02x", machine_id[i]);
	}
	hex_string[HEX_STRING_LAST] = 0x0a;

	// Writing the hex string to a file
	FILE * file = fopen("/etc/machine-id", "w");
	if (file == NULL){
		printf("Could not open /etc/machine-id. You probably forgot to run midrand with sudo.\n");
		return 1;
	}

	if (fwrite(hex_string, sizeof(uint8_t), HEX_STRING_SIZE, file) != HEX_STRING_SIZE){
		printf("Writing to /etc/machine-id failed\n");
	}

	if (fclose(file) != 0){
		printf("Could not close file.\n");
		return 3;
	}
}
