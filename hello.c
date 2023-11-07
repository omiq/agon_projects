#include <stdio.h>
#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

char screen[25][20];

int main(void)
{
	char k = ' ';
	int x, y, oldx, oldy;

	for(int r=0; r<25; r++) {
		for (int c=0; c<20; c++) {
			screen[r][c]=32;

		}

	}
	
//vdp_mode(3); - Doesn't work, send the characters instead!
	char mode[2] = {22,3};
	mos_puts(mode,2,0);
	vdp_clear_screen();

	// Try turning off flashing cursor (doesn't work, neither does the C library function)
	//char cursoff[3] = {23,1,0};
	//vdp_vdu_init();
	//mos_puts(cursoff,3,0);
	putch(23); putch(1); putch(0);

	

	// Get the screen dimensions (result is actually incorrect)
	vdp_set_text_colour(2);
	printf("Screen Dimensions: %d,%d\n\n",sysvar_scrCols,sysvar_scrRows);
	
	// Do our "game" 
	vdp_set_text_colour(3);

	k = 0;
	x = 0;
	y = 2;

	// Loop until the Esc key is pressed
	while (k!=27) {

		// Backup the "player" location
		oldx = x;
		oldy = y;

		// Check the key pressed
		k = inchar();
		switch (k)
		{
		case 'q':
			y--;
			break;
		case 'a':
			y++;
			break;
		case 'o':
			x--;
			break;
		case 'p':
			x++;
			break;
		
		// Otherwise keep going
		default:
			break;
		}

		// Check if walking into an obstacle
		if(screen[y][x]==32)
		{	
			// Blank space baby
			vdp_cursor_tab(y,x);
			putch(64); putch(8);
			screen[y][x]=64;
		}
		else
		{
			// Beep and hit reverse
			vdp_bell(); // Unfortunately does not work
			x = oldx;
			y = oldy;
		}

	}

	// Traditionally returning 0 means program worked
	// Non-zero would be an error code
	// Doesn't actually make any difference
	return 0;

}
