#include <graphx.h>
#include <ti/getcsc.h>


int main()
{
    gfx_Begin();
    while(os_GetCSC());
    return 0;
}
