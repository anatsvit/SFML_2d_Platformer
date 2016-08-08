#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#define IMAGE_HEIGHT 240
#define IMAGE_WIDTH 320

using namespace sf;
using namespace std;

int last_level;
int last_y;

int tile_x_location;
int tile_y_location;
bool is_end;

int find_y_pixel(int x, Image img, int px_color = 0);
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
	
	
	tile_x_location = 0;
	tile_y_location = 120;
	int counter = 0;
	//xstart + 8 при каждом новом тайле
	while(tile_x_location < IMAGE_WIDTH && !is_end)
	{
		cout << "tile_" << counter << "[8] = ";
		build_tile(tile_x_location, img);
		tile_x_location += 8;
		counter++;
	}
       
  
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
int find_y_pixel(int x, Image img, int px_color)
{
	Color control_pixel = img.getPixel(0, 0);
    
	Color pixel;
    //Color set;
	int y = 0;
	
	for(int i = 0; i < IMAGE_HEIGHT; i++)
	{
		pixel = img.getPixel(x, i);
        
        if (px_color > 0)
        {
            switch(px_color)
            {
                case 1: img.setPixel(x, y, Color::Red); break;
                case 2: img.setPixel(x, y, Color::Green); break;
                case 3: img.setPixel(x, y, Color::Blue); break;
                default: img.setPixel(x, y, Color::Black); break;
            }
        }
        
		if (pixel != control_pixel)
		{
			y = i;
            
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
	if (xstart == 0)
	{
		//наклон вправо
		if (end_y > first_y)
		{
			first_level = 0;
		}
		
		//наклон влево
		if (end_y < first_y)
		{
			first_level = 7;
            
		}
		
	}
    
    
    int y = 0;
    int level = 0;
    
    //Тайл ниже предыдущего
    if (first_level > 7) 
    {
        first_level = 0;
		tile_y_location++;
    }
    
    //Тайл выше предыдущего
    if (first_level < 0)
    {
        first_level = 7;
		tile_y_location--;
    }
    
    cout << "{";
    cout << first_level << ",";
    for(int i = xstart + 1; i < xstart + 8; i++)
    {
        y = find_y_pixel(i, img);
		if (y > 0)
        {
            //при наклоне вправо
            if (end_y > first_y)
            {
                level = first_level + (y - first_y);
            }
            
            //при наклоне влево
            if (end_y < first_y)
            {
                level = first_level - (first_y - y);
            }
        }
        else
        {
            is_end = true;
            break;
        }
        
		 
        last_y = y;
        last_level = level;
		
		if (i < xstart + 7)
		{
			cout << level << ",";
		}
		else
		{
			cout << level << "};";
			cout << last_level << "-";
			cout << " //" << "X = " << tile_x_location;
			cout << ", " << "Y = " << tile_y_location << endl;
		}
        
    }
    
}

