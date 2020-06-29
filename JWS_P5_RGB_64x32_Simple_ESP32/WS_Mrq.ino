void dwMrq(const char* msg, int Speed, int dDT, int DrawAdd)
{
  // check RunSelector
  static uint16_t   x ;
  if (!dwDo(DrawAdd)) return;
  if (reset_x != 0) {
    x = 0;
    reset_x = 0;
  }


  static uint32_t   lsRn;
  String message = msg;
  int    textX   = matrix.width(),
         textMin = sizeof(message) * -12,
         hue     = 0;
  textMin = message.length() * -12;
  int fullScroll = message.length() + (2.5 * DWidth);
  if (dDT == 1)fullScroll = message.length() + (2.5 * DWidth) + 64;
  uint32_t          Tmr = millis();
  if ((Tmr - lsRn) > Speed)
  { lsRn = Tmr;
    if (x < fullScroll) {
      ++x;
    }
    else {
      dwDone(DrawAdd);
      x = 0; return;
    }
    //    matrix.fillScreen(0);

    DoSwap = true;

  }
  if (dDT == 1)
  {
    // matrix.fillScreen(0);
    drawLargeTS();
    fType(1);
    matrix.setTextColor(matrix.Color333(7, 0, 0), matrix.Color333(0, 0, 0));
    matrix.setCursor(DWidth - x, 31);
    matrix.setTextWrap(false);
    matrix.print( msg);

    //matrix.writeFillRect(0,0,33,16,0);

    drawSholat(DrawAdd);
    suhu();
    //drawGreg_DS();
  }

  if (dDT == 2)
  {
    fType(4);
    matrix.setTextColor(matrix.Color333(7, 0, 0), matrix.Color333(0, 0, 0));
    matrix.setCursor(DWidth - x, 11 + 15);
    matrix.setTextWrap(false);

    matrix.print( msg);
    //         matrix.writeFillRect(0,0,12,16,0);
    //         matrix.drawLine(10,0,10,16,matrix.Color333(0,7,0));
    drawSholat2(DrawAdd);
    drawLargeTS();
    //         drawSmallTS();
    //         drawGreg_DS();
  }
}


