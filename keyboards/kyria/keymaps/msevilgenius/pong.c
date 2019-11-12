#include "pong.h"
#include <stdint.h>
#include <timer.h>

#ifdef OLED_DRIVER_ENABLE
#include "oled_driver.h"
#include <avr/pgmspace.h>
#endif


enum update_flag_bit {
    update_player_left = 0,
    update_player_right = 1,
    update_net = 2,
    update_ball = 3,
    update_score_left = 4,
    update_score_right = 5,
    update_clear_all = 7,
};

#define FLAG_CHECK(a, b) (a & (1 << b))
#define FLAG_CLEAR(a, b) a &= (~(1 << b))
#define FLAG_SET(a, b) a |= (1 << b)

#define ABS(i) ((i < 0) ? (-(i)) : (i))

#define PLAYER_STEP 1
#define PADDLE_HEIGHT 8
#define PADDLE_MAX (64 - PADDLE_HEIGHT)

#define NET_COLUMN 64

#define FRAME_TIME 75

typedef struct {
    int8_t x;
    int8_t y;
} vec2_t;

typedef struct {
    vec2_t position;
    vec2_t velocity;
} ball_t;

ball_t ball = {
    .position = {
        .x = 64,
        .y = 32
    },
    .velocity = {
        .x = 0,
        .y = 0
    }
};

vec2_t prev_ball_pos = { .x = 64, .y = 32 };

uint8_t update_flag = 0;

int8_t player_positions[] = {0, 0};
int8_t player_scores[] = {0, 0};

volatile uint16_t frame_timer = 0;

void pong_reset() {
    prev_ball_pos.x = ball.position.x;
    prev_ball_pos.y = ball.position.y;
    ball.velocity.x = 0;
    ball.velocity.y = 0;
    ball.position.x = 64;
    ball.position.y = 32;
    update_flag = 0 | 1 << update_player_left | 1 << update_player_right | 1 << update_score_left | 1 << update_score_right | 1 << update_ball;
}

void pong_init() {
    pong_reset();
    player_positions[0] = 28;
    player_positions[1] = 28;
    player_scores[0] = 0;
    player_scores[1] = 0;
    FLAG_SET(update_flag, update_clear_all);
    FLAG_SET(update_flag, update_net);
    frame_timer = timer_read();
}

int8_t paddle_bounce_velocity(int8_t hit_pos) {
    if (hit_pos < PADDLE_HEIGHT / 2) {
        return hit_pos - ((PADDLE_HEIGHT / 2) - 1);
    }else{
        return hit_pos - (PADDLE_HEIGHT / 2);
    }
}

void ball_update(void) {
    uint16_t frame_elapsed = 0;

    frame_elapsed = timer_elapsed(frame_timer);

    if (ball.velocity.x == 0) {
        frame_timer = timer_read();
        return;
    }

    if (frame_elapsed < (FRAME_TIME) / (ABS(ball.velocity.x))) {
        return;
    }

    int8_t y_movement = (ball.velocity.y < 0 ? -1 : 1) * (ball.position.x % 3 < ABS(ball.velocity.y) ? 1 : 0);

    vec2_t new_ball_pos = { .x = ball.position.x + (ball.velocity.x < 0 ? -1 : 1), .y = ball.position.y + y_movement };

    if (new_ball_pos.x == 0) {
        // hit left edge
        FLAG_SET(update_flag, update_player_left);
        int8_t collision_y = new_ball_pos.y - player_positions[player_left];

        if (collision_y >= 0 && collision_y < PADDLE_HEIGHT) {
            // hit paddle
            ball.velocity.y = paddle_bounce_velocity(collision_y);
            ball.velocity.x = -ball.velocity.x;
        }else{
            // missed, other player scores
            player_scores[player_right] += 1;
            FLAG_SET(update_flag, update_score_right);
            pong_reset();
            return;
        }
    } else if (new_ball_pos.x == (OLED_DISPLAY_WIDTH - 1)) {
        // hit right edge
        FLAG_SET(update_flag, update_player_right);
        int8_t collision_y = new_ball_pos.y - player_positions[player_right];

        if (collision_y >= 0 && collision_y < PADDLE_HEIGHT) {
            // hit paddle
            ball.velocity.y = paddle_bounce_velocity(collision_y);
            ball.velocity.x = -ball.velocity.x;
        }else{
            // missed, other player scores
            player_scores[player_left] += 1;
            FLAG_SET(update_flag, update_score_left);
            pong_reset();
            return;
        }
    }

    // bounce off top/bottom
    if (new_ball_pos.y < 0){
        ball.velocity.y = -ball.velocity.y;
        new_ball_pos.y = -new_ball_pos.y;
    } else if (new_ball_pos.y > OLED_DISPLAY_HEIGHT - 1) {
        ball.velocity.y = -ball.velocity.y;
        new_ball_pos.y += (OLED_DISPLAY_HEIGHT - 1) - new_ball_pos.y;
    }

    prev_ball_pos.x = ball.position.x;
    prev_ball_pos.y = ball.position.y;
    ball.position.x = new_ball_pos.x;
    ball.position.y = new_ball_pos.y;

    FLAG_SET(update_flag, update_ball);

    frame_timer = timer_read32();
}

uint8_t pre_ball_byte = 0x60;

// this sets the pixel for the ball to 'on' without affecting the other pixels in the byte
// and saves the value of the byte the ball is being drawn on before doing so, so it can be reverted later
void ball_render_func(uint8_t *data, void *user_args) {
    uint8_t ball = *(uint8_t*)user_args;
    pre_ball_byte = *data;
    *data |= ball;
}


void pong_frame() {
#ifdef OLED_DRIVER_ENABLE

    if (FLAG_CHECK(update_flag, update_clear_all)){
        oled_clear();
        FLAG_CLEAR(update_flag, update_clear_all);
        return;
    }


    // update the ball
    ball_update();

    // draw 'net'
    if (FLAG_CHECK(update_flag, update_net)){
        oled_write_byte(NET_COLUMN, 0, 0x60);
        oled_write_byte(NET_COLUMN, 1, 0x60);
        oled_write_byte(NET_COLUMN, 2, 0x60);
        oled_write_byte(NET_COLUMN, 3, 0x60);
        oled_write_byte(NET_COLUMN, 4, 0x60);
        oled_write_byte(NET_COLUMN, 5, 0x60);
        oled_write_byte(NET_COLUMN, 6, 0x60);
        oled_write_byte(NET_COLUMN, 7, 0x60);
        FLAG_CLEAR(update_flag, update_net);
    }

    // left paddle
    if (FLAG_CHECK(update_flag, update_player_left)) {
        uint8_t line = player_positions[0] / 8;
        uint8_t sub_pos = player_positions[0] % 8;
        oled_write_byte(0, line - 1, 0x00);
        oled_write_byte(0, line, 0xFF << sub_pos);
        oled_write_byte(0, line + 1, ~(0xFF << sub_pos));
        FLAG_CLEAR(update_flag, update_player_left);
    }

    // right paddle
    if (FLAG_CHECK(update_flag, update_player_right)) {
        uint8_t line = player_positions[1] / 8;
        uint8_t sub_pos = player_positions[1] % 8;
        oled_write_byte(127, line - 1, 0x00);
        oled_write_byte(127, line, 0xFF << sub_pos);
        oled_write_byte(127, line + 1, ~(0xFF << sub_pos));
        FLAG_CLEAR(update_flag, update_player_right);
    }

    // scores
    if (FLAG_CHECK(update_flag, update_score_left)) {
        oled_set_cursor(8, 1);
        oled_write_char('0' + (player_scores[0] / 10),false);
        oled_write_char('0' + (player_scores[0] % 10),false);
        FLAG_CLEAR(update_flag, update_score_left);
    }
    if (FLAG_CHECK(update_flag, update_score_right)) {
        oled_set_cursor(12, 1);
        oled_write_char('0' + (player_scores[1] / 10),false);
        oled_write_char('0' + (player_scores[1] % 10),false);
        FLAG_CLEAR(update_flag, update_score_right);
    }


    if (FLAG_CHECK(update_flag, update_ball)) {

        // erase the previous position of the ball
        {
            uint8_t line = prev_ball_pos.y / 8;
            oled_write_byte(prev_ball_pos.x, line, pre_ball_byte); // revert the display to its previous value
        }

        // draw the new position of the ball
        {
            uint8_t line = ball.position.y / 8;
            uint8_t sub_pos = ball.position.y % 8;
            uint8_t ball_byte = 0b00000001 << sub_pos;
            oled_byte_apply_func(ball.position.x, line, ball_render_func, &ball_byte);
        }
        FLAG_CLEAR(update_flag, update_ball);
    }


#endif
}

void pong_press(pong_player_t player) {
    // start the ball, if we're waiting on the player to do so
    if (ball.velocity.x == 0) {

        // 'random' value to determine direction and vertical speed of ball
        int8_t r = timer_read() ^ player_scores[0] ^ player_scores[1] ^ player_positions[0] ^ player_positions[1];

        int8_t vx = 3;
        int8_t vy = r & 0x3;
        if (((r >> 2) & 1) == 1) vx = -vx;
        if (((r >> 3) & 1) == 1) vy = -vy;

        ball.velocity.x = vx;
        ball.velocity.y = vy;

    }
}

void pong_input(pong_player_t player, pong_input_t input) {
    int8_t new_pos;
    switch (input) {
        case clockwise:
            new_pos = player_positions[player] - PLAYER_STEP;
            if (new_pos < 0) { new_pos = 0; }
            player_positions[player] = new_pos;
            FLAG_SET(update_flag, player);
            break;
        case anticlockwise:
            new_pos = player_positions[player] + PLAYER_STEP;
            if (new_pos > PADDLE_MAX) { new_pos = PADDLE_MAX; }
            player_positions[player] = new_pos;
            FLAG_SET(update_flag, player);
            break;
        case pressed:
            // start the ball, if we're waiting on the player to do so
            // if (ball.velocity.x == 0) {
            //     // todo set the x based on the winning player/alternate it, set the y randomly?
            //     ball.velocity.x = 3;
            //     ball.velocity.y = 2;
            // }
            break;
        default:
            break;
    }
}

