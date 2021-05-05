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

enum planck_layers { _QWERTY, _COLEMAK, _ONESHOT, _LAYERS, _SYMBOLS, _NAVIGATION, _MOUSE, _GAMING, _MEDIA, _ADJUST, _ALT };

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAK,
    A_TAB,     // alt tab
    A_F4,      // close window
    C_INS,     // copy in some terminals
    S_INS,     // paste in some terminals
    G_L,       // lock
    GS_S,      // screenshot
    G_TAB,     // task view
    GC_LEFT,   // left virtual desktop
    GC_RIGHT,  // right virtual desktop
    G_1,       // 1st pinned program in Taskbar
    G_2,       // 2st pinned program in Taskbar
    G_E,       // Windows Explorer,
    G_LEFT,    // maximize window to left side of screen
    G_DOWN,    // minimize window
    G_UP,      // maximize window
    G_RIGHT,   // maximize window to right side of screen
    GS_LEFT,   // move window to another monitor
    GS_RIGHT   // move window to another monitor
};

// Super Alt Tab
// Needs to be near the beginning
// https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros#super-alt-tab
bool     is_alt_tab_active = false;
uint16_t alt_tab_timer     = 0;

#define ONESHOT OSL(_ONESHOT)
#define LAYERS OSL(_LAYERS)
#define SYMBOLS OSL(_SYMBOLS)
#define NAVIGATION TT(_NAVIGATION)
#define MOUSE TO(_MOUSE)
#define GAMING TO(_GAMING)
#define MEDIA TO(_MEDIA)
#define ALT LM(_ALT, MOD_LALT)

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_D LSFT_T(KC_D)
#define CTL_F LCTL_T(KC_F)

// Right-hand home row mods
#define CTL_J RCTL_T(KC_J)
#define SFT_K RSFT_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define GUI_SCLN RGUI_T(KC_SCLN)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LSFT_T(KC_S)
#define HOME_T LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N RCTL_T(KC_N)
#define HOME_E RSFT_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RGUI_T(KC_O)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default
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
    KC_TAB,        KC_Q,    KC_W,      KC_E,  KC_R,    KC_T,    KC_Y,       KC_U,   KC_I,    KC_O,    KC_P,     KC_BSPC,
    KC_ESC,        GUI_A,   ALT_S,     SFT_D, CTL_F,   KC_G,    KC_H,       CTL_J,  SFT_K,   ALT_L,   GUI_SCLN, KC_QUOT,
    OSM(MOD_LSFT), KC_Z,    KC_X,      KC_C,  KC_V,    KC_B,    KC_N,       KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
    LAYERS,    _______, _______,   ALT,   SYMBOLS, ONESHOT, NAVIGATION, KC_SPC, KC_ESC,  KC_DEL,  KC_DOWN,  KC_UP
),

/* COLEMAK
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
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,        KC_Q,    KC_W,    KC_F,   KC_P,    KC_G,    KC_J,       KC_L,   KC_U,    KC_Y,   KC_SCLN, KC_BSPC,
    KC_ESC,        HOME_A,  HOME_R,  HOME_S, HOME_T,  KC_D,    KC_H,       HOME_N, HOME_E,  HOME_I, HOME_O,  KC_QUOT,
    OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_K,       KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
    OSL(_LAYERS),    _______, _______, ALT,    SYMBOLS, ONESHOT, NAVIGATION, KC_SPC, KC_ESC,  KC_DEL, KC_DOWN, KC_UP
),

/* One Shot
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
    A_F4, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
    KC_HOME, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), KC_F12, KC_F2, KC_PLUS, KC_COMM, KC_DOT, KC_SLSH, KC_DEL,
    KC_END, GS_S, KC_WBAK, KC_PGUP, KC_PGDN, KC_WFWD, KC_F11, KC_MINUS, KC_ASTERISK, _______, _______, KC_ENT,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Layers
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'F
 */
[_LAYERS] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, MOUSE,   GAMING, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Symbols
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
[_SYMBOLS] = LAYOUT_planck_grid(
    _______, KC_EXCLAIM,    KC_AT,         KC_HASH,       KC_DOLLAR,     KC_PERCENT, KC_CIRCUMFLEX, KC_AMPERSAND, KC_ASTERISK,   KC_LEFT_PAREN,       KC_RIGHT_PAREN,       KC_BSPC,
    KC_CAPS, KC_GRAVE,      KC_PIPE,       KC_BSLASH,     KC_UNDERSCORE, _______,    _______,       KC_MINUS,     KC_EQUAL,      KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_DEL,
    _______, _______,       G_TAB,         GC_LEFT,       GC_RIGHT,      _______,    _______,       KC_TILDE,     KC_PLUS,       KC_LBRACKET,         KC_RBRACKET,          _______,
    _______, _______,       _______,       _______,       _______,       _______,    _______,       _______,      _______,       _______,             _______,              _______
),

/* Navigation
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
[_NAVIGATION] = LAYOUT_planck_grid(
    _______, _______,       KC_TAPP,       KC_TAPU,       KC_TAPD,       _______, _______,             KC_MEDIA_PLAY_PAUSE, KC_UP,           KC_AUDIO_MUTE,       _______, KC_BSPC,
    _______, OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LSFT), OSM(MOD_LCTL), _______, _______,             KC_LEFT,             KC_DOWN,         KC_RIGHT,            _______, KC_DEL,
    _______, _______,       _______,       KC_HOME,       KC_END,        _______, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK, _______, _______,
    _______, _______,       _______,       _______,       _______,       _______, _______,             _______,             _______,         _______,             _______, _______
),

/* Media
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
[_MEDIA] = LAYOUT_planck_grid(
    _______, _______, _______,             _______,         _______,             _______,               _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_UP, KC_AUDIO_VOL_DOWN,   KC_MEDIA_NEXT_TRACK,   _______, _______, _______, _______, _______, _______,
    _______, _______, KC_MEDIA_REWIND,     KC_AUDIO_MUTE,   KC_MEDIA_PLAY_PAUSE, KC_MEDIA_FAST_FORWARD, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,             _______,         _______,             _______,               _______, _______, _______, _______, _______, _______
),

/* Mouse Keys
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

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sh/En |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |j2
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y,    KC_U,   KC_I,    KC_O,              KC_P,            KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H,    KC_J,   KC_K,    KC_L,              KC_SCLN,         KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N,    KC_M,   KC_COMM, KC_DOT,            KC_SLSH,         KC_ENT,
    KC_LCTL, KC_4,    KC_3,    KC_2,    KC_SPC,  KC_1, KC_LBRC, KC_RBRC,KC_PSCR, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, TO(_QWERTY)
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
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, _______,  _______,  _______,  _______,_______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

[_ALT] = LAYOUT_planck_grid(
    _______, _______, KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_DEL,  _______, _______, _______, KC_DEL,  KC_RSFT, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _ONESHOT, _NAVIGATION, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
        case A_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case A_F4:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_F4);
                unregister_code(KC_LALT);
            }
            break;
        case C_INS:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_TAP(X_INS)));
            }
            break;
        case S_INS:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_TAP(X_INS)));
            }
            break;
        case G_L:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("l"));
            }
            break;
        case GS_S:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT("s")));
            }
            break;
        case G_TAB:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_TAB)));
            }
            break;
        case GC_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_LEFT))));
            }
            break;
        case GC_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LCTRL(SS_TAP(X_RIGHT))));
            }
            break;
        case G_1:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("1"));
            }
            break;
        case G_2:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("2"));
            }
            break;
        case G_E:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI("e"));
            }
            break;
        case G_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
            }
            break;
        case G_DOWN:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
            }
            break;
        case G_UP:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_UP)));
            }
            break;
        case G_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)));
            }
            break;
        case GS_LEFT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_LEFT))));
            }
            break;
        case GS_RIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_RIGHT))));
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {  // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

// TAPPING_FORCE_HOLD_PER_KEY
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_A:
        case ALT_S:
        case SFT_D:
        case CTL_F:
        case CTL_J:
        case SFT_K:
        case ALT_L:
        case GUI_SCLN:
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GUI_A:
        case GUI_SCLN:
            return TAPPING_TERM;
        case ALT_S:
        case ALT_L:
            return TAPPING_TERM;
        case SFT_D:
        case SFT_K:
            return TAPPING_TERM;
        case CTL_F:
        case CTL_J:
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

// bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case GUI_A:
//         case GUI_SCLN:
//             return false;
//         case ALT_S:
//         case ALT_L:
//             return false;
//         case SFT_D:
//         case SFT_K:
//             return true;
//         case CTL_F:
//         case CTL_J:
//             return true;
//         default:
//             return false;
//     }
// }
