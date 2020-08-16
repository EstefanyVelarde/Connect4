#include <allegro.h>
#include "inicia.h"

#define LENGHT 800
#define WIDTH 576

#include <iostream>

using namespace std;


class pMenu {
    BITMAP *buffer, *background, *background1, *background2, *background3, *cursor;

public:
    pMenu(char *bgName1, char *bgName2, char *bgName3, char *cursorName);

    int draw();
};

pMenu::pMenu(char *bgName1, char *bgName2, char *bgName3, char *cursorName) {
    background1 = load_bitmap(bgName1, NULL);
    background2 = load_bitmap(bgName2, NULL);
    background3 = load_bitmap(bgName3, NULL);
    cursor = load_bitmap(cursorName, NULL);

    buffer = create_bitmap(LENGHT, WIDTH);

    background = background1;
}

int pMenu::draw() {
    int exit = 0;

    while(exit == 0 && !key[KEY_ESC]) {
        if(mouse_x > 306 && mouse_x < 493 &&
           mouse_y > 278 && mouse_y < 329) {
            background = background2;

            if(mouse_b & 1)
                exit = 1;

        } else
            if(mouse_x > 306 && mouse_x < 493 &&
               mouse_y > 359 && mouse_y < 408) {

                background = background3;

                if(mouse_b & 1)
                    exit = -1;

            } else
                background = background1;

        blit(background, buffer, 0, 0, 0, 0, LENGHT, WIDTH);
        draw_sprite(buffer, cursor, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, LENGHT, WIDTH);
    }

    return exit;
}


int color[6][7] = {{0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0},  //0 = null, 1 = red, -1 = yellow
                   {0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0}};

int coord_x[7] = {202, 259, 317, 375, 432, 489, 548};
int coord_y[6] = {174, 232, 289, 346, 404, 462};
int turn = 1;

bool gameover;


void add(int column)  {
    int i = 5;

    while(color[i][column] != 0 && i >= 0 )
        i--;

    if(i >= 0) {
        color[i][column] = turn;
        turn *= -1;
    }
}

void check() {
    int red, yellow;

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
            if(color[i][j] == 1)
                red++;
            if(color[i][j] == -1)
                yellow++;

            if(red == 4)
                gameover = true;
            if(yellow == 4)
                gameover = true;

        }
    }
}

int main()
{
    inicia in;
    in.allegro(LENGHT, WIDTH);
    in.audio(70, 70);
    install_mouse();

    BITMAP *buffer = create_bitmap(LENGHT, WIDTH);
    BITMAP *cursor = load_bitmap("cursor.bmp", NULL);
    BITMAP *background = load_bitmap("pantalla-juego.bmp", NULL);
    BITMAP *board = load_bitmap("tablero.bmp", NULL);
    BITMAP *disc1 = load_bitmap("ficha-roja.bmp", NULL);
    BITMAP *disc2 = load_bitmap("ficha-amarilla.bmp", NULL);
    BITMAP *disc = disc1;
 //   BITMAP *button1 = load_bitmap("boton-regresar.bmp", NULL);
 //   BITMAP *button2 = load_bitmap("boton-regresar2.bmp", NULL);

    pMenu M("menu.bmp", "menu-iniciar.bmp", "menu-salir.bmp", "cursor.bmp");

    bool exit, re_menu;

    do {
        if(M.draw() == -1) {
            exit = true;
            re_menu = false;
        } else
            re_menu = true;

        while(!exit && !key[KEY_ESC] && !gameover) {
            blit(background, buffer, 0, 0, 0, 0, LENGHT, WIDTH);

            //MOUSE ON BOARD
            if(mouse_x > 180 && mouse_x < 617 &&
               mouse_y > 153 && mouse_y < 529) {

                if(turn == 1) disc = disc1;
                else disc = disc2;

                if(mouse_x > 200 && mouse_x < 255) {
                    draw_sprite(buffer, disc, 200, 102);

                    if(mouse_b & 1) {
                        add(0);
                        rest(500);
                    }
                }

                if(mouse_x > 255 && mouse_x < 314) {
                    draw_sprite(buffer, disc, 255, 102);

                    if(mouse_b & 1) {
                        add(1);
                        rest(500);
                    }
                }

                if(mouse_x > 314 && mouse_x < 371) {
                    draw_sprite(buffer, disc, 314, 102);

                    if(mouse_b & 1) {
                        add(2);
                        rest(500);
                    }
                }

                if(mouse_x > 371 && mouse_x < 429) {
                    draw_sprite(buffer, disc, 371, 102);

                    if(mouse_b & 1) {
                        add(3);
                        rest(500);
                    }
                }

                if(mouse_x > 429 && mouse_x < 486) {
                    draw_sprite(buffer, disc, 429, 102);

                    if(mouse_b & 1) {
                        add(4);
                        rest(500);
                    }
                }

                if(mouse_x > 486 && mouse_x < 545) {
                    draw_sprite(buffer, disc, 486, 102);

                    if(mouse_b & 1) {
                        add(5);
                        rest(500);
                    }
                }

                if(mouse_x > 545 && mouse_x < 602) {
                    draw_sprite(buffer, disc, 545, 102);

                    if(mouse_b & 1) {
                        add(6);
                        rest(500);
                    }
                }
            }


            for(int i = 0; i < 6; i++) {
                for(int j = 0; j < 7; j++) {
                    if(color[i][j] == 1)
                        draw_sprite(buffer, disc1, coord_x[j], coord_y[i]);

                    if(color[i][j] == -1)
                        draw_sprite(buffer, disc2, coord_x[j], coord_y[i]);
                }
            }

            draw_sprite(buffer, board, 171, 141);
            draw_sprite(buffer, cursor, mouse_x, mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, LENGHT, WIDTH);

            //check();
        }
    } while(re_menu);
    return 0;
}
END_OF_MAIN();
