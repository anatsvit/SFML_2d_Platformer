#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

#define MAX_PIXON 500

#define MODE_NORMAL 0
#define MODE_LEFT   1
#define MODE_RIGHT  2

///////////////////////BACKGROUND
#define BG_WIDTH   768
#define BG_HEIGHT  480
#define WIN_WIDTH  320
#define WIN_HEIGHT 240
//Чем больше PARALLAX_FACTOR тем дальше фон
#define PARALLAX_FACTOR 6
///////////////////////

#define GAME_SPEED  70 //70 - default

using namespace sf;
using namespace std;

///////////////////
void init_map();
void load_map();
void set_pixon(int x, int y, bool logging = false);
bool is_tile_type(int x, int y, int type);
int get_my_y(int x, int y, int mode = MODE_NORMAL);
int modify_xy(int my_x, int my_y, int new_y, int shift_new_y = 0);
int calculate_y(int px, int py);
void keyboard_control(float *dx, float *dy);

///////////////////
unsigned char tile_map[MAP_H][MAP_W];
///////////////////
bool on_ground = false;
bool is_jumping = false;
bool is_falling = false;
bool move_left = false;
bool move_right = false;
float timega;

bool debug_mode = false;
///////////////////

Coords coords;

int pixons_count = 0;
int pixon_x[MAX_PIXON];
int pixon_y[MAX_PIXON];

int main()
{
    load_map();

    float px = 180;
    float py = 14;
    int ground_y = 0;

    Clock clock;

    float dx = 0;
    float dy = 0;

    RenderWindow window(VideoMode(320, 240), "Window");

    window.setFramerateLimit(GAME_SPEED);

    RectangleShape player;
    player.setFillColor(Color::Red);
    player.setPosition(px, py);
    player.setSize(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));

    RectangleShape tile;
    tile.setFillColor(Color::Cyan);
    tile.setPosition(0, 0);
    tile.setSize(Vector2f(TILE_WIDTH, TILE_HEIGHT));

    RectangleShape pixon;
    pixon.setFillColor(Color::Blue);
    pixon.setPosition(0, 0);
    pixon.setSize(Vector2f(1, 1));

    float gravity = 0;
    int ny = 0;

    int mouse_x = 0;
    int mouse_y = 0;
    
    ////////////////////////BACKGROUND
    Texture bg_texture;
    Sprite bg_sprite;
    bg_texture.setSmooth(true);

    //Фон загружается как обычный спрайт:
    bg_texture.loadFromFile("bg.jpg");
    bg_sprite.setTexture(bg_texture);
    
    View view;
    view.reset(FloatRect(0,0,WIN_WIDTH,WIN_HEIGHT));
    view.setViewport(FloatRect(0,0,1.0f,1.0f));

    Vector2f pos(0,0);
    
    ////////////////////////

    while(window.isOpen())
    {
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
        }

        keyboard_control(&dx, &dy);
        
        ///////////////////////////BACKGROUND
         //Получить позицию игрока для камеры
        pos.x = px + 10 - (WIN_WIDTH / 2);
        pos.y = py + 10 - (WIN_HEIGHT / 2);

        //Ограничить камеру вначале
        if(pos.x < 0) pos.x = 0;
        if(pos.y < 0) pos.y = 0;
        //и в конце уровня
        if(PARALLAX_FACTOR > 0)
        {
            if(pos.x > BG_WIDTH-WIN_WIDTH / PARALLAX_FACTOR) pos.x = BG_WIDTH-WIN_WIDTH / 2;
            if(pos.y > BG_HEIGHT-WIN_HEIGHT / PARALLAX_FACTOR) pos.y = BG_HEIGHT-WIN_HEIGHT / 2;
        }
        else
        {
            if(pos.x > BG_WIDTH-WIN_WIDTH) pos.x = BG_WIDTH-WIN_WIDTH;
            if(pos.y > BG_HEIGHT-WIN_HEIGHT) pos.y = BG_HEIGHT-WIN_HEIGHT;
        }


        //Это для Parallax Scrolling
        if(PARALLAX_FACTOR > 0)
        bg_sprite.setPosition(pos.x / PARALLAX_FACTOR, pos.y / PARALLAX_FACTOR);
        else
        bg_sprite.setPosition(pos.x, pos.y);

        view.reset(FloatRect(pos.x,pos.y,WIN_WIDTH,WIN_HEIGHT));
        ///////////////////////////

        px = px + dx; dx = 0;
        if(!debug_mode)
        {
            //gravity
            if(!on_ground)
            {
                dy = dy + 0.2;
                if(dy > 3) dy = 3;

                py = py + dy; 
            }
        }
        else
        {
            if(!on_ground)
            {
                py = py + dy;
            }
        }

        if(py > 350) py = 0;

        update_coords(px, py, &coords);
        on_ground = false;
        
        if(dy >= 0) { py = calculate_y(px, py); }

        if(on_ground)
        {
            dy = 0; //Полезно
            is_jumping = false;
        }

        //В падении ли?
        is_falling = false;
        if (!on_ground && !is_jumping && dy > 0)
        {
            is_falling = true;
        }

        update_coords(px, py, &coords);

        //set_pixon(px, py);
        player.setPosition(px, py);
        
        
        window.clear();
        window.setView(view);
        window.draw(bg_sprite); //Отобразить фон
        for(int i = 0; i < 100; i++)
        {
            for(int j = 0; j < 100; j++)
            {
                if (tile_map[i][j] != 0)
                {
                    tile.setPosition(i*8, j*8);
                    window.draw(tile);
                }
            }  
        }
        
        window.draw(player);
        for(int i = 0; i < pixons_count; i++)
        {
            pixon.setPosition(pixon_x[i], pixon_y[i]);
            window.draw(pixon);
        }

        window.display();
    }

    return 0;
}


//ok
void load_map()
{
    init_map();
    int x_shift = 4;
    
    FILE *f = fopen("level.hex","r");
    unsigned char tile[6];
    int x = 0;
    int y = 0;
    int t = 0;
    
    int i = 0;
    if(f != NULL)
    {
        while(!feof(f))
        {
            fread(&tile,6,1,f);
            x = tile[0];
            x = x << 8;
            x = x | tile[1];
            
            y = tile[2];
            y = y << 8;
            y = y | tile[3];
            
            t = tile[4];
            t = t << 8;
            t = t | tile[5];
            
            tile_map[x][y] = t;
     
            i++;
        }
        fclose(f);
    }
    else
    {
        cout << "Error: open file";
    }
    
    
    /*
    //Test #1
    //Левый склон
    for (int i = 0; i < 10; i++)
    {
        tile_map[i+x_shift][20-i] = 0x15;
    }
    
    //Прямая
    for (int i = 0; i < 10; i++)
    {
        tile_map[10+i+x_shift][11] = 0x22;
    }
    
    //Правый склон
    for (int i = 0; i < 10; i++)
    {
        tile_map[20+i+x_shift][11+i] = 0x23;
    }
    */
    
    
    //Test #2
    //Левый склон
    for (int i = 0; i < 10; i++)
    {
        tile_map[i+x_shift][10+i] = 0x23;
    }
    
    //Прямая
    for (int i = 0; i < 10; i++)
    {
        tile_map[10+i+x_shift][20] = 0x22;
    }
    
    //Правый склон
    for (int i = 0; i < 10; i++)
    {
        tile_map[20+i+x_shift][19-i] = 0x15;
    }
    
    
}

//ok
void init_map()
{
    for(int i = 0; i < MAP_H; i++)
      for(int j = 0; j < MAP_W; j++)
      {
        tile_map[i][j] = 0;
      }
}

//ok
void set_pixon(int x, int y, bool logging)
{
    bool is_new_pixon = true;
    for(int i = 0; i < pixons_count+1; i++)
    {
        if(pixon_x[i] == x && pixon_y[i] == y)
        {
            is_new_pixon = false;
            break;
        }
    }
    if(is_new_pixon)
    {
        pixon_x[pixons_count] = x;
        pixon_y[pixons_count] = y;
        if(logging)
        {
            cout << "pixon_x: " << x << endl;
            cout << "pixon_y: " << y << endl;
        }
        if(pixons_count < MAX_PIXON)
        {
            pixons_count++;
        }
        else
        {
            pixons_count = 0;
            if(logging)
            {
                cout << "---------------------" << endl;
            }
        }
    }
}

//ok
bool is_tile_type(int x, int y, int type)
{
   return (get_tile_type(get_tile(x, y)) & type) > 0;
}

int get_my_y(int x, int y, int mode)
{
    int result = 0;
    if(mode == MODE_LEFT)
    {
        result = get_left_level(get_tile(x, y)) + get_tile_y_global(y) - PLAYER_HEIGHT;
    }
    if(mode == MODE_RIGHT)
    {
        result = get_right_level(get_tile(x, y)) + get_tile_y_global(y) - PLAYER_HEIGHT;
    }
    if(mode == MODE_NORMAL)
    {
        result = get_y_level(get_x_in_tile(x), get_tile(x, y)) + get_tile_y_global(y) - PLAYER_HEIGHT;
    }
        
    return result;
}

int modify_xy(int my_x, int my_y, int new_y, int shift_new_y)
{
    int py = my_y;
    if (my_y >= new_y || (!is_jumping && !is_falling))
    {
      py = new_y + shift_new_y;
      on_ground = true;
    }
    update_coords(my_x, py, &coords);
    return py;
}

//Вычисление на склонах и ровных поверхностях
int calculate_y(int px, int py)
{
    int ny = 0;
    int new_py = py;
    
    if(tile_place(coords.fx, coords.fy))
    {
        ny = get_my_y(coords.fx, coords.fy);
        new_py = modify_xy(px, py, ny);
    }

    if(tile_place(coords.fx, coords.fy+1))
    {
        ny = get_my_y(coords.fx, coords.fy + 1);
        new_py = modify_xy(px, py, ny - 1, 1);
    }

    
    if(!tile_place(coords.fx, coords.fy) && (tile_place(coords.gx, coords.gy) || tile_place(coords.gx, coords.gy + 1)))
    {
        if (tile_place(coords.gx, coords.gy))
        {
            if (is_tile_type(coords.gx, coords.gy, TT_SLOPE_LEFT))
            {
                ny = get_my_y(coords.gx, coords.gy, MODE_RIGHT);
                new_py = modify_xy(px, py, ny);
            }

            if (is_tile_type(coords.gx, coords.gy, TT_SLOPE_RIGHT))
            {
                ny = get_my_y(coords.gx, coords.gy, MODE_RIGHT);
                new_py = modify_xy(px, py, ny, 1);
            }
        }

        if (tile_place(coords.gx, coords.gy + 1))
        {
            if (is_tile_type(coords.gx, coords.gy + 1, TT_SLOPE_LEFT))
            {
                ny = get_my_y(coords.gx, coords.gy + 1, MODE_RIGHT);
                new_py = modify_xy(px, py, ny);
            }

            if (is_tile_type(coords.gx, coords.gy + 1, TT_SLOPE_RIGHT))
            {
                ny = get_my_y(coords.gx, coords.gy + 1, MODE_RIGHT);
                new_py = modify_xy(px, py, ny, 1);
            }

            if (is_tile_type(coords.gx, coords.gy + 1, TT_FLAT))
            {
                ny = get_my_y(coords.gx, coords.gy + 1, MODE_RIGHT);
                new_py = modify_xy(px, py, ny);
            }
        }
    }

    if(!tile_place(coords.fx, coords.fy) && (tile_place(coords.ex, coords.ey) || tile_place(coords.ex, coords.ey + 1)))
    {
        if (tile_place(coords.ex, coords.ey))
        {
            if (is_tile_type(coords.ex, coords.ey, TT_SLOPE_LEFT))
            {
                ny = get_my_y(coords.ex, coords.ey, MODE_LEFT) + 1;
                new_py = modify_xy(px, py, ny);
            }

            if (is_tile_type(coords.ex, coords.ey, TT_SLOPE_RIGHT))
            {
                ny = get_my_y(coords.ex, coords.ey, MODE_LEFT);
                new_py = modify_xy(px, py, ny, 1);
            }
        }

        if (tile_place(coords.ex, coords.ey + 1))
        {
            if (is_tile_type(coords.ex, coords.ey + 1, TT_SLOPE_RIGHT))
            {
                ny = get_my_y(coords.ex, coords.ey + 1, MODE_LEFT);
                new_py = modify_xy(px, py, ny);
            }
        }
    }

    if(!tile_place(coords.fx, coords.fy) && tile_place(coords.ex, coords.ey + 1))
    {
        if (is_tile_type(coords.ex, coords.ey + 1, TT_FLAT))
        {
            ny = get_my_y(coords.ex, coords.ey + 1, MODE_LEFT);
            new_py = modify_xy(px, py, ny);
        }
    }
    
    return new_py;
}

void keyboard_control(float *dx, float *dy)
{
        move_left = false;
        move_right = false;
        
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            *dx=-1;
            move_left = true;
            move_right = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            *dx=1;
            move_right = true;
            move_left = false;
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if(!debug_mode)
            {
                if(on_ground){*dy = -4; on_ground = false; is_jumping = true;}
            }
            else
            {
                *dy = -1;
            }
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if(debug_mode)
            {
                *dy = 3;
            }
        } 
}