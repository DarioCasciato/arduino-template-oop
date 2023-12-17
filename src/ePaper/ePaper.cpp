# include <ePaper/ePaper.h>

#if defined(USING_SOFT_SPI)
GxIO_Class io(EPD_SCLK, EPD_MISO, EPD_MOSI,  EPD_CS, EPD_DC,  EPD_RSET);
#else
GxIO_Class io(SPI,  EPD_CS, EPD_DC,  EPD_RSET);
#endif

namespace
{
    void drawHelloWorld()
    {
        ePaper::display.setTextColor(GxEPD_BLACK);
        ePaper::display.setTextSize(2);
        ePaper::display.setRotation(0);
        ePaper::display.print("Hello World!");
        ePaper::display.print("\nFritig Again!");
    }
}

namespace ePaper
{
    GxEPD_Class display(io, /*RST=*/ EPD_RSET, /*BUSY=*/ EPD_BUSY); // default selection of (9), 7

    void init()
    {

        #if !defined(USING_SOFT_SPI)
        SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
        #endif
        display.init();
        display.eraseDisplay();
        // comment out next line to have no or minimal Adafruit_GFX code
        display.drawPaged(drawHelloWorld); // version for AVR using paged drawing, works also on other processors
    }
}
