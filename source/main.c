/*
	Code borrowed and referenced from: hello-world, both-screen-text, colored-text, and read-controls examples by Aurelio Mannara
	
	Pixel-Painter homebrew made by 8BitWonder, This is a small project just to get my feet wet, in the end it should:
	
	- Make cursor move in the direction that input is equal to on bottom screen
	- If passes the top/bottom or left/right of screen frame then comes back on other side
	- Show controls and selected color and info on top screen
	- Be able to draw/erase on bottom screen
	- Controls:
	A = Toggle between Draw/Erase
	L/R = Cycle through colors
	D-Pad = Move cursor
	Start = Exit to homebrew menu

*/

#include <3ds.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	//Inervals : [0,29]
	int row = 15;
	//Intervals : [0,49(top)/39(bottom)]
	int column = 20;
	
	//Declare isDrawing, when true paint the selected color, otherwise paint black (erase)
	bool isDrawing = false;
	
	// Initialize services
	gfxInitDefault();
	
	//Declare printscreen for both screens
	PrintConsole topScreen, bottomScreen;

	//Initialize console for both screen
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	//Print out info on top screen
	consoleSelect(&topScreen);
	
	//Print out color layout
	int color = 0;
	printf("\x1b[29;3H\x1b[41m    \x1b[40m    \x1b[43m    \x1b[40m    \x1b[42m    \x1b[40m    \x1b[44m    \x1b[40m    \x1b[46m    \x1b[40m    \x1b[45m    ");
	printf("\x1b[40m");
	
	//Print out controls
	printf("\x1b[7;18HPixel-Painter");
	printf("\x1b[10;21HControls");
	printf("\x1b[12;11HL/R = Cycle color left/right");
	printf("\x1b[14;12HA = Toggle drawing/erasing");
	printf("\x1b[16;13HDPad = Cursor controller");
	printf("\x1b[18;14HStart = Exit to HBmenu");
	
	//Print out white frame on bottom screen
	consoleSelect(&bottomScreen);
	printf("\x1b[0;0H\x1b[47m                                        ");
	printf("\x1b[29;0H                                        ");
	int j = 1;
	while (j < 29)
	{
		printf("\x1b[%d;0H ", j);
		printf("\x1b[%d;39H ", j);
		j++;
	}
	
	// Main loop
	while (aptMainLoop())
	{
		int initRow = row;
		int initCol = column;
		
		//Print Current Co-ords in top left of top screen
		consoleSelect(&topScreen);
		printf("\x1b[40m\x1b[1;1H                                     ");
		printf("\x1b[1;1HCurrent coords: X:%d Y:%d", column-1, 28-row);
		printf("\x1b[1;27HColor:%d", color);
		printf("\x1b[1;45H     ");
		printf("\x1b[1;35HDrawing: %s", isDrawing ? "True" : "False");

		//Print current selected color
		printf("\x1b[26;3H                                            ");
		printf("\x1b[27;3H                                            ");
		printf("\x1b[28;3H                                            ");
		
		if (color == 0)
		{
			printf("\x1b[26;3H\x1b[41m    ");
			printf("\x1b[27;3H    ");
			printf("\x1b[28;3H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[41m");
		}
		if (color == 1)
		{
			printf("\x1b[26;11H\x1b[43m    ");
			printf("\x1b[27;11H    ");
			printf("\x1b[28;11H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[43m");
		}
		if (color == 2)
		{
			printf("\x1b[26;19H\x1b[42m    ");
			printf("\x1b[27;19H    ");
			printf("\x1b[28;19H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[42m");
		}
		if (color == 3)
		{
			printf("\x1b[26;27H\x1b[44m    ");
			printf("\x1b[27;27H    ");
			printf("\x1b[28;27H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[44m");
		}
		if (color == 4)
		{
			printf("\x1b[26;35H\x1b[46m    ");
			printf("\x1b[27;35H    ");
			printf("\x1b[28;35H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[46m");
		}
		if (color == 5)
		{
			printf("\x1b[26;43H\x1b[45m    ");
			printf("\x1b[27;43H    ");
			printf("\x1b[28;43H    ");
			
			//Switch bottom screen to current color
			consoleSelect(&bottomScreen);
			printf("\x1b[45m");
		}
		
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		
		if (kDown & KEY_START) break; //Break in order to return to hbmenu if start is pressed
		
		//Check if a key is pressed down
			int i;
			for (i = 0; i < 32; i++)
			{
				//Toggles isDrawing to true or false when A is pressed
				if (kDown & KEY_A)
				{	
					if (isDrawing)
					{
						isDrawing = false;
						break;
					}
					else
					{
						isDrawing = true;
						break;
					}
				}
				
				//Cycles color to right if R is pressed
				if (kDown & KEY_R)
				{
					color = (color + 1);
					if (color > 5)
					{
						color = 0;
						break;
					}
					break;
				}
				
				//Cycles color to left if L is pressed
				if (kDown & KEY_L)
				{
					color = (color - 1);
					if (color < 0)
					{
						color = 5;
						break;
					}
					break;
				}
				
				//Moves cursor down one if D-down is pressed
				if (kDown & KEY_DDOWN)
				{	
					//move cursor down one
					row++;
					
					//If cursor reaches border, reset to top so it doesn't shift
					if (row == 29) row = 1;
					
					//break out of for loop so that does not add 32
					break;
				}
				
				//Moves cursor up one if D-up is pressed
				if (kDown & KEY_DUP)
				{
					//Move cursor up one
					row--;
					
					//If cursor reaches border, reset to bottom so it doesn't shift
					if (row == 0) row = 28;
					
					//break out of for loop so that does not add 32
					break;
				}
				
				//Moves cursor left one if D-left is pressed
				if (kDown & KEY_DLEFT)
				{
					//Move cursor left one
					column--;
					
					//If cursor reaches border, reset to right so it doesn't shift
					if (column == 0) column = 38;
					
					//break out of for loop so that does not add 32
					break;
				}
				
				//Moves cursor right one if D-right is pressed
				if (kDown & KEY_DRIGHT)
				{
					//Move cursor right one
					column++;
					
					//If cursor reaches border, reset to left so it doesn't shift
					if (column == 39) column = 1;
					
					//break out of for loop so that does not add 32
					break;
				}	
			}
		
		//Print symbol at current co-ords
		//default to black (erase) if not drawing (isDrawing is false)
		if (!(isDrawing))
		{
			printf("\x1b[40m");
		}
		
		printf("\x1b[%d;%dH ", initRow, initCol);
		printf("\x1b[%d;%dH#", row, column);
		
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}
	
	//Close services
	gfxExit();
	return 0;	
}
