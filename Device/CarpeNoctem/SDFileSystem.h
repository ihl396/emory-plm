/* mbed Microcontroller Library - SDFileSystem
 * Copyright (c) 2008-2009, sford
 */

#ifndef SDFILESYSTEM_H
#define SDFILESYSTEM_H

#include "mbed.h"
#include "FATFileSystem.h"

/* Class: SDFileSystem
 *  Access the filesystem on an SD Card using SPI
 *
 * Example:
 * > SDFileSystem sd(p5, p6, p7, p12, "sd");
 * > 
 * > int main() {
 * >     FILE *fp = fopen("/sd/myfile.txt", "w");
 * >     fprintf(fp, "Hello World!\n");
 * >     fclose(fp);
 * > }
 */
class SDFileSystem : public FATFileSystem {
public:

	/* Constructor: SDFileSystem
	 *  Create the File System for accessing an SD Card using SPI
	 *
	 * Variables:
	 *  mosi - SPI mosi pin connected to SD Card
	 *  miso - SPI miso pin conencted to SD Card
	 *  sclk - SPI sclk pin connected to SD Card
	 *  cs   - DigitalOut pin used as SD Card chip select
   *  name - The name used to access the filesystem
	 */
	SDFileSystem(PinName mosi, PinName miso, PinName sclk, PinName cs, const char* name);
	virtual int disk_initialize();
	virtual int disk_write(const char *buffer, int block_number);
	virtual int disk_read(char *buffer, int block_number);	
	virtual int disk_status();
	virtual int disk_sync();
	virtual int disk_sectors();

protected:

	int _cmd(int cmd, int arg);
	int _read(char *buffer, int length);
	int _write(const char *buffer, int length);
	int _sd_sectors();
	int _sectors;
	
	SPI _spi;
	DigitalOut _cs;	 
};

#endif
