#include <graphx.h>
#include <ti/getcsc.h>

//screen dimensions are 320, 240, with midpoint being 160, 120

const uint8_t cellsize = 26;

void init()
{
    uint8_t height = 4;    // Starting position (top-left corner)

    // Draw horizontal lines
    for (int i = height; i <= cellsize * 9 + height; i += cellsize)
    {
        // Check if this is a "big grid" line
        if ((i - height) % (cellsize * 3) == 0)
        {
            gfx_SetColor(224); // Red for big grid lines
        }
        else
        {
            gfx_SetColor(0); // Black for small grid lines
        }
        gfx_HorizLine_NoClip(height, i, cellsize * 9 + 1);
    }

    // Draw vertical lines
    for (int i = height; i <= cellsize * 9 + height; i += cellsize)
    {
        // Check if this is a "big grid" line
        if ((i - height) % (cellsize * 3) == 0)
        {
            gfx_SetColor(224); // Red for big grid lines
        }
        else
        {
            gfx_SetColor(0); // Black for small grid lines
        }
        gfx_VertLine_NoClip(i, height, cellsize * 9);
    }
}

void drawSymbol(char SymbolID, char arrX, int arrY){
    uint8_t X = (int)arrX*cellsize+4; //values derived by cellsize and height from init()
    uint8_t Y = arrY*cellsize+4;

    switch (SymbolID)
    {
    case '1':
        gfx_SetColor(17);
        gfx_Line_NoClip(X+1, Y+1, X+cellsize-1, Y+cellsize-1);
        gfx_Line_NoClip(X+1, Y+cellsize-1, X+cellsize-1, Y+1);
        break;
    case '2':
        gfx_SetColor(160);
        gfx_Circle_NoClip(X+cellsize/2, Y+cellsize/2, cellsize/2-1);
        break;
    
    default:
        gfx_SetColor(41);
        gfx_FillRectangle_NoClip(X+1, Y+1, cellsize-1, cellsize-1); 
        break;
    }
}

// Function to highlight the current big square
void highlightSquare(uint8_t *bigX, uint8_t *bigY) {
    gfx_SetColor(39); // Set color to yellow for the highlight
    gfx_Rectangle_NoClip(*bigX * cellsize*3 + 4, *bigY * cellsize*3 + 4, cellsize*3+1, cellsize*3+1); // Draw the border
}
void unhighlightSquare(uint8_t *bigX, uint8_t *bigY){
    gfx_BlitRectangle(gfx_buffer, *bigX * cellsize*3 + 4, *bigY * cellsize*3 + 4, cellsize*3+1, cellsize*3+1);
}


bool game(char GameGrid[][10], char *currSymbol, uint8_t *currBigSquare) {
    uint8_t key = os_GetCSC();

    if (key == sk_Clear) return true;
    // Function to highlight the current big square

    uint8_t bigX = *currBigSquare % 3;
    uint8_t bigY = *currBigSquare / 3;

    highlightSquare(&bigX, &bigY);

    int smallX = -1, smallY = -1;
    switch (key) {
        case sk_1: smallX = 0; smallY = 2; *currBigSquare = 6; break;
        case sk_2: smallX = 1; smallY = 2; *currBigSquare = 7; break;
        case sk_3: smallX = 2; smallY = 2; *currBigSquare = 8; break;
        case sk_4: smallX = 0; smallY = 1; *currBigSquare = 3; break;
        case sk_5: smallX = 1; smallY = 1; *currBigSquare = 4; break;
        case sk_6: smallX = 2; smallY = 1; *currBigSquare = 5; break;
        case sk_7: smallX = 0; smallY = 0; *currBigSquare = 0; break;
        case sk_8: smallX = 1; smallY = 0; *currBigSquare = 1; break;
        case sk_9: smallX = 2; smallY = 0; *currBigSquare = 2; break;
        default:
            // Optionally handle big square navigation here:
            // Use arrow keys or other keys to update *currBigSquare
            return false;
    }
    unhighlightSquare(&bigX, &bigY);

    if (smallX != -1 && smallY != -1) {
        uint8_t gridX = bigX * 3 + smallX;
        uint8_t gridY = bigY * 3 + smallY;

        if (GameGrid[gridY][gridX] == '0') {
            GameGrid[gridY][gridX] = *currSymbol;
            // Toggle between players
            *currSymbol = (*currSymbol == '1') ? '2' : '1';
        }
    }

    // Redraw symbols (unchanged logic)
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            if (GameGrid[y][x] != '0') {
                drawSymbol(GameGrid[y][x], x, y);
            }
        }
    }

    return false; // Continue the game
}

int main() {
    bool quit = false;

    // Define a 10x10 game grid
    char GameGrid[10][10];

    // Initialize the grid
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            GameGrid[i][j] = '0'; // Empty cell
        }
    }
    char currSymbol = '1';
    uint8_t currBigSquare = 0;
    // Main game loop
    gfx_Begin();
    gfx_SetDrawBuffer();
    init();
    gfx_SetDrawScreen();
    gfx_BlitBuffer();
    while (!quit) {
        quit = game(GameGrid, &currSymbol, &currBigSquare); // Pass the grid to the game function
    }

    gfx_End();
    return 0;
}