#include "tile.h"
#include "utils.h"

//PLATFORMS_PARAMS
/////////////////////
unsigned char R1[8] =  {7,6,5,4,3,2,1,0}; //0x15
unsigned char R2[8] =  {7,6,5,4,4,3,2,1}; //0x16
unsigned char R3[8] =  {7,6,6,5,4,3,3,2}; //0x17
unsigned char R4[8] =  {7,6,6,5,5,4,4,3}; //0x18
unsigned char R5[8] =  {7,7,6,6,5,5,4,4}; //0x19
unsigned char R6[8] =  {7,7,6,6,6,6,5,5}; //0x1a
unsigned char R7[8] =  {7,7,7,7,6,6,6,6}; //0x1b
unsigned char R8[8] =  {6,5,4,3,3,2,1,0}; //0x1c
unsigned char R9[8] =  {5,4,4,3,2,1,1,0}; //0x1d
unsigned char R10[8] = {4,3,3,2,2,1,1,0}; //0x1e
unsigned char R11[8] = {3,3,2,2,1,1,0,0}; //0x1f
unsigned char R12[8] = {2,2,1,1,1,1,0,0}; //0x20
unsigned char R13[8] = {1,1,1,1,0,0,0,0}; //0x21
unsigned char R14[8] = {0,0,0,0,0,0,0,0}; //0x22
unsigned char R15[8] = {0,1,2,3,4,5,6,7}; //0x23
unsigned char R16[8] = {0,1,2,3,3,4,5,6}; //0x24
unsigned char R17[8] = {0,1,1,2,3,4,4,5}; //0x25
unsigned char R18[8] = {0,1,1,2,2,3,3,4}; //0x26
unsigned char R19[8] = {0,0,1,1,2,2,3,3}; //0x27
unsigned char R20[8] = {0,0,1,1,1,1,2,2}; //0x28
unsigned char R21[8] = {0,0,0,0,1,1,1,1}; //0x29
unsigned char R22[8] = {1,2,3,4,4,5,6,7}; //0x2a
unsigned char R23[8] = {2,3,3,4,5,6,6,7}; //0x2b
unsigned char R24[8] = {3,4,4,5,5,6,6,7}; //0x2c
unsigned char R25[8] = {4,4,5,5,6,6,7,7}; //0x2d
unsigned char R26[8] = {5,5,6,6,6,6,7,7}; //0x2e
unsigned char R27[8] = {6,6,6,6,7,7,7,7}; //0x2f
unsigned char R28[8] = {7,7,7,7,7,7,7,7}; //0x30
unsigned char R29[8] = {1,1,1,1,1,1,1,1}; //0x31
unsigned char R30[8] = {2,2,2,2,2,2,2,2}; //0x32
unsigned char R31[8] = {3,3,3,3,3,3,3,3}; //0x33
unsigned char R32[8] = {4,4,4,4,4,4,4,4}; //0x34
unsigned char R33[8] = {5,5,5,5,5,5,5,5}; //0x35
unsigned char R34[8] = {6,6,6,6,6,6,6,6}; //0x36
/////////////////////

//ok
bool tile_place(int x, int y)
{
    int tx = (int)(x / TILE_WIDTH);
    int ty = (int)(y / TILE_HEIGHT);
	return (0 != tile_map[tx][ty]);
}

//ok
unsigned char get_tile(int x, int y)
{
	int tx = (int)(x / TILE_WIDTH);
    int ty = (int)(y / TILE_HEIGHT);
	return tile_map[tx][ty];
}

//ok
int get_x_in_tile(int x)
{
    int tx = (int)(x / TILE_WIDTH);
    tx = tx * TILE_WIDTH;
    return x - tx;
}

//ok
int get_y_in_tile(int y)
{
    int ty = (int)(y / TILE_HEIGHT);
    ty = ty * TILE_HEIGHT;
    return y - ty;
}

//ok
int get_y_level(int x_in_tile, int tile)
{
    int level = 0;
    switch(tile)
    {
        case 0x15: level = R1[x_in_tile]; break;
        case 0x16: level = R2[x_in_tile]; break;
        case 0x17: level = R3[x_in_tile]; break;
        case 0x18: level = R4[x_in_tile]; break;
        case 0x19: level = R5[x_in_tile]; break;
        case 0x1A: level = R6[x_in_tile]; break;
        case 0x1B: level = R7[x_in_tile]; break;
        case 0x1C: level = R8[x_in_tile]; break;
        case 0x1D: level = R9[x_in_tile]; break;
        case 0x1E: level = R10[x_in_tile]; break;
        case 0x1F: level = R11[x_in_tile]; break;
        case 0x20: level = R12[x_in_tile]; break;
        case 0x21: level = R13[x_in_tile]; break;
        case 0x22: level = R14[x_in_tile]; break;
        case 0x23: level = R15[x_in_tile]; break;
        case 0x24: level = R16[x_in_tile]; break;
        case 0x25: level = R17[x_in_tile]; break;
        case 0x26: level = R18[x_in_tile]; break;
        case 0x27: level = R19[x_in_tile]; break;
        case 0x28: level = R20[x_in_tile]; break;
        case 0x29: level = R21[x_in_tile]; break;
        case 0x2A: level = R22[x_in_tile]; break;
        case 0x2B: level = R23[x_in_tile]; break;
        case 0x2C: level = R24[x_in_tile]; break;
        case 0x2D: level = R25[x_in_tile]; break;
        case 0x2E: level = R26[x_in_tile]; break;
        case 0x2F: level = R27[x_in_tile]; break;
        case 0x30: level = R28[x_in_tile]; break;
        case 0x31: level = R29[x_in_tile]; break;
        case 0x32: level = R30[x_in_tile]; break;
        case 0x33: level = R31[x_in_tile]; break;
        case 0x34: level = R32[x_in_tile]; break;
        case 0x35: level = R33[x_in_tile]; break;
        case 0x36: level = R34[x_in_tile]; break;
        default:   level = 0; break;
    }
    return level;
}

//ok
int get_tile_x_location(int x)
{
    return (int)(x / TILE_WIDTH);
}

//ok
int get_tile_y_location(int y)
{
    return (int)(y / TILE_HEIGHT);
}

//ok
int get_tile_x_global(int x)
{
    return get_tile_x_location(x) * TILE_WIDTH;
}

//ok
int get_tile_y_global(int y)
{
    return get_tile_y_location(y) * TILE_HEIGHT;
}

//ok
int get_right_level(int tile)
{
    return get_y_level(7, tile);
}

//ok
int get_left_level(int tile)
{
    return get_y_level(0, tile);
}

//ok
void update_coords(int px, int py, Coords* coords)
{
    coords->ax = px;
    coords->ay = py;

    coords->bx = px + (PLAYER_WIDTH / 2) - 1;
    coords->by = py;

    coords->cx = px + PLAYER_WIDTH - 1;
    coords->cy = py;

    coords->dx = px + PLAYER_WIDTH - 1;
    coords->dy = py + (PLAYER_HEIGHT / 2) - 1;

    coords->ex = px + PLAYER_WIDTH - 1;
    coords->ey = py + PLAYER_HEIGHT - 1;

    coords->fx = px + (PLAYER_WIDTH / 2) - 1;
    coords->fy = py + PLAYER_HEIGHT - 1;

    coords->gx = px;
    coords->gy = py + PLAYER_HEIGHT - 1;

    coords->hx = px;
    coords->hy = py + (PLAYER_HEIGHT / 2) - 1;

    coords->ix = px + (PLAYER_WIDTH / 2) - 1;
    coords->iy = py + (PLAYER_HEIGHT / 2) - 1;

}

int get_tile_type(int tile)
{
    if (in_diapazon(tile, 0x15, 0x21)) return TT_SLOPE_LEFT | TT_SOLID;
    if (in_diapazon(tile, 0x23, 0x2f)) return TT_SLOPE_RIGHT | TT_SOLID;
    if (in_diapazon(tile, 0x30, 0x36) || 0x22 == tile) return TT_FLAT | TT_SOLID;
}
