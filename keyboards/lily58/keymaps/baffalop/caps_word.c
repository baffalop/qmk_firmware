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
static bool caps_word_enabled = false;
static bool snake_case_enabled = false;

void enable_caps_word(void) {
    caps_word_enabled = true;
    if (!host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void enable_snake_case(void) {
    snake_case_enabled = true;
}

void enable_screaming_snake_case(void) {
    enable_caps_word();
    enable_snake_case();
}

bool is_caps_anything_enabled(void) {
    return caps_word_enabled || snake_case_enabled;
}

void disable_caps_word(void) {
    caps_word_enabled = false;
    if (host_keyboard_led_state().caps_lock) {
        tap_code(KC_CAPS);
    }
}

void toggle_caps_word(void) {
    caps_word_enabled ? disable_caps_word() : enable_caps_word();
}

void toggle_snake_case(void) {
    snake_case_enabled = !snake_case_enabled;
}

void toggle_screaming_snake_case(void) {
    toggle_caps_word();
    snake_case_enabled = !snake_case_enabled;
}

void disable_all(void) {
    disable_caps_word();
    snake_case_enabled = false;
}

void disable_caps_all(void) {
    disable_all();
}

bool process_caps_word(uint16_t keycode, keyrecord_t *record) {
    static bool last_press_was_space = false;

    /* Return value determines if processing the keycode should continue to core code.
     * This allows more customizability. */
    if(caps_word_enabled || snake_case_enabled) {
        // first strip of the mod taps and layer taps if needed
        switch (keycode) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                if (record->tap.count == 0)
                    return true;
                keycode = keycode & 0xFF;
        }

        // we end caps word on one of the following keypresses
        switch (keycode) {
            case KC_SPC:
                if (snake_case_enabled) {
                    // _ on space
                    if (record->event.pressed) {
                        if (!last_press_was_space) {
                            last_press_was_space = true;
                            register_code16(KC_UNDS);
                        } else {
                            last_press_was_space = false;
                            disable_all();
                            tap_code(KC_BSPC);
                            return true;
                        }
                    } else {
                        unregister_code16(KC_UNDS);
                    }
                    return false;
                } else { // disable snake casing
                    if (record->event.pressed) {
                        disable_all();
                    }
                    return true;
                }
            case KC_ESC:
            case KC_ENT:
            case KC_TAB:
            case KC_DOT:
            case KC_COMM:
                if (record->event.pressed) {
                    last_press_was_space = false;
                    disable_all();
                }
                return true;
            default:
                last_press_was_space = false;
        }
    }

    return true;
}
