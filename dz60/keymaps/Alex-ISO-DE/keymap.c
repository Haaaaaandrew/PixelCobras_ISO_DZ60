#include "dz60.h"
#include "keymap_german.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ISO 7u layout w/ Split RShift layer 0
* ,-----------------------------------------------------------------------------------------.
* |  ESC  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  ß  |  ´  |   BSPC    |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  Q  |  W  |  E  |  R  |  T  |  Z  |  U  |  I  |  O  |  P  |  Ü  | *  |  ENTER  |
* |---------------------------------------------------------------------------------|       +
* | Caps Lock|  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  Ö  |  Ä |  #  |       |
* |-----------------------------------------------------------------------------------------+
* | Shift  | < |  Y  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  -  |  RShift  | Fn_1|S
* |-----------------------------------------------------------------------------------------+
* | LCtrl   |LGUI|  LAlt  |                  Space                 |  ALGR  | RGUI |  RCtrl |
* `-----------------------------------------------------------------------------------------'
*/

/* ISO 7u layout w/ Split RShift layer 1 ("--" indicates no change from layer 0) [I haven't started modifying the code for this yet.]
* ,-----------------------------------------------------------------------------------------------------------------------.
* | Esc   |  F1   | F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   | F10   | F11    | F12   |     BSPC      |
* |-----------------------------------------------------------------------------------------------------------------------+
* | --    |  --  |  VolU  |  --  |  --  |  --  |  --  |  PgUp  |  UP  |  PgDn  |  PrntScr  |  ScrLk  | PauBrk  |  ENTER   |
* |---------------------------------------------------------------------------------------------------------------|       +
* |   --    | PTrk  | VolD | NTrk |  --  |  --   |  HOME  |  LEFT  |  DOWN  |  RIGHT    |  END    | --   |  --    |       |
* |-----------------------------------------------------------------------------------------------------------------------+
* |   --  | -- |LEDTog|  LEDmod  |  Bright-  |  Bright+ |  Satur-  |  Satur+  |  µ     |  Hue-  | Hue+  |  --  |  --  | --|
* |-----------------------------------------------------------------------------------------------------------------------+
* |    --   |RESET|     --     |                       Space                          |     --     |    --    |     --    |
* `-----------------------------------------------------------------------------------------------------------------------'
*/

	KEYMAP(
		KC_GESC,  DE_1,       DE_2,     DE_3,     DE_4,     DE_5,     DE_6,     DE_7, 	DE_8, 		DE_9,		DE_0, 		DE_SS,    DE_ACUT, 	KC_BSPC, 	KC_BSPC,
		KC_TAB,   DE_Q,       DE_W,     DE_E,     DE_R,     DE_T,     DE_Z,     DE_U, 	DE_I, 		DE_O,		DE_P, 	  DE_UE,    DE_PLUS, 	DE_HASH,
		KC_CAPS,  DE_A,       DE_S,     DE_D,     DE_F,     DE_G,     DE_H,     DE_J, 	DE_K, 		DE_L, 	DE_OE, 	  DE_AE,    KC_ENT,
		KC_LSFT,  DE_LESS,    DE_Y,     DE_X,     DE_C,     DE_V,     DE_B,     DE_N, 	DE_M, 		DE_COMM, 	DE_DOT, 	DE_MINS, KC_RSFT, MO(1),
    KC_LCTL,  KC_LGUI,  KC_LALT,  KC_SPC,   KC_SPC,   KC_SPC,   KC_NO,	DE_ALGR, 	KC_NO, 		KC_RGUI, 		KC_RCTL),


	KEYMAP(
    KC_TRNS,   KC_F1,     KC_F2,    KC_F3,     KC_F4,      KC_F5,     KC_F6,       KC_F7,     KC_F8,       KC_F9,      KC_F10,     KC_F11,    KC_F12,    KC_DEL,   KC_DEL,
    KC_TRNS,  KC_TRNS,   KC_VOLU,  KC_TRNS,   KC_PSCR,   KC_SLCK,    KC_PAUS,     KC_PGUP,   KC_TRNS,       KC_PGUP,      KC_HOME,   KC_UP,    KC_END,   KC_TRNS,
    KC_CAPS,  KC_MPRV,    KC_VOLD,  KC_MNXT,  KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,    KC_PGDN,    KC_LEFT,    KC_RIGHT,    KC_TRNS,
    KC_LSFT,  DE_LESS,   RGB_TOG,  RGB_MOD,   RGB_VAD,   RGB_VAI,    RGB_SAD,     RGB_SAI,   KC_TRNS,     RGB_HUD,    RGB_HUI,   KC_DOWN,    KC_RSFT,   KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,     KC_TRNS,   KC_TRNS,     KC_TRNS,    KC_TRNS),


};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
        send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}
