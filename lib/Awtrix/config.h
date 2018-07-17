
#ifndef config_h
#define config_h

    extern int game;
    extern int gamemode;
    extern int paddle;
    extern int direction;

    extern int SHOW_IP_ON_BOOT;
    extern int AUTO_BRIGHTNESS;
    extern int BRIGHTNESS;
    extern int SHOW_WEEKDAY;
    extern int UTC_OFFSET;
    extern int BIG_TIME;
    extern int PET_MOOD;
    extern char TEXT_COLOR_R;
    extern char TEXT_COLOR_G;
    extern char TEXT_COLOR_B;
    extern int RAINBOW;
    extern int SCROLL_SPEED;
    extern int AUTO_UPDATE;
    extern int SOUND;

    extern int MATRIX_MODE;
    extern int ALEXA_ACTIVE;

    extern int SNAKE_ACTIVE;
    extern int PONG_ACTIVE; 
    extern int TIME_ACTIVE;
    extern int WEATHER_ACTIVE;
    extern int WEATHERHUM_ACTIVE;
    extern int PET_ACTIVE;
    extern int GOL_ACTIVE;
    extern int DHT_ACTIVE;
    extern int YT_ACTIVE;
    extern int FB_ACTIVE;
    extern int TWITTER_ACTIVE;
    extern int FIRE_ACTIVE;
    extern int MQTT_ACTIVE;
    extern int BLYNK_ACTIVE;
    extern int SETTINGS_FOUND;
    extern int APP_DURATION;

    extern int SLEEP_START_MIN;
    extern int SLEEP_START_HR;
    extern int SLEEP_STOP_MIN;
    extern int SLEEP_STOP_HR;
    extern int SLEEP_MODE;
    extern int SLEEP_MODE_ACTIVE;



    extern char* OWM_API_KEY;
    extern char* OWM_LOCATION;
    extern char* YT_API_KEY;
    extern char* YT_CHANNEL_ID;
    extern char* FB_API_URL;
    extern char* TWITTER_PROFILE;
    extern char* FINGERPRINT;
    extern char* MQTT_SERVER;
    extern int MQTT_PORT;
    extern char* MQTT_USERNAME;
    extern char* MQTT_PASSWORD;
    extern char* BLYNK_KEY;

#endif
