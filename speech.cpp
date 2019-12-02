#include "speech.h"

#include "globals.h"
#include "hardware.h"
#include "graphics.h"

GameInputs inputs;
Timer passedtime;

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();


/**
 * Erase the speech bubble.
 */
//static void erase_speech_bubble();


/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();



/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line( char* line);



void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 113 , 128, 93, WHITE);
    uLCD.filled_rectangle(0,    93, 128,  94, 0x8282ff); 
    uLCD.filled_rectangle(0,   113, 128, 112, 0x8282ff); 
    uLCD.filled_rectangle(0,    113,   1, 93, 0x8282ff);
    uLCD.filled_rectangle(128,  113, 126, 93, 0x8282ff); 
}


static void speech_bubble_wait()
{
    passedtime.start();
	int elapsedtime=0;
    int blink=0;
    while(inputs.b1 || !(elapsedtime > 300 && !inputs.b1))
    {
        inputs = read_inputs();
        elapsedtime = passedtime.read_ms();
        wait_ms(100);
        blink = !blink;
        if (blink) 
        	uLCD.filled_circle(120,121,4,0x66DDAA); //green blink
        else 
        	uLCD.filled_circle(120,121,4,BLACK);
        inputs = read_inputs();
    }

    uLCD.filled_circle(120,121,4,BLACK); //return to normal bar
    return;
}


void draw_speech_line( char* line)
{
    uLCD.color(BLACK);
    uLCD.textbackground_color(WHITE);
    const char* space = " ";
    int linelength = strlen(line);
    int i;
    while (*line)
    {
        uLCD.locate(1,12);
        i = 0;
        draw_speech_bubble();
        while (i<17 && *line) {
            if (i == 0) {
                if (*line == *space) {
                    i++;
                    line++;
                    continue;
                }
            }

            uLCD.printf("%c", *line);
            wait_ms(40);
            i++;
            line++;
        }
        if (!*line) 
            break;
        uLCD.locate(1,13);
        while(i<34 && *line) {
            if (i == 17) {
                if (*line == *space) {
                    i++;
                    line++;
                    continue;
                }
            }

            uLCD.printf("%c", *line);
            wait_ms(30);
            i++;
            line++;
        }
         speech_bubble_wait();

    }
}


void speech( char* line)
{
    draw_speech_bubble();
    draw_speech_line(line);
    draw_border();
}