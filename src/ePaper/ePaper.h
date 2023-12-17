#define LILYGO_T5_V266

#include <GxEPD.h>
#include <GxDEPG0266BN/GxDEPG0266BN.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0266BN/GxDEPG0266BN.h>
#include <FS.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <boards.h>



namespace ePaper
{
    extern GxEPD_Class display;

    void init();
}