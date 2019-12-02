#include "graphics.h"

#include "globals.h"



void draw_player(int u, int v, int key)
{
    char blueman[122] = "BBBLLLLLBBBBBBWTWTWBBBBBBWWWWWBBBBBBBW1WBBBBBBBBBWBBBBBBBBBTWTBBBBBBBTBTBTBBBBBBBBTBBBBBBBBBBTBBBBBBBBBTBTBBBBBBB2BBB2BBB";
    char blueman2[122] ="BBBLLLLLBBBBBBWWWWWBBBBBBWWWWWBBBBBBBWWWBBBBBBBBBWBBBBBBBBBTWTBBBBBBBTBTBTBBBBBBBBTBBBBBBBBBBTBBBBBBBBBTBTBBBBBBB2BBB2BBB";
    char blueman3[122] ="BBLLLLLBBBBBBBBWWTBBBBBBBBWWWBBBBBBBBWWWBBBBBBBBWW1BBBBBBBBBWBBBBBBBBBBTTTBBBBBBBBTBBBBBBBBBBTTBBBBBBBBBTBBBBBBBBB3B3BBBB";
    char blueman4[122] ="BBBBLLLLBBBBBBBTWWBBBBBBBBWWWBBBBBBBBWWWBBBBBBBB1WWBBBBBBBBBWBBBBBBBBTTTBBBBBBBBBBTBBBBBBBBBTTBBBBBBBBBBTBBBBBBBBB3B3BBBB";
    if (key==1) //down
    draw_img(u,v,blueman);
    if (key==2) //up
    draw_img(u,v,blueman2);
    if (key==3) //right
    draw_img(u,v,blueman3);
    if (key==4) //left
    draw_img(u,v,blueman4);
}

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
#define TEAL   0x008080
#define RED    0xFF0000
#define WHITE  0xFFFFFF
#define BLACK  0x000000 
#define GOLD   0xD4AF37
#define LBLUE  0xADD8E6
#define AQUA   0x66DDAA
#define ORANGE 0xFF4500
#define MAROON 0x8B0000
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'L') colors[i] = LBLUE;
        else if (img[i] == '1') colors[i] = GOLD;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '2') colors[i] = BROWN;
        else if (img[i] == 'B') colors[i] = BLACK;
        else if (img[i] == 'T') colors[i] = TEAL;
        else if (img[i] == 'A') colors[i] = AQUA;
        else if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'M') colors[i] = MAROON;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'O') colors[i] = ORANGE;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}
void draw_red_wall(int u, int v)
{
    char wall[122]="MMMMOMMMMMMMOOMOMMMMOMMMMMOMMMMOMMMMMMMMMMOMMMMMMOOMMOMMMMMMMMMMOMMMMOOMMMMMMMMMMMMMMMMMMMMMMMMOOMMMOOMMMMMMMMMMMMMMMMOOM";
    draw_img(u,v,wall);
}
void draw_blue_wall(int u, int v)
{
    char wall[122]="LLLLLLLLLLLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLTTTTTTTTTLLLLLLLLLLLL";
    draw_img(u,v,wall);
}

void draw_plant(int u, int v)
{
    char plant[122]="BBBBLLLBBBBBBBLLLLLBBBBBLLLLLLLBBBBLLLLLLBBBBBBLLLLLBBBBBBLLLLLBBBBBBBLLLBBBBBBBBBLBBBBBBBBBB2BBBBBBBBBB2BBBBBBBBBB2BBBBB";
    draw_img(u,v,plant);
}
void draw_fire(int u, int v)
{
    char fire[122]="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBOBBBBBBBBOOOBBBBBBBOOOOOBBBBBBOOOOOBBBOBOOOOOOOOOOOOOOOOOO";
    draw_img(u,v,fire);
}
void draw_heart(int u, int v)
{
    char heart[122]="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBTTBTTBBBBBTTTTTTTBBBBTTTTTTTBBBBTTTTTTTBBBBBTTTTTBBBBBBTTTTTBBBBBBBTTTBBBBBBBBBTBBBBB";
    draw_img(u,v,heart);
}
void draw_water(int u, int v)
{
    char plant[122]="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBLBBBBBBBBLLLBBBBBBBLLLLLBBBBBBLLLLLBBBLBLLLLLLLLLLLLLLLLLL";
    draw_img(u,v,plant);
}
void draw_house(int u, int v)
{
    char house[122]="BBBBBLBBBBBBBBBLLLBBBBBBBLLLLLBBBBBLLLLLLLBBBBTTTTTTTBBBBTBTTTBTBBBBTBTTTBTBBBBTBT5TBTBBBBTTT5TTTBBBBTTT5TTTBBBBTTT5TTTBB";
    draw_img(u,v,house);
}
void draw_sonar(int u, int v)
{
    char sonar[122]="BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBTTTTBBBBBBTTTTTTBBBBTTTRATTTBBBTTTAATTTBBBTTTTTTTTBBBBTTTTTTBBBBBBBTTBBB";
    draw_img(u,v,sonar);
}
void draw_sword(int u, int v)
{
    char sword[122]="BBBBBBBBBBBTTBBBBBBBBBBTTBBBBBBBBBBTTBBBBBBBBBBTTBBBBBBBBBTTTBBBBBBBBBTTTBBBBBBBBTTT3BBBBBBBBTT3BBBBBBBBBT33BBBBBBBBBB33B";
    draw_img(u,v,sword);
}
void draw_treasure(int u, int v)
{
    char treasure[122]="BBBBBBBBBBBBBBBBBBBBBBBBB21112BBBBB2111112BBBB2111112BBB211121112BB2122R2212BB211121112BB211111112BB211111112BB211111112B";
    draw_img(u,v,treasure);
}
void draw_opened_treasure(int u, int v)
{
    char treasure[122]="BBBBBBBBBBBBBB11111BBBBB1BBBBB1BBB1BBBBBBB1BB1BBBBBBB1BBDBBBBBBBDBB11DDRDD11BB1111D1111BB111111111BB111111111BB111111111B";
    draw_img(u,v,treasure);
}
void draw_guide(int u, int v)
{
    char guide[122] = "BBB22222BBBBBBWTWTWBBBBBBWWWWWBBBBBBBW1WBBBBBBBBBWBBBBBBBBBWWWBBBBBBBWBWBWBBBBBBBBWBBBBBBBBBBWBBBBBBBBBWBWBBBBBBBWBBBWBBB";
    draw_img(u,v,guide);
}
void draw_villager(int u, int v)
{
    char villager[122] = "BBB55555BBBBBBWTWTWBBBBBBWWWWWBBBBBBBW1WBBBBBBBBBWBBBBBBBBBDWDBBBBBBBDBDBDBBBBBBBBDBBBBBBBBBBDBBBBBBBBBDBDBBBBBBB2BBB2BBB";
    draw_img(u,v,villager);
}
void draw_master(int u, int v)
{
    char master[122] = "BBBBBBBBBBBB55BBBBBBBBBWWBBBBBBBBBWWBBRBBBBBBWWTTTTTBBBBTWTTTTTRBBBBBTTTTTBRBBBTTTTTTBBBBTBTBTBTRBBBBRTBTBTRBBBBBTRTBTBBB";
    draw_img(u,v,master);
}
void draw_guard(int u, int v)
{
    char guard[122] = "BBB22222BBBBBWRRWRRWBBBBWWWWWWWBBBBBWW1WWBBBBBBBBWBBBB3BBBBRRRBB3BBBBRBRBR3BBBBBBBRB3BBBBBBBBRBBBBBBBBBRBRBBBBBBB5BBB5BBB";
    draw_img(u,v,guard);
}
void draw_red_ladder(int u, int v)
{
    char ladder[122] = "BBBRBBBRBBBBBBRRRRRBBBBBBRBBBRBBBBBBRBBBRBBBBBBRBBBRBBBBBBRBBBRBBBBBBRBBBRBBBBBBRRRRRBBBBBBRBBBRBBBBBBRBBBRBBBBBBRBBBRBBB";
    draw_img(u,v,ladder);
}
void draw_blue_ladder(int u, int v)
{
    char ladder[122] = "BBBTBBBTBBBBBBTTTTTBBBBBBTBBBTBBBBBBTBBBTBBBBBBTBBBTBBBBBBTBBBTBBBBBBTBBBTBBBBBBTTTTTBBBBBBTBBBTBBBBBBTBBBTBBBBBBTBBBTBBB";
    draw_img(u,v,ladder);
}
// void draw_exclamation(int u, int v)
// {
//     char exclamation[122] = "BBBBB1BBBBBBBBBB1BBBBBBBBBB1BBBBBBBBBB1BBBBBBBBBB1BBBBBBBBBB1BBBBBBBBBB1BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB1BBBBBBBBBB1BBBBB";
//     draw_img(u,v,exclamation);
// }
void draw_upper_status(int x, int y)
{
    // Draw bottom border of status bar
    uLCD.color(WHITE);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.line(0, 9, 127, 9,0x008080);
    uLCD.locate(1,0);
    uLCD.printf("(%d,",x);
    uLCD.locate(6,0);
    uLCD.printf("%d)",y);
    
    // Add other status info drawing code here
}

void draw_lower_status(int lives)
{
     // Draw top border of status bar
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.line(0, 9, 127, 9, 0x008080);
    uLCD.locate(1,15);
    uLCD.printf("Lives: %d",lives);
    // Add other status info drawing code here
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, 0x008080); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, 0x008080); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, 0x008080); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, 0x008080); // Right
}


