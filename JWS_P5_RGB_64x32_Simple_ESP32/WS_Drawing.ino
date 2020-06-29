void drawGreg_DS()   //tanggal
  {  
  fType(0);
  matrix.setCursor(8, 31);
  warnaWaktu(1);
  if(now.day()<10) matrix.print(0, DEC);
  matrix.print(now.day(), DEC);
  matrix.print('-');
  
  warnaWaktu(2);
  if(now.month()<10) matrix.print(0, DEC);
  matrix.print(now.month(), DEC);
  matrix.print('-');
  
  warnaWaktu(3);
  if(now.year()<10) matrix.print(0, DEC);
  matrix.print(now.year(), DEC);
  //matrix.writeFillRect(0,0,32,16,0); //untuk menghapus
  DoSwap = true;
  }

void jamkecil(){
  static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    fType(0);
    warnaWaktu(1);
    matrix.setCursor(12, 11);
    if(now.hour()<10) matrix.print(0, DEC);
    matrix.print(now.hour(), DEC);
    matrix.print(':');

    warnaWaktu(2);
    if(now.minute()<10) matrix.print(0, DEC);
    matrix.print(now.minute(), DEC);
    matrix.print(':');

    warnaWaktu(3);
    matrix.setTextColor(matrix.Color333(7,7,0));    
    if(now.second()<10) matrix.print(0, DEC);
    matrix.print(now.second(), DEC);
    
    //matrix.writeFillRect(0,0,32,16,0); //untuk menghapus
    DoSwap = true;
}

void warnaWaktu(int x){
  if(x==1){ //berdasarkan Jam
    if(now.hour()<12){matrix.setTextColor (matrix .Color333 (0,7,0));} //Hijau
    if(now.hour()>12){matrix.setTextColor (matrix .Color333 (0,128,21));} //Biru
  }
  if(x==2){ //berdasarkan Menit
    if(now.minute()<30){matrix.setTextColor(matrix.Color333(7,0,7));} //Merah
    if(now.minute()>30) {matrix.setTextColor (matrix .Color333 (0,7,0));} //Hijau
  }
   if(x==3){ //berdasarkan Jam
    if(now.hour()<12){matrix.setTextColor (matrix .Color333 (0,128,21));} //Biru
    if(now.hour()>12){matrix.setTextColor(matrix.Color333(7,0,7));} //Merah
  }
   if(x==4){ //berdasarkan Menit
    if(now.minute()<30){matrix.setTextColor (matrix .Color333 (0,128,21));} //Biru
    if(now.minute()>30) {matrix.setTextColor (matrix .Color333 (0,7,0));} //Hijau
  }

}
void suhu(){
    char temp[2];
    sprintf(temp, "SUHU");
    fType(1);
    matrix.setCursor(37, 6);
    warnaWaktu(3);
    matrix.print("SUHU");
    
    matrix.setCursor(41, 14);
//    warnaWaktu(1);
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.print(uint8_t(Clock.getTemperature()), DEC);
    matrix.print("C");
}

void drawSmallTS()//jam kecil
  { 
    static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    fType(0);
    warnaWaktu(2);
    matrix.setCursor(0, 11);
    if(now.hour()<10) matrix.print(0, DEC);
    matrix.print(now.hour(), DEC);

    if (now.second() % 2 == 0) { //DOT
      warnaWaktu(1);
      matrix.setCursor(0, 20);
      if(now.minute()<10) matrix.print(0, DEC);
      matrix.print(now.minute(), DEC);
    } else {
     matrix.setTextColor(matrix.Color333(0,0,0));
      matrix.setCursor(0, 20);
      if(now.minute()<10) matrix.print(0, DEC);
      matrix.print(now.minute(), DEC);
    }
    
//    if(Tmr-lsRn<500) {
//     warnaWaktu(1);
//      matrix.setCursor(0, 20);
//      if(now.minute()<10) matrix.print(0, DEC);
//      matrix.print(now.minute(), DEC);}
//    if(Tmr-lsRn>1000) lsRn = Tmr;

    

   
    //matrix.fillCircle(0,0,13,16);
    DoSwap = true;
  }  

void drawLargeTS()//jam besar
  { 
     static uint16_t   lsRn;
    uint16_t          Tmr = millis();

    fType(4);
    warnaWaktu(1);
    matrix.setCursor(0, 10);
    if(now.hour()<10) matrix.print(0, DEC);
    matrix.print(now.hour(), DEC);

    warnaWaktu(2);
    matrix.setCursor(18, 10);
    if(now.minute()<10) matrix.print(0, DEC);
    matrix.print(now.minute(), DEC);

//    matrix.setTextSize  (1);
//    matrix.setCursor(20, 8);  
//    matrix.setTextColor(matrix.Color333(7,7,0));    
//    if(now.second()<10) matrix.print(0, DEC);
//    matrix.print(now.second(), DEC);

//   if(Tmr-lsRn<500) {
//       matrix.drawRect(15,5,2,2,matrix.Color333(7, 7, 7));
//      matrix.drawRect(15,9,2,2,matrix.Color333(7, 7, 7));}
//    if(Tmr-lsRn>1000) lsRn = Tmr;
    
    
    if (now.second() % 2 == 0) { //DOT
      matrix.drawRect(15,5,2,2,matrix.Color333(7, 7, 7));
      matrix.drawRect(15,9,2,2,matrix.Color333(7, 7, 7));
    } else {
      matrix.drawRect(15,5,2,2,matrix.Color333(0, 0, 0));
      matrix.drawRect(15,9,2,2,matrix.Color333(0, 0, 0));
    }
    //matrix.writeFillRect(0,0,32,16,0); //untuk menghapus
    DoSwap = true;
  }  
void blinkBlock(int DrawAdd)
  {
    // check RunSelector
    if(!dwDo(DrawAdd)) return;

    static uint32_t   lsRn;
    static uint16_t   ct, ct_l;
    int               mnt, scd;
    uint32_t          Tmr = millis();
    char              locBuff[6];

    if(jumat)       {ct_l = Prm.JM * 60;}
    else            {ct_l = Prm.SO * 60;}

     
    if((Tmr-lsRn)> 1000)
      {   lsRn=Tmr;
//          mnt = floor((ct_l-ct)/60); 
//          scd = (ct_l-ct)%60;
//          sprintf(locBuff,"%02d:%02d",mnt,scd);
//          //matrix.drawRect(0,0,64,32,matrix.Color333(0,7,0));
//          matrix.setCursor(1,21);
//          fType(2);
//          matrix.setTextColor(matrix.Color333(0,7,7));
//          matrix.print(locBuff);

       
        DoSwap = true; 
        ct++;
        }
         if((ct%2) == 0)
          { 
            matrix.writeFillRect(0, 0, 2, 2, matrix.Color333(7, 7, 7));
          }else{
            matrix.writeFillRect(0, 0, 2, 2, matrix.Color333(0, 0, 0));
          }
        
    if (ct> ct_l) 
      { dwDone(DrawAdd);
        azzan = false;
        jumat = false;
        ct = 0;
      }
  }

// =========================================
// Drawing Tools============================
// =========================================

boolean dwDo(int DrawAdd)
  { if (RunSel== DrawAdd) {return true;}
    else return false;}
  
void dwDone(int DrawAdd)
  { RunFinish = DrawAdd;
    RunSel = 0;}
/*   
void dwCtr(int x, int y,const char* Msg)
  { int   tw = matrix.length(Msg);
   // int   th = mxtrix.textHeight();
    int   c = int((DWidth-x-tw)/2);
    matrix.drawFilledRect(x+c-1,y,x+tw+c,y,0);
    matrix.print(x+c,y,Msg);
   }
*/

void Buzzer(uint8_t state)
  {
    if(state ==1 and Prm.BZ == 1)
      {digitalWrite(BUZZ, HIGH);}
    else 
      {digitalWrite(BUZZ, LOW);}
  }

void bz()
{
  static uint32_t   lsRn;
  static uint8_t    b;
  uint32_t          Tmr = millis();
  if (bzzz == 1) {
    lsRn = Tmr;
    bzzz = 0;
    b = 1;
  }
  if ((Tmr - lsRn) < 200)
  {
    //    lsRn = Tmr;
    Buzzer(1);
  } else {
    if (b == 1) {
      b = 0;
      Buzzer(0);
    }
  }
}

void fType(int x)
  {
    if(x==0) matrix.setFont (Font0);
    else if(x==1) matrix.setFont(Font1); 
    else if(x==2) matrix.setFont(Font2);
    else if(x==3) matrix.setFont(Font3); 
    else if(x==4) matrix.setFont(Font4);  
  }
