#pragma once

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 125

#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define TAPPING_TOGGLE 2 // Tapping this number of times toggles Tap-Toggle layer - TT(layer)

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD_PER_KEY

// Apply the modifier on keys that are tapped during a short hold of a modtap
// #define PERMISSIVE_HOLD_PER_KEY
#define PERMISSIVE_HOLD

// https://github.com/manna-harbour/miryoku_qmk/blob/bdb9fd81e8aa2afb3882f7c0f6ae2d3ba448ac93/users/manna-harbour_miryoku/config.h#L23-L33
// default: 50
#define MOUSEKEY_INTERVAL 16

// default: 300
#define MOUSEKEY_DELAY 0

// default: 20
#define MOUSEKEY_TIME_TO_MAX 60

// default: 10
#define MOUSEKEY_MAX_SPEED 7

// default: 300
#define MOUSEKEY_WHEEL_DELAY 0
