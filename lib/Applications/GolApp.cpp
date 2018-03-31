#include <GolApp.h>
#include <DisplayManager.h>



#define GAMEOFLIFE_SEEDS            (32 * 8 / 3,41)
#define GAMEOFLIFE_INTERVAL         500
#define GAMEOFLIFE_AUTORESET        20
#define GAMEOFLIFE_NEW              {0, 255, 0}
#define GAMEOFLIFE_OLD              {0, 0, 255}
byte numCells = 0;
byte prevCells = 0;
byte autoResetCount = 0;
bool gameOfLifeStatus[32][8] = {false};

bool isAlive(int x, int y) {
    if (x < 0) x += 32;
    if (x >= 32) x -= 32;
    if (y < 0) y += 8;
    if (y >= 8) y -= 8;
    return gameOfLifeStatus[x][y];
}

byte countNeighbours(int x, int y) {
    byte neighbours = 0;
    if (isAlive(x-1, y-1)) neighbours++;
    if (isAlive(x-1, y)) neighbours++;
    if (isAlive(x-1, y+1)) neighbours++;
    if (isAlive(x, y-1)) neighbours++;
    if (isAlive(x, y+1)) neighbours++;
    if (isAlive(x+1, y-1)) neighbours++;
    if (isAlive(x+1, y)) neighbours++;
    if (isAlive(x+1, y+1)) neighbours++;
    return neighbours;
}

void gameOfLifeInit() {
    byte x,y;
    byte index;
   

    numCells = 0;

    for (x=0; x<32; x++) {
        for (y=0; y<8; y++) {
            gameOfLifeStatus[x][y] = false;
        }
    }

    while (numCells < GAMEOFLIFE_SEEDS) {
        x = random(0, 32);
        y = random(0, 8);
        if (!gameOfLifeStatus[x][y]) {
            gameOfLifeStatus[x][y] = true;
             DisplayManager::getInstance().drawPixel(x, y, GAMEOFLIFE_NEW);
            numCells++;
        }
    }
     DisplayManager::getInstance().refresh();
}


void GolApp::render(DisplayManager& display) {
    byte x, y;
     
    unsigned int index;
    bool gameOfLifeNew[32][8] = {false};
    numCells = 0;
    for (x=0; x<32; x++) {
        for (y=0; y<8; y++) {

            byte neighbours = countNeighbours(x, y);
            bool living = isAlive(x, y);

            // a living cell
            if (living) {

                // keeps on living if 2-3 neighbours
                if (neighbours == 2 || neighbours == 3) {
                    display.drawPixel(x, y, GAMEOFLIFE_OLD);
                    gameOfLifeNew[x][y] = true;
                    numCells++;

                // else dies due to under/over-population
                } else {
                    // NOP
                }

            // a dead cell
            } else {

                // comes to life if 3 living neighbours
                if (neighbours == 3) {
                    display.drawPixel(x, y, GAMEOFLIFE_NEW);
                    gameOfLifeNew[x][y] = true;
                    numCells++;

                // else nothing
                } else {
                    // NOP
                }

            }
        }
    }
    delay(200);
    display.show();
    DisplayManager::getInstance().clear();

    if (numCells == prevCells) autoResetCount++;
    if (autoResetCount == GAMEOFLIFE_AUTORESET) {
        numCells = 0;
        autoResetCount = 0;
    }
    prevCells = numCells;
    if (numCells == 0) {
        gameOfLifeInit();
    } else {
        for (x=0; x<32; x++) {
            for (y=0; y<8; y++) {
                gameOfLifeStatus[x][y] = gameOfLifeNew[x][y];
            }
        }
    }
}

void GolApp::enable() {
    gameOfLifeInit();
}
