#include "H7.h"
#include "eeprom.h"

// begin: dynamic unicode method handling
#define EECONFIG_USERSPACE (uint8_t *) 19

#define OS_OSX 0
#define OS_LNX 1
#define OS_WIN 2
#define OS_BSD 3

uint8_t os_target = 1;

// uint8_t (unsigned char) has 8 bits available
// we are able to store the active unicode input mechanism using
// 3 of those bits (with 3 spare slots)
//
// leaving 5 bits remaining for additional feature flags
//
// decimal  |  binary           |  represents
//       -  |  8 7 6 5 4 3 2 1  |  bits
// ---------|-----------------------------------------------
//       0  |  0 0 0 0 0 0 0 0  |  UC_OSX
//       1  |  0 0 0 0 0 0 0 1  |  UC_LNX
//       2  |  0 0 0 0 0 0 1 0  |  UC_WIN
//       3  |  0 0 0 0 0 0 1 1  |  UC_BSD
//       4  |  0 0 0 0 0 1 0 0  |  UC_WINC
//       5  |  0 0 0 0 0 1 0 1  |  -unused-
//       6  |  0 0 0 0 0 1 1 0  |  -unused-
//       7  |  0 0 0 0 0 1 1 1  |  -unused-
typedef union {
  uint8_t raw;
  struct {
    uint8_t uc_input_method:3; // to store 0-7
  };
} userspace_config_t;

userspace_config_t userspace_config;

// unicode input mode setting
// pressing [Mode] cycles through the list, setting the current input method
// pressing [Function]-[Mode] commits the current input method to EEPROM
const uint8_t UC_OPTIONS[] = { UC_OSX, UC_LNX, UC_WIN, UC_BSD, UC_WINC };
const uint8_t UC_OPTIONS_LENGTH = (uint8_t) ( sizeof(UC_OPTIONS) / sizeof(UC_OPTIONS[0]) );

int comparator( const void *lhs, const void *rhs )
{
  if ( *( const uint8_t * )lhs < *( const uint8_t * )rhs ) return -1;
  else if ( *( const uint8_t * )rhs < *( const uint8_t * )lhs ) return 1;
  else return 0;
}

uint8_t getCurrentUCInputMethodIndex(uint8_t currentInputMethod)
{
  uint8_t *p  = ( uint8_t * ) bsearch( &currentInputMethod, UC_OPTIONS, UC_OPTIONS_LENGTH, sizeof( uint8_t ), comparator );

  if ( p != NULL ) return p - UC_OPTIONS;

  return 0;
}

uint8_t getNextUCInputMethod(uint8_t currentInputMethod)
{
  uint8_t currentInputMethodIndex = getCurrentUCInputMethodIndex(currentInputMethod);

  printf("current method index: %d\n", currentInputMethodIndex );
  uint8_t index = 0;
  if (currentInputMethodIndex < (UC_OPTIONS_LENGTH - 1)) {
    index = currentInputMethodIndex + 1;
  }
  return UC_OPTIONS[index];
}

uint8_t getOSFromInputMethod(uint8_t currentInputMethod) {
  uint8_t currentInputMethodIndex = getCurrentUCInputMethodIndex(currentInputMethod);
  uint8_t OS = OS_LNX;
  switch ( currentInputMethodIndex ) {
    case 1:
      /* Linux */
      OS = OS_LNX;
      break;
    case 0:
      /* OSX */
      OS = OS_OSX;
      break;
    case 2:
      /* WIN */
    case 4:
      /* WINC */
      OS = OS_WIN;
      break;
    case 3:
      /* BSD */
      OS = OS_BSD;
      break;
  }

  return OS;
}
// end: dynamic unicode method handling

// Brevity defines
#define FT KC_TRNS

// Unicode char definitions
#define AT_SYMBOL 0x0040
#define GBP 0x00A3
#define JPY 0x00A5
#define EURO 0x20AC
#define PLUS_MINUS 0x00B1
#define QUOTATION_MARK 0x0022
#define TILDE_OPERATOR 0x223C
#define SINGLE_RIGHT_POINTING_ANGLE_QUOTATION_MARK 0x203A
#define SINGLE_LEFT_POINTING_ANGLE_QUOTATION_MARK 0x2039
#define BACKTICK 0x2018
#define DQUOTE_OPEN 0x201C
#define DQUOTE_CLOSE 0x201D
#define PRIME 0x2019
#define PIPE 0x2502

// APL
#define N_ARY_LOGICAL_AND 0x22C0
#define N_ARY_LOGICAL_OR 0x22C1
#define N_ARY_INTERSECT 0x22C2
#define N_ARY_UNION 0x22C3
#define SUBSET_OF 0x2282
#define SUPERSET_OF 0x2282
#define FORALL 0x2200
#define _INFINITY 0x221E
#define END_OF_PROOF 0x220E
#define PARTIAL_DIFFERENTIAL 0x2202
#define UP_TACK 0x22A5
#define DOWN_TACK 0x22A4
#define RIGHT_TACK 0x22A2
#define LEFT_TACK 0x22A3
#define UPWARDS_ARROW 0x2191
#define DOWNARDS_ARROW 0x2193
#define LEFTWARDS_ARROW 0x2190
#define RIGHTWARDS_ARROW 0x2192
#define LEFTRIGHT_ARROW 0x2194
#define LEFT_FLOOR 0x230A
#define LEFT_CEILING 0x2308
#define NOT_EQUAL_TO 0x2260
#define ASYMPTOTICALLY_EQUAL_TO 0x2243
#define NOT_ASYMPTOTICALLY_EQUAL_TO 0x2261
#define LESS_THAN_OR_EQUAL 0x2264
#define GREATER_THAN_OR_EQUAL 0x2265

// Greek (lower case)
// [main board] row 0
#define CONTOUR_INTEGRAL 0x222E
#define COPTIC_SMALL_LETTER_DEI 0x03EF
#define DOUBLE_DAGGER 0x2021
#define NABLA 0x2207
#define CENT 0x00A2
#define DEGREE 0x00B0
#define APL_QUAD 0x2395
#define DIVISION 0x00F7
#define MULTIPLICATION 0x00D7
#define PILCROW 0x00B6
#define LARGE_CIRCLE 0x25EF
#define HORIZONTAL_BAR 0x2015
#define APPROXIMATELY_EQUAL_TO 0x2248
#define DOUBLE_VERTICAL_LINE 0x2016
#define SQUARE_IMAGE_OF 0x228F
#define SQUARE_ORIGINAL_OF 0x2290

// [main board] row 1
#define GREEK_SMALL_LETTER_THETA 0x03B8
#define GREEK_SMALL_LETTER_OMEGA 0x03C9
#define GREEK_SMALL_LETTER_EPSILON 0x03B5
#define GREEK_SMALL_LETTER_RHO 0x03C1
#define GREEK_SMALL_LETTER_TAU 0x03C4
#define GREEK_SMALL_LETTER_PSI 0x03C8
#define GREEK_SMALL_LETTER_UPSILON 0x03C5
#define GREEK_SMALL_LETTER_IOTA 0x03B9
#define GREEK_SMALL_LETTER_OMICRON 0x03BF
#define GREEK_SMALL_LETTER_PI 0x03C0
#define MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET 0x27E6
#define MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET 0x27E7

// [main board] row 2
#define GREEK_SMALL_LETTER_ALPHA 0x03B1
#define GREEK_SMALL_LETTER_SIGMA 0x03C3
#define GREEK_SMALL_LETTER_DELTA 0x03B4
#define GREEK_SMALL_LETTER_PHI 0x03C6
#define GREEK_SMALL_LETTER_GAMMA 0x03B3
#define GREEK_SMALL_LETTER_ETA 0x03B7
#define GREEK_LETTER_YOT 0x03F3
#define GREEK_SMALL_LETTER_KAPPA 0x03BA
#define GREEK_SMALL_LETTER_LAMDA 0x03BB
#define TWO_DOT_LEADER 0x2025
#define BULLET 0x2022

// [main board] row 3
#define GREEK_SMALL_LETTER_ZETA 0x03B6
#define GREEK_SMALL_LETTER_XI 0x03BE
#define GREEK_SMALL_LETTER_CHI 0x03C7
#define GREEK_SMALL_LETTER_FINAL_SIGMA 0x03C2
#define GREEK_SMALL_LETTER_BETA 0x03B2
#define GREEK_SMALL_LETTER_NU 0x03BD
#define GREEK_SMALL_LETTER_MU 0x03BC
#define MUCH_LESS_THAN 0x226A
#define MUCH_GREATER_THAN 0x226B
#define INTEGRAL 0x222B

// Greek (upper case)
// [main board] row 1
#define GREEK_CAPITAL_LETTER_THETA 0x0398
#define GREEK_CAPITAL_LETTER_OMEGA 0x03A9
#define GREEK_CAPITAL_LETTER_EPSILON 0x0395
#define GREEK_CAPITAL_LETTER_RHO 0x03A1
#define GREEK_CAPITAL_LETTER_TAU 0x03A4
#define GREEK_CAPITAL_LETTER_PSI 0x03A8
#define GREEK_CAPITAL_LETTER_UPSILON 0x03A5
#define GREEK_CAPITAL_LETTER_IOTA 0x0399
#define GREEK_CAPITAL_LETTER_OMICRON 0x039F
#define GREEK_CAPITAL_LETTER_PI 0x03A0

// [main board] row 2
#define GREEK_CAPITAL_LETTER_ALPHA 0x0391
#define GREEK_CAPITAL_LETTER_SIGMA 0x03A3
#define GREEK_CAPITAL_LETTER_DELTA 0x0394
#define GREEK_CAPITAL_LETTER_PHI 0x03A6
#define GREEK_CAPITAL_LETTER_GAMMA 0x0393
#define GREEK_CAPITAL_LETTER_ETA 0x0397
#define GREEK_CAPITAL_LETTER_YOT 0x037F
#define GREEK_CAPITAL_LETTER_KAPPA 0x039A
#define GREEK_CAPITAL_LETTER_LAMDA 0x039B

// [main board] row 3
#define GREEK_CAPITAL_LETTER_ZETA 0x0396
#define GREEK_CAPITAL_LETTER_XI 0x039E
#define GREEK_CAPITAL_LETTER_CHI 0x03A7
#define GREEK_CAPITAL_LETTER_SIGMA 0x03A3
#define GREEK_CAPITAL_LETTER_BETA 0x0392
#define GREEK_CAPITAL_LETTER_NU 0x039D
#define GREEK_CAPITAL_LETTER_MU 0x039C

// This timeout is the total time that the leader is activated for
// feel free to tune for your use cases
// see: https://docs.qmk.fm/#/feature_leader_key
#define LEADER_TIMEOUT 1000

// activate leader functionality
LEADER_EXTERNS();

// modifier masks used for determining modifier actuation within macros
#define MODS_SHIFT_MASK   (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MODS_META_MASK    (MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI))
#define MODS_CTRL_MASK    (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))
#define MODS_ALT_MASK     (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MODS_HYPR_MASK     MOD_BIT(KC_HYPR)
#define MODS_SUPER_MASK    MOD_BIT(KC_SUPER)

/*
 * Each layer gets a name for readability, which is then used in the keymap matrix below.
 * The underscores don't mean anything - you can have a layer called STUFF or any other name.
 * Layer names don't all need to be of the same length, obviously, and you can also skip them
 * entirely and just use numbers.
 */
#define _BASE 0   // Base layer
#define _APL 1    // APL symbols
#define _SYML 2   // lower case greek symbols
#define _SYMU 3   // upper case greek symbols
#define _FN 4     // FN & media keys

enum custom_keycodes {
  // daughter board r0
  H_HELP = SAFE_RANGE,
  H_MACRO,
  H_TERMINAL,
  H_QUOTE,
  H_OVERSTRIKE,
  H_CLEAR_INSERT,
  H_CLEAR_SCREEN,
  H_HOLD_OUTPUT,
  H_STOP_OUTPUT,
  H_ABORT,
  H_BREAK,
  H_RESUME,
  H_CALL,

  // daughter board r1
  H_LOCAL,
  H_NETWORK,
  H_SYSTEM,
  H_REFRESH,
  H_BUFFER,
  H_SQUARE,
  H_CIRCLE,
  H_TRIANGLE,
  H_DIAMOND,
  H_REPEAT,
  H_TRANSMIT,
  H_STATUS,
  H_SUSPEND,

  // daughter board r2
  H_CLOSE,
  H_OPEN,
  H_COMPLETE,

  // main board r0
  H_WRITE,
  H_DOUBLE_QUOTE__PLUS_MINUS,
  H_COLON__TILDE,
  H_LEFT_BRACE__LEFT_CHEVRON,
  H_RIGHT_BRACE__RIGHT_CHEVRON,

  // main board r1
  H_MARK,

  // main board r2
  H_SELECT,
  H_DEBUG,
  H_MODE_CYCLE,
  H_MODE_STORE,
  H_LINE,
  H_PAGE,

  // main board r3
  H_TTY,
  H_LOCK, // lock machine? a little close to other used keys on a single keypress?
  H_TICK__DOUBLE_QUOTE,
  H_SEMI_COLON__BACKTICK,

  // main board r4
  H_EOF,
  H_7BIT,
  H_CIRCLE_SM,
  H_RUN
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* _BASE: Base Layer(Default)
  * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  * | --- |Help | --- |Macro|#| --- |Trmnl| --- |Quote| --- |OvrSk| --- |ClrIn| --- |ClrSc| --- |HldOu| --- |StpOu| --- |Abort| --- |Break| --- |Rsume|#| --- |Call | --- |RESET|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | --- |Local| --- |Netwk|#| --- |Systm| --- |Rfrsh| --- |Buffr| --- |Squar| --- |Circl| --- |Trian| --- |DiamD| --- |Rpeat| --- |Trnmt| --- |Stats|#| --- |Sspnd| --- |CapLk|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F1  | F2  |Close|Open |#|   Esc     |  ?  |  !  |  @  |  £  |  €  |  ¥  |  '  |  “  |  ”  |  '  |  _  |  <  |  >  |  |  |  {  |  }  | Complete  |#|  ^  |  %  |  #  |  $  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |###############################################################################################################################################################################|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F3  | F4  |Find |Write|#|Compose | "/± | :/~ |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  |  | {/‹  | }/›  | Undo   |#|  ~  |  /  |  *  |  -  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F5  | F6  |Mark |Undo |#|Paste|  Cut   |  Tab   |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  (  |  )  | Bspace | Clear  |Begin|#|  7  |  8  |  9  |  +  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F7  | F8  |Selec|Debug|#|Function|  Mode  |  Top   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  | '/"  | ;/` | Return |  Line  |  Page  |#|  4  |  5  |  6  |  &  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F9  | F10 | TTY |LOCK |#|Begin| End | Symbol | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift  | Symbol |  Up | End |#|  1  |  2  |  3  |  =  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F11 | F12 |Home | EOF |#|Prior|Next |7bit | Alt | Hyper  | Spr |  Ctrl  | Space |TRNS |  Del   |  Ctrl  | Spr  | Hyper  |Meta |Left |Down |Right|#| Del |  0  |  .  | Run |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  *  incomplete mappings
  *  r1: Macro, Terminal, Clear Insert, Clear Screen, Hold Output, Stop Output, Break, Call
  *  r2: Local, Network, System, Buffer, Repeat, Transmit, Status
  *  r3: Close, Open
  *
  *  r1: Find, Write
  *  r2: Mark
  *  r3: Select, Debug, Line, Page
  *  r4: TTY
  *  r2: 7bit, [circle]
  */

  [_BASE] = H7_KEYMAP(
    KC_NO,  H_HELP,  KC_NO,     H_MACRO,   KC_NO,    H_TERMINAL,  KC_NO,    H_QUOTE,       KC_NO,   H_OVERSTRIKE, KC_NO,    H_CLEAR_INSERT,  KC_NO,    H_CLEAR_SCREEN, KC_NO,    H_HOLD_OUTPUT, KC_NO,  H_STOP_OUTPUT, KC_NO,   H_ABORT,  KC_NO,  H_BREAK,    KC_NO,  H_RESUME,  KC_NO, H_CALL,    KC_NO,   RESET,
    KC_NO,  H_LOCAL, KC_NO,     H_NETWORK, KC_NO,    H_SYSTEM,    KC_NO,    H_REFRESH,     KC_NO,   H_BUFFER,     KC_NO,    H_SQUARE,        KC_NO,    H_CIRCLE,       KC_NO,    H_TRIANGLE,    KC_NO,  H_DIAMOND,     KC_NO,   H_REPEAT, KC_NO,  H_TRANSMIT, KC_NO,  H_STATUS,  KC_NO, H_SUSPEND, KC_NO,   KC_CAPS,
    KC_F1,  KC_F2,   H_CLOSE,   H_OPEN,    KC_ESC,   KC_QUES,     KC_EXLM,  UC(AT_SYMBOL), UC(GBP), UC(EURO),     UC(JPY),  UC(BACKTICK),    UC(DQUOTE_OPEN), UC(DQUOTE_CLOSE),UC(PRIME), KC_UNDS, KC_LABK,  KC_RABK,  UC(PIPE),KC_LCBR, KC_RCBR,  H_COMPLETE,                       KC_CIRC, KC_PERC,  KC_HASH, KC_DLR,

    KC_F3,  KC_F4,   KC_FIND,   H_WRITE,   KC_LEAD,  H_DOUBLE_QUOTE__PLUS_MINUS, H_COLON__TILDE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    KC_6,     KC_7,    KC_8,     KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_NUBS, H_LEFT_BRACE__LEFT_CHEVRON,  H_RIGHT_BRACE__RIGHT_CHEVRON,  KC_UNDO,             KC_TILD, KC_SLSH,  KC_PAST, KC_PMNS,
    KC_F5,  KC_F6,   KC_EXLM,   KC_UNDO,   KC_PASTE, KC_CUT ,  KC_TAB ,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_Y,     KC_U,    KC_I,     KC_O,    KC_P,     KC_LPRN,  KC_RPRN, KC_BSPC, KC_CLEAR, KC_HOME,                     KC_P7,    KC_P8,     KC_P9,    KC_PPLS,
    KC_F7,  KC_F8,   KC_SELECT, H_DEBUG,   MO(_FN),  H_MODE_CYCLE,       MO(_APL), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    KC_H,     KC_J,    KC_K,     KC_L,    H_TICK__DOUBLE_QUOTE,  H_SEMI_COLON__BACKTICK,  KC_ENT , H_LINE, H_PAGE,                           KC_P4,    KC_P5,     KC_P6,    KC_AMPR,
    KC_F9,  KC_F10,  H_TTY,     KC_NO,    KC_HOME,  KC_END ,  MO(_SYML), KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT, MO(_SYML),KC_UP,    KC_END,                        KC_P1,    KC_P2,     KC_P3,    KC_EQL,
    KC_F11, KC_F12,  KC_HOME,   H_EOF,     KC_MPRV,  KC_MNXT,  H_7BIT,  KC_LALT,  KC_HYPR,  KC_LGUI,  KC_LCTL,  KC_SPC,  H_CIRCLE_SM,  KC_DEL,  KC_RCTL,  KC_RGUI, KC_HYPR,  KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT,                              KC_DEL,   KC_P0,     KC_PDOT,  H_RUN
  ),
 /* _APL: Cadet Symbol Layer (Default)
  * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |###############################################################################################################################################################################|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |        |        |  ⋀  |  ⋁  |  ⋂  |  ⋃  |  ⊂  |  ⊃  |  ∀  |  ∞  |  ∎  |  ∂  |     |     |        |        |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |        |        |  ⊥  |  ⊤  |  ⊢  |  ⊣  |  ↑  |  ↓  |  ←  |  →  |  ↔  |  ;  |  '  |        |        |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |        |        |  ⌊  |  ⌈  |  ≠  |  ≃  |  ≡  |  ≤  |  ≥  |     |     |     |        |        |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_APL] = H7_KEYMAP(
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(N_ARY_LOGICAL_AND), UC(N_ARY_LOGICAL_OR), UC(N_ARY_INTERSECT), UC(N_ARY_UNION), UC(SUBSET_OF),UC(SUPERSET_OF), UC(FORALL),UC(_INFINITY), UC(END_OF_PROOF),UC(PARTIAL_DIFFERENTIAL),      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(UP_TACK), UC(DOWN_TACK), UC(RIGHT_TACK), UC(LEFT_TACK), UC(UPWARDS_ARROW),UC(DOWNARDS_ARROW), UC(LEFTWARDS_ARROW),UC(RIGHTWARDS_ARROW), UC(LEFTRIGHT_ARROW),     FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,  UC(LEFT_FLOOR), UC(LEFT_CEILING), UC(NOT_EQUAL_TO), UC(ASYMPTOTICALLY_EQUAL_TO),UC(NOT_ASYMPTOTICALLY_EQUAL_TO), UC(LESS_THAN_OR_EQUAL),UC(GREATER_THAN_OR_EQUAL),      FT,      FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
  ),
 /* _SYML: LOWER case greek only (needs shift modifier application for upper case chars) from codepage U0370.pdf \
  * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |###############################################################################################################################################################################|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |  ∮  |     |  ϯ  |  ‡  |  ∇  |  ¢  |  °  |  ⎕  |  ÷  |  ×  |  ¶  |  ◯  |  ―  |  ≈  |  ‖  |  ⊏  |  ⊐  |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |        |        |  θ  |  ω  |  ε  |  ρ  |  τ  |  ψ  |  υ  |  ι  |  ο  |  π  |  ⟦  |  ⟧  |        |        |      |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |        |        |  α  |  σ  |  δ  |  φ  |  γ  |  η  |  ϳ  |  κ  |  λ  |  ‥  |  •  |        |        |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |         | SHIFT |  ζ  |  ξ  |  χ  |  ς  |  β  |  ν  |  μ  |  ≪  |  ≫  |  ∫  |        |        |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_SYML] = H7_KEYMAP(
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,      FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,      FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,      FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT, UC(CONTOUR_INTEGRAL),  FT,  UC(COPTIC_SMALL_LETTER_DEI), UC(DOUBLE_DAGGER), UC(NABLA), UC(CENT), UC(DEGREE), UC(APL_QUAD), UC(DIVISION), UC(MULTIPLICATION), UC(PILCROW), UC(LARGE_CIRCLE), UC(HORIZONTAL_BAR), UC(APPROXIMATELY_EQUAL_TO), UC(DOUBLE_VERTICAL_LINE), UC(SQUARE_IMAGE_OF), UC(SQUARE_ORIGINAL_OF),       FT,       FT,                 FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_SMALL_LETTER_THETA), UC(GREEK_SMALL_LETTER_OMEGA), UC(GREEK_SMALL_LETTER_EPSILON), UC(GREEK_SMALL_LETTER_RHO), UC(GREEK_SMALL_LETTER_TAU),UC(GREEK_SMALL_LETTER_PSI), UC(GREEK_SMALL_LETTER_UPSILON),UC(GREEK_SMALL_LETTER_IOTA), UC(GREEK_SMALL_LETTER_OMICRON),UC(GREEK_SMALL_LETTER_PI), UC(MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET), UC(MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET),     FT,      FT,      FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_SMALL_LETTER_ALPHA), UC(GREEK_SMALL_LETTER_SIGMA), UC(GREEK_SMALL_LETTER_DELTA), UC(GREEK_SMALL_LETTER_PHI), UC(GREEK_SMALL_LETTER_GAMMA),UC(GREEK_SMALL_LETTER_ETA), UC(GREEK_LETTER_YOT),UC(GREEK_SMALL_LETTER_KAPPA), UC(GREEK_SMALL_LETTER_LAMDA), UC(TWO_DOT_LEADER), UC(BULLET),      FT,      FT,      FT,                                     FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,   FT,       FT,       FT,  MO(_SYMU),  UC(GREEK_SMALL_LETTER_ZETA), UC(GREEK_SMALL_LETTER_XI), UC(GREEK_SMALL_LETTER_CHI), UC(GREEK_SMALL_LETTER_FINAL_SIGMA),UC(GREEK_SMALL_LETTER_BETA), UC(GREEK_SMALL_LETTER_NU),UC(GREEK_SMALL_LETTER_MU), UC(MUCH_LESS_THAN),UC(MUCH_GREATER_THAN), UC(INTEGRAL),      FT,      FT,      FT,      FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,                                     FT,      FT,       FT,      FT
  ),
 /* _SYMLS: UPPER case greek only (needs shift modifier application for upper case chars) from codepage U0370.pdf \
  * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |###############################################################################################################################################################################|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |        |        |  Θ  |  Ω |  Ε  |  Ρ  |  Τ  |  Ψ  |  Υ  |  Ι  |  Ο  |  Π  |     |     |        |        |      |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |        |        |  Α  |  Σ  |  Δ  |  Φ  |  Γ  |  Η  |  Ϳ  |  Κ  |  Λ  |     |     |        |        |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |         |       |  Ζ  |  Ξ  |  Χ  |  Σ  |  Β  |  Ν  |  Μ  |     |     |     |        |        |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_SYMU] = H7_KEYMAP(
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_CAPITAL_LETTER_THETA), UC(GREEK_CAPITAL_LETTER_OMEGA), UC(GREEK_CAPITAL_LETTER_EPSILON), UC(GREEK_CAPITAL_LETTER_RHO), UC(GREEK_CAPITAL_LETTER_TAU),UC(GREEK_CAPITAL_LETTER_PSI), UC(GREEK_CAPITAL_LETTER_UPSILON),UC(GREEK_CAPITAL_LETTER_IOTA), UC(GREEK_CAPITAL_LETTER_OMICRON),UC(GREEK_CAPITAL_LETTER_PI), FT, FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_CAPITAL_LETTER_ALPHA), UC(GREEK_CAPITAL_LETTER_SIGMA), UC(GREEK_CAPITAL_LETTER_DELTA), UC(GREEK_CAPITAL_LETTER_PHI), UC(GREEK_CAPITAL_LETTER_GAMMA),UC(GREEK_CAPITAL_LETTER_ETA), UC(GREEK_CAPITAL_LETTER_YOT),UC(GREEK_CAPITAL_LETTER_KAPPA), UC(GREEK_CAPITAL_LETTER_LAMDA),     FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  FT,  UC(GREEK_CAPITAL_LETTER_ZETA), UC(GREEK_CAPITAL_LETTER_XI), UC(GREEK_CAPITAL_LETTER_CHI), UC(GREEK_CAPITAL_LETTER_SIGMA),UC(GREEK_CAPITAL_LETTER_BETA), UC(GREEK_CAPITAL_LETTER_NU),  UC(GREEK_CAPITAL_LETTER_MU), FT, FT, FT,      FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,       FT,      FT,       FT,      FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
  ),
 /* _FN: Function layer, media & LED mods
  * ,-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------.
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|           |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |           |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |###############################################################################################################################################################################|
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |        |        |     |    |     |     |     |     |     |     |     |     |     |     |        |        |      |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|        |        |        |     |     |     |     |     |     |     |     |     |     |     |        |        |        |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |         |       |     |     |     |     |     |     |     |     |     |     |        |        |     |     |#|     |     |     |     |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * |     |     |     |     |#|     |     |     |     |        |     |        |        |     |        |        |     |        |     |     |     |     |#|     |     |     |     |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  */
  [_FN] = H7_KEYMAP(
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       H_MODE_STORE,   FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
    FT,      FT,      FT,       H_LOCK,   FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      BL_INC,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       BL_BRTG,       FT,       FT,       FT,       FT,       FT,       BL_TOGG,       FT,       FT,       FT,       FT,       FT,       FT,      BL_DEC,      FT,                                      FT,      FT,       FT,      FT
  )
};


void matrix_init_user(void) {
  // read persisted data on initialisation
  userspace_config.raw = eeprom_read_byte(EECONFIG_USERSPACE);

  // windows users, to enable UC_WIN:
  // 1. Create a registry key (run regedit) of type REG_SZ called EnableHexNumpad with value 1 under:
  //   - HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad
  // 2. Reboot
  set_unicode_input_mode(userspace_config.uc_input_method);
  os_target = getOSFromInputMethod(userspace_config.uc_input_method);
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // slash :: find
    SEQ_ONE_KEY(KC_SLASH) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_F)));
    }

    // COPY WORD
    SEQ_TWO_KEYS(KC_W, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT))SS_LSFT(SS_LCTRL(SS_TAP(X_RIGHT)))SS_LCTRL(SS_TAP(X_C)));
    }

    // COPY LINE
    SEQ_TWO_KEYS(KC_L, KC_C) {
      SEND_STRING(SS_TAP(X_HOME)SS_LSFT(SS_TAP(X_END))SS_LCTRL(SS_TAP(X_C)));
    }

    // COPY ALL
    SEQ_TWO_KEYS(KC_A, KC_C) {
      SEND_STRING(SS_LCTRL(SS_TAP(X_A)SS_TAP(X_C)));
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    // [daughter board] row 0 POS key macros
    case H_HELP:
      if (record -> event.pressed) {
        switch (os_target) {
          case OS_LNX:
            SEND_STRING("LINUX [HELP] key macro");
            break;
          case OS_OSX:
            SEND_STRING("OSX [HELP] key macro");
            break;
          case OS_WIN:
            SEND_STRING("WINDOWS [HELP] key macro");
            break;
          case OS_BSD:
            SEND_STRING("BSD [HELP] key macro");
            break;
          default:
            SEND_STRING("WHAT THE F*CK? [HELP] key macro");
            break;
        }
      }
      return false;
    case H_TERMINAL:
      if (record -> event.pressed) {
        SEND_STRING("[TERMINAL] key macro");
      }
      return false;
    case H_QUOTE:
      // wraps selected (editable) text in quotation marks
      if (record -> event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_X))SS_TAP(X_QUOTE)SS_LCTRL(SS_TAP(X_V))SS_TAP(X_QUOTE));
      }
      return false;
    case H_OVERSTRIKE:
      // toggles insert/overstrike
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_INSERT));
      }
      return false;
    case H_CLEAR_INSERT:
      if (record -> event.pressed) {
        SEND_STRING("[CLEAR INSERT] key macro");
      }
      return false;
    case H_CLEAR_SCREEN:
      if (record -> event.pressed) {
        // linux/osx shell specific, for windows command replace with
        // SEND_STRING(SS_TAP(X_C)SS_TAP(X_L)SS_TAP(X_S)SS_TAP(KC_ENTER));
        SEND_STRING(SS_LCTRL(SS_TAP(X_L)));
      }
      return false;
    case H_HOLD_OUTPUT:
      SEND_STRING("[HOLD OUTPUT] key macro");
      return false;
    case H_STOP_OUTPUT:
      if (record -> event.pressed) {
        SEND_STRING("[STOP OUTPUT] key macro");
      }
      return false;
    case H_ABORT:
      if (record -> event.pressed) {
        // stops process (SIGINT)
        SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
      }
      return false;
    case H_BREAK:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_PAUSE));
      }
      return false;
    case H_RESUME:
      if (record -> event.pressed) {
        // resumes a backgrounded process
        SEND_STRING(SS_TAP(X_F)SS_TAP(X_G)SS_TAP(X_ENTER));
      }
      return false;
    case H_CALL:
      if (record -> event.pressed) {
        SEND_STRING("[CALL] key macro");
      }
      return false;

      // [daughter board] row 1 POS key macros
    case H_LOCAL:
      if (record -> event.pressed) {
        SEND_STRING("[LOCAL] key macro");
      }
      return false;
    case H_NETWORK:
      if (record -> event.pressed) {
        SEND_STRING("[NETWORK] key macro");
      }
      return false;
    case H_SYSTEM:
      if (record -> event.pressed) {
        SEND_STRING("[SYSTEM] key macro");
      }
      return false;
    case H_REFRESH:
      if (record -> event.pressed) {
        SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_R))));
      }
      return false;
    case H_BUFFER:
      if (record -> event.pressed) {
        SEND_STRING("[BUFFER] key macro");
      }
      return false;
    case H_SQUARE:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_MEDIA_STOP));
      }
      return false;
    case H_CIRCLE:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_MEDIA_PREV_TRACK));
      }
      return false;
    case H_TRIANGLE:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_MEDIA_PLAY_PAUSE));
      }
      return false;
    case H_DIAMOND:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_MEDIA_NEXT_TRACK));
      }
      return false;
    case H_REPEAT:
      if (record -> event.pressed) {
        SEND_STRING("[REPEAT] key macro");
      }
      return false;
    case H_TRANSMIT:
      if (record -> event.pressed) {
        SEND_STRING(SS_TAP(X_ENTER));
      }
      return false;
    case H_STATUS:
      if (record -> event.pressed) {
        SEND_STRING("[STATUS] key macro");
      }
      return false;
    case H_SUSPEND:
      if (record -> event.pressed) {
        // background the current process (SIGSTOP)
        SEND_STRING(SS_LCTRL(SS_TAP(X_Z)));
      }
      return false;

    // [daughter board] row 2
    case H_CLOSE:
      if (record -> event.pressed) {
        // ctrl-w: closes a tab/panel within an application
        SEND_STRING(SS_LCTRL(SS_TAP(X_W)));
      }
      return false;
    case H_OPEN:
      if (record -> event.pressed) {
        // ctrl-n: opens a tab/panel
        SEND_STRING(SS_LCTRL(SS_TAP(X_N)));
      }
      return false;
    case H_COMPLETE:
      if (record -> event.pressed) {
        // tab tab: bash command line completion
        SEND_STRING(SS_TAP(X_TAB)SS_TAP(X_TAB));
      }
      return false;

    // [main board] row 0
    case H_WRITE:
      if (record -> event.pressed) {
        SEND_STRING("[WRITE] key macro");
      }
      return false;

    case H_DOUBLE_QUOTE__PLUS_MINUS:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          process_unicode(UC(PLUS_MINUS | QK_UNICODE), record);
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          process_unicode(UC(QUOTATION_MARK | QK_UNICODE), record);
        }
      }
      return false;

    case H_COLON__TILDE:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          process_unicode(UC(TILDE_OPERATOR | QK_UNICODE), record);
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          SEND_STRING(":");
        }
      }
      return false;

    case H_LEFT_BRACE__LEFT_CHEVRON:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          process_unicode(UC(SINGLE_LEFT_POINTING_ANGLE_QUOTATION_MARK | QK_UNICODE), record);
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          SEND_STRING("{");
        }
      }
      return false;

    case H_RIGHT_BRACE__RIGHT_CHEVRON:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          process_unicode(UC(SINGLE_RIGHT_POINTING_ANGLE_QUOTATION_MARK | QK_UNICODE), record);
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          SEND_STRING("}");
        }
      }
      return false;

    // [main board] row 1
    case H_MARK:
      if (record -> event.pressed) {
        SEND_STRING("[MARK] key");
      }
      return false;

    // [main board] row 2
    case H_SELECT:
      if (record -> event.pressed) {
        SEND_STRING("[SELECT] key");
      }
      return false;
    case H_DEBUG:
      if (record -> event.pressed) {
        SEND_STRING("[DEBUG] key");
      }
      return false;
    case H_MODE_CYCLE:
      userspace_config.uc_input_method = getNextUCInputMethod(userspace_config.uc_input_method);
      os_target = getOSFromInputMethod(userspace_config.uc_input_method);
      set_unicode_input_mode(userspace_config.uc_input_method);
      return false;
    case H_MODE_STORE:
      eeprom_update_byte(EECONFIG_USERSPACE, userspace_config.raw);
      return false;
    case H_LINE:
      if (record -> event.pressed) {
        SEND_STRING("[LINE] key");
      }
      return false;
    case H_PAGE:
      if (record -> event.pressed) {
        SEND_STRING("[PAGE] key");
      }
      return false;

    // [main board] row 3
    case H_TTY:
      if (record -> event.pressed) {
        SEND_STRING("[TTY] key");
      } else {

      }
      return false;
    case H_LOCK:
      if (record -> event.pressed) {
        SEND_STRING(SS_LGUI(SS_TAP(X_L)));
      }
      return false;

    // [main board] row 4
    case H_TICK__DOUBLE_QUOTE:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          SEND_STRING(SS_TAP(X_QUOTE));
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          SEND_STRING("'");
        }
      }
      return false;

    case H_SEMI_COLON__BACKTICK:
      if (record -> event.pressed) {
        if (keyboard_report -> mods & MODS_SHIFT_MASK) {
          SEND_STRING("`");
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
        } else {
          SEND_STRING(SS_TAP(X_SCOLON));
        }
      }
      return false;

    case H_EOF:
      if (record -> event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_PGDOWN)));
      }
      return false;
    case H_7BIT:
      if (record -> event.pressed) {
        SEND_STRING("[7BIT] key");
      }
      return false;
    case H_CIRCLE_SM:
      if (record -> event.pressed) {
        SEND_STRING("[CIRCLE_SM] key");
      }
      return false;
    case H_RUN:
      if (record -> event.pressed) {
        SEND_STRING("[RUN] key");
      }
      return false;
  }
  return true;
};

void led_set_user(uint8_t usb_led) {

}
