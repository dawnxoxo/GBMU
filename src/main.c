#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cpu.h"

void hex_dump(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

int main () {
    FILE *f = fopen("./ROMS/pokemon_red.gb", "r");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);  /* same as rewind(f); */

    char *rom_buffer = malloc(fsize);
    fread(rom_buffer, fsize, 1, f);
    fclose(f);


    //hex_dump(rom_buffer, fsize);

    free(rom_buffer);
}