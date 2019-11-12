#pragma once

typedef enum {
    player_left = 0,
    player_right = 1,
} pong_player_t;

typedef enum {
    clockwise = 0,
    anticlockwise = 1,
    pressed = 2
} pong_input_t;

void pong_frame(void);

void pong_press(pong_player_t player);
void pong_input(pong_player_t player, pong_input_t input);

void pong_init(void);
void pong_reset(void);
