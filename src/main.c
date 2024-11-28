#include <graphx.h>
#include <ti/getcsc.h>

//screen dimensions are 320, 240, with midpoint being 160, 120

void init()
{
    int cellsize = 25; // Size of each small cell
    int height = 8;    // Starting position (top-left corner)

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


int main()
{
    gfx_Begin();
    init();
    while(!os_GetCSC()){}
    gfx_End();
    return 0;
}
