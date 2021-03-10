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
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GUI1,
  GUI2,
  CTLINS,
  SHFTINS,
  UNDERSCORE,
  GUIUP,
  GUIDOWN,
  GUILEFT,
  GUIRIGHT
};

enum tapdancers {
    T_BR = 0, // [, ]
    T_PA, // (, )
    T_CU, // {, }
    T_GT, // `, ~
    T_ME, // -, =
    T_BP, // \, |
    T_PS, // +, /
    T_EXLM_W1, // !, GUI + 1
    T_AT_W2 // @, GUI + 2
};

// Maybe I can refactor this so that I don't repeat myself for win2
void exlm_win1(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    SEND_STRING("!");
    reset_tap_dance(state);
    break;
  case 2:
    register_code16(G(KC_1)); unregister_code16(G(KC_1));
    break;
  }
}

void at_win2(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    SEND_STRING("@");
    reset_tap_dance(state);
    break;
  case 2:
    register_code16(G(KC_2)); unregister_code16(G(KC_2));
    break;
  }
}

void gt(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    SEND_STRING("@");
    reset_tap_dance(state);
    break;
  case 2:
    SEND_STRING("~");
    break;
  }
}

void bp(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    SEND_STRING("@");
    reset_tap_dance(state);
    break;
  case 2:
    register_code16(G(KC_2)); unregister_code16(G(KC_2));
    break;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [T_BR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [T_PA] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [T_CU] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [T_GT] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
  [T_ME] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQUAL),
  [T_BP] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE), // ACTION_TAP_DANCE_FN b/c need shifted version?
  [T_PS] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_PSLS),
  [T_EXLM_W1] = ACTION_TAP_DANCE_FN (exlm_win1),
  [T_AT_W2] = ACTION_TAP_DANCE_FN (at_win2)
};

// Macros and Functions Needed
// TD_GT
// TD_BP

// TODO: Update ASCII Representation and align everything

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sh/En |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),
    _______, _______, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    TD(T_EXLM_W1),    TD(T_AT_W2), KC_HASH, KC_DLR, KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_7, KC_8, KC_9, KC_BSPC,
    GUI1,           KC_F8,       KC_F12,   KC_END,   KC_HOME,   TD(T_GT),   TD(T_ME),   TD(T_PA),    KC_4,    KC_5, KC_6, KC_DEL,
    GUI2,          CTLINS,       SHFTINS,    KC_PGDN,  KC_PGUP,  UNDERSCORE,  TD(T_BR),  TD(T_CU), KC_1, KC_2, KC_3,  TD(T_PS),
    _______, _______, _______, _______, _______, _______, KC_SPC, TD(T_BP),    KC_0,    KC_COMM, KC_KP_DOT, KC_PENT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    _______,  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    GUIUP,    _______,    _______,
    _______,  _______,   _______,   _______,   _______,   _______,   _______,   _______, GUILEFT,  GUIDOWN, GUIRIGHT, _______,
    _______, _______,   _______,   _______,   KC_CAPS,  _______,  _______,  _______, KC_MPRV, KC_MPLY, KC_MNXT, _______,
    _______, _______, _______, _______, KC_LSFT, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______,  _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
        if (record -> event.pressed) {
            print("mode just switched to qwerty and this is a huge string\n");
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
    case GUI1:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI("1"));
        }
        break;
    case GUI2:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI("2"));
        }
        break;
    case CTLINS:
        if (record -> event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_INS)));
        }
        break;
    case SHFTINS:
        if (record -> event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_INS)));
        }
        break;
    case UNDERSCORE:
        if (record -> event.pressed) {
            SEND_STRING("_");
        }
        break;
    case GUIUP:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_UP)));
        }
        break;
    case GUIDOWN:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
        }
        break;
    case GUILEFT:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
        }
        break;
    case GUIRIGHT:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
        }
        break;
    }
  return true;
}
