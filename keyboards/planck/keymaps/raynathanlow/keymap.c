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
  _ONESHOT,
  _ALT,
  _GUI,
  _MOUSE,
  _GAME,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOCK,
  ALTF4,
  CTLINS,
  SHFTINS,
};

enum tapdancers {
    T_1 = 0, // 1, !
    T_2, // 2, @
    T_3, // 3, #
    T_4, // 4, $
    T_5, // 5, %
    T_6, // 6, ^
    T_7, // 7, &
    T_8, // 8, *
    T_9, // 9, (
    T_0, // 0, )
    T_BR, // [, ]
    T_PA, // (, )
    T_CU, // {, }
    T_GT, // `, ~
    T_ME, // -, =
    T_BP, // \, |
    T_PU, // +, _
};

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
  [T_1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_EXLM),
  [T_2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_AT),
  [T_3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_HASH),
  [T_4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_DLR),
  [T_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_PERC),
  [T_6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_CIRC),
  [T_7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_AMPR),
  [T_8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_ASTR),
  [T_9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_LPRN),
  [T_0] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_RPRN),
  [T_BR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [T_PA] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [T_CU] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [T_GT] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),
  [T_ME] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQUAL),
  [T_BP] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  [T_PU] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_UNDS),
};

// TODO: Update ASCII Representation and align everything

#define LOWER TT(_LOWER)
#define RAISE MO(_RAISE)
#define ONESHOT OSL(_ONESHOT)
#define ALT LM(_ALT, MOD_LALT)
#define GUI LM(_GUI, MOD_LGUI)
#define MOUSE TT(_MOUSE)
#define GAME TT(_GAME)

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
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENT),
    _______, ONESHOT, GUI,     ALT,     KC_LCTL, LOWER,   RAISE,   KC_SPC,  MOUSE  , GAME,   KC_DOWN, KC_UP
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
    KC_TAB,  TD(T_1), TD(T_2), TD(T_3), TD(T_4), TD(T_5), TD(T_6), TD(T_7), TD(T_8), TD(T_9),  TD(T_0),  KC_BSPC,
    KC_ESC,  _______, KC_WBAK, KC_PGDN, KC_PGUP, KC_WFWD, TD(T_GT),TD(T_PA),TD(T_CU),TD(T_BR), TD(T_PU), KC_DEL,
    KC_LSFT, _______, _______, _______, _______, _______, TD(T_BP),TD(T_ME),KC_COMM, KC_KP_DOT,KC_PENT,  MT(MOD_RSFT, KC_ENT),
    _______, _______, _______, _______, _______, _______, _______, KC_SPC,  _______, _______, _______,   _______
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
    KC_TAB,  _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,  _______, _______,
    KC_ESC,  _______, _______, _______, _______, _______, KC_MUTE, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD,  KC_MPLY, _______,
    _______, _______, _______, _______, KC_LCTL, _______, _______, _______, _______, _______,  _______, _______
),

/* ONESHOT
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
[_ONESHOT] = LAYOUT_planck_grid(
    _______, _______, KC_F11,  KC_F12,  KC_F2,   KC_F8, _______, _______, _______, _______, _______, KC_SLEP,
    KC_CAPS, _______, _______, KC_END,  KC_HOME, ALTF4, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, CTLINS,  SHFTINS, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LOCK
),

/* ALT
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
[_ALT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* GUI
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
[_GUI] = LAYOUT_planck_grid(
    KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    _______, _______, _______, KC_UP,   _______, _______, _______,
    KC_ESC,  _______, KC_E,    _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* MOUSE
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
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______, _______, KC_MS_U, _______, _______, _______, KC_WH_D, KC_WH_U, _______, _______, _______,
    _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_WH_L, KC_BTN1, KC_BTN2, KC_WH_R, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* GAME
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
[_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT),
    _______, KC_4,    KC_3,    KC_2,    KC_SPC,  KC_1, KC_LBRC, KC_RBRC,_______, _______, _______, _______
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
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______,  _______,_______,
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
    case LOCK:
        if (record -> event.pressed) {
            SEND_STRING(SS_LGUI("l"));
        }
        break;
    case ALTF4:
        if (record -> event.pressed) {
            register_code(KC_LALT);
            tap_code(KC_F4);
            unregister_code(KC_LALT);
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
    }
  return true;
}
