#define TILE_HEIGHT 8
#define TILE_WIDTH 8
#define MAP_W 512
#define MAP_H 120

#define PLAYER_HEIGHT 4*TILE_HEIGHT
#define PLAYER_WIDTH 2*TILE_WIDTH

#define TT_SOLID       1 //0000000000000001
#define TT_SLOPE_LEFT  2 //0000000000000010
#define TT_SLOPE_RIGHT 4 //0000000000000100
#define TT_FLAT        8 //0000000000001000

extern unsigned char tile_map[MAP_W][MAP_H];

typedef struct Coords
{
    int ax, bx, cx, dx, ex, fx, gx, hx, ix;
    int ay, by, cy, dy, ey, fy, gy, hy, iy;
};

bool tile_place(int x, int y);
unsigned char get_tile(int x, int y);
int get_x_in_tile(int x);
int get_y_in_tile(int y);
int get_y_level(int x_in_tile, int tile);
int get_tile_x_location(int x);
int get_tile_y_location(int y);
int get_tile_x_global(int x);
int get_tile_y_global(int y);
void update_coords(int px, int py, Coords* coords);
int get_right_level(int tile);
int get_left_level(int tile);
int get_tile_type(int tile);

