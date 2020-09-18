#include QMK_KEYBOARD_H
#include "planck.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_planck_mit(KC_TAB,          KC_Q,        KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
	                        LCTL_T(KC_ESC),  KC_A,        KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
	                        KC_LSHIFT,       KC_Z,        KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_SFTENT,
	                        KC_MPLY,         KC_LCTL,     KC_LALT,  KC_LGUI,  OSL(1),   KC_SPC,             OSL(2),   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT),

	[1] = LAYOUT_planck_mit(KC_TRNS,         KC_GRV,      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_MINS,  KC_EQL,   KC_DEL,
	                        KC_TRNS,         KC_1,        KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_NUHS,
	                        KC_TRNS,         KC_NUBS,     KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LBRC,  KC_RBRC,  KC_TRNS,
	                        KC_TRNS,         KC_TRNS,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            MO(3),    KC_MRWD,  KC_MUTE,  KC_MPLY,  KC_MNXT),

	[2] = LAYOUT_planck_mit(KC_TRNS,         S(KC_GRV),   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_UNDS,  KC_PLUS,  KC_DEL,
	                        KC_TRNS,         S(KC_1),     S(KC_2),  S(KC_3),  S(KC_4),  S(KC_5),  S(KC_6),  S(KC_7),  S(KC_8),  S(KC_9),  S(KC_0),  S(KC_NUHS),
	                        KC_TRNS,         S(KC_NUBS),  KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_LCBR,  KC_RCBR,  KC_TRNS,
	                        KC_TRNS,         KC_TRNS,     KC_TRNS,  KC_TRNS,  MO(3),    KC_TRNS,            KC_TRNS,  KC_MRWD,  KC_MUTE,  KC_MPLY,  KC_MNXT),

	[3] = LAYOUT_planck_mit(KC_NO,           KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
	                        KC_NO,           KC_F1,       KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_NO,
	                        KC_NO,           KC_F11,      KC_F12,   KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
	                        KC_NO,           KC_NO,       KC_NO,    KC_NO,    KC_TRNS,  KC_NO,              KC_TRNS,  KC_NO,    KC_NO,    KC_NO,    KC_NO)
};

void encoder_update_user(uint8_t index, bool clockwise) {
    clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
}
