static unsigned char WALogo[]={0x18,0x24,0x42,0x81,0x81,0x42,0xa4,0xd8};
static unsigned char phone[]={0x0,0x0,0x10,0x20,0x14,0x8,0x0,0x0 };
static unsigned char mask1[]={ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
static unsigned char FBF[]={0x7,0xf,0xc,0x1e,0x1e,0xc,0xc,0xc};


void doJob(char data[]){
  String dat;
  String command;
  String payload;
  dat = String(data);
  command = dat.substring(0,dat.indexOf("%"));
  payload = dat.substring(dat.indexOf("%")+1,dat.length());
  
  Serial.println("Command: " + command);
  Serial.println("Payload: " +payload);

  if (command == "settings"){
    if (payload=="get"){
      sendMSG(loadConfig());
      Serial.println("Send Config");
    }
    else if(payload=="D")
    {
      restoreSettings();
    }else{      
    int str_len = payload.length() + 1; 
    char char_array[str_len];
    payload.toCharArray(char_array, str_len);
    parsesettings(char_array);
    Serial.println("new Settings recieved");
  }
  }

   
  if (command == "gol"){
    if (payload == "on"){
      gameOfLifeStart();
   }
   if (payload == "off"){
     gameOfLifeStop();
   }
  }

    if (command == "pet"){
    if (payload == "on"){
      gameOfLifeStop();
      PET=true;
   }
   if (payload == "off"){
     PET=false;
   }
  }

      if (command == "mood"){
    PET_MOOD=payload.toInt();
   }

   if (command == "time"){
   if (payload == "on"){
      TIME=true;
    }
   }

   if (command == "bri"){
      BRIGHTNESS= payload.toInt();
   }

  if (command == "text"){
        NOTIFICATION=true;
    int i;
    i = payload.length()*7;
    Serial.println(payload.length());
     for ( int x=MATRIX_WIDTH ; x >  -i ; x-- ) {
        matrix.clear();
        matrix.setCursor( x, 0 );
        matrix.print(payload);
        matrix.show();
        delay(30);
    }
        NOTIFICATION=false;
  }

  if (command == "whatsapp"){
    NOTIFICATION=true;
    int i;
    i = payload.length()*7;
    Serial.println(payload.length());
     for ( int x=MATRIX_WIDTH ; x >  -i ; x-- ) {
        matrix.clear();
        matrix.setCursor( x, 0 );
        matrix.print(payload);
        matrixBitmap8x8(mask1,37,211,102);
        matrixBitmap8x8(WALogo,255,255,255);
        matrixBitmap8x8(phone,255,255,255);
        matrix.show();
        delay(30);
    }
       delay(200);
        matrix.fillScreen(0);
        matrix.show();
        NOTIFICATION=false;
  }

  if (command == "facebook"){
        NOTIFICATION=true;
    int i;
    i = payload.length()*7;
    Serial.println(payload.length());
     for ( int x=MATRIX_WIDTH ; x >  -i ; x-- ) {
        matrix.clear();
        matrix.setCursor( x, 0 );
        matrix.print(payload);
        matrixBitmap8x8(mask1,59,89,152);
        matrixBitmap8x8(FBF,155,155,155);
        matrix.show();
        delay(30);
    }
    delay(200);
        matrix.fillScreen(0);
        matrix.show();
            NOTIFICATION=false;
  }

   if (command == "color"){
    long number = (long) strtol( &payload[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xff;
    int b = number & 0xff;
    matrix.setTextColor(matrix.Color(r, g, b));
    matrix.show();
}

   if (command == "screen"){
    long number = (long) strtol( &payload[1], NULL, 16);
    int r = number >> 16;
    int g = number >> 8 & 0xff;
    int b = number & 0xff;
    matrix.fillScreen(matrix.Color(r,g,b));
    matrix.show();
}
}

