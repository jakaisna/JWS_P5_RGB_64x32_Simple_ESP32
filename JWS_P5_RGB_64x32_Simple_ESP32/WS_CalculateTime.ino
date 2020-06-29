//------------------------------------------
// Function calculate Pray Time
//------------------------------------------
/*Macro Function */
#define d2r(x) x*M_PI/180
#define r2d(x) x*180/M_PI

//Constanta 
    const float lunarY          = 354.367068f;

// Main Function
void sholatCal()
  {
    float EJD = E_Julian_date(now.year(),now.month(),now.day(),Prm.L_LO);
    float Decl=Dql(EJD);
    float EqOfTime=EqT(EJD);
    Pray_Time(Prm.L_TZ, Prm.L_LA, Prm.L_LO,Prm.L_AL,Decl, EqOfTime );
  }

//Julian Date at GMT mid day
float E_Julian_date(int Year,int Month,int Days,float Longitude) // juliant date - 2451545
  {

    if (Month <= 2)
      {
      Year -= 1;
      Month += 12;
      }

    float A = floor(((float)Year/100.0));

    float B = 2 - A + floor(A/4.0);

    float CLong = Longitude/(float)(15 * 24);
    float JD = floor(365.25 *(float)(Year+ 4716)) 
              - 2451545 
              + floor(30.6001 * (float)(Month + 1)) 
              + (float)Days + B 
              - 1524.5
              -CLong;
    return JD; 
  }

//Sun Declination 
float EqT(const float EJD) 
  {
    float g = fix_angle(357.529f + 0.98560028f* EJD);
    float q = fix_angle(280.459f + 0.98564736f* EJD);
    float L = fix_angle(q + 1.915* sin(d2r(g)) + 0.020* sin(d2r(2*g)));
    float e = (23.439f - 0.00000036f* EJD);

    float RA = r2d(atan2(cos(d2r(e))* sin(d2r(L)), cos(d2r(L))))/ 15;
    float Eq =(q/15-fix_hour(RA));
    return Eq;
 //   Ds = r2d(asin(sin(d2r(e))* sin(d2r(L))));  // declination of the Sun
  }
  
float Dql(float EJD) 
  {
    float g = fix_angle((357.529f + 0.98560028f* EJD));
    float q = fix_angle((280.459f + 0.98564736f* EJD));
    float L = fix_angle((q + 1.915f* sin(d2r(g)) + 0.020f* sin(d2r(2*g))));
    float e = (23.439f - 0.00000036f* EJD);

    float dd = r2d(asin(sin(d2r(e))* sin(d2r(L))));  // declination of the Sun
    return dd;
  }

float HourAngle( float Alfa, float Declination, float Latitude)
  {
     float rn =acos(
                      (-sin(d2r(Alfa))-sin(d2r(Latitude))*sin(d2r(Declination)))
                      /
                      (cos(d2r(Latitude))*cos(d2r(Declination)))
                     )/15;
     return r2d(rn);
  }

void Pray_Time(float TimeZone, float Latitude, float Longitude,float Altitude,float Declination, float EquationOfTime )
  { 
    // Dzuhur
    float BaseTime = fix_hour((float)12+TimeZone-(Longitude/15)-EquationOfTime);
    sholatT[4] = BaseTime + (float)Prm.IH/60 + (float)Prm.K4/60;

    // Ashr
    float alfa =r2d(-atan(1 / (1+tan(d2r(fabs(Latitude-Declination))))));
    float HA = HourAngle(alfa,Declination,Latitude);
    sholatT[5] = BaseTime + HA + (float)Prm.IH/60+ (float)Prm.K5/60;

    // Maghrib
    alfa = 0.8333f+0.0347f*sqrt(Altitude);
    HA = HourAngle(alfa,Declination,Latitude);
    sholatT[6] = BaseTime + HA + (float)Prm.IH/60+ (float)Prm.K6/60;

    // Terbit
    sholatT[2] = BaseTime - HA;

    // Isya
    HA = HourAngle((float)18,Declination,Latitude);
    sholatT[7] = BaseTime + HA + (float)Prm.IH/60+ (float)Prm.K7/60;

    // Shubuh
    HA = HourAngle((float)20,Declination,Latitude);
    sholatT[1] = BaseTime - HA + (float)Prm.IH/60+ (float)Prm.K1/60;
    // Imsak
    sholatT[0] = sholatT[1]-(float)10/60;  
    // Dhuha
    HA = HourAngle((float)-4.5,Declination,Latitude);
    sholatT[3] = BaseTime - HA;
  char buff[100];
  }

float fix_hour(float a)
  {
    a = a - (float)24.0 * floor(a / 24.0);
    a = a < 0.0 ? a + 24.0 : a;
    return a;
  }

float fix_angle(float a)
  {
    a = a - (float)360.0 * floor(a / 360.0);
    a = a < 0.0 ? a + 360.0 : a;
    return a;
  }  

//------------------------------------------
// Function calculate Hijriah Date
//------------------------------------------

long Days(uint16_t Y,uint8_t M,uint8_t D)
  {
    if (M < 3)
      { 
      Y -= 1; 
      M +=12;
      }
    Y = Y - 2000;
    long ndays= floor(365.25*Y)+floor(30.6001*(M + 1))+floor(Y/100)+floor(Y/400)+D+196;
    //long ndays= d1 + d2 - A + B + D + 196;
    return ndays;
  }

long DaysHijri(uint16_t Y,uint8_t M,uint8_t D)
  {
    Y = Y - 1420;   
    long hari = floor(29.5*M - 28.999)+floor(lunarY*Y)+D ;
    return hari;
  }
  
hijir_date toHijri(uint16_t Y, uint8_t M, uint8_t D,uint8_t cor) // core --> corection date today=0   yesterday=-1 tomorrow=1
  {
    hijir_date BuffDate;
    long nday = Days(Y, M, D)+ Prm.CH+ cor+1; //NEW
    
    long tahun = floor(nday/lunarY) + 1420;
    long bulan = 1;
    long harike = 1;
    while(DaysHijri(tahun, bulan, 1) <= nday){tahun++;};
    tahun--;
    while(DaysHijri(tahun, bulan, 1) <= nday){bulan++;};
    bulan--;
    harike = 1 + nday - DaysHijri(tahun, bulan, 1);
    if (bulan == 13){bulan = 12; harike += 29;};
    BuffDate.hD = harike;
    BuffDate.hM = bulan;
    BuffDate.hY = tahun;

    return BuffDate;
  }
