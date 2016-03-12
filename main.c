/* 
 * GUNS & RIDERS - Game Boy game
 * 
 * Author: J.M. Climent
 * email: kanfor@yahoo.es
 * 
 * This game was created usind gbdk lib.
 * http://gbdk.sourceforge.net/
 *
 * Created on 5 de March of 2016
 * 
 * ---GNU GENERAL PUBLIC LICENSE---
 */

#include <stdio.h>
#include <gb/gb.h>
#include <string.h>
#include <rand.h>
#include <stdlib.h>
#include "K.c"
#include "gfx.c"

/*
 * 
 */

enum sprites_tiles_8x8
{
    SP_COWBOY1,
    SP_COWBOY2,
    SP_COWBOY3,
    SP_COWBOY4,
    SP_ENEMY1,
    SP_ENEMY2,
    SP_ENEMY3,
    SP_ENEMY4,
    SP_LETTER_P,
    SP_LETTER_O,
    SP_LETTER_I,
    SP_LETTER_N,
    SP_LETTER_T,
    SP_LETTER_S,
    SP_LETTER_0,
    SP_LETTER_1,
    SP_LETTER_2,
    SP_LETTER_3,
    SP_LETTER_4,
    SP_LETTER_5,
    SP_LETTER_6,
    SP_LETTER_7,
    SP_LETTER_8,
    SP_LETTER_9,
    SP_BULLET,
    TOTAL_SPRITES_TILES_8X8
};

enum enum_state
{
    MAIN_TITLE,
    GAME_PLAY,
    GAME_PAUSE,
    GAME_DEAD,
    GAME_OVER
} state;

enum enum_sprites
{
    SPRITE_COWBOY,
    SPRITE_ENEMY1,
    SPRITE_ENEMY2,
    SPRITE_ENEMY3,
    SPRITE_ENEMY4,
    TOTAL_SPRITES
};

//Constants dont work. Mistery. We can use enums instead.
enum enum_total_elements
{
    TOTAL_BULLETS = 5,
    TOTAL_ENEMYS = 4
};

typedef struct
{
    UINT8 x_;
    UINT8 y_;
    BOOLEAN isAlive_;
    BOOLEAN isRightMove_;
} Bullet;
Bullet bulletPlayer[TOTAL_BULLETS];
Bullet bulletEnemy[TOTAL_BULLETS];

typedef struct
{
    UINT8 x_;
    UINT8 y_;
    BOOLEAN isAlive_;
    BOOLEAN isOnScreen_;
    UINT8 numSprite_;
    UINT8 currentFrame_;
    UINT16 timeToChangeFrame_;
} Sprite;
Sprite sprite[TOTAL_SPRITES];

void draw_sprite(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void move_sprite_to(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void update_sprite();

UINT8 print_number(UINT8 number_);

void load_sprites_data();

void load_tiles_game();

void load_tiles_menu();

void paint_points();

//Global variables. Dont use ints. Use UINT8 instead.
UINT8 clock;
UINT8 clock2;
UINT8 frame;
UINT8 pointsX;
UINT8 pointsY;
UINT8 pointsDigit1;
UINT8 pointsDigit2;
UINT8 pointsDigit3;
UINT8 countBulletPlayer;
UINT8 countBulletEnemy;

int main() {
    //Variables.
    UINT8 i;
    UINT8 keys = 0;
    BOOLEAN isInited = FALSE;
    UINT8 tempx = 0;
    UINT8 tempy = 0;
    UINT8 speedEnemy = 0;
    UINT8 scroll = 0;
    UINT8 clockSpeedEnemy = 0;
    UINT8 clockScroll = 0;
    UINT8 timeToMoveEnemy = 2;
    UINT8 timeToScroll = 4;
    UINT8 random = 0;
    UBYTE points[3];
    UBYTE moveUpDown, moveLeftRight;
    BOOLEAN shoot = FALSE;
    
    clock = 0;
    clock2 = 0;
    frame = 0;
    points[0] = 0;
    points[1] = 0;
    points[2] = 0;
    moveUpDown = 0;
    moveLeftRight = 0;
    pointsX = 48;
    pointsY = 20;
    pointsDigit1 = 0;
    pointsDigit2 = 5;
    pointsDigit3 = 8;
    countBulletPlayer = 0;
    countBulletEnemy = 0;
    
    /*for (i = 0; i < TOTAL_BULLETS; i++)
    {
        bulletPlayer[i].isAlive_ = FALSE;
        bulletPlayer[i].isRightMove_ = FALSE;
        bulletPlayer[i].x_ = -10;
        bulletPlayer[i].y_ = -10;
        bulletEnemy[i].isAlive_ = FALSE;
        bulletEnemy[i].isRightMove_ = TRUE;
        bulletEnemy[i].x_ = -10;
        bulletEnemy[i].y_ = -10;
    }*/
    bulletPlayer[0].x_ = -10;
    bulletPlayer[0].y_ = 100;

    //Cowboy
    sprite[SPRITE_COWBOY].x_ = 40;
    sprite[SPRITE_COWBOY].y_ = 80;
    sprite[SPRITE_COWBOY].isAlive_ = 1;
    sprite[SPRITE_COWBOY].isOnScreen_ = 1;
    sprite[SPRITE_COWBOY].numSprite_ = 0;
    sprite[SPRITE_COWBOY].currentFrame_ = 0;
    sprite[SPRITE_COWBOY].timeToChangeFrame_ = 7;
    
    //Enemy
    for (i = 0; i < TOTAL_ENEMYS; i++)
    {
        random = Krand();
        if (random < 56)
        {
            random = 56;
        }
        if (random > 128)
        {
            random = 128;
        }
        sprite[SPRITE_ENEMY1 + i].x_ = 160 + (i*50);
        sprite[SPRITE_ENEMY1 + i].y_ = random;
        sprite[SPRITE_ENEMY1 + i].isAlive_ = 1;
        sprite[SPRITE_ENEMY1 + i].isOnScreen_ = 1;
        sprite[SPRITE_ENEMY1 + i].numSprite_ = 4 + (4*i);
        sprite[SPRITE_ENEMY1 + i].currentFrame_ = 0;
        sprite[SPRITE_ENEMY1 + i].timeToChangeFrame_ = 7;
    }
    
    SPRITES_8x8;

    load_sprites_data();
    
    state = MAIN_TITLE;

    while (1) {
        
        Kwait_vbl_done();
        
        switch(state)
        {
            // <editor-fold defaultstate="collapsed" desc="MAIN TITLE">
            case MAIN_TITLE:
                if (!isInited) {
                    load_tiles_menu();
                    isInited = TRUE;
                    SHOW_BKG;
                }
                clock2++;
                if (clock2 > 25) {
                    //Kgotoxy(4, 14);
                    //Kgprint("PRESS  START");
                }
                if (clock2 > 50) {
                    //Kgotoxy(4, 14);
                    //Kgprint("            ");
                    clock2 = 0;
                }
                keys = Kjoypad();
                if (keys & (J_START)) {
                    load_tiles_game();
                    state = GAME_PLAY;
                }

                break; // </editor-fold>

            case GAME_PLAY:
                SHOW_SPRITES;
                SHOW_BKG;
                if (!isInited)
                {
                    isInited = TRUE;
                }
                
                //////////
                //UPDATE//
                //////////
                update_sprite();
                
                //////////////////
                //UPDATE BULLETS//
                //////////////////       
                if (shoot)
                {
                    bulletPlayer[0].x_ = sprite[SPRITE_COWBOY].x_ + 4;
                    bulletPlayer[0].y_ = sprite[SPRITE_COWBOY].y_ + 8;
                    shoot = FALSE;
                }
                if (bulletPlayer[0].isAlive_)
                {
                    bulletPlayer[0].x_ += 1;
                    Kmove_sprite(36, bulletPlayer[0].x_, bulletPlayer[0].y_);
                }
                if (bulletPlayer[0].x_ > 168)
                {
                    bulletPlayer[0].x_ = -10;
                    bulletPlayer[0].isAlive_ = FALSE;
                }
                
/*
                for (i = 0; i < TOTAL_BULLETS; i++)
                {
                    //if (bulletPlayer[i].isAlive_)
                    {
                        bulletPlayer[i].x_ += 2;
                        //Kmove_sprite(36, bulletPlayer[i].x_, bulletPlayer[i].y_);
                        Kmove_sprite(36, 10, 10);
                    }
                    if (bulletPlayer[i].x_ > 150)
                    {
                        bulletPlayer[i].x_ = -10;
                        bulletPlayer[i].isAlive_ = FALSE;
                    }
                }
*/
                
                //////////
                //SCROLL//
                //////////
                clockSpeedEnemy++;
                if (clockSpeedEnemy > timeToMoveEnemy)
                {
                    clockSpeedEnemy = 0;
                    speedEnemy = 1;
                }
                else
                {
                    speedEnemy = 0;
                }
                clockScroll++;
                if (clockScroll > timeToScroll)
                {
                    clockScroll = 0;
                    scroll = 1;
                }
                else
                {
                    scroll = 0;
                }
                Kscroll_bkg(scroll, 0);
                
                //////////////////
                //UPDATE SPRITES//
                //////////////////
                tempx = sprite[SPRITE_COWBOY].x_;
                tempy = sprite[SPRITE_COWBOY].y_;
                draw_sprite(sprite[SPRITE_COWBOY].numSprite_, tempx, tempy);

                for (i = 0; i < TOTAL_ENEMYS; i++)
                {
                    sprite[SPRITE_ENEMY1 + i].x_ -= speedEnemy;
                    tempx = sprite[SPRITE_ENEMY1 + i].x_;
                    tempy = sprite[SPRITE_ENEMY1 + i].y_;
                    draw_sprite(sprite[SPRITE_ENEMY1 + i].numSprite_, tempx, tempy);
                }

                ///////
                //HUD//
                ///////
                paint_points();
                
                ////////////
                //CONTROLS//
                ////////////
                keys = Kjoypad();
                moveUpDown = 0;
                moveLeftRight = 0;
                if( keys & (J_RIGHT)){
                    moveLeftRight = 1;
                }
                if( keys & (J_LEFT)){
                    moveLeftRight = -1;
                }
                if( keys & (J_UP)){
                    moveUpDown = -1;
                }
                if( keys & (J_DOWN)){
                    moveUpDown = 1;
                }
                if ( keys & (J_A) && !bulletPlayer[0].isAlive_)
                {
                    //Shoot.
                    shoot = TRUE;
                    bulletPlayer[0].isAlive_ = TRUE;

                }
                if (keys)
                {
                    move_sprite_to(sprite[SPRITE_COWBOY].numSprite_,moveLeftRight, moveUpDown);
                }
                break;
                }   
            }


}                   

void move_sprite_to(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    if (sprite[SPRITE_COWBOY].y_ > 128)
    {
        sprite[SPRITE_COWBOY].y_ = 128;
        y_ = 0;
    }
    if (sprite[SPRITE_COWBOY].y_ < 56)
    {
        sprite[SPRITE_COWBOY].y_ = 56;
        y_ = 0;
    }
    
    Kscroll_sprite(numSprite_, x_, y_);
    Kscroll_sprite(numSprite_ + 1, x_, y_);
    Kscroll_sprite(numSprite_ + 2, x_, y_);
    Kscroll_sprite(numSprite_ + 3, x_, y_);
    
    sprite[numSprite_].x_ += x_;
    sprite[numSprite_].y_ += y_;
}

void draw_sprite(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    if (frame == 0)
    {
        Kmove_sprite(numSprite_, x_, y_);
        Kmove_sprite(numSprite_ + 1, x_, y_ + 8);
        
        Kmove_sprite(numSprite_ + 2, -50, -50);
        Kmove_sprite(numSprite_ + 3, -50, -50);
    }
    else
    {
        Kmove_sprite(numSprite_ + 2, x_, y_);
        Kmove_sprite(numSprite_ + 3, x_, y_ + 8);
        
        Kmove_sprite(numSprite_, -50, -50);
        Kmove_sprite(numSprite_ + 1, -50, -50);
    }
}

void update_sprite()
{
    clock++;
    if (clock > 7)
    {
        //draw_sprite(sprite[numSprite_].numSprite_, sprite[numSprite_].x_, sprite[numSprite_].y_);
        clock = 0;
        frame++;
        
        if (frame > 1)
        {
            frame = 0;
        }
    }
}

UINT8 print_number(UINT8 number_)
{
    switch(number_)
    {
        case 0:
            return 26;
            break;
        case 1:
            return 27;
            break;
        case 2:
            return 28;
            break;
        case 3:
            return 29;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 32;
            break;
        case 7:
            return 33;
            break;
        case 8:
            return 34;
            break;
        case 9:
            return 35;
            break;
    }
}

void load_sprites_data()
{
    int i = 0;
    Kset_sprite_data(0, TOTAL_SPRITES_TILES_8X8, sprites);
    
    //Sprites.
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_, 0);
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_ + 1, 1);
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_ + 2, 2);
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_ + 3, 3);
    
    for (i = 0; i < TOTAL_ENEMYS; i++)
    {
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_, 4);
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_ + 1, 5);
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_ + 2, 6);
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_ + 3, 7);
    }
    
    //Fonts.
    for (i = 0; i < 16; i++)
    {
        Kset_sprite_tile(20 + i, 8 + i);
    }
    
    //Bullet.
    Kset_sprite_tile(36, 24);
}

void paint_points()
{
    //Text.
    Kmove_sprite(20, pointsX, pointsY);
    Kmove_sprite(21, pointsX + 8, pointsY);
    Kmove_sprite(22, pointsX + 16, pointsY);
    Kmove_sprite(23, pointsX + 24 , pointsY);
    Kmove_sprite(24, pointsX + 32, pointsY);
    Kmove_sprite(25, pointsX + 40, pointsY);
    //Numbers.
    Kmove_sprite(print_number(pointsDigit1), pointsX + 56, pointsY);
    Kmove_sprite(print_number(pointsDigit2), pointsX + 64, pointsY);
    Kmove_sprite(print_number(pointsDigit3), pointsX + 72, pointsY);
}

void load_tiles_game()
{
    int i = 0;
    Kset_bkg_data(0, 32, bkgdata);
    
    //Clean garbage memery.
    for (i = 0; i < 17; i++)
    {
        Kset_bkg_tiles(0,i,32,1,clear);
    }

    //Mountains.
    Kset_bkg_tiles(0,3,25,1,tilesmap);
    Kset_bkg_tiles(0,4,25,1,tilesmap2);
    //Gradient.
    Kset_bkg_tiles(0,5,32,1,tilesmap3);
    Kset_bkg_tiles(0,6,32,1,tilesmap4);
    //Cactus.
    Kset_bkg_tiles(0,16,32,1,tilesmap5);
    Kset_bkg_tiles(0,17,32,1,tilesmap6);
}

void load_tiles_menu()
{
    int i = 0;
    Kset_bkg_data(0, 154, menudata);
    
    //Clean garbage memery.
    for (i = 0; i < 17; i++)
    {
        Kset_bkg_tiles(0,i,32,1,menuClear);
    }
    
    Kset_bkg_tiles(0,0,20,18,gunsriders_map);
}