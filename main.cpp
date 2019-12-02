// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
//FEELING BLUE
//blue lost master, trying to recover, talks to naked guide, goes to red, finds master, gives sword to main, can destroy any red char a block away, kill guards, get sonar, go back to main map, recover treasure.
// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void start();
void instructions();
void redstart();
void play_noise(int n);
int main ();
int omni = false;
int go_up(int x, int y);
int go_down(int x, int y);
int go_right(int x, int y);
int go_left(int x, int y);
int run_up(int x, int y);
int run_down(int x, int y);
int run_right(int x, int y);
int run_left(int x, int y);
int interact_obj(int x, int y);
int attack_obj(int x, int y);
int move = 23;
int movedirection = 0;
int lives = 3;
int treasurex = 0;
int treasurey = 0;
GameInputs input;
Timer t1;
int action;
int update;
int dt1 = 0;
int start_instructions=0;
int haspower=0;
int hassonar=0;
int placetreasure=0;
int guidespeech=0;
int ladderspeech=0;
int arriveredspeech=0;
int findmasterspeech = 0;
int findsonarspeech=0;
int startgamespeech=0;
/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    // You can add other properties for the player here
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define ATTACK 2
#define WIN_GAME 3
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_UP 6
#define GO_DOWN 7
#define OMNI 8
#define LOSS_GAME 9
#define RUN_LEFT 10
#define RUN_RIGHT 11
#define RUN_UP 12
#define RUN_DOWN 13
int get_action(GameInputs inputs)
{
    if (lives == 0)
        return LOSS_GAME;
    if (!inputs.b3) 
        omni = !omni;
    if (inputs.ay >= 0.10 && inputs.ay <= 0.40) 
        return GO_UP;
    if (inputs.ay < -0.20 && inputs.ay > -0.50) 
        return GO_DOWN;
    if (inputs.ax < -0.40 && inputs.ax > -0.70)  
        return GO_LEFT;
    if (inputs.ax >= 0.40 && inputs.ax <= 0.70) 
        return GO_RIGHT;
    if (inputs.ay > 0.40) 
        return RUN_UP;
    if (inputs.ay < -0.50) 
        return RUN_DOWN;
    if (inputs.ax < -0.70)  
        return RUN_LEFT;
    if (inputs.ax >= 0.70) 
        return RUN_RIGHT;
    if (!inputs.b1) 
        return ACTION_BUTTON;
    if (!inputs.b2) 
        return ATTACK;
    return NO_ACTION;
}
char *startgame="Search for the naked villager...";

char *talkvillager="VILLAGER: I wonder where master is...";

char *guide1="NAKED MAN: Dude...where have you been......The reds invaded our villa, took my clothes, and most importantly, have BM(blue master) in hostage......Take the ladder to the red villa and save him!!";
char *guide2="NAKED MAN: Why are you still talking to me I'm naked...take the ladder!";

char *nosonar1="Keep searching...";
char *nosonar2="";

char *findsonar1="*SONAR acquired*...";

char *laddertravel1="Brace yourself...............";
char *laddertravel2="Home is where the heart is...";

char *arrivered1="GUARD: BM is dead. You heard what I said.";

char *findmaster1="MASTER: ...b-b-blue?....I think I'm at the end...ta-take this............*drops blue bayonet*............here...they sent a group of reds to steal the BM loot back at blue, but they don't know about the secret sonar in their guard's room....kill the reds from a block away, get the sonar, and find the loot before the reds......I trust in you kid....";
char *findmaster2=".....";

char *findsword="*picks up sword*...";

char *findtreasure1= "*opens treasure box*.......it's only a third filled? The rest must be somewhere else...";
char *findtreasure2= "*opens treasure box*.......here it is!!!....I will carry on the tradition BM.......";

char *findfaketreasure="*opens treasure box*.......wait there's no loot..?....";



/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP:
        if (go_up(Player.px,Player.py))
        {
            Player.has_key = 2; 
            return FULL_DRAW;
        }
        else break;
        case RUN_UP:
        if (run_up(Player.px,Player.py))
        {
            Player.has_key = 2; 
            return FULL_DRAW;
        }
        else break;
        case GO_LEFT:   
        if (go_left(Player.px,Player.py)) 
        {
            Player.has_key = 4; 
            return FULL_DRAW;
        }
        else break;
        case RUN_LEFT:
        if (run_left(Player.px,Player.py))
        {
            Player.has_key = 4; 
            return FULL_DRAW;
        }
        else break;            
        case GO_DOWN:   
        if (go_down(Player.px,Player.py)) 
        {
            Player.has_key = 1; 
            return FULL_DRAW;
        }
        else break;
        case RUN_DOWN:   
        if (go_down(Player.px,Player.py)) 
        {
            Player.has_key = 1; 
            return FULL_DRAW;
        }
        else break;
        case GO_RIGHT:  
        if (go_right(Player.px,Player.py)) 
        {
            Player.has_key = 3; 
            return FULL_DRAW;
        }
        else break;
        case RUN_RIGHT:  
        if (run_right(Player.px,Player.py)) 
        {
            Player.has_key = 3; 
            return FULL_DRAW;
        }
        else break;
        case ACTION_BUTTON: 
        if (interact_obj(Player.px,Player.py))
            return FULL_DRAW;
        else break;
        case ATTACK:
        if (attack_obj(Player.px,Player.py))
            return FULL_DRAW;
        else break;
        default:        break;
    }
    return NO_RESULT;
}

int interact_obj(int x, int y)
{
    MapItem *item1 = get_north(x, y); 
    MapItem *item2 = get_south(x,y);
    MapItem *item3 = get_east(x, y); 
    MapItem *item4 = get_west(x,y);
    MapItem *item5 = get_here(x,y);

    if((item1->type == GUIDE || item2->type == GUIDE || item3->type == GUIDE || item4->type == GUIDE) && guidespeech == 0)
    {
        speech(guide1);
        guidespeech++;
        add_red_ladder(2,6);
    }
    else if((item1->type == GUIDE || item2->type == GUIDE || item3->type == GUIDE || item4->type == GUIDE) && guidespeech == 1)
    {
        speech(guide2);
    }
        

    else if((item1->type == MASTER || item2->type == MASTER || item3->type == MASTER || item4->type == MASTER) && findmasterspeech == 0)
    {
        speech(findmaster1);
        findmasterspeech++;
        add_sword(11,5);
    }
    else if((item1->type == MASTER || item2->type == MASTER || item3->type == MASTER || item4->type == MASTER) && findmasterspeech == 1)
    {
        speech(findmaster2);
    }


    else if((item1->type == GUARD || item2->type == GUARD || item3->type == GUARD || item4->type == GUARD))
    {
        speech(arrivered1);
    }


    else if((item1->type == VILLAGER || item2->type == VILLAGER || item3->type == VILLAGER || item4->type == VILLAGER))
    {
        speech(talkvillager);
    }



    else if((item1->type == SONAR) && hassonar == 0)
    {
        speech(findsonar1);
        map_erase(x, y-1);
        hassonar++;
    }
    else if((item2->type == SONAR) && hassonar == 0)
    {
        speech(findsonar1);
        map_erase(x, y+1);
        hassonar++;
    }
    else if((item3->type == SONAR) && hassonar == 0)
    {
        speech(findsonar1);
        map_erase(x+1, y);
        hassonar++;
    }
    else if((item4->type == SONAR) && hassonar == 0)
    {
        speech(findsonar1);
        map_erase(x-1, y);
        hassonar++;
    }


    else if((item1->type == SWORD))
    {
        speech(findsword);
        map_erase(x, y-1);
        haspower++;

    }
    else if((item2->type == SWORD))
    {
        speech(findsword);
        map_erase(x, y+1);
        haspower++;
    }
    else if((item3->type == SWORD))
    {
        speech(findsword);
        map_erase(x+1, y);
        haspower++;
    }
    else if((item4->type == SWORD))
    {
        speech(findsword);
        map_erase(x-1, y);
        haspower++;
    }


    else if((item1->type == HEART))
    {
        map_erase(x, y-1);
        lives++;

    }
    else if((item2->type == HEART))
    {
        map_erase(x, y+1);
        lives++;
    }
    else if((item3->type == HEART))
    {
        map_erase(x+1, y);
        lives++;
    }
    else if((item4->type == HEART))
    {
        map_erase(x-1, y);
        lives++;
    }


    else if((item1->type == TREASURE) && placetreasure == 1)
    {
        speech(findtreasure1);
        map_erase(x, y-1);
        placetreasure++;
        treasurex = (rand() % 48) + 1;
        treasurey = (rand() % 48) + 1;
        add_treasure(treasurex, treasurey);
    }
    else if((item2->type == TREASURE) && placetreasure == 1)
    {
        speech(findtreasure1);
        map_erase(x, y+1);
        placetreasure++;
        treasurex = (rand() % 48) + 1;
        treasurey = (rand() % 48) + 1;
        add_treasure(treasurex, treasurey);
    }
    else if((item3->type == TREASURE) && placetreasure == 1)
    {
        speech(findtreasure1);
        map_erase(x+1, y);
        placetreasure++;
        treasurex = (rand() % 48) + 1;
        treasurey = (rand() % 48) + 1;
        add_treasure(treasurex, treasurey);
    }
    else if((item4->type == TREASURE) && placetreasure == 1)
    {
        speech(findtreasure1);
        map_erase(x-1, y);
        placetreasure++;
        treasurex = (rand() % 48) + 1;
        treasurey = (rand() % 48) + 1;
        add_treasure(treasurex, treasurey);
    }


    else if((item1->type == TREASURE) && placetreasure == 2)
    {
        speech(findtreasure2);
        map_erase(x, y-1);
        draw_game(4);
    }
    else if((item2->type == TREASURE) && placetreasure == 2)
    {
        speech(findtreasure2);
        map_erase(x, y+1);
        draw_game(4);
    }
    else if((item3->type == TREASURE) && placetreasure == 2)
    {
        speech(findtreasure2);
        map_erase(x+1, y);
        draw_game(4);
    }
    else if((item4->type == TREASURE) && placetreasure == 2)
    {
        speech(findtreasure2);
        map_erase(x-1, y);
        draw_game(4);
    }


    else if((item1->type == FAKETREASURE))
    {
        speech(findfaketreasure);
        map_erase(x, y-1);
        add_opened_treasure(x, y-1);

    }
    else if((item2->type == FAKETREASURE))
    {
        speech(findfaketreasure);
        map_erase(x, y+1);
        add_opened_treasure(x, y+1);
    }
    else if((item3->type == FAKETREASURE))
    {
        speech(findfaketreasure);
        map_erase(x+1, y);
        add_opened_treasure(x+1, y);
    }
    else if((item4->type == FAKETREASURE))
    {
        speech(findfaketreasure);
        map_erase(x-1, y);
        add_opened_treasure(x-1, y);
    }


    else if((item5->type == LADDER))
    {
        if(ladderspeech % 2 == 0)
        { 
        ladderspeech++;
        speech(laddertravel1);
        redstart();
        set_active_map(1);
    }
        else if(ladderspeech % 2 == 1)
        { 
        ladderspeech++;
        speech(laddertravel2);
        start();
        set_active_map(0);
        }
    }

    else if(hassonar == 0)
        speech(nosonar1);
    else if(hassonar == 1)
    {
        if(Player.y < treasurey && Player.x < treasurex){
            nosonar2="SONAR: SE";
        }
        else if(Player.y > treasurey && Player.x < treasurex)
        {
            nosonar2="SONAR: NE";
        }
        else if(Player.y < treasurey && Player.x > treasurex)
        {
            nosonar2="SONAR: SW";
        }
        else if(Player.y > treasurey && Player.x > treasurex)
        {
            nosonar2="SONAR: NW";
        }
        speech(nosonar2);
    }
    return 1;
}
int attack_obj(int x, int y)
{
    MapItem *item1 = get_north(x, y); 
    MapItem *item2 = get_south(x,y);
    MapItem *item3 = get_east(x, y); 
    MapItem *item4 = get_west(x,y);
    MapItem *item5 = get_here(x,y);
    
    if((item1->type == GUARD) && haspower == 1)
    {
        map_erase(x, y-1);
    }
    else if((item2->type == GUARD) && haspower == 1)
    {
        map_erase(x, y+1);
    }
    else if((item3->type == GUARD) && haspower == 1)
    {
        map_erase(x+1, y);
    }
    else if((item4->type == GUARD) && haspower == 1)
    {
        map_erase(x-1, y);
    }
    return 1;
}

void play_noise(int n)
{
    switch(n){
        case 0:
            speaker.period(1/500);
        case 1:
            speaker.period(1/1000);
    }
    speaker=0.3; 
    wait(.5);
    speaker=0.0;
}
/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */

void draw_game(int init)
{
    if (init==3){
    uLCD.filled_rectangle(0,0,255,255,BLACK);
        uLCD.locate(2,7);
        uLCD.textbackground_color(BLACK);
        uLCD.text_width(1);
        uLCD.text_height(1);
        uLCD.color(RED);
        uLCD.printf("YOU DIED...");
        wait(10000000000);
        }
    if (init == 4) {
        uLCD.filled_rectangle(0,0,255,255,BLACK);
        uLCD.locate(2,4);
        uLCD.textbackground_color(BLACK);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.color(0x008080);
        uLCD.printf("YOU WIN");
        wait(10000000000);
        }
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status(Player.x, Player.y);
    draw_lower_status(lives);
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion. Note: using the similar
 * procedure you can init the secondary map(s).
 */
void init_main_map()
{
    if(start_instructions == 0)
    {
        instructions();
        start_instructions++;
    }

    start();
    // "Random" plants
    Map* map = set_active_map(0);
    play_noise(0);
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_blue_wall(0,              0,              HORIZONTAL, map_width());
    add_blue_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_blue_wall(0,              0,              VERTICAL,   map_height());
    add_blue_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    add_blue_wall(10,1,VERTICAL,5);
    add_blue_wall(10,30,VERTICAL,5);
    add_blue_wall(20,1,VERTICAL,5);
    add_blue_wall(20,30,VERTICAL,5);
    add_blue_wall(30,1,VERTICAL,5);
    add_blue_wall(30,30,VERTICAL,5);
    add_blue_wall(40,1,VERTICAL,5);
    add_blue_wall(40,30,VERTICAL,5);
    add_plant(1,3);
    add_plant(1,4);
    add_plant(2,3);
    add_plant(3,3);
    add_plant(3,4);
    add_house(2,4);
    add_plant(11,3);
    add_plant(11,4);
    add_plant(12,3);
    add_plant(13,3);
    add_plant(13,4);
    add_house(12,4);
    add_plant(21,3);
    add_plant(21,4);
    add_plant(22,3);
    add_plant(23,3);
    add_plant(23,4);
    add_house(22,4);
    add_plant(31,3);
    add_plant(31,4);
    add_plant(32,3);
    add_plant(33,3);
    add_plant(33,4);
    add_house(32,4);
    add_plant(41,3);
    add_plant(41,4);
    add_plant(42,3);
    add_plant(43,3);
    add_plant(43,4);
    add_house(42,4);
    add_water(4,15);
    add_water(5,15);
    add_water(4,25);
    add_water(5,35);
    add_water(4,45);
    add_water(14,15);
    add_water(15,15);
    add_water(14,25);
    add_water(15,35);
    add_water(14,45);
    add_water(24,15);
    add_water(25,15);
    add_water(24,25);
    add_water(25,35);
    add_water(24,45);
    add_water(34,15);
    add_water(35,15);
    add_water(34,25);
    add_water(35,35);
    add_water(34,45);
    add_water(44,15);
    add_water(45,15);
    add_water(44,25);
    add_water(45,35);
    add_water(44,45);
    add_plant(3,10);
    add_plant(5,20);
    add_plant(4,30);
    add_plant(5,40);
    add_plant(13,10);
    add_plant(15,20);
    add_plant(14,30);
    add_plant(15,40);
    add_plant(23,10);
    add_plant(25,20);
    add_plant(24,30);
    add_plant(25,40);
    add_plant(33,10);
    add_plant(35,20);
    add_plant(34,30);
    add_plant(35,40);
    add_plant(43,10);
    add_plant(45,20);
    add_plant(44,30);
    add_plant(45,40);
    add_villager(1,5);
    add_villager(3,5);
    add_villager(11,5);
    add_villager(13,5);
    add_villager(21,5);
    add_villager(31,5);
    add_villager(33,5);
    add_villager(41,5);
    add_villager(43,5);
    add_guide(23,5);
    add_water(5,3);
    add_water(6,3);
    add_water(7,3);
    add_water(15,3);
    add_water(16,3);
    add_water(17,3);
    add_water(25,3);
    add_water(26,3);
    add_water(27,3);
    add_water(35,3);
    add_water(36,3);
    add_water(37,3);
    add_water(45,3);
    add_water(46,3);
    add_water(47,3);
    print_map();
}
void init_second_map()
{
    Map* map = set_active_map(1);
    pc.printf("Adding walls!\r\n");
    add_red_wall(0,              0,              HORIZONTAL, map_width());
    add_red_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_red_wall(0,              0,              VERTICAL,   map_height());
    add_red_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    //MASTER AT (9,5)
    //SONAR AT (10,13)
    //GUARD AT (11,15)
    add_red_wall(11,0,VERTICAL,3);
    add_red_wall(0,3,HORIZONTAL,4);
    add_red_wall(6, 3, HORIZONTAL, 11);
    add_red_wall(3, 3, VERTICAL, 3);
    add_red_wall(6, 3, VERTICAL, 10);
    add_red_wall(1, 9, HORIZONTAL, 2);
    add_red_wall(1, 9, VERTICAL, 5);
    add_red_wall(3, 9, VERTICAL, 8);
    add_red_wall(6, 12, HORIZONTAL, 10);
    add_red_wall(6, 12, VERTICAL, 9);
    add_red_wall(6, 7, HORIZONTAL, 5);
    add_red_wall(6, 15, HORIZONTAL, 5);
    add_red_wall(6, 19, HORIZONTAL, 6);
    add_red_wall(6, 25, HORIZONTAL, 2);
    add_red_wall(6, 25, VERTICAL, 2);
    add_red_wall(3, 21, VERTICAL, 9);
    add_red_wall(10, 19, VERTICAL, 8);
    add_red_wall(12, 15, HORIZONTAL, 2);
    add_red_wall(9, 27, HORIZONTAL, 3);
    add_red_wall(13, 12, VERTICAL, 15);
    add_red_wall(13, 3, VERTICAL, 7);
    add_red_wall(17, 15, HORIZONTAL,3);
    add_red_wall(15, 12, VERTICAL, 5);
    add_red_wall(19, 12, VERTICAL, 8);
    add_red_wall(17, 8, VERTICAL, 17);

    //Guards at (1,4) , (5,7), (6,2), (3, 19), (3, 18), (2,10), (6,22), (7, 26), (4,28), (12,27), (17,25), (15,24), (15,17), (10,8), (7,11), (14,4)
    add_guard(1,4);
    add_guard(5,7);
    add_guard(6,2);
    add_guard(3,19);
    add_guard(3,18);
    add_guard(2,10);
    add_guard(6,22);
    add_guard(7,26);
    add_guard(4,28);
    add_guard(12,27);
    add_guard(17,25);
    add_guard(15,24);
    add_guard(15,17);
    add_guard(10,8);
    add_guard(7,11);
    add_guard(14,4); 
    add_guard(11,14);
    add_guard(11,15);
    add_guard(11,16);
    add_sonar(10,13);
    add_master(9,5);
    add_heart(14,13);
    add_heart(15,20);
    add_blue_ladder(2,5);
    add_fire(2,8);
    add_fire(3,8);
    add_fire(4,4);
    add_fire(4,11);
    add_fire(5,14);
    add_fire(5,19);
    add_fire(5,25);
    add_fire(13,27);
    add_fire(14,20);
    add_fire(16,23);
    add_fire(17,28);
    add_fire(17,27);
    add_fire(15,5);
    add_fire(15,6);
    add_fire(15,7);
    add_fire(16,1);
    add_fire(13,10);
    add_fire(11,7);
    add_fire(12,9);
    add_fire(8,4);
    add_fire(9,4);
    add_fire(10,4);
    print_map();
}
int go_up(int x, int y)
{
    MapItem *item = get_north(x, y);
    if(item->walkable || omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.y--;
        return 1;
    }
    return 0;

}
int run_up(int x, int y)
{
    MapItem *item = get_north(x, y);
    MapItem *item2 = get_north(x, y-1);
    if((item->walkable && item2->walkable)|| omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.y-=2;
        return 1;
    }
    return 0;

}
int go_down(int x, int y)
{
    MapItem *item = get_south(x, y);
    if(item->walkable || omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.y++;
        return 1;
    }
    return 0;

}
int run_down(int x, int y)
{
    MapItem *item = get_south(x, y);
    MapItem *item2 = get_south(x, y+1);
    if((item->walkable && item2->walkable)|| omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.y+=2;
        return 1;
    }
    return 0;

}
int go_right(int x, int y)
{
    MapItem *item = get_east(x, y);
    if(startgamespeech == 0)
    {
        speech(startgame);
        startgamespeech++;
    }
    if(item->walkable || omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.x++;
        return 1;
    }
    return 0;
}
int run_right(int x, int y)
{
    MapItem *item = get_east(x, y);
    MapItem *item2 = get_east(x+1, y);
    if((item->walkable && item2->walkable)|| omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.x+=2;
        return 1;
    }
    return 0;

}
int go_left(int x, int y)
{
    MapItem *item = get_west(x, y);
    if(item->walkable || omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.x--;
        return 1;
    }
    return 0;

}
int run_left(int x, int y)
{
    MapItem *item = get_west(x, y);
    MapItem *item2 = get_west(x-1, y);
    if((item->walkable && item2->walkable) || omni)
    {
        if(item->type == GUARD || item->type == FIRE)
        {
            lives--;
        }
        if(lives == 0)
        {
            draw_game(3);
        }
        Player.x-=2;
        return 1;
    }
    return 0;

}
/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */

void start(){
    uLCD.textbackground_color(BLACK);
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.locate(4,4);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(0x008080);
    uLCD.printf("BLUE");
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.locate(9,4.25);
    uLCD.printf("\n   VILLA");
    do{
    input = read_inputs();
    }while(input.b1);
    if(hassonar == 1 && placetreasure == 0)
    {
        set_active_map(0);
        for(int i = 0; i < 10; i++)
        {
            treasurex = (rand() % 48) + 1;
            treasurey = (rand() % 48) + 1;
            add_fake_treasure(treasurex, treasurey);
        }
        treasurex = (rand() % 48) + 1;
        treasurey = (rand() % 48) + 1;
        add_treasure(treasurex, treasurey);
        placetreasure++;
    }
}
void instructions(){
    t1.start();
    uLCD.textbackground_color(BLACK);
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.locate(1,1);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(0x008080);
    uLCD.printf("FEELING BLUE");
    uLCD.color(0xFFFFFF);
    uLCD.locate(1,3);
    uLCD.printf("B1-Action Button(Speak, Pick Up)");
    uLCD.locate(1,5);
    uLCD.printf("\n B2-Attack");
    uLCD.locate(1,7);
    uLCD.printf("\n B3-Omni-Potent Mode");
    uLCD.color(0x008080);
    uLCD.locate(1,11);
    uLCD.printf("By: Justin Lau");
    uLCD.color(0xFFFFFF);
    uLCD.locate(1,12);
    uLCD.printf("\n Press B1 to continue: ");
    do{
    input = read_inputs();
    }while(input.b1);
    t1.stop();
    dt1 = t1.read_ms();
    srand(dt1);
}
void redstart(){
    uLCD.textbackground_color(BLACK);
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.locate(4,4);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(0xFF0000);
    uLCD.printf("RED");
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.locate(9,4.25);
    uLCD.printf("\n   VILLA");  
    do{
    input = read_inputs();
    }while(input.b1);
}
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    maps_init();
    init_main_map();
    init_second_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        Timer walk; walk.start();
        
        // Actuall do the game update:
        // 1. Read inputs     
        input = read_inputs();   
        // 2. Determine action (get_action)     
        action = get_action(input);   
        // 3. Update game (update_game)
        update = update_game(action);
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        draw_game(update);
        // 5. Frame delay
        t.stop();
        walk.stop();
        int dt = t.read_ms();
        int walkdt = t.read_ms();

        if(walkdt % 2 == 0) //naked man walking movement
        {
            wait_ms(100);
            if(move == 23)
            {
                movedirection = 0;
            }
            if(move == 25)
            {
                movedirection = 1;
            }
            if(movedirection == 0)
            {
                add_guide(move+1, 5);
                map_erase(move, 5);
                move++;
            }
            if(movedirection == 1)
            {
                add_guide(move-1, 5);
                map_erase(move, 5);
                move--;
            }
        }
        if (dt < 100) wait_ms(100 - dt);
    }
}
