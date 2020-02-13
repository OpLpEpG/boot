/*
 * dev.cpp
 *
 *  Created on: 29 џэт. 2019 у.
 *      Author: Oleg
 */
#include <dev.h>



#ifndef UNUSE_DEVROOT
dev_c* dev_root_c::devs[DEV_COUNT];
uint8_t dev_root_c::cnt;
#endif

#ifdef USE_ARDUINO_MAIN
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	  Setup();

	  dev_root_c::begin();

	  while (1)
	  {
		Loop();
	  }
}

#pragma GCC diagnostic pop
#endif


