#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;

    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map map2;
static int active_map;
unsigned int NUMBUCKETS = 100;
/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    return Y*(map.w) + X; // Because Y * Width will be larger than anything Y*X could be, adding X on top creates unique value
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key%NUMBUCKETS; // Use same hash function in project 2-1
}

void maps_init()
{ 
    // Initialize hash table
    set_active_map(0)->items=createHashTable(map_hash,NUMBUCKETS);
    get_active_map()->w=50;
    get_active_map()->h=50;
    set_active_map(1)->items=createHashTable(map_hash,NUMBUCKETS);
    get_active_map()->w=20;
    get_active_map()->h=30;
}

Map* get_active_map()
{
    switch(active_map)
    {
    case 0:
    return &map;
    case 1:
    return &map2;
    default:
    return &map;
    }
}

Map* set_active_map(int m)
{
    active_map = m;
    switch(active_map)
    {
    case 0:
    return &map;
    case 1:
    return &map2;
    default:
    return &map;
    }
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    Map *map = get_active_map();
    return map->w;

}

int map_height()
{
    Map *map = get_active_map();
    return map->h;

}

int map_area()
{
    Map *map = get_active_map();
    return (map->w * map->h);    
}

MapItem* get_north(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x,y-1);
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    return item_pos;     
}

MapItem* get_south(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x,y+1); 
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    return item_pos;       
}

MapItem* get_east(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x+1,y); //the cell directly right of current cell
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    return item_pos;       
}

MapItem* get_west(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x-1,y); //the cell directly above current cell
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    return item_pos;   
}

MapItem* get_here(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x,y); //the current_cell
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    return item_pos;   
}


void map_erase(int x, int y)
{
    Map *map = get_active_map();
    int key = XY_KEY(x,y);
    MapItem* item_pos = (MapItem*) getItem(map->items,key);
    if(item_pos) deleteItem(map->items, key); // if the item exists at the current cell, delete it
    
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_sonar(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SONAR;
    w1->draw = draw_sonar;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_guide(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GUIDE;
    w1->draw = draw_guide;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_master(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = MASTER;
    w1->draw = draw_master;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_guard(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GUARD;
    w1->draw = draw_guard;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_treasure(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TREASURE;
    w1->draw = draw_treasure;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_red_ladder(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = LADDER;
    w1->draw = draw_red_ladder;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_blue_ladder(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = LADDER;
    w1->draw = draw_blue_ladder;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}