/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "pong.h"

enum layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    LOWER = SAFE_RANGE,
    RAISE,
    BRKTS,
    LENC,
    RENC,
};

// #define SCROLL 0
// #define MOUSE 1
// #define TEXT 2
// #define APPSW 3
// #define MEDIA 4
// #define PONG 5

enum encoder_modes {
    SCROLL,
    MOUSE,
    TEXT,
    APPSW,
    MEDIA,
    PONG
};

uint8_t enc_mode = SCROLL;


//Tap Dance Declarations
enum {
    TD_BRC = 0
};

//Tap Dance Definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     //Tap once for [{, twice for ]}
//     [TD_BRC]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC)
// };

void dance_brc_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LBRC);
  } else if (state->count == 2) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_LBRC);
    register_code (KC_RBRC);
  }
}

void dance_brc_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LBRC);
  } else if (state->count == 2) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_LBRC);
    unregister_code (KC_RBRC);
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_BRC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_brc_finished, dance_brc_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   TAB  |   Q  |   W  |   F  |   P  |   G  |                              |   J  |   L  |   U  |   Y  | ;  : |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  Ctrl  |   A  |   R  |  S   |   T  |   D  |                              |   H  |   N  |   E  |   I  |   O  |  ' @   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  Del | Lower|  | Raise|TD_BRC|   K  |   M  | ,  < | . >  | /  ? | RShift |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | Alt  | back | Raise| Esc  |  | gui  | Lower| Tab  | space| enter|
 *                        |      |      | space|      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      KC_TAB,    KC_Q,   KC_W,   KC_F,   KC_P,   KC_G,                                                  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NUBS, \
      KC_LCTL,   KC_A,   KC_R,   KC_S,   KC_T,   KC_D,                                                  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
      KC_LSPO,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_DEL,    LOWER,            RAISE, TD(TD_BRC),KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
                                 LENC, KC_LALT,KC_BSPC,RAISE,     KC_ESC,           KC_LGUI, LOWER,   KC_SPC,  KC_ENT,  RENC
    ),
/*
 * Lower Layer:
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
      _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  _______,                                     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                 LENC,    _______, _______, _______, _______, _______, _______, _______, _______, RENC
    ),
/*
 * Raise Layer:
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_NUHS, KC_DLR,  KC_PERC,                                       KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  KC_PLUS, \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
      _______, KC_CAPS, KC_SLCK, KC_NLCK, KC_F5,   KC_F6,   _______, _______, _______, _______,   KC_F7,   KC_F8,   KC_INS,  KC_PSCR, KC_PAUS, _______, \
                                 LENC,    _______, _______, _______, _______, _______, _______, _______, _______, RENC
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,                                      KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  _______, \
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F23,  KC_F24,  _______, \
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                 LENC,    _______, _______, _______, _______, _______, _______, _______, _______, RENC
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

bool status_changed = true;

layer_state_t layer_state_set_user(layer_state_t state) {
    status_changed = true;
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint8_t prev_led_usb_state = 0;
void matrix_scan_user(void) {
    uint8_t led_usb_state = host_keyboard_leds();
    if (prev_led_usb_state != led_usb_state) {
        prev_led_usb_state = led_usb_state;
        status_changed = true;
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}


static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    oled_write_P(PSTR("Encoders: "), false);
    switch (enc_mode) {
        case SCROLL:
            oled_write_P(PSTR("Scroll\n"), false);
            break;
        case MOUSE:
            oled_write_P(PSTR("Mouse\n"), false);
            break;
        case TEXT:
            oled_write_P(PSTR("Text manip\n"), false);
            break;
        case APPSW:
            oled_write_P(PSTR("App Switch\n"), false);
            break;
        case MEDIA:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case PONG:
            oled_write_P(PSTR("PONG!\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

// uint8_t render_counter = 0;

void oled_task_user(void) {
    if (enc_mode == PONG && is_keyboard_master()) {
        pong_frame();
        return;
    }
    // if (is_keyboard_master() && ((++render_counter & 0b10000000) == 0b10000000)) {
    //     render_counter = 0;
    if ((!status_changed) && (enc_mode != PONG)) {
        return;
    }
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
    status_changed = false;
}
#endif

#ifdef ENCODER_ENABLE

void left_encoder_pressed(bool pressed) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = SCROLL;
        status_changed = true;
        return;
    }

    switch (enc_mode) {
        case SCROLL:
            if (pressed) {
                register_code(KC_MS_BTN3);
            }
            else {
                unregister_code(KC_MS_BTN3);
            }
            break;
        case MOUSE:
            if (pressed) {
                register_code(KC_MS_BTN1);
            }
            else {
                unregister_code(KC_MS_BTN1);
            }
            break;
        case TEXT:
            if (pressed) {
                register_code(KC_LCTRL);
                tap_code(KC_C);
                unregister_code(KC_LCTRL);
            }
            break;
        case APPSW:
            if (pressed) {
                tap_code(KC_ENTER);
            }
            break;
        case MEDIA:
            if (pressed) {
                tap_code(KC_MUTE);
            }
            break;
        case PONG:
            if (pressed) {
                // pong_input(player_left, pressed);
                pong_press(player_left);
            }
            break;
        default:
            break;
    }
}

void right_encoder_pressed(bool pressed) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = MOUSE;
        status_changed = true;
        return;
    }
    switch (enc_mode) {
        case SCROLL:
            if (pressed) {
                register_code(KC_MS_BTN3);
            }
            else {
                unregister_code(KC_MS_BTN3);
            }
            break;
        case MOUSE:
            if (pressed) {
                register_code(KC_MS_BTN2);
            }
            else {
                unregister_code(KC_MS_BTN2);
            }
            break;
        case TEXT:
            if (pressed) {
                register_code(KC_LCTRL);
                tap_code(KC_V);
                unregister_code(KC_LCTRL);
            }
            break;
        case APPSW:
            if (pressed) {
                register_code(KC_LALT);
                tap_code(KC_ESC);
                unregister_code(KC_LALT);
            }
            break;
        case MEDIA:
            if (pressed) {
                tap_code(KC_MPLY);
            }
            break;
        case PONG:
            if (pressed) {
                // pong_input(player_right, pressed);
                pong_press(player_right);
            }
            break;
        default:
            break;
    }
}

void left_encoder_cw(void) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = TEXT;
        status_changed = true;
        return;
    }
    switch (enc_mode) {
        case SCROLL:
            tap_code(KC_MS_WH_RIGHT);
            break;
        case MOUSE:
            tap_code(KC_MS_LEFT);
            break;
        case TEXT:
            register_code(KC_LCTRL);
            register_code(KC_LSFT);
            tap_code(KC_W);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTRL);
            break;
        case APPSW:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_LSFT);
            _delay_ms(20);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            break;
        case MEDIA:
            tap_code(KC_VOLD);
            break;
        case PONG:
            pong_input(player_left, clockwise);
            break;
        default:
            break;
    }
}

void left_encoder_acw(void) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = APPSW;
        status_changed = true;
        return;
    }
    switch (enc_mode) {
        case SCROLL:
            tap_code(KC_MS_WH_LEFT);
            break;
        case MOUSE:
            tap_code(KC_MS_RIGHT);
            break;
        case TEXT:
            register_code(KC_LCTRL);
            tap_code(KC_W);
            unregister_code(KC_LCTRL);
            break;
        case APPSW:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            _delay_ms(20);
            tap_code(KC_TAB);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            break;
        case MEDIA:
            tap_code(KC_VOLU);
            break;
        case PONG:
            pong_input(player_left, anticlockwise);
            break;
        default:
            break;
    }
}

void right_encoder_cw(void) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = MEDIA;
        status_changed = true;
        return;
    }
    switch (enc_mode) {
        case SCROLL:
            tap_code(KC_MS_WH_UP);
            break;
        case MOUSE:
            tap_code(KC_MS_DOWN);
            break;
        case TEXT:
            register_code(KC_LCTRL);
            tap_code(KC_LEFT);
            unregister_code(KC_LCTRL);
            break;
        case APPSW:
            register_code(KC_LCTRL);
            register_code(KC_LSFT);
            _delay_ms(20);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTRL);
            break;
        case MEDIA:
            tap_code(KC_MPRV);
            break;
        case PONG:
            pong_input(player_right, clockwise);
            break;
        default:
            break;
    }
}

void right_encoder_acw(void) {
    if (get_highest_layer(layer_state) == _ADJUST) {
        enc_mode = PONG;
        pong_init();
        status_changed = true;
        return;
    }
    switch (enc_mode) {
        case SCROLL:
            tap_code(KC_MS_WH_DOWN);
            break;
        case MOUSE:
            tap_code(KC_MS_UP);
            break;
        case TEXT:
            register_code(KC_LCTRL);
            tap_code(KC_RIGHT);
            unregister_code(KC_LCTRL);
            break;
        case APPSW:
            register_code(KC_LCTRL);
            _delay_ms(20);
            tap_code(KC_TAB);
            unregister_code(KC_LCTRL);
            break;
        case MEDIA:
            tap_code(KC_MNXT);
            break;
        case PONG:
            pong_input(player_right, anticlockwise);
            break;
        default:
            break;
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            left_encoder_cw();
        } else {
            left_encoder_acw();
        }
    }
    else if (index == 1) {
        if (clockwise) {
            right_encoder_cw();
        } else {
            right_encoder_acw();
        }
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                register_code(KC_ACL0);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                unregister_code(KC_ACL0);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                register_code(KC_ACL0);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                unregister_code(KC_ACL0);
            }
            return false;
            break;
        case KC_CAPS:
        case KC_SLCK:
        case KC_NLCK:
            status_changed = true;
            return true;
        case LENC:
#ifdef ENCODER_ENABLE
            left_encoder_pressed(record->event.pressed);
#endif
            return false;
            break;
        case RENC:
#ifdef ENCODER_ENABLE
            right_encoder_pressed(record->event.pressed);
#endif
            return false;
            break;
    }
    return true;
}
