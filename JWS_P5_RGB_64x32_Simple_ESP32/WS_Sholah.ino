
void drawCentreString(const char *buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w=DWidth, h=DHeight;
    matrix.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    matrix.setCursor(x - w / 2, y);
    matrix.print(buf);
}

void drawAzzan(int DrawAdd)
  {
    
    
    // check RunSelector
    if(!dwDo(DrawAdd)) return;
    uint8_t           ct_limit =18;  //harus angka genap
    static uint8_t    ct;
    static uint32_t   lsRn;
    uint32_t          Tmr = millis();

    if((Tmr-lsRn) > 500 and ct <= ct_limit)
      {
       lsRn = Tmr;
        DoSwap = true; 
        ct++;
      }
       
        if((ct%2) == 0)
          {
              fType(4);
              //matrix.drawRect(0,0,64,16,matrix.Color333(7,0,7));
              matrix.setCursor(10,11);
              matrix.setTextColor(matrix.Color333(7,7,7),matrix.Color333(0,0,0));
//              matrix.print("ADZAN");
              drawCentreString("ADZAN",32,11);
            if(jumat) {
              fType(1);
//              matrix.setCursor(10,26);
              matrix.setTextColor(matrix.Color333(0,7,0),matrix.Color333(0,0,0));
//              matrix.print(sholatN(8));
              drawCentreString(sholatN(8),32,27);
              }
            else      {
              fType(4);
//              matrix.setCursor(10,26);
              matrix.setTextColor(matrix.Color333(7,0,0),matrix.Color333(0,0,0));
//              matrix.print(sholatN(SholatNow));
              drawCentreString(sholatN(SholatNow),32,27);             
              }
            Buzzer(1);
            
          }
        else 
          { Buzzer(0);}
    if ((Tmr-lsRn)>2000 and (ct > ct_limit))
      {dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);} 
       
  }


void drawIqomah(int DrawAdd)  // Countdown Iqomah (9 menit)
  {  
    // check RunSelector
    if(!dwDo(DrawAdd)) return;

    static uint32_t   lsRn;
    uint32_t          Tmr = millis();
    static int        ct;
    int               mnt, scd,cn_l ;
    char              locBuff[6];           
    
    cn_l  = (Iqomah[SholatNow]*60);

    if((Tmr-lsRn) > 1000 and ct <=cn_l)
      {
          lsRn = Tmr;        
          
                 
          if (ct> (cn_l-10)) Buzzer(1);   // Buzzer on 2 seccon before Iqomah
          ct++;
            
          
//          matrix.drawLine(10,0,10,16,matrix.Color333(0,7,0));
//          drawSmallTS(); 
          DoSwap = true;   
      }
          mnt = floor((cn_l-ct)/60); 
          scd = (cn_l-ct)%60;
          if(mnt>0) { matrix.setCursor(15,11+16); sprintf(locBuff,"%02d:%02d",mnt,scd);} 
          else    { matrix.setCursor(27,11+16); sprintf(locBuff,"%02d",scd);}          
          fType(4);
          warnaWaktu(4);
          matrix.print(locBuff);  
     if ((ct%2)== 0){
              matrix.setCursor(12,11);
              fType(4);
              matrix.setTextColor(matrix.Color333(7,0,0));
              matrix.print("IQOMAH");
              } else {
                matrix.setCursor(12,11);
                fType(4);
                matrix.setTextColor(matrix.Color333(0,7,0));
                matrix.print("IQOMAH");
                }
    if (ct > cn_l)
      {
       dwDone(DrawAdd);
       ct = 0;
       Buzzer(0);
      }    
  }


void drawSholat_S(int sNum,int c) // Box Sholah Time
  {
    char  BuffTime[10];
    char  BuffShol[7];
    float   stime   = sholatT[sNum];
    uint8_t shour   = floor(stime);
    uint8_t sminute = floor((stime-(float)shour)*60);
    uint8_t ssecond = floor((stime-(float)shour-(float)sminute/60)*3600);
    sprintf(BuffTime,"%02d:%02d",shour,sminute);
    matrix.setCursor(3,22);
    fType(1);
    warnaWaktu(3);
    matrix.print(sholatN(sNum));
    matrix.setCursor(33,22);
    fType(1);
    warnaWaktu(4);
    matrix.print(BuffTime);
    //drawLargeTS();
    DoSwap = true;        
  }


void drawSholat(int DrawAdd)
  { 
    if(!dwDo(DrawAdd)) return;
    static uint8_t    x;
    static uint8_t    s; // 0=in, 1=out
    static uint8_t    sNum; 
    static uint32_t   lsRn;
    uint32_t          Tmr = millis();
    uint8_t           c=30;
    uint8_t           first_sNum = 0; 
    int               DrawWd=DWidth - c; 
    String message;

    int    textX   = matrix.width(),
           textMin = sizeof(message) * -12,
           hue     = 0;
           textMin = message.length()* -12;
      if((Tmr-lsRn)<3000) 
      {
      
         drawSholat_S(sNum, c);
      }
      
      if((Tmr-lsRn)>2000) 
      {
        lsRn=Tmr;
        sNum++;
          } 
           if(sNum==8)   {sNum=0;}

    //matrix.drawLine(35,8,64,8,matrix.Color333(0,7,0));
//    matrix.writeFillRect(32,0,DrawWd/2-x,35,matrix.Color333(0,0,0));
//    matrix.writeFillRect(32+DrawWd/2+x,0,64,20,matrix.Color333(0,0,0));
  }

void drawSholat_S2(int sNum,int c) // Box Sholah Time
  {
    char  BuffTime[10];
    char  BuffShol[7];
    float   stime   = sholatT[sNum];
    uint8_t shour   = floor(stime);
    uint8_t sminute = floor((stime-(float)shour)*60);
    uint8_t ssecond = floor((stime-(float)shour-(float)sminute/60)*3600);
    sprintf(BuffTime,"%02d:%02d",shour,sminute);
    matrix.setCursor(37,6);
    fType(1);
    warnaWaktu(3);
    matrix.print(sholatN(sNum));
    matrix.setCursor(34,14);
    fType(1);
    warnaWaktu(4);
    matrix.print(BuffTime);
    //drawLargeTS();
    DoSwap = true;        
  }


void drawSholat2(int DrawAdd)
  { 
    if(!dwDo(DrawAdd)) return;
    static uint8_t    x;
    static uint8_t    s; // 0=in, 1=out
    static uint8_t    sNum; 
    static uint32_t   lsRn;
    uint32_t          Tmr = millis();
    uint8_t           c=30;
    uint8_t           first_sNum = 0; 
    int               DrawWd=DWidth - c; 
    String message;

    int    textX   = matrix.width(),
           textMin = sizeof(message) * -12,
           hue     = 0;
           textMin = message.length()* -12;
      if((Tmr-lsRn)<3000) 
      {
      
         drawSholat_S2(sNum, c);
      }
      
      if((Tmr-lsRn)>2000) 
      {
        lsRn=Tmr;
        sNum++;
          } 
           if(sNum==8)   {sNum=0;}

    //matrix.drawLine(35,8,64,8,matrix.Color333(0,7,0));
//    matrix.writeFillRect(32,0,DrawWd/2-x,35,matrix.Color333(0,0,0));
//    matrix.writeFillRect(32+DrawWd/2+x,0,64,20,matrix.Color333(0,0,0));
  }
