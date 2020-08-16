#include "inicia.h"
#include <allegro.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

void inicia::allegro(int ANCHO_ , int ALTO_){
    allegro_init();

    install_keyboard();
    install_mouse();

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_, ALTO_, 0, 0);
}

int inicia::audio(int izquierda, int derecha){
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }

	set_volume(izquierda, derecha);
}
