/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

enum planck_layers {
    _QWERTY,
    _COLEMAK,
    _SYMBOLS,
    _NUMBERS,
    _NAVIGATION,
    _LEFT_NAVIGATION,
    _MEDIA,
    _GAME,
    _SWAPPER,
    _FUNCTION,
    _ADJUST,
};

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    A_F4,
    SNIP,      // Open Snip & Sketch
    ALT_TAB
};

bool is_alt_tab_active = false;

#define SYM LT(_SYMBOLS, KC_SPC)
#define NUM TG(_NUMBERS)
#define NAV LT(_NAVIGATION, KC_SPC)
#define L_NAV MO(_LEFT_NAVIGATION)
#define SWAPPER MO(_SWAPPER)
#define MEDIA MO(_MEDIA)
#define FUNCTION OSL(_FUNCTION)
#define GAME TG(_GAME)

// QWERTY
// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

// Colemak
// Left-hand home row mods
#define HOME_R LALT_T(KC_R)
#define COLE_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,         KC_Q,          KC_W,    KC_E,   KC_R,   KC_T,     KC_Y,   KC_U,   KC_I,     KC_O,    KC_P,     KC_BSPC,
    RCTL_T(KC_ESC), KC_A,          HOME_S,  HOME_D, HOME_F, KC_G,     KC_H,   HOME_J, HOME_K,   HOME_L,  KC_SCLN,  KC_QUOT,
    KC_LSFT,        KC_Z,          KC_X,    KC_C,   KC_V,   KC_B,     KC_N,   KC_M,   KC_COMMA, KC_DOT,  KC_SLASH, RSFT_T(KC_ENT),
    KC_ESC,         OSM(MOD_LGUI), ALT_TAB, L_NAV,  SYM,    FUNCTION, MEDIA,  NAV,    KC_DEL,   _______, _______,  GAME
),

[_COLEMAK] = LAYOUT_planck_grid(
    _______, _______, _______, KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCOLON, _______,
    _______, KC_A,    HOME_R,  COLE_S,  HOME_T,  KC_D,    _______, HOME_N,  HOME_E,  HOME_I,  KC_O,      _______,
    _______, _______, _______, _______, _______, _______, KC_K,    _______, _______, _______, _______,   _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______
),

[_SYMBOLS] = LAYOUT_planck_grid(
    A_F4,          KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,          KC_7,         KC_8,        KC_9,          KC_0,           KC_DEL,
    KC_CAPS,       KC_EXCLAIM, KC_AT,      KC_HASH,    KC_DOLLAR,  KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_UNDS,
    OSM(MOD_LGUI), LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_S), KC_PLUS,       KC_MINS,      KC_EQL,      KC_LCBR,       KC_RCBR,        KC_PIPE,
    _______,       _______,    _______,    _______,    _______,    _______,    KC_GRAVE,      _______,      KC_BSLS,     KC_LBRC,       KC_RBRC,        KC_TILD
),

[_NUMBERS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, KC_NLCK, KC_P7,  KC_P8,   KC_P9,   KC_PMNS, KC_BSPC,
    _______, _______, _______, _______, _______, _______, _______, KC_P4,  KC_P5,   KC_P6,   KC_PPLS, KC_PAST,
    _______, _______, _______, _______, _______, _______, KC_COMM, KC_P1,  KC_P2,   KC_P3,   KC_EQL,  _______,
    _______, _______, _______, _______, KC_SPC,  _______, KC_SPC,  KC_P0,  KC_COMM, KC_PDOT, KC_PSLS, _______
),

[_NAVIGATION] = LAYOUT_planck_grid(
    _______, _______, _______, KC_LBRC, KC_RBRC, _______, KC_PAUS, KC_APP,  KC_UP,   KC_INS,   KC_SCROLLLOCK, _______,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,        _______,
    _______, _______, _______, _______, KC_TILD, _______, _______, _______, _______, _______,  _______,       _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,       _______
),

[_LEFT_NAVIGATION] = LAYOUT_planck_grid(
    KC_MYCM, KC_PGUP, KC_HOME, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______,
    KC_WBAK, KC_PGDN, KC_END,  KC_WFWD, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
    _______, _______, _______, _______, NUM,     _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_MEDIA] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLU, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_MRWD, KC_VOLD, KC_MFFD, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,   KC_E, KC_R,     KC_T, _______, _______, _______, _______, _______, _______,
    KC_LCTL, KC_A,    KC_S,   KC_D, KC_F,     KC_G, KC_H, _______, _______, _______, _______, _______,
    KC_LSFT, KC_Z,    KC_X,   KC_C, KC_V,     KC_B, _______, _______, _______, _______, _______, _______,
    KC_LCTL, _______, KC_ESC, KC_4, KC_SPACE, _______, _______, _______, _______, _______, KC_PSCR, GAME
),

[_SWAPPER] = LAYOUT_planck_grid(
    KC_ESC,  KC_UP,   KC_DEL,   _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_FUNCTION] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, KC_LGUI, KC_LALT,  KC_LCTL, KC_LSFT, _______, _______, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, _______,
    _______, _______, _______,  KC_PSCR, SNIP,    _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    QWERTY,  _______, MU_MOD,  AU_ON,   AU_OFF,  _______, KC_TAPP, KC_TAPD, KC_TAPU,  _______, _______, COLEMAK,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _FUNCTION, _MEDIA, _ADJUST);
}

bool is_swapper_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case KC_UP:
        case KC_LEFT:
        case KC_DOWN:
        case KC_RGHT:
        case KC_DEL:
            return true;
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == ALT_TAB) {
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                register_code(KC_LALT);
                layer_on(_SWAPPER);
            }
            register_code(KC_TAB);
            } else {
            unregister_code(KC_TAB);
            }
    } else if (is_alt_tab_active && !is_swapper_ignored_key(keycode)) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
        layer_off(_SWAPPER);
        return false;
    }

    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case A_F4:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_F4);
                unregister_code(KC_LALT);
            }
            break;
        case SNIP:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("s")));
            }
            break;
    }
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // GUI
        case HOME_A:
        case HOME_SCLN:
        case HOME_O:
            return TAPPING_TERM;
        // ALT
        case HOME_S:
        case HOME_L:
        case HOME_R:
        case HOME_I:
            return TAPPING_TERM;
        // SHIFT
        case HOME_D:
        case HOME_K:
        case COLE_S:
        case HOME_E:
            return TAPPING_TERM;
        // CONTROL
        case HOME_F:
        case HOME_J:
        case HOME_T:
        case HOME_N:
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}
