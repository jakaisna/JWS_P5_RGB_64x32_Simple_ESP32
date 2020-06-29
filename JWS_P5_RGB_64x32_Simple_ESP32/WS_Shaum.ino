void check_puasa()
  {
    // hitung tanggal besok
    hijir_date tmrH = toHijri(now.year(),now.month(),now.day(),1); 
    ty_puasa = 0;
    // cek hari dilarang puasa
    if (  ((tmrH.hM == 12)  and   (tmrH.hD == 10)) or   // Idul Adha
          ((tmrH.hM == 12)  and   (tmrH.hD == 11)) or   // Hari Tarsik 1
          ((tmrH.hM == 12)  and   (tmrH.hD == 12)) or   // Hari Tarsik 2
          ((tmrH.hM == 12)  and   (tmrH.hD == 13)) or   // Hari Tarsik 3
          ((tmrH.hM == 10)  and   (tmrH.hD ==  1)) or   // Idul Fitri
          ((tmrH.hM ==  8)  and   (tmrH.hD == 29)) or   // Akhir bulan Sya'ban
          ((tmrH.hM ==  8)  and   (tmrH.hD == 30)))
        {
          ty_puasa = 0;
        }
    else 
        {
          if ((tmrH.hM == 10) and (tmrH.hD > 2))  // Bulan Syawal --> Puasa 6 Hari Sawal
            {
              ty_puasa = 1;  
              hd_puasa = 2;
            }
          if ((tmrH.hM == 8) and (tmrH.hD >= 1))  // Perbanyak puasa sunnah bulan Sya'ban
            {
              ty_puasa = 2;
              hd_puasa = 3;
            }  
        if(daynow== 1)  // Jika sekarang Minggu --> besok puasa Senin
            {
              ty_puasa = 3;
              hd_puasa = 1;
            }
        if(daynow== 4)  // Jika sekarang Rabu --> besok puasa Kamis
            {
              ty_puasa = 4;
              hd_puasa = 1;
            }
          if(tmrH.hD == 13 or tmrH.hD == 14 or tmrH.hD == 15)   // Puasa Tengah Bulan tgl 13,14,15
            {
              ty_puasa = 5;
              hd_puasa = 1;
            }
          if ((tmrH.hM == 12) and (tmrH.hD == 9))  // 9 Dzulhijah --> Puasa Arofah
            {
              ty_puasa = 6;
              hd_puasa = 1;
            }
          if ((tmrH.hM == 12) and (tmrH.hD < 9))  // 9 hari pertama Dzulhijah --> Puasa Awal Dzulhijah
            {
              ty_puasa = 7;
              hd_puasa = 1;
            }
          if ((tmrH.hM == 1) and (tmrH.hD == 9))  // 9 Muharram --> Puasa Arofah
            {
              ty_puasa = 8;
              hd_puasa = 1;
            }
          if ((tmrH.hM == 1) and (tmrH.hD == 10))  // 10 Muharram --> Puasa Asura
            {
              ty_puasa = 9;
              hd_puasa = 1;
            }
          if (tmrH.hM == 9)  // Puasa Ramadhan
            {
              ty_puasa = 10;
              hd_puasa = 4;
            }
        }
  }
