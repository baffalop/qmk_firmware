#include "quantum.h"
#include "process_keycode/process_tap_dance.h"
#include "caps_word.h"

// Only activate the tap dance when oneshot shift is activated
// RAW_TAP is for any taps when OSS is not active - to be handled as RSFT_T(KC_BSPC)
enum tap_state {
    RAW_HOLD = 1,
    RAW_TAP,
    SINGLE_TAP,
    DOUBLE_TAP,
};

static uint8_t tap_state = 0;

bool is_lshift_on(void) {
    return get_mods() & MOD_BIT(KC_LSFT)
        || get_oneshot_mods() & MOD_BIT(KC_LSFT);
}

uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (!is_lshift_on()) {
        if (!state->interrupted && state->pressed)
            return RAW_HOLD;
        else
            return RAW_TAP;
    }

    switch (state->count) {
        case 1: return SINGLE_TAP;
        case 2: return DOUBLE_TAP;
    }

    return DOUBLE_TAP;
}

void td_capsw_bspc_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (cur_dance(state)) {
        case RAW_HOLD:
            /* register_mods(MOD_BIT(KC_RSFT)); */
            tap_code(KC_BSPC);
            break;
        case RAW_TAP:
            tap_code(KC_BSPC);
            break;
    }
}

void td_capsw_bspc_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state = cur_dance(state);
    switch (tap_state) {
        case RAW_HOLD:
            register_mods(MOD_BIT(KC_RSFT));
            break;
        case SINGLE_TAP:
            enable_screaming_x_case();
            clear_oneshot_mods();
            break;
        case DOUBLE_TAP:
            enable_x_case();
            clear_oneshot_mods();
            break;
    }
}

void td_capsw_bspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state) {
        case RAW_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT));
    }
    tap_state = 0;
}
