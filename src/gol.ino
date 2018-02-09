// -----------------------------------------------------------------------------
// Game of Life
// -----------------------------------------------------------------------------

Ticker gameOfLifeTicker;
byte numCells = 0;
byte prevCells = 0;
byte autoResetCount = 0;
bool gameOfLifeStatus[MATRIX_WIDTH][MATRIX_HEIGHT] = {false};

//--------------------------------------------------------------------------------
// CONFIGURATION
//--------------------------------------------------------------------------------

#define GAMEOFLIFE_SEEDS            (MATRIX_WIDTH * MATRIX_HEIGHT / 3,41)
#define GAMEOFLIFE_INTERVAL         500
#define GAMEOFLIFE_AUTORESET        50
#define GAMEOFLIFE_NEW              matrix.Color(0, 255, 0)
#define GAMEOFLIFE_OLD              matrix.Color(0, 0, 255)

bool isAlive(int x, int y) {
    if (x < 0) x += MATRIX_WIDTH;
    if (x >= MATRIX_WIDTH) x -= MATRIX_WIDTH;
    if (y < 0) y += MATRIX_HEIGHT;
    if (y >= MATRIX_HEIGHT) y -= MATRIX_HEIGHT;
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
    matrixClear();

    numCells = 0;

    for (x=0; x<MATRIX_WIDTH; x++) {
        for (y=0; y<MATRIX_HEIGHT; y++) {
            gameOfLifeStatus[x][y] = false;
        }
    }

    while (numCells < GAMEOFLIFE_SEEDS) {

        x = random(0, MATRIX_WIDTH);
        y = random(0, MATRIX_HEIGHT);
        if (!gameOfLifeStatus[x][y]) {
            gameOfLifeStatus[x][y] = true;
            matrix.drawPixel(x, y, GAMEOFLIFE_NEW);
            numCells++;
        }

    }

    matrixRefresh();
}

void gameOfLifeStart() {
    PET=false;
    GOL=true;
    gameOfLifeInit();
    gameOfLifeTicker.attach_ms(GAMEOFLIFE_INTERVAL, gameOfLifeLoop);
}

void gameOfLifeLoop() {
    if (NOTIFICATION) return;
    byte x, y;
    unsigned int index;
  
    matrix.clear();

    bool gameOfLifeNew[MATRIX_WIDTH][MATRIX_HEIGHT] = {false};

    numCells = 0;
    for (x=0; x<MATRIX_WIDTH; x++) {
        for (y=0; y<MATRIX_HEIGHT; y++) {

            byte neighbours = countNeighbours(x, y);
            bool living = isAlive(x, y);

            // a living cell
            if (living) {

                // keeps on living if 2-3 neighbours
                if (neighbours == 2 || neighbours == 3) {
                    matrix.drawPixel(x, y, GAMEOFLIFE_OLD);
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
                    matrix.drawPixel(x, y, GAMEOFLIFE_NEW);
                    gameOfLifeNew[x][y] = true;
                    numCells++;

                // else nothing
                } else {
                    // NOP
                }

            }
        }
    }

    matrix.show();

    if (numCells == prevCells) autoResetCount++;
    if (autoResetCount == GAMEOFLIFE_AUTORESET) {
        numCells = 0;
        autoResetCount = 0;
    }
    prevCells = numCells;
    if (numCells == 0) {
        gameOfLifeInit();
    } else {
        for (x=0; x<MATRIX_WIDTH; x++) {
            for (y=0; y<MATRIX_HEIGHT; y++) {
                gameOfLifeStatus[x][y] = gameOfLifeNew[x][y];
            }
        }
    }
}

void gameOfLifeStop() {
    GOL=false;
    gameOfLifeTicker.detach();
    matrixClear();
}
