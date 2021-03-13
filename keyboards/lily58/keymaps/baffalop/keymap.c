#include QMK_KEYBOARD_H
#include "caps_word.h"
#include "tap_dance_capsw_bspc.h"

#ifdef PROTOCOL_LUFA
#    include "lufa.h"
#    include "split_util.h"
#endif
#ifdef SSD1306OLED
#    include "ssd1306.h"
#endif

extern uint8_t is_master;


enum layer_number {
    _COLEMAK = 0,
    _QWERTY,
    _NAVNUM,
    _SYMBOLS,
    _FUNCTION,
};

enum custom_keycodes {
    SW_APP = SAFE_RANGE,
    SW_WIND,
};

enum tap_dance_codes {
    TD_CAPSW_BSPC,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CAPSW_BSPC] = ACTION_TAP_DANCE_FN_ADVANCED(td_capsw_bspc_each, td_capsw_bspc_finished, NULL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* COLEMAK
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | 0  |   1  |   2  |   3  |   4  |   5  |                      |  6  |   7  |   8  |   9  |   0  |  =   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab |   Q  |   W  |   C  |   P  |   B  |                     |   J  |   L  |   U  |   Y  |   /  |  -   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  '   |
     * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
     * |  [  |   Z  |   X  |   F  |   D  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   ;  |  ]   |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | Lang |  [   |  OS- | /Enter/ /       \Space/\  |BckSP/        |  DEL |QWERTY|
     *                   |      |      | SHIFT|/ SYM   /         \NAVNUM\ |tap dance caps|      |      |
     *                   `----------------------------'           '------''---------------------'
     */

    [_COLEMAK] = LAYOUT(
        KC_0,    KC_1,         KC_2,         KC_3,         KC_4,           KC_5,                             KC_6,    KC_7,             KC_8,         KC_9,         KC_0,         KC_BSPC,
        KC_TAB,  KC_Q,         KC_W,         KC_C,         KC_P,           KC_B,                             KC_J,    KC_L,             KC_U,         KC_Y,         KC_SLSH,      KC_MINS,
        KC_ESC,  LSFT_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LGUI_T(KC_T),   KC_G,                             KC_M,    RGUI_T(KC_N),     RCTL_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), KC_QUOT,
        KC_LBRC, KC_Z,         KC_X,         KC_F,         KC_D,           KC_V,        KC_LBRC, KC_RBRC,    KC_K,    KC_H,             KC_COMM,      KC_DOT,       KC_SCLN,      KC_RBRC,
                               KC_CAPS,      KC_LBRC,      OSM(MOD_LSFT),  LT(_SYMBOLS, KC_ENT), LT(_NAVNUM, KC_SPC), TD(TD_CAPSW_BSPC), KC_DEL,       TG(_QWERTY)
    ),

    [_QWERTY] = LAYOUT(
        _______, _______,      _______,      _______,      _______,      _______,                   _______, _______,      _______,      _______,      _______,         _______,
        _______, KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                      KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            _______,
        _______, LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G,                      KC_H,    RGUI_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RSFT_T(KC_SCLN), _______,
        _______, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    _______, _______, KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         _______,
                                             _______,      _______, _______, _______, _______, _______,      _______,      _______
    ),

    [_NAVNUM] = LAYOUT(
        _______, _______,      _______,      _______,      _______,      _______,                   _______, _______,         _______,       _______,         _______,        _______,
        _______, KC_0,         KC_4,         KC_3,         KC_5,         KC_5,                      KC_LBRC, KC_LCBR,         KC_0,          KC_RCBR,         KC_RBRC,        _______,
        _______, LSFT_T(KC_6), LALT_T(KC_1), LCTL_T(KC_2), LGUI_T(KC_0), KC_6,                      KC_LEFT, RGUI_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_EQL), KC_UNDS,
        _______, KC_0,         KC_7,         KC_8,         KC_9,         _______, _______, SW_WIND, _______, KC_MINS,         KC_UNDS,       KC_PLUS,         KC_SLSH,        _______,
                                             _______,      _______,      _______, _______, _______, _______, _______,         _______
    ),

    [_SYMBOLS] = LAYOUT(
        _______, _______,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_3,     KC_2,    KC_0,    KC_1,    KC_0,                      KC_CIRC, KC_LCBR, KC_ASTR, KC_RCBR, _______, _______,
        _______, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_MINS, KC_LPRN, KC_PLUS, KC_RPRN, KC_EQL,  KC_BSLS,
        KC_GRV,  KC_TILD,  KC_LT,   KC_GRV,  KC_GT,   _______, SW_APP,  _______, KC_AMPR, KC_LBRC, KC_UNDS, KC_RBRC, KC_PIPE, _______,
                                    _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        _______, _______,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______,  KC_F1,   KC_F2,   KC_F3,   _______,                   _______, KC_VOLD, KC_VOLU, _______, _______, _______,
        _______, _______,  KC_F4,   KC_F5,   KC_F6,   _______,                   KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______,  KC_F7,   KC_F8,   KC_F9,   _______, _______, _______, _______, KC_BRID, KC_BRIU, _______, _______, _______,
                                    _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

// SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write_ln(read_layer_state(), false);
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
        // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        // oled_write_ln(read_host_led_state(), false);
        // oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
}
#endif  // OLED_DRIVER_ENABLE

// MACROS

bool app_switcher_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // keylogger from lily58
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
    }

    if (!process_caps_word(keycode, record)) {
        return false;
    }

    switch (keycode) {
        // app and window switcher macros
        case SW_APP:
            if (!record->event.pressed) {
                return false;
            }

            if (!app_switcher_active) {
                app_switcher_active = true;
                register_code(KC_LGUI); // to be unregistered on layer change
            }
            tap_code(KC_TAB);

            return false;

        case SW_WIND:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_GRV));
            }
            return false;

        case OSM(MOD_LSFT):
            if (is_caps_anything_enabled()) {
                disable_caps_all();
                return false;
            }
            
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (app_switcher_active && IS_LAYER_OFF_STATE(state, _SYMBOLS)) {
        app_switcher_active = false;
        unregister_code(KC_LGUI);
    }

    // Tri-state layer _FUNCTION (when both layers are enabled, the third layer is activated
    return update_tri_layer_state(state, _NAVNUM, _SYMBOLS, _FUNCTION);
}
