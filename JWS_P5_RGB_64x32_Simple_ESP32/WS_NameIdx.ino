/*=============================================
 * PROGMEM DATA
 ==============================================*/
  // sholatN 9 x 8 
   const char static sholatN_E[] PROGMEM = {"IMSK\0\0\0\0"
                                            "SBUH\0\0\0\0" 
                                            "TRBT\0\0\0\0"  
                                            "DUHA\0\0\0\0"   
                                            "DUHR\0\0\0\0"    
                                            "ASHR\0\0\0\0"   
                                            "MGRB\0\0\0\0"    
                                            "ISYA\0\0\0\0"
                                            "JUM'AT\0\0"
                                            };
  //h_month 12 x 11
  const char static h_month_E[] PROGMEM = { "Muharram\0\0\0" 
                                            "Shafar\0\0\0\0\0"    
                                            "Rab.Awal\0\0\0" 
                                            "Rab.Akhir\0\0" 
                                            "Jum.Awal\0\0\0"
                                            "Jum.Akhir\0\0" 
                                            "Rajab\0\0\0\0\0\0" 
                                            "Sya'ban\0\0\0\0" 
                                            "Ramadhan\0\0\0" 
                                            "Syawal\0\0\0\0\0" 
                                            "Dzulqa'dah\0" 
                                            "Dzulhijah\0\0"};
  //m_month 12 x 10
  const char static m_month_E[] PROGMEM = { "JAN\0"      
                                            "FEB\0"       
                                            "MAR\0" 
                                            "APR\0" 
                                            "MEI\0" 
                                            "JUN\0" 
                                            "JUL\0" 
                                            "AGS\0" 
                                            "SEP\0" 
                                            "OKT\0" 
                                            "NOV\0" 
                                            "DES\0"};
  //DayName 7 x 7                                        
  const char static DayName_E[] PROGMEM = { "AHAD\0\0\0"
                                            "SENIN\0\0"
                                            "SELASA\0" 
                                            "RABU\0\0\0" 
                                            "KAMIS\0\0" 
                                            "JUM'AT\0" 
                                            "SABTU\0\0"};
  //MT_Name 4 x 10
  const char static MT_Name_E[] PROGMEM = { "MASJID\0\0\0\0"   
                                            "MUSHOLLA\0\0"  
                                            "SURAU\0\0\0\0\0"
                                            "LANGGAR\0\0\0"};

  const char static HD_Puasa[] PROGMEM    = { 
                                            "MARI PUASA\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"   
                                            "SUDAHKAN KITA PUASA\0\0\0\0\0\0\0"  
                                            "MARI KITA PERBANYAK PUASA\0"
                                            "SELAMAT MENJALANKAN PUASA\0" 
                                            };
                                            
  const char static TY_Puasa[] PROGMEM    = {
                                            "SYAWAL\0\0\0\0\0\0\0"
                                            "SYA'BAN\0\0\0\0\0\0"
                                            "SENIN\0\0\0\0\0\0\0\0"
                                            "KAMIS\0\0\0\0\0\0\0\0"
                                            "TENGAH BULAN\0"
                                            "AROFAH\0\0\0\0\0\0\0"
                                            "DZULHIJAH\0\0\0\0"
                                            "TASU'A\0\0\0\0\0\0\0"
                                            "ASYURA\0\0\0\0\0\0\0"
                                            "RAMADHAN\0\0\0\0\0"  
                                            };
                                            
/*=============================================
// List fungsi Call Name off :
// 1. Header Puasa          : Header_Puasa(1-4)      
// 2. Sholat Name           : sholahN(integer 0-6)    0-Subuh 1-Terbit 2-Dhuha 3-Dzuhur 4-Ashar 5-Magrib 3-Isya
// 3. DayName               : DayName(1-7)            1-Minggu  .... 7-Sabtu
// 4. Hijriah Month Name    : drawGregDate(OutPut String)
// 5. Masehi Month Name     : drawHijrDate(OutPut String)
// 6. Masjid Name           : drawMasjidName(OutPut String)    depend on Masjid Tipe  1-Masjid 2-Musholla 3-Surau 4-Langgar
 ==============================================*/ 
char* msgPuasa(int hd, int ty) // get sholat name from EEPROM
    {
      static char output[50];
      char  hdBuff[26];
      int locLen = (hd-1)*26;
      memccpy_P(hdBuff,HD_Puasa+locLen  ,0,26);
      char  tyBuff[13];
      locLen = (ty-1)*13;
      memccpy_P(tyBuff,TY_Puasa+locLen  ,0,13);
      if(hd ==1)
        {sprintf(output,"%s %s ESOK HARI" ,hdBuff,tyBuff);}
      else
        {sprintf(output,"%s %s" ,hdBuff,tyBuff);}
      return output;
    }

char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      int locLen = number*8;
      memccpy_P(locBuff,sholatN_E+locLen  ,0,8);
      return locBuff;
    }

char * DayName(int number)  // get Day Name from EEPROM
    {
      static char  locBuff[7];
      int locLen = (number-1)*7;
      memccpy_P(locBuff,DayName_E+locLen  ,0,7);
      return locBuff;
    }

char * MonthName(int number)  // get  Month Name from EEPROM
    {
      static char  locBuff[4];
      int   locLen = (number-1)*4;
      memccpy_P(locBuff,m_month_E+locLen,0,4);
      return locBuff;
    }

char * drawDayDate()
  {
      char  locBuff[20];
      static char  out[30];
      int   locLen = (nowH.hM-1)*11;
      memccpy_P(locBuff,h_month_E+locLen,0,11);
      sprintf(out,"%s, %02d-%02d-%04d   %d %s %dH\0",DayName(daynow),now.day(),now.month(),now.year(),nowH.hD,locBuff,nowH.hY);
      return out;
  }

char *  drawMasjidName()
  {
      char  bufMN[75];
      static char  out[85];
      char  locBuff[10];
      int   locLen = (Prm.MT-1)*10;
      memccpy_P(locBuff,MT_Name_E+locLen  ,0,10);
      EEPROM.get(55,bufMN);
      sprintf(out,"%s %s\0",locBuff,bufMN);
      
      return out;
  }
 
char *  drawInfo(int addr)
  {
      static char  out[150];
      EEPROM.get(addr,out);
      return out;
  }
