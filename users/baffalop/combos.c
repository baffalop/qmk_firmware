#include "casemodes.h"

// right hand combos
const uint16_t PROGMEM combo_comm_dot[]      = { KC_COMM,      KC_DOT,       COMBO_END };
const uint16_t PROGMEM combo_h_comm[]        = { KC_H,         KC_COMM,      COMBO_END };
const uint16_t PROGMEM combo_h_dot[]         = { KC_H,         KC_DOT,       COMBO_END };
const uint16_t PROGMEM combo_h_scln[]        = { KC_H,         KC_SCLN,      COMBO_END };
const uint16_t PROGMEM combo_comm_scln[]     = { KC_COMM,      KC_SCLN,      COMBO_END };
const uint16_t PROGMEM combo_dot_scln[]      = { KC_DOT,       KC_SCLN,      COMBO_END };
const uint16_t PROGMEM combo_h_comm_dot[]    = { KC_H,         KC_COMM,      KC_DOT,       COMBO_END };
const uint16_t PROGMEM combo_comm_dot_scln[] = { KC_COMM,      KC_DOT,       KC_SCLN,      COMBO_END };
const uint16_t PROGMEM combo_n_e[]           = { RGUI_T(KC_N), RCTL_T(KC_E), COMBO_END };
const uint16_t PROGMEM combo_e_i[]           = { RCTL_T(KC_E), RALT_T(KC_I), COMBO_END };
const uint16_t PROGMEM combo_n_e_i[]         = { RGUI_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), COMBO_END };
const uint16_t PROGMEM combo_e_i_o[]         = { RCTL_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_n_e_o[]         = { RGUI_T(KC_N), RCTL_T(KC_E), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_n_i_o[]         = { RGUI_T(KC_N), RALT_T(KC_I), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_i_o[]           = { RALT_T(KC_I), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_n_i[]           = { RGUI_T(KC_N), RALT_T(KC_I), COMBO_END };
const uint16_t PROGMEM combo_e_o[]           = { RCTL_T(KC_E), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_n_o[]           = { RGUI_T(KC_N), RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_n_u[]           = { RGUI_T(KC_N), KC_U,         COMBO_END };
const uint16_t PROGMEM combo_u_i[]           = { KC_U,         RALT_T(KC_I), COMBO_END };
const uint16_t PROGMEM combo_n_u_i[]         = { RGUI_T(KC_N), KC_U,         RALT_T(KC_I), COMBO_END };
const uint16_t PROGMEM combo_h_e[]           = { KC_H,         RCTL_T(KC_E), COMBO_END };
const uint16_t PROGMEM combo_e_dot[]         = { RCTL_T(KC_E), KC_DOT,       COMBO_END };
const uint16_t PROGMEM combo_l_u[]           = { KC_L,         KC_U,         COMBO_END };
const uint16_t PROGMEM combo_l_y[]           = { KC_L,         KC_Y,         COMBO_END };
const uint16_t PROGMEM combo_u_y[]           = { KC_U,         KC_Y,         COMBO_END };
const uint16_t PROGMEM combo_l_u_y[]         = { KC_L,         KC_U,         KC_Y,         COMBO_END };
const uint16_t PROGMEM combo_u_o[]           = { KC_U,         RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_l_o[]           = { KC_L,         RSFT_T(KC_O), COMBO_END };
const uint16_t PROGMEM combo_u_slsh[]        = { KC_U,         KC_SLSH, COMBO_END };
const uint16_t PROGMEM combo_l_slsh[]        = { KC_L,         KC_SLSH, COMBO_END };
const uint16_t PROGMEM combo_j_l[]           = { KC_J,         KC_L,         COMBO_END };
const uint16_t PROGMEM combo_j_u[]           = { KC_J,         KC_U,         COMBO_END };
const uint16_t PROGMEM combo_j_y[]           = { KC_J,         KC_Y,         COMBO_END };
const uint16_t PROGMEM combo_j_l_u[]         = { KC_J,         KC_L,         KC_U,         COMBO_END };

// left hand combos
const uint16_t PROGMEM combo_x_f[]   = { KC_X,         KC_F,         COMBO_END };
const uint16_t PROGMEM combo_a_r[]   = { LSFT_T(KC_A), LALT_T(KC_R), COMBO_END };
const uint16_t PROGMEM combo_a_s[]   = { LSFT_T(KC_A), LCTL_T(KC_S), COMBO_END };
const uint16_t PROGMEM combo_r_s[]   = { LALT_T(KC_R), LCTL_T(KC_S), COMBO_END };
const uint16_t PROGMEM combo_s_t[]   = { LCTL_T(KC_S), LGUI_T(KC_T), COMBO_END };
const uint16_t PROGMEM combo_a_t[]   = { LSFT_T(KC_A), LGUI_T(KC_T), COMBO_END };
const uint16_t PROGMEM combo_r_t[]   = { LALT_T(KC_R), LGUI_T(KC_T), COMBO_END };
const uint16_t PROGMEM combo_s_d[]   = { LCTL_T(KC_S), KC_D,         COMBO_END };
const uint16_t PROGMEM combo_c_p[]   = { KC_C,         KC_P,         COMBO_END };
const uint16_t PROGMEM combo_w_t[]   = { KC_W,         KC_T,         COMBO_END };
const uint16_t PROGMEM combo_w_c[]   = { KC_W,         KC_C,         COMBO_END };
const uint16_t PROGMEM combo_w_p[]   = { KC_W,         KC_P,         COMBO_END };
const uint16_t PROGMEM combo_w_c_p[] = { KC_W,         KC_C,         KC_P, COMBO_END };

enum combo_actions {
    COMBO_ACTION_CAPS,
    COMBO_ACTION_CAPS_XCASE,
    COMBO_ACTION_XCASE,
    COMBO_ACTION_CAMELCASE,
};

combo_t key_combos[COMBO_COUNT] = {
    // actions
    [COMBO_ACTION_CAPS] = COMBO_ACTION(combo_n_e_i),
    [COMBO_ACTION_CAPS_XCASE] = COMBO_ACTION(combo_n_i_o),
    [COMBO_ACTION_XCASE] = COMBO_ACTION(combo_e_i_o),
    [COMBO_ACTION_CAMELCASE] = COMBO_ACTION(combo_n_e_o),
    // right hand combos
    COMBO(combo_comm_dot, KC_QUES),
    COMBO(combo_h_comm, KC_UNDS),
    COMBO(combo_h_comm_dot, KC_PLUS),
    COMBO(combo_comm_dot_scln, KC_PIPE),
    COMBO(combo_n_e, KC_MINS),
    COMBO(combo_e_i, KC_DQT),
    COMBO(combo_h_scln, KC_EQL),
    COMBO(combo_n_u, KC_SLSH),
    COMBO(combo_u_i, KC_BSLS),
    COMBO(combo_n_u_i, KC_CIRC),
    COMBO(combo_h_dot, KC_LBRC),
    COMBO(combo_comm_scln, KC_RBRC),
    COMBO(combo_u_y, KC_0),
    COMBO(combo_l_u, KC_1),
    COMBO(combo_l_y, KC_2),
    COMBO(combo_l_u_y, KC_3),
    COMBO(combo_u_slsh, KC_9),
    COMBO(combo_l_slsh, KC_4),
    COMBO(combo_j_l, KC_5),
    COMBO(combo_j_u, KC_6),
    COMBO(combo_j_y, KC_7),
    COMBO(combo_j_l_u, KC_8),
    // left hand combos
    COMBO(combo_x_f, KC_GRV),
    COMBO(combo_r_s, KC_AT),
    COMBO(combo_s_t, KC_DLR),
    COMBO(combo_a_t, KC_EXLM),
    COMBO(combo_r_t, KC_HASH),
    COMBO(combo_s_d, KC_PERC),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        return;
    }

    switch (combo_index) {
        case COMBO_ACTION_CAPS:
            enable_caps_word();
            break;
        case COMBO_ACTION_CAPS_XCASE:
            enable_caps_word();
            enable_xcase();
            break;
        case COMBO_ACTION_XCASE:
            enable_xcase();
            break;
        case COMBO_ACTION_CAMELCASE:
            enable_xcase_with(OSM(MOD_LSFT));
            break;
    }
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // If you want *all* combos, that have Mod-Tap/Layer-Tap/Momentary keys in its chord, to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;
}
