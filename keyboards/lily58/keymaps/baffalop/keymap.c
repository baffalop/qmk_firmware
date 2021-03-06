#include QMK_KEYBOARD_H
#include "casemodes.h"

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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return 165;
}

bool get_hold_on_other_keypress(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM(MOD_LSFT):
            return true;
    }

    switch (keycode & 0xFF) {
        case KC_ENT:
            return true;
    }

    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* COLEMAK
     * ,-----------------------------------------.                   ,--------------------------------------.
     * | 0  |   1  |   2  |   3  |   4  |   5  |                     |  6  |   7  |   8  |   9  |  0  |  =  |
     * |------+------+------+------+------+------|                   |-----+------+------+------+-----+-----|
     * | Tab |   Q  |   W  |   C  |   P  |   B  |                    |  J  |   L  |   U  |   Y  |  /  |  -  |
     * |-----+------+------+------+------+------|                    |-----+------+------+------+-----+-----|
     * | Esc |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|  M  |   N  |   E  |   I  |   O  |  ' |
     * |-----+------+------+------+------+------|   [   |    |    ]  |-----+------+------+------+------+----|
     * |  `  |   Z  |   X  |   F  |   D  |   V  |-------|    |-------|  K  |   H  |   ,  |   .  |   ;  |  \ |
     * `-----------------------------------------/       /     \      \-------------------------------------'
     *                   | Caps |  [   |  OS- | /Enter/ /       \Space/\  | BckSP/ |  DEL |QWERTY|
     *                   |      |      | SHIFT|/ SYM   /         \NAVNUM\ |  SHIFT |      |      |
     *                   `----------------------------'           '-------'----------------------'
     */

    [_COLEMAK] = LAYOUT(
        KC_0,       KC_1,         KC_2,         KC_3,         KC_4,         KC_5,                                                      KC_6,            KC_7,         KC_8,         KC_9,         KC_0,         KC_BSPC,
        KC_TAB,     KC_Q,         KC_W,         KC_C,         KC_P,         KC_B,                                                      KC_J,            KC_L,         KC_U,         KC_Y,         KC_SLSH,      KC_MINS,
        KC_ESC,     LSFT_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LGUI_T(KC_T), KC_G,                                                      KC_M,            RGUI_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), KC_QUOT,
        KC_GRV,     KC_Z,         KC_X,         KC_F,         KC_D,         KC_V,          KC_LBRC,               KC_RBRC,             KC_K,            KC_H,         KC_COMM,      KC_DOT,       KC_SCLN,      KC_BSLS,
                                                KC_CAPS,      KC_LBRC,      OSM(MOD_LSFT), LT(_SYMBOLS,  KC_ENT), LT(_NAVNUM, KC_SPC), RSFT_T(KC_BSPC), KC_DEL,       TG(_QWERTY)
    ),
                                         
    [_QWERTY] = LAYOUT(                  
        _______, _______,      _______,      _______,      _______,      _______,                   _______, _______,      _______,      _______,      _______,         _______,
        _______, KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                      KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            _______,
        _______, LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G,                      KC_H,    RGUI_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RSFT_T(KC_SCLN), _______,
        _______, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    _______, _______, KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         _______,
                                             _______,      _______, _______, _______, _______, _______,      _______,      _______
    ),

    [_NAVNUM] = LAYOUT(
        _______,                 _______,      _______,      _______,      _______,      _______,                   _______, _______,         _______,       _______,         _______,        _______,
        _______,                 KC_0,         KC_6,         KC_5,         KC_4,         A(KC_3),                   KC_6,    KC_7,            KC_8,          KC_9,            KC_9,           _______,
        _______,                 LSFT_T(KC_0), LALT_T(KC_2), LCTL_T(KC_3), LGUI_T(KC_1), KC_PERC,                   KC_LEFT, RGUI_T(KC_DOWN), RCTL_T(KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_EQL), KC_SLSH,
        _______,                 KC_0,         KC_7,         KC_8,         KC_9,         _______, _______, SW_WIND, KC_PLUS, KC_MINS,         _______,       _______,         KC_COLN,        _______,
                                                             _______,      _______,      _______, KC_0,    _______, _______, _______,         _______
    ),

    [_SYMBOLS] = LAYOUT(
        _______, _______,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_3,     KC_2,    KC_0,    KC_1,    KC_0,                      KC_CIRC, KC_LCBR, KC_ASTR, KC_RCBR, KC_BSLS, _______,
        _______, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_MINS, KC_LPRN, KC_PLUS, KC_RPRN, KC_EQL,  KC_PIPE,
        KC_GRV,  KC_TILD,  KC_LT,   KC_GRV,  KC_GT,   _______, SW_APP,  _______, KC_AMPR, KC_LBRC, KC_UNDS, KC_RBRC, KC_SLSH, KC_BSLS,
                                    _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
        _______, _______,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, _______,  KC_F4,   KC_F5,   KC_F6,   _______,                   _______, KC_VOLD, KC_VOLU, _______, RGB_HUI, _______,
        _______, _______,  KC_F1,   KC_F2,   KC_F3,   _______,                   KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, RGB_TOG, _______,
        _______, _______,  KC_F7,   KC_F8,   KC_F9,   _______, _______, _______, _______, KC_BRID, KC_BRIU, _______, RGB_VAI, _______,
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

// overriding function in casemodes.c
bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) { 
        case KC_A ... KC_Z: 
        case KC_1 ... KC_0: 
        case KC_SPC:
            return true; 
    } 
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // keylogger from lily58
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
    }

    bool case_modes_were_on = case_modes_enabled();

    if (!process_case_modes(keycode, record)) {
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
            if (!record->event.pressed) {
                return true;
            }

            // pressing OSS again cancels it
            if (get_oneshot_mods() & MOD_MASK_SHIFT) {
                clear_oneshot_mods();
                return false;
            }

            if (case_modes_were_on) {
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
