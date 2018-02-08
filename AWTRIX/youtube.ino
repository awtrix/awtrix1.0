bool yt;
static unsigned char maskyt[]={ 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
static unsigned char play[]={0x00,0x00,0x10,0x18,0x1c,0x18,0x10,0x00}; //Bitmap Playsymbol
static unsigned char rond[]={0x00,0x7e,0xff,0xff,0xff,0xff,0xff,0x7e}; // Bitmap Round Icon
const char* ytHost = "www.youtube.com";
String subCounter;
void getYTSubs(const char *channelId)
{

  WiFiClientSecure client;
  Serial.print("connecting to "); Serial.println(ytHost);
  if (!client.connect(ytHost, 443)) {
    Serial.println("connection failed");

  }
  client.print(String("GET /channel/") + String(channelId) +"/about HTTP/1.1\r\n" + "Host: " + ytHost + "\r\nConnection: close\r\n\r\n");
  int repeatCounter = 10;
  while (!client.available() && repeatCounter--) {
    Serial.println("Get SubCounter"); delay(300);
  }
  int idxS, idxE, statsFound = 0;
  while (client.connected() && client.available()) {
    String line = client.readStringUntil('\n');
    if(statsFound == 0) {
      statsFound = (line.indexOf("about-stats")>0);
    } else {
      idxS = line.indexOf("<b>");
      idxE = line.indexOf("</b>");
      subCounter = line.substring(idxS + 3, idxE);
      
     

      client.stop();
        break;
      }
    }
  }

  void showYT(){
     int i;
     i = subCounter.length()*7;
     for ( int x=MATRIX_WIDTH ; x >  -i ; x-- ) {
        matrix.clear();
        matrix.setCursor( x, 0 );
        matrix.print(subCounter);
        matrixBitmap8x8(maskyt,0,0,0);
        matrixBitmap8x8(rond,255,0,0);
        matrixBitmap8x8(play,255,255,255);
        matrix.show();
        delay(80);
    }
  }

