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
#include "music.c"

// <editor-fold defaultstate="collapsed" desc="ENUMS, FUNCTIONS AND GLOBAL VARIABLES">
enum limits_game
{
    K_WIDTH = 160,
    K_HEIGHT = 144,
    K_LIMIT_UP = 56,
    K_LIMIT_DOWN = 128
};
//This enum is to count the total tiles of sprites I must to load.
enum sprites_tiles_8x8 {
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
    SP_ENEMY_DEAD1,
    SP_ENEMY_DEAD2,
    TOTAL_SPRITES_TILES_8X8
};

enum enum_state {
    MAIN_TITLE,
    GAME_PLAY,
    GAME_PAUSE,
    GAME_DEAD,
    GAME_OVER
} state;

enum enum_sprites {
    SPRITE_COWBOY,
    SPRITE_ENEMY1,
    SPRITE_ENEMY2,
    SPRITE_ENEMY3,
    SPRITE_ENEMY4,
    TOTAL_SPRITES
};

//Constants dont work. We can use enums instead.

enum enum_total_elements {
    TOTAL_BULLETS = 5,
    TOTAL_ENEMYS = 4
};

enum enum_first_tile_sprite {
    TILE_COWBOY = 0,
    TILE_ENEMY = 4,
    TILE_LETTER = 8,
    TILE_BULLET = 24,
    TILE_ENEMY_DEAD = 25
};

enum enum_sprite_letter {
    SPRITE_LETTER = 10,
    SPRITE_BULLET = 26
};

typedef struct {
    UINT8 x_;
    UINT8 y_;
    BOOLEAN isAlive_;
    BOOLEAN isReadyToMove_;
    BOOLEAN isRightMove_;
} Bullet;
Bullet bulletPlayer[TOTAL_BULLETS];
Bullet bulletEnemy[TOTAL_BULLETS];

typedef struct {
    UINT8 x_;
    UINT8 y_;
    BOOLEAN isAlive_;
    BOOLEAN isOnScreen_;
    UINT8 numSprite_;
    UINT8 numTile_;
    UINT8 currentFrame_;
    UINT16 timeToChangeFrame_;
    UINT8 timeToCheckCollision_;
    UINT8 timeDeadReset_;
} Sprite;
Sprite sprite[TOTAL_SPRITES];

void draw_sprite_conwboy(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void draw_sprite_enemy(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void draw_sprite_enemy_dead(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void move_sprite_to(UINT8 numSprite_, UINT8 x_, UINT8 y_);

void update_sprite();

UINT8 get_random_y();

UINT8 print_number(UINT8 number_);

void load_sprites_data();

void load_tiles_game();

void load_tiles_menu();

void paint_points();

void sound_init();

void sound_shoot();

void sound_dead_enemy();

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
UINT8 countBulletEnemy; // </editor-fold>

int main() {
    
    // <editor-fold defaultstate="collapsed" desc="INIT VARIABLES">
    //Variables.
    UINT8 i;
    UINT8 j;
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
    UBYTE points[3];
    UBYTE moveUpDown, moveLeftRight;
    BOOLEAN isPossibleToShoot = TRUE;
    UINT8 timePauseShoot = 0;
    UINT8 totalTimePauseShoot = 15;
    UINT8 totalTimeCheclCollision = 2;
    UINT8 timeDeadEnemyReset = 20;

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
    countBulletPlayer = 1;
    countBulletEnemy = 0;

    for (i = 0; i < TOTAL_BULLETS; i++) {
        bulletPlayer[i].isAlive_ = FALSE;
        bulletPlayer[i].isRightMove_ = FALSE;
        bulletPlayer[i].isReadyToMove_ = FALSE;
        bulletPlayer[i].x_ = 20;
        bulletPlayer[i].y_ = 20;

        bulletEnemy[i].isAlive_ = FALSE;
        bulletEnemy[i].isRightMove_ = TRUE;
        bulletEnemy[i].x_ = 20;
        bulletEnemy[i].y_ = 20;
    }

    //Cowboy
    sprite[SPRITE_COWBOY].x_ = 40;
    sprite[SPRITE_COWBOY].y_ = 80;
    sprite[SPRITE_COWBOY].isAlive_ = TRUE;
    sprite[SPRITE_COWBOY].isOnScreen_ = TRUE;
    sprite[SPRITE_COWBOY].numSprite_ = 0;
    sprite[SPRITE_COWBOY].numTile_ = TILE_COWBOY;
    sprite[SPRITE_COWBOY].currentFrame_ = 0;
    sprite[SPRITE_COWBOY].timeToChangeFrame_ = 7;

    //Enemy
    for (i = 0; i < TOTAL_ENEMYS; i++) {
        sprite[SPRITE_ENEMY1 + i].x_ = K_WIDTH + (i * 25);
        sprite[SPRITE_ENEMY1 + i].y_ = get_random_y();
        sprite[SPRITE_ENEMY1 + i].isAlive_ = TRUE;
        sprite[SPRITE_ENEMY1 + i].isOnScreen_ = TRUE;
        sprite[SPRITE_ENEMY1 + i].numSprite_ = 2 + (2 * i);
        sprite[SPRITE_ENEMY1 + i].numTile_ = TILE_ENEMY;
        sprite[SPRITE_ENEMY1 + i].currentFrame_ = 0;
        sprite[SPRITE_ENEMY1 + i].timeToChangeFrame_ = 7;
        sprite[SPRITE_ENEMY1 + i].timeToCheckCollision_ = 0;
        sprite[SPRITE_ENEMY1 + i].timeDeadReset_ = 0;
    }

    SPRITES_8x8;

    HIDE_BKG;
    HIDE_SPRITES;
    
    load_sprites_data();

    state = MAIN_TITLE; // </editor-fold>

    while (1) {
        
        Kwait_vbl_done();
        
        switch(state)
        {
            // <editor-fold defaultstate="collapsed" desc="MAIN TITLE">
            case MAIN_TITLE:
                if (!isInited) {
                    sound_init();
                    load_tiles_menu();
                    isInited = TRUE;
                    playChannel1();
                    SHOW_BKG;
                }
                timerInterrupt();
                clock2++;
                if (clock2 > 25) {
                    Kset_bkg_tiles(0,14,20,1,gunsriders_press_on);
                }
                if (clock2 > 50) {
                    Kset_bkg_tiles(0,14,20,1,gunsriders_press_off);
                    clock2 = 0;
                }
                keys = Kjoypad();
                if (keys & (J_START)) {
                    HIDE_BKG;
                    HIDE_SPRITES;
                    load_tiles_game();
                    state = GAME_PLAY;
                    isInited = FALSE;
                }

                break; // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="GAME_PLAY">
            case GAME_PLAY:
                if (!isInited)
                {
                    isInited = TRUE;
                    SHOW_BKG;
                    SHOW_SPRITES;
                }

                //////////
                //UPDATE//
                //////////
                update_sprite();

                // <editor-fold defaultstate="collapsed" desc="BULLETS">
                //////////////////
                //UPDATE BULLETS//
                //////////////////
                if (!isPossibleToShoot)
                {
                    timePauseShoot++;
                    if (timePauseShoot > totalTimePauseShoot)
                    {
                        timePauseShoot = 0;
                        isPossibleToShoot = TRUE;
                    }
                }
                for (i = 1; i < TOTAL_BULLETS; i++)
                {
                    if (bulletPlayer[i].isAlive_)
                    {
                        if (!bulletPlayer[i].isReadyToMove_)
                        {
                            sound_shoot();

                            bulletPlayer[i].x_ = sprite[SPRITE_COWBOY].x_ + 4;
                            bulletPlayer[i].y_ = sprite[SPRITE_COWBOY].y_ + 7 /*+ (i*2)*/;
                            bulletPlayer[i].isReadyToMove_ = TRUE;
                        }
                        bulletPlayer[i].x_ += 2;
                        Kmove_sprite(SPRITE_BULLET + i, bulletPlayer[i].x_, bulletPlayer[i].y_);
                    }
                    if (bulletPlayer[i].x_ > 165)
                    {
                        bulletPlayer[i].x_ = -10;
                        bulletPlayer[i].isAlive_ = FALSE;
                        bulletPlayer[i].isReadyToMove_ = FALSE;
                    }
                }// </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="SCROLL">
                //////////
                //SCROLL//
                //////////
                clockSpeedEnemy++;
                if (clockSpeedEnemy > timeToMoveEnemy) {
                    clockSpeedEnemy = 0;
                    speedEnemy = 1;
                } else {
                    speedEnemy = 0;
                }
                clockScroll++;
                if (clockScroll > timeToScroll) {
                    clockScroll = 0;
                    scroll = 1;
                } else {
                    scroll = 0;
                }
                Kscroll_bkg(scroll, 0); // </editor-fold>

                // <editor-fold defaultstate="collapsed" desc="SPRITES">
                //////////////////
                //UPDATE SPRITES//
                //////////////////
                tempx = sprite[SPRITE_COWBOY].x_;
                tempy = sprite[SPRITE_COWBOY].y_;
                draw_sprite_conwboy(sprite[SPRITE_COWBOY].numSprite_, tempx, tempy);

                for (i = 0; i < TOTAL_ENEMYS; i++)
                {   
                    if (sprite[SPRITE_ENEMY1 + i].isAlive_)
                    {
                        if (speedEnemy == 1)
                        {
                            sprite[SPRITE_ENEMY1 + i].x_ -= speedEnemy;
                            tempx = sprite[SPRITE_ENEMY1 + i].x_;
                            tempy = sprite[SPRITE_ENEMY1 + i].y_;
                            draw_sprite_enemy(sprite[SPRITE_ENEMY1 + i].numSprite_, tempx, tempy); 
                            /////////////////////////
                            //COLLISION WITH BULLET//
                            /////////////////////////
                            sprite[SPRITE_ENEMY1 + i].timeToCheckCollision_++;
                            if (sprite[SPRITE_ENEMY1 + i].timeToCheckCollision_ > totalTimeCheclCollision)
                            {
                                sprite[SPRITE_ENEMY1 + i].timeToCheckCollision_ = 0;
                                for (j = 0; j < TOTAL_BULLETS; j++)
                                {
                                    if (bulletPlayer[j].isAlive_)
                                    {
                                        if (bulletPlayer[j].x_ > tempx - 16)
                                        {
                                            if (bulletPlayer[j].x_ < tempx + 8)
                                            {
                                                if (bulletPlayer[j].y_ > tempy - 1)
                                                {
                                                    if (bulletPlayer[j].y_ < tempy + 16)
                                                    {
                                                        //sprite[SPRITE_ENEMY1 + i].x_ = 170;
                                                        sprite[SPRITE_ENEMY1 + i].isAlive_ = FALSE;
                                                        bulletPlayer[j].isAlive_ = FALSE;
                                                        bulletPlayer[j].isReadyToMove_ = FALSE;
                                                        Kmove_sprite(SPRITE_BULLET + j, -10, -10);
                                                        sound_dead_enemy();
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        sprite[SPRITE_ENEMY1 + i].x_ -= scroll;
                        tempx = sprite[SPRITE_ENEMY1 + i].x_;
                        tempy = sprite[SPRITE_ENEMY1 + i].y_;
                        draw_sprite_enemy_dead(sprite[SPRITE_ENEMY1 + i].numSprite_, tempx, tempy);
                        
                        sprite[SPRITE_ENEMY1 + i].timeDeadReset_++;
                        if (sprite[SPRITE_ENEMY1 + i].timeDeadReset_ > timeDeadEnemyReset)
                        {
                            sprite[SPRITE_ENEMY1 + i].timeDeadReset_ = 0;
                            //Reset enemy.
                            sprite[SPRITE_ENEMY1 + i].x_ = 170;
                            sprite[SPRITE_ENEMY1 + i].y_ = get_random_y();
                            sprite[SPRITE_ENEMY1 + i].isAlive_ = TRUE;
                        }
                    }
                }
                // </editor-fold>

                ///////
                //HUD//
                ///////
                paint_points();

                // <editor-fold defaultstate="collapsed" desc="CONTROLS">
                ////////////
                //CONTROLS//
                ////////////
                keys = Kjoypad();
                moveUpDown = 0;
                moveLeftRight = 0;
                if (keys & (J_RIGHT)) {
                    moveLeftRight = 1;
                }
                if (keys & (J_LEFT)) {
                    moveLeftRight = -1;
                }
                if (keys & (J_UP)) {
                    moveUpDown = -1;
                }
                if (keys & (J_DOWN)) {
                    moveUpDown = 1;
                }
                if (keys & (J_A) /*&& !bulletPlayer[1].isAlive_*/) {
                    if (isPossibleToShoot)
                    {
                        isPossibleToShoot = FALSE;
                        bulletPlayer[countBulletPlayer].isAlive_ = TRUE;
                        bulletPlayer[countBulletPlayer].isReadyToMove_ = FALSE;
                        countBulletPlayer++;
                        if (countBulletPlayer >= TOTAL_BULLETS)
                        {
                            countBulletPlayer = 1;
                        }
                    }
                }
                if (keys) {
                    move_sprite_to(sprite[SPRITE_COWBOY].numSprite_, moveLeftRight, moveUpDown);
                }
                break;
        }// </editor-fold>
    }// </editor-fold>
}                   

void move_sprite_to(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    if (sprite[SPRITE_COWBOY].y_ > K_LIMIT_DOWN)
    {
        sprite[SPRITE_COWBOY].y_ = K_LIMIT_DOWN;
        y_ = 0;
    }
    if (sprite[SPRITE_COWBOY].y_ < K_LIMIT_UP)
    {
        sprite[SPRITE_COWBOY].y_ = K_LIMIT_UP;
        y_ = 0;
    }
    
    Kscroll_sprite(numSprite_, x_, y_);
    Kscroll_sprite(numSprite_ + 1, x_, y_);
    
    sprite[numSprite_].x_ += x_;
    sprite[numSprite_].y_ += y_;
}

void draw_sprite_conwboy(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    int i = 0;
    if (frame == 0)
    {
        Kset_sprite_tile(numSprite_, TILE_COWBOY);
        Kset_sprite_tile(numSprite_ + 1, TILE_COWBOY + 1);
    }
    else
    {
        Kset_sprite_tile(numSprite_, TILE_COWBOY + 2);
        Kset_sprite_tile(numSprite_ + 1, TILE_COWBOY + 3);
    }
    Kmove_sprite(numSprite_, x_, y_);
    Kmove_sprite(numSprite_ + 1, x_, y_ + 8);
}

void draw_sprite_enemy(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    int i = 0;
    if (frame == 0)
    {
        Kset_sprite_tile(numSprite_ + (2 * i), TILE_ENEMY);
        Kset_sprite_tile(numSprite_+ 1 + (2 * i) , TILE_ENEMY + 1);
    }
    else
    {
        Kset_sprite_tile(numSprite_ + (2 * i), TILE_ENEMY + 2);
        Kset_sprite_tile(numSprite_ + 1 + (2 * i) , TILE_ENEMY + 3);
    }
    Kmove_sprite(numSprite_, x_, y_);
    Kmove_sprite(numSprite_ + 1, x_, y_ + 8);
}

void draw_sprite_enemy_dead(UINT8 numSprite_, UINT8 x_, UINT8 y_)
{
    int i = 0;
    Kset_sprite_tile(numSprite_ + (2 * i), TILE_ENEMY_DEAD);
    Kset_sprite_tile(numSprite_+ 1 + (2 * i) , TILE_ENEMY_DEAD + 1);
    
    Kmove_sprite(numSprite_, x_, y_ + 8);
    Kmove_sprite(numSprite_ + 1, x_ + 8, y_ + 8);
}

void update_sprite()
{
    clock++;
    if (clock > 7)
    {
        clock = 0;
        frame++;
        
        if (frame > 1)
        {
            frame = 0;
        }
    }
}

UINT8 get_random_y()
{
    UINT8 random = Krand();
    
    while (random > K_LIMIT_DOWN - K_LIMIT_UP)
    {
        random = Krand();
    }
    
    return random + K_LIMIT_UP;
}

UINT8 print_number(UINT8 number_)
{
    switch(number_)
    {
        case 0:
            return SPRITE_LETTER + 6;
            break;
        case 1:
            return SPRITE_LETTER + 7;
            break;
        case 2:
            return SPRITE_LETTER + 8;
            break;
        case 3:
            return SPRITE_LETTER + 9;
            break;
        case 4:
            return SPRITE_LETTER + 10;
            break;
        case 5:
            return SPRITE_LETTER + 11;
            break;
        case 6:
            return SPRITE_LETTER + 12;
            break;
        case 7:
            return SPRITE_LETTER + 13;
            break;
        case 8:
            return SPRITE_LETTER + 14;
            break;
        case 9:
            return SPRITE_LETTER + 15;
            break;
    }
}

void load_sprites_data()
{
    int i = 0;
    Kset_sprite_data(0, TOTAL_SPRITES_TILES_8X8, sprites);
    
    //Sprites.
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_, TILE_COWBOY);
    Kset_sprite_tile(sprite[SPRITE_COWBOY].numSprite_ + 1, TILE_COWBOY + 1);
    
    for (i = 0; i < TOTAL_ENEMYS; i++)
    {
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_, TILE_COWBOY);
        Kset_sprite_tile(sprite[SPRITE_ENEMY1 + i].numSprite_ + 1, TILE_COWBOY + 1);
    }
    
    //Fonts.
    for (i = 0; i < 16; i++)
    {
        Kset_sprite_tile(SPRITE_LETTER + i, TILE_LETTER + i);
    }
    
    //Bullet.
    for (i = 0; i < TOTAL_BULLETS; i++)
    {
        Kset_sprite_tile(SPRITE_BULLET + i, TILE_BULLET);
    }
}

void paint_points()
{
    //Text.
    Kmove_sprite(SPRITE_LETTER, pointsX, pointsY);
    Kmove_sprite(SPRITE_LETTER + 1, pointsX + 8, pointsY);
    Kmove_sprite(SPRITE_LETTER + 2, pointsX + 16, pointsY);
    Kmove_sprite(SPRITE_LETTER + 3, pointsX + 24 , pointsY);
    Kmove_sprite(SPRITE_LETTER + 4, pointsX + 32, pointsY);
    Kmove_sprite(SPRITE_LETTER + 5, pointsX + 40, pointsY);
    //Numbers.
    Kmove_sprite(print_number(pointsDigit1), pointsX + 56, pointsY);
    Kmove_sprite(print_number(pointsDigit2), pointsX + 64, pointsY);
    Kmove_sprite(print_number(pointsDigit3), pointsX + 72, pointsY);
}

void load_tiles_game()
{
    int i = 0;
    Kset_bkg_data(0, 50, bkgdata);
    
    //Clean garbage memery.
    for (i = 0; i < 17; i++)
    {
        Kset_bkg_tiles(0,i,50,1,clear);
    }

    Kset_bkg_tiles( 0, 0, 32, 18, background_map);
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

void sound_init()
{
    NR52_REG = 0xFFU;
    NR51_REG = 0x00U;
    NR50_REG = 0x77U;
}

void sound_dead_enemy()
{
    NR41_REG = 0x0FU;
    NR42_REG = 0xF3U;
    NR43_REG = 100;
    NR44_REG = 0xC0U;
    NR51_REG |= 0x88;
}

void sound_shoot()
{
    //Fuego
    //NR41_REG = 0x0FU;
    //NR42_REG = 0xF3U;
    //NR43_REG = 100;
    //NR44_REG = 0xC0U;
    //NR51_REG |= 0x88;
    
    //Item - Coin
    //NR21_REG = 0x80U;
    //NR22_REG = 0x73U;
    //NR23_REG = 0x9AU;
    //NR24_REG = 0xC7U;
    //NR51_REG |= 0x22;
    
    //Electricidad
    //NR52_REG = 0x00;
    //NR52_REG = 0xF8;
    //NR41_REG = 0x0FU;
    //NR42_REG = 0xF3U;
    //NR43_REG = 0x1FU;
    //NR44_REG = 0xC0U;
    //NR51_REG |= 0x88;
    
/*
    NR41_REG = 15;      //Duracion. Mas grande, menos dura.
    NR42_REG = 250;     //Volumen. Mas grande, mas alto.
    NR43_REG = 100;      //Importante. Separacion entre ondas. Claridad - ruido.
    NR44_REG = 192;
    NR51_REG |= 136;    //Parece afectar al stero. No tocar.
*/
    
    NR41_REG = 0x0FU;
    NR42_REG = 0xF3U;
    NR43_REG = 128;
    NR44_REG = 0xC0U;
    NR51_REG |= 0x88;
}