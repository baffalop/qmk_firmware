#include QMK_KEYBOARD_H
#include <stdbool.h>
#include "caps_word.h"

// This particular implementation is by @dnaq at splitkb.com discord.
// Idea originally from @iaap, also at splitkb.com discord.
// Modified by @sevanteri (added underscores on spaces)
// Modified by @metheon (added ability to toggle between states)

// These two bools produces four states:
// if both false the features is turned off
// if caps word is true then CAPITALIZE next word
// if snake case enabled then_replace_spaces_with_underscores
// if both true THEN_SCREAMING_SNAKE_CASE_ALL_TEXT

#define DEFAULT_SEPARATOR KC_UNDS

enum x_case_state {
    X_CASE_DISABLED,
    AWAITING_SEPARATOR,
    X_CASE_ACTIVE,
};

static bool caps_word_enabled = false;
static uint8_t x_case_state = X_CASE_DISABLED;
static uint16_t separator = DEFAULT_SEPARATOR;

void enable_caps_word(void) {
    caps_word_enabled = true;
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void enable_x_case(void) {
    x_case_state = AWAITING_SEPARATOR;
}

void disable_x_case(void) {
    x_case_state = X_CASE_DISABLED;
    separator = DEFAULT_SEPARATOR;
}

bool is_x_case_enabled(void) {
    return x_case_state != X_CASE_DISABLED;
}

void enable_screaming_x_case(void) {
    enable_caps_word();
    enable_x_case();
}

bool is_caps_anything_enabled(void) {
    return caps_word_enabled || is_x_case_enabled();
}

void disable_caps_word(void) {
    caps_word_enabled = false;
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void disable_all(void) {
    disable_caps_word();
    disable_x_case();
}

void disable_caps_all(void) {
    disable_all();
}

bool is_awaiting_separator(void) {
    return x_case_state == AWAITING_SEPARATOR;
}

void resolve_separator(uint16_t keycode) {
    separator = keycode;
    x_case_state = X_CASE_ACTIVE;
}

void resolve_separator_default(void) {
    resolve_separator(DEFAULT_SEPARATOR);
}

void apply_separator(void) {
    tap_code16(separator);
}

bool process_caps_word(uint16_t keycode, keyrecord_t *record) {
    static bool last_press_was_space = false;

    /* Return value determines if processing the keycode should continue to core code.
     * This allows more customizability. */
    if (!caps_word_enabled && !is_x_case_enabled()) {
        return true;
    }

    if (!record->event.pressed) {
        return true;
    }

    // first strip of the mod taps and layer taps if needed
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0)
                return true;
            keycode = keycode & 0xFF;
    }

    // we end caps word on one of the following keypresses
    if (keycode == KC_SPC) {
        if (is_awaiting_separator()) {
            resolve_separator_default();
        }

        if (last_press_was_space) {
            last_press_was_space = false;
            disable_all();
            tap_code(KC_BSPC);
            return true;
        }

        apply_separator();
        last_press_was_space = true;
        return false;
    }

    last_press_was_space = false;

    switch (keycode) {
        case KC_DOT:
        case KC_COMM:
        case KC_TAB:
            if (is_awaiting_separator()) {
                resolve_separator(keycode);
                return false;
            }
        case KC_ESC:
        case KC_ENT:
            if (record->event.pressed) {
                disable_all();
            }
            return true;
        case KC_A ... KC_0:
            if (is_awaiting_separator()) {
                resolve_separator_default();
            }
            return true;
        default:
            if (is_awaiting_separator()) {
                resolve_separator(keycode);
                return false;
            }
    }

    return true;
}
