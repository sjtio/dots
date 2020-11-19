#include QMK_KEYBOARD_H
#include "planck.h"

enum layers {
    _QWERTY=0,
    _LOWER,
    _HIGHER,
    _EXTRA
};

enum keycode {
    SHFT_HLD=SAFE_RANGE
};

enum tapdance {
    TD_SHIFT
};

qk_tap_dance_action_t tap_dance_actions[] = { [TD_SHIFT] = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_CAPS) };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY] = LAYOUT_planck_mit(KC_TAB,          KC_Q,        KC_W,     KC_E,     KC_R,         KC_T,     KC_Y,     KC_U,          KC_I,     KC_O,     KC_P,     KC_BSPC,
	                              LCTL_T(KC_ESC),  KC_A,        KC_S,     KC_D,     KC_F,         KC_G,     KC_H,     KC_J,          KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
	                              TD(TD_SHIFT),    KC_Z,        KC_X,     KC_C,     KC_V,         KC_B,     KC_N,     KC_M,          KC_COMM,  KC_DOT,   KC_SLSH,  KC_SFTENT,
	                              SHFT_HLD,        KC_NO,       KC_LALT,  KC_LGUI,  OSL(_LOWER),  KC_SPC,             OSL(_HIGHER),  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT),

	[_LOWER]  = LAYOUT_planck_mit(KC_TRNS,         KC_GRV,      KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_MINS,  KC_EQL,   KC_BSPC,
	                              KC_TRNS,         KC_1,        KC_2,     KC_3,     KC_4,         KC_5,     KC_6,     KC_7,          KC_8,     KC_9,     KC_0,     KC_NUHS,
	                              KC_TRNS,         KC_NUBS,     KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_LBRC,  KC_RBRC,  KC_TRNS,
	                              KC_MUTE,         KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,            MO(_EXTRA),    KC_MPRV,  KC_MUTE,  KC_MPLY,  KC_MNXT),

	[_HIGHER] = LAYOUT_planck_mit(KC_TRNS,         S(KC_GRV),   KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_UNDS,  KC_PLUS,  KC_BSPC,
	                              KC_TRNS,         S(KC_1),     S(KC_2),  S(KC_3),  S(KC_4),      S(KC_5),  S(KC_6),  S(KC_7),       S(KC_8),  S(KC_9),  S(KC_0),  S(KC_NUHS),
	                              KC_TRNS,         S(KC_NUBS),  KC_NO,    KC_NO,    KC_NO,        KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_LCBR,  KC_RCBR,  KC_TRNS,
	                              KC_TRNS,         KC_TRNS,     KC_TRNS,  KC_TRNS,  MO(_EXTRA),   KC_TRNS,            KC_TRNS,       KC_MPRV,  KC_MUTE,  KC_MPLY,  KC_MNXT),

	[_EXTRA]  = LAYOUT_planck_mit(KC_NO,           KC_F1,       KC_F2,    KC_F3,    KC_F4,        KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,    KC_NO,    KC_DEL,
	                              KC_NO,           KC_F5,       KC_F6,    KC_F7,    KC_F8,        KC_NO,    KC_LEFT,  KC_DOWN,       KC_UP,    KC_RGHT,  KC_NO,    KC_NO,
	                              KC_NO,           KC_F9,       KC_F10,   KC_F11,   KC_F12,       KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,    KC_NO,    KC_NO,
	                              KC_NO,           KC_NO,       KC_NO,    KC_NO,    KC_TRNS,      KC_NO,              KC_TRNS,       KC_NO,    KC_NO,    KC_NO,    KC_NO)
};

bool shift_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode == SHFT_HLD && record->event.pressed) {
      if (shift_pressed) {
          unregister_code(KC_LSHIFT);
          shift_pressed = false;
      } else {
          register_code(KC_LSHIFT);
          shift_pressed = true;
      }
      return false;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {
        case (_QWERTY):
            clockwise ? tap_code(KC_LEFT) : tap_code(KC_RIGHT);
            break;
        case (_LOWER):
            clockwise ? tap_code(KC_VOLD) : tap_code(KC_VOLU);
            break;
        case (_HIGHER):
            clockwise ? tap_code(KC_BRID) : tap_code(KC_BRIU);
            break;
        case (_EXTRA):
            clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
            break;
    }
}
