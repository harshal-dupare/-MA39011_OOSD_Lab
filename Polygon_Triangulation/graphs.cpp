#include <graphics.h>
#include<X11/Xlib.h>


int main() 
{ 
    // gm is Graphics mode which is 
    // a computer display mode that 
    // generates image using pixels. 
    // DETECT is a macro defined in 
    // "graphics.h" header file 
    XInitThreads();
    int gd = DETECT, gm; 
  	char driver[] = "";
    // initgraph initializes the 
    // graphics system by loading a 
    // graphics driver from disk 
    initgraph(&gd, &gm, driver); 
  
    // circle function 
    circle(250, 200, 50); 
  
    getch(); 
  
    // closegraph function closes the 
    // graphics mode and deallocates 
    // all memory allocated by 
    // graphics system . 
    closegraph(); 
  
    return 0; 
} 