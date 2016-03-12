/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <gb/drawing.h>
#include <types.h>
#include <asm/types.h>
#include <gb/gb.h>

/*
 * 
 */
void Kgprint(char *texto)
{
    gprint(texto);
}

void Kplot_point(UINT8 x, UINT8 y)
{
    plot_point(x, y);
}

void Kdraw_image(unsigned char *data)
{
    draw_image(data);
}

void Kline(UINT8 x1, UINT8 y1, UINT8 x2, UINT8 y2)
{
    line(x1, y1, x2, y2);
}

void Kbox(UINT8 x1, UINT8 y1, UINT8 x2, UINT8 y2, UINT8 style)
{
    box(x1, y1, x2, y2, style);
}

void Kgotoxy(UINT8 x, UINT8 y)
{
    gotogxy(x, y);
}

void Kwait_vbl_done()
{
    wait_vbl_done();
}

UINT8 Kjoypad()
{
    return joypad();
}

void Kset_sprite_data(UINT8 first_tile_, UINT8 nb_tiles_, unsigned char* data)
{
    set_sprite_data(first_tile_, nb_tiles_, data);
}

void Kset_sprite_tile(UINT8 nb_, UINT8 tiles_)
{
    set_sprite_tile(nb_, tiles_);
            
}

void Kmove_sprite(UINT8 nb, UINT8 x, UINT8 y)
{
   move_sprite(nb, x, y); 
}

void Kscroll_sprite(INT8 nb, INT8 x, INT8 y)
{
    scroll_sprite(nb, x, y);
}

void KprintNumber(INT16 number)
{
    gprintln(number, 200 , UNSIGNED);
}

void Kset_bkg_data(UINT8 first_tile, UINT8 nb_tiles, unsigned char *data)
{
    set_bkg_data(first_tile, nb_tiles, data);
}

void Kset_bkg_tiles(UINT8 x, UINT8 y, UINT8 w, UINT8 h, unsigned char *tiles)
{
    set_bkg_tiles(x, y, w, h, tiles);
}

void Kscroll_bkg(INT8 x, INT8 y)
{
    scroll_bkg(x, y);
}

UINT8 Krand()
{
    return rand();
}
