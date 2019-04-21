#include QMK_KEYBOARD_H
#include "bit-shifter.h"

// Brevity defines
#define FT KC_TRNS

// This timeout is the total time that the leader is activated for
// feel free to tune for your use cases
// see: https://docs.qmk.fm/#/feature_leader_key
#define LEADER_TIMEOUT 1000

// activate leader functionality
LEADER_EXTERNS();

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
  * | F5  | F6  |Mark |Undo |#|Paste|  Cut   |Tab     |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  (  |  )  | Bspace | Clear  |Begin|#|  7  |  8  |  9  |  +  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F7  | F8  |Selec|Debug|#|Function|  Mode  |  Top   |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  | Return |  Line  |  Page  |#|  4  |  5  |  6  |  &  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F9  | F10 | TTY |LOCK |#|Begin| End | Symbol | Shift  |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  | Shift  | Symbol |  Up | End |#|  1  |  2  |  3  |  =  |
  * |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
  * | F11 | F12 |Home | EOF |#|Prev |Next |7bit | Alt | Hyper  | Spr |  Ctrl  | Space |TRNS |  Del   |  Ctrl  | Spr  | Hyper  |Meta |Left |Down |Right|#| Del |  0  |  .  | Run |
  * `-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------'
  *  missing mappings
  *  r1: Macro, Terminal, Quote, Overstrike, Clear Insert, Clear Screen, Hold Output, Stop Output, Abort, Break, Resume, Call
  *  r2: Local, Network, System, Refresh, Buffer, Square, Circle, Tringle, Diamond, Repeat, Transmit, Status, Suspend
  *  r3: Close, Open, Complete
  *
  *  r1: Find, Write
  *    [Compose]
  *       A: we'll use KC_COMPOSE to allow users to define they're own cadet-like compose functionality
  *  r2:: Mark
  *  r3: Select, Debug, Mode, Line, Page
  *  r4: TTY
  *  r2: EOF, 7bit, [circle], Run
  */

  [_BASE] = H7_KEYMAP(
    KC_NO,  H_HELP,  KC_NO, H_MACRO,    KC_NO, H_TERMINAL,  KC_NO,    H_QUOTE,    KC_NO,  H_OVERSTRIKE, KC_NO,    H_CLEAR_INSERT,  KC_NO,    H_CLEAR_SCREEN, KC_NO,    H_HOLD_OUTPUT, KC_NO,  H_STOP_OUTPUT, KC_NO,   H_ABORT,  KC_NO,  H_BREAK,    KC_NO,  H_RESUME,  KC_NO, H_CALL,    KC_NO,   RESET,
    KC_NO,  H_LOCAL, KC_NO, H_NETWORK,  KC_NO, H_SYSTEM,    KC_NO,    H_REFRESH,  KC_NO,  H_BUFFER,     KC_NO,    H_SQUARE,        KC_NO,    H_CIRCLE,       KC_NO,    H_TRIANGLE,    KC_NO,  H_DIAMOND,     KC_NO,   H_REPEAT, KC_NO,  H_TRANSMIT, KC_NO,  H_STATUS,  KC_NO, H_SUSPEND, KC_NO,   KC_CAPS,
    KC_F1,  KC_F2,    H_CLOSE, H_OPEN,    KC_ESC,   KC_QUES,  KC_EXLM,  UC(AT_SYMBOL),    UC(GBP), UC(EURO), UC(JPY),  UC(BACKTICK),UC(DQUOTE_OPEN), UC(DQUOTE_CLOSE),UC(PRIME), KC_UNDS, KC_LABK,  KC_RABK,  UC(PIPE),KC_LCBR, KC_RCBR,  H_COMPLETE,                       KC_CIRC, KC_PERC,  KC_HASH, KC_DLR,

    KC_F3,  KC_F4,    KC_FIND,  H_WRITE,  KC_LEAD,  H_DOUBLE_QUOTE__PLUS_MINUS, H_COLON__TILDE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    KC_6,     KC_7,    KC_8,     KC_9,    KC_0,     KC_MINS,  KC_EQL,  KC_NUBS, H_LEFT_BRACE__LEFT_CHEVRON,  H_RIGHT_BRACE__RIGHT_CHEVRON,  KC_UNDO,             KC_TILD, KC_SLSH,  KC_PAST, KC_PMNS,
    KC_F5,  KC_F6,    KC_EXLM,  KC_UNDO,  KC_PASTE, KC_CUT ,  KC_TAB ,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_Y,     KC_U,    KC_I,     KC_O,    KC_P,     KC_LPRN,  KC_RPRN, KC_BSPC, KC_CLEAR, KC_HOME,                     KC_P7,    KC_P8,     KC_P9,    KC_PPLS,
    KC_F7,  KC_F8,    KC_SELECT, H_DEBUG, MO(_FN), H_MODE,       MO(_APL), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    KC_H,     KC_J,    KC_K,     KC_L,    KC_SCLN,  KC_QUOT,  KC_ENT , H_LINE, H_PAGE,                           KC_P4,    KC_P5,     KC_P6,    KC_AMPR,
    KC_F9,  KC_F10,   H_TTY,  H_LOCK, KC_HOME,  KC_END ,  MO(_SYML), KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,     KC_N,    KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT, MO(_SYML),KC_UP,    KC_END,                        KC_P1,    KC_P2,     KC_P3,    KC_EQL,
    KC_F11, KC_F12,   KC_HOME,  H_EOF,  KC_MPRV,  KC_MNXT,  H_7BIT,  KC_LALT,  KC_HYPR,  KC_LGUI,  KC_LCTL,  KC_SPC,  H_CIRCLE_SM,  KC_DEL,  KC_RCTL,  KC_RGUI, KC_HYPR,  KC_RGUI,  KC_LEFT, KC_DOWN, KC_RGHT,                              KC_DEL,   KC_P0,     KC_PDOT,  H_FUNCTION_SM
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
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT ,      FT ,      FT ,      FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT,      FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT ,      FT ,      FT ,      FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT,      FT,       FT,      FT,      FT,       FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT ,      FT ,      FT ,      FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT,      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT ,      FT ,      FT ,      FT ,      FT ,     FT ,      FT ,     FT ,      FT ,     FT ,      FT,       FT,      FT,      FT,       FT,       FT,                  FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(N_ARY_LOGICAL_AND), UC(N_ARY_LOGICAL_OR), UC(N_ARY_INTERSECT), UC(N_ARY_UNION), UC(SUBSET_OF),UC(SUPERSET_OF), UC(FORALL),UC(_INFINITY), UC(END_OF_PROOF),UC(PARTIAL_DIFFERENTIAL),      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(UP_TACK), UC(DOWN_TACK), UC(RIGHT_TACK), UC(LEFT_TACK), UC(UPWARDS_ARROW),UC(DOWNARDS_ARROW), UC(LEFTWARDS_ARROW),UC(RIGHTWARDS_ARROW), UC(LEFTRIGHT_ARROW),     FT ,      FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT , UC(LEFT_FLOOR), UC(LEFT_CEILING), UC(NOT_EQUAL_TO), UC(ASYMPTOTICALLY_EQUAL_TO),UC(NOT_ASYMPTOTICALLY_EQUAL_TO), UC(LESS_THAN_OR_EQUAL),UC(GREATER_THAN_OR_EQUAL),      FT ,     FT ,      FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT ,      FT ,      FT ,      FT ,      FT ,     FT ,      FT ,     FT ,      FT ,     FT ,      FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
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
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT ,      FT ,     FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT ,     FT,      FT,      FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT ,      FT ,     FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT ,     FT,      FT,      FT,       FT,      FT,         FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT ,      FT ,     FT ,      FT ,     FT ,      FT ,     FT ,      FT ,      FT ,     FT,      FT,      FT,                            FT,      FT,       FT,      FT,

    FT,      FT,      FT,       FT,       FT, UC(CONTOUR_INTEGRAL),  FT,  UC(COPTIC_SMALL_LETTER_DEI), UC(DOUBLE_DAGGER), UC(NABLA), UC(CENT), UC(DEGREE), UC(APL_QUAD), UC(DIVISION), UC(MULTIPLICATION), UC(PILCROW), UC(LARGE_CIRCLE), UC(HORIZONTAL_BAR), UC(APPROXIMATELY_EQUAL_TO), UC(DOUBLE_VERTICAL_LINE), UC(SQUARE_IMAGE_OF), UC(SQUARE_ORIGINAL_OF),       FT,       FT,                 FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_SMALL_LETTER_THETA), UC(GREEK_SMALL_LETTER_OMEGA), UC(GREEK_SMALL_LETTER_EPSILON), UC(GREEK_SMALL_LETTER_RHO), UC(GREEK_SMALL_LETTER_TAU),UC(GREEK_SMALL_LETTER_PSI), UC(GREEK_SMALL_LETTER_UPSILON),UC(GREEK_SMALL_LETTER_IOTA), UC(GREEK_SMALL_LETTER_OMICRON),UC(GREEK_SMALL_LETTER_PI), UC(MATHEMATICAL_LEFT_WHITE_SQUARE_BRACKET), UC(MATHEMATICAL_RIGHT_WHITE_SQUARE_BRACKET),     FT,      FT,      FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  UC(GREEK_SMALL_LETTER_ALPHA), UC(GREEK_SMALL_LETTER_SIGMA), UC(GREEK_SMALL_LETTER_DELTA), UC(GREEK_SMALL_LETTER_PHI), UC(GREEK_SMALL_LETTER_GAMMA),UC(GREEK_SMALL_LETTER_ETA), UC(GREEK_LETTER_YOT),UC(GREEK_SMALL_LETTER_KAPPA), UC(GREEK_SMALL_LETTER_LAMDA), UC(TWO_DOT_LEADER), UC(BULLET),      FT ,     FT,      FT,                                     FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,  MO(_SYMU),  UC(GREEK_SMALL_LETTER_ZETA), UC(GREEK_SMALL_LETTER_XI), UC(GREEK_SMALL_LETTER_CHI), UC(GREEK_SMALL_LETTER_FINAL_SIGMA),UC(GREEK_SMALL_LETTER_BETA), UC(GREEK_SMALL_LETTER_NU),UC(GREEK_SMALL_LETTER_MU), UC(MUCH_LESS_THAN),UC(MUCH_GREATER_THAN), UC(INTEGRAL),      FT ,     FT,      FT,      FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT ,      FT,       FT ,      FT ,     FT ,      FT ,     FT ,      FT,      FT ,      FT ,      FT ,     FT,      FT,                                     FT,      FT,       FT,      FT
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
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,       FT,                            FT,      FT,       FT,      FT,
    FT,      FT,      FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,       FT,      FT,      FT,                                      FT,      FT,       FT,      FT
  )
};


void matrix_init_user(void) {
  // replace UC_WIN or UC_WINC with UC_OSX for mac or UC_LNX for Linux.
  // To enable UC_WIN:
  // create registry key under:
  // HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad
  // of type:
  // REG_SZ
  // called EnableHexNumpad
  // set its value to 1, and reboot.
  set_unicode_input_mode(UC_LNX);
}

void matrix_scan_keymap(void) {
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
    // SEQ_THREE_KEYS(KC_A, KC_A, KC_S) {
    //   SEND_STRING("https://start.duckduckgo.com"SS_TAP(X_ENTER));
    // }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
