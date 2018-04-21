#include <AwtrixBroker.h>

String AwtrixBroker::doJob(String command,String payload){
        if (command== "bri"){
                BRIGHTNESS=payload.toInt();
                DisplayManager::getInstance().setBrightness(payload.toInt());
                return "ACK";
        } 

        if (command== "save"){
                AwtrixSettings::getInstance().saveSettings();
                return "ACK";
        }

        if (command==  "reset"){
                ESP.reset();
                return "ACK";
        }

        if (command==  "mood"){
                PET_MOOD=payload.toInt();
                return "ACK";
        }

        if (command==  "pongmove"){
                paddle=payload.toInt();
                return "ACK";  
        } 

        if (command==  "snakemove"){
                direction=payload.toInt();
                return "ACK";
        }

        if (command==  "text"){
                DisplayManager::getInstance().scrollText(payload);
                return "ACK";
        }

        if (command==  "next"){
                //ApplicationManager::getInstance().nextApplication();
                return "ACK";
        }

        if (command==  "game"){
                game=payload.toInt();
                return "ACK";  
        }

        if (command==  "gamemode"){
                gamemode=payload.toInt();
            
                return "ACK";
        }
        if (command==  "color"){
                long number = (long) strtol( &payload[1], NULL, 16);
                TEXT_COLOR_R = number >> 16;
                TEXT_COLOR_G = number >> 8 & 0xff;
                TEXT_COLOR_B = number & 0xff;
                DisplayManager::getInstance().setColor({TEXT_COLOR_R,TEXT_COLOR_G,TEXT_COLOR_B});
                return "ACK";
        }   

        if (command==  "settings"){
                if (payload=="get"){
                    return AwtrixSettings::getInstance().loadSettings(); 
                }else{
                    int str_len = payload.length() + 1; 
                    char char_array[str_len];
                    payload.toCharArray(char_array, str_len);
                    AwtrixSettings::getInstance().parseSettings(char_array);
                }
                return "ACK";     
        }
    
    return "ERROR";
        
}

    void AwtrixBroker::log(String msg){
        MQTT::getInstance().sendLog(msg);


    }