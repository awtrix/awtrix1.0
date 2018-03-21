//------------------------------------------------------------------------------
// DEFAULT SETTINGS
//------------------------------------------------------------------------------
String  DEVICE=                  "Awtrix";
String  VERSION=                 "0.1";
bool    SHOW_IP_ON_BOOT=         true;
bool    SHOW_APP_COMMANDS=       true;
bool    ENABLE_HEARTBEAT=        false;
bool    AUTO_BRIGHTNESS=         false;
int     BRIGHTNESS=              150;
int     SCROLL_INTERVAL=         75;

//--------------------------------------------------------------------------------
// Time & Weather
//--------------------------------------------------------------------------------

int UTC_OFFSET=                 1;
bool IS_METRIC=                 true;

const char* WUNDERGRROUND_API_KEY=      "b9cd2ae34c2974b6";
const char* WUNDERGRROUND_LANGUAGE=     "DL";
const char* WUNDERGROUND_COUNTRY=       "DE";
const char* WUNDERGROUND_CITY=          "Maintal";
const char* WUNDERGROUND_ZMW_CODE=      "0000.2150.10348";
int    UPDATE_INTERVAL_SECS=       600;

//--------------------------------------------------------------------------------
// Virtual Pet
//--------------------------------------------------------------------------------

#define EYE_COLOR              matrix.Color(255, 255, 255) 


//--------------------------------------------------------------------------------
// MATRIX
//--------------------------------------------------------------------------------

#define MATRIX_PIN                 4
#define LDR_PIN                     A0
#define MATRIX_WIDTH                32
#define MATRIX_HEIGHT               8
#define MATRIX_MODE                 NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG
#define MATRIX_TYPE                 NEO_GRB + NEO_KHZ800


//--------------------------------------------------------------------------------
// BUTTON
//--------------------------------------------------------------------------------

#define BUTTTON_RESET_CONFIG        D3

// -----------------------------------------------------------------------------
// SOUND
// -----------------------------------------------------------------------------

#define BUZZER_PIN                  0

// -----------------------------------------------------------------------------
// YOUTUBE
// -----------------------------------------------------------------------------

const char* YTchannel = "UCFo2uTuDWU-klP58hE34iLg";   // YT user id

// -----------------------------------------------------------------------------
// MQTT
// -----------------------------------------------------------------------------

const char* mqttServer = "m14.cloudmqtt.com";
const int   mqttPort = 18422;
const char* mqttUser = "qhesfmkc";
const char* mqttPassword = "tIyVJka59iDw";





