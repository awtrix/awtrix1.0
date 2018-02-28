// -----------------------------------------------------------------------------
// Game of Life
// -----------------------------------------------------------------------------


int pattern_size[] = {7, 22};

//--------------------------------------------------------------------------------
// CONFIGURATION
//--------------------------------------------------------------------------------

#define GAMEOFLIFE_SEEDS            (MATRIX_WIDTH * MATRIX_HEIGHT / 3,41)
#define GAMEOFLIFE_INTERVAL         500
#define GAMEOFLIFE_AUTORESET        50
#define GAMEOFLIFE_NEW              matrix.Color(0, 255, 0)
#define GAMEOFLIFE_OLD              matrix.Color(0, 0, 255)



bool isAlive(int x, int y) {
    if (x < 0) x += 32;
    if (x >= 32) x -= MATRIX_WIDTH;
    if (y < 0) y += 8;
    if (y >= 8) y -= MATRIX_HEIGHT;
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
   int k = 0;
  int row = 0;
  int column = 0;
  while (pattern_init[k] != '!') {
    if (pattern_init[k] == ',') {
      row++;
      k++;
      column = 0;
    }
    else if (pattern_init[k] == '.') {
      WORLD[row + 2][column + 4] = 0;
      k++;
      column ++;
    }
    else  {
      WORLD[row + 2][column + 4] = 1;
      k++;
      column ++;
    }
  }
}

void gameOfLifeStart() {


    gameOfLifeInit();

}

void gameOfLifeLoop() {
  
    Byte x, y;
    unsigned int index;
  
    

    bool gameOfLifeNew[32][8] = {false};

    numCells = 0;
    for (x=0; x<MATRIX_WIDTH; x++) {
        for (y=0; y<MATRIX_HEIGHT; y++) {

            Byte neighbours = countNeighbours(x, y);
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
