// 2PlayerPacMan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

int main()
{
    std::cout << "Hello World!\n";
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    if (!display)
        return -1;

    ALLEGRO_FONT* font = al_load_ttf_font("Pacifico.ttf", 64, 0);
    if (!font)
        return -2;
    
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0, 0, 0), 20, 20, 0, "hello andrew!");
    al_flip_display();

    al_rest(5);

    al_destroy_font(font);
    al_destroy_display(display);

    return 0;
}