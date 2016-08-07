#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#define IMAGE_HEIGHT 240
#define IMAGE_WIDTH 320

using namespace sf;
using namespace std;

int last_level;
int last_y;

int find_y_pixel(int x, Image img);
void build_tile(int xstart, Image img);


int main(int argc, char *argv[])
{
    RenderWindow window(VideoMode(320,240),"Window");
    window.setFramerateLimit(60);
    Image img;
    //img.loadFromFile(argv[1]);
    img.loadFromFile("1.bmp");
    Texture t;
    //t.loadFromFile(argv[1]);
    t.loadFromFile("1.bmp");
    Sprite spr;
    spr.setTexture(t);
    
    last_level = 0;
    last_y = 0;
    build_tile(0, img);   
  
    while(window.isOpen())
    {
        Event event;
        
        
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(spr);
        window.display();
    }
    return 0;
}


//Ищет Y пикселя
int find_y_pixel(int x, Image img)
{
	Color control_pixel = img.getPixel(0, 0);
	Color pixel;
	int y = 0;
	
	for(int i = 0; i < IMAGE_HEIGHT; i++)
	{
		pixel = img.getPixel(x, i);
		if (pixel != control_pixel)
		{
			y = i;
            cout << "Y=" << y << endl;
			break;
		}
	}
	
	return y;
	
}

//строит тайл
//void build_tile(int xstart, int shift_level = 0, int tile_number = 0)

void build_tile(int xstart, Image img)
{
    int first_y = find_y_pixel(xstart, img);
    int end_y = find_y_pixel(xstart + 7, img);
    
    int first_level = last_level + (first_y - last_y);
    int y = 0;
    int level = 0;
    
    //Тайл ниже предыдущего
    if (first_level > 7) 
    {
        first_level = 0;
    }
    
    //Тайл выше предыдущего
    if (first_level < 0)
    {
        first_level = 7;
    }
    
    
    cout << first_level << ",";
    for(int i = xstart + 1; i < xstart + 7; i++)
    {
        y = find_y_pixel(i, img);
        level = first_level + (first_y - y);
        last_y = y;
        last_level = level;
        cout << level << ",";
    }
    
}

