#include "quantum.h"
#include "process_keycode/process_tap_dance.h"
#include "caps_word.h"

// Only activate the tap dance when oneshot shift is activated
// RAW_TAP is for any taps when OSS is not active - to be handled as RSFT_T(KC_BSPC)
enum tap_state {
    RAW_TAP = 1,
    SINGLE_HOLD,
    SINGLE_TAP,
    DOUBLE_TAP,
    TRIPLE_TAP,
};

bool is_lshift_on(void) {
    return get_mods() & MOD_BIT(KC_LSFT)
        || get_oneshot_mods() & MOD_BIT(KC_LSFT);
}

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (!is_lshift_on()) {
        return RAW_TAP;
    }

    if (state->count == 1) {
        if (state->pressed)
            return SINGLE_HOLD;
        else {
            return SINGLE_TAP;
        }
    } else {
        switch (state->count) {
            case 2: return DOUBLE_TAP;
            case 3: return TRIPLE_TAP;
        }
    }

    return TRIPLE_TAP;
}

void td_capsw_bspc_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        // ensure shift is registered immediately on first keydown, then unregistered when necessary
        case RAW_HOLD:
            tap_code(KC_BSPC);
            break;
    }
}

void td_capsw_bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case SINGLE_TAP:
            enable_caps_word();
            clear_oneshot_mods();
            break;
        case DOUBLE_TAP:
            enable_snake_case();
            clear_oneshot_mods();
            break;
        case TRIPLE_TAP:
            enable_screaming_snake_case();
            clear_oneshot_mods();
            break;
    }
}

void td_capsw_bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    unregister_code16(KC_RSFT);
}
