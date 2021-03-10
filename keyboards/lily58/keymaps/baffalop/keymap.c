#include QMK_KEYBOARD_H

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
     *                   | Lang |  [   |  OS- | /Enter/ /       \Space/\  |BckSP/|  ]   |QWERTY|
     *                   |      |      | SHIFT|/ SYM   /         \NAVNUM\ | Shift|      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_COLEMAK] = LAYOUT(
        KC_0,    KC_1,         KC_2,         KC_3,         KC_4,          KC_5,                             KC_6,    KC_7,            KC_8,         KC_9,         KC_0,         KC_BSPC,
        KC_TAB,  KC_Q,         KC_W,         KC_C,         KC_P,          KC_B,                             KC_J,    KC_L,            KC_U,         KC_Y,         KC_SLSH,      KC_MINS,
        KC_ESC,  LSFT_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LGUI_T(KC_T),  KC_G,                             KC_M,    RGUI_T(KC_N),    RCTL_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), KC_QUOT,
        KC_LBRC, KC_Z,         KC_X,         KC_F,         KC_D,          KC_V,        KC_LBRC, KC_RBRC,    KC_K,    KC_H,            KC_COMM,      KC_DOT,       KC_SCLN,      KC_RBRC,
                               KC_CAPS,      KC_LBRC,      OSM(MOD_LSFT), LT(_SYMBOLS, KC_ENT), LT(_NAVNUM, KC_SPC), RSFT_T(KC_BSPC), KC_RBRC,      TG(_COLEMAK)
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
        _______, KC_0,         KC_7,         KC_8,         KC_9,         _______, _______, _______, _______, KC_MINS,         KC_UNDS,       KC_PLUS,         KC_SLSH,        _______,
                                             _______,      _______,      _______, _______, _______, _______, _______,         _______
    ),

    [_SYMBOLS] = LAYOUT(
        _______, _______,  _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        _______, KC_3,     KC_2,    KC_0,    KC_1,    KC_0,                      KC_CIRC, KC_LCBR, KC_ASTR, KC_RCBR, _______, _______,
        _______, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_MINS, KC_LPRN, KC_PLUS, KC_RPRN, KC_EQL,  KC_BSLS,
        KC_GRV,  KC_TILD,  KC_LT,   KC_GRV,  KC_GT,   _______, _______, _______, KC_AMPR, KC_LBRC, KC_UNDS, KC_RBRC, KC_PIPE, _______,
                                    _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* FUNC
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_FUNCTION] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_F1, KC_F2, KC_F3, _______, _______, KC_VOLU, KC_BRIU, _______, _______, _______,
        _______, _______, KC_F4, KC_F5, KC_F6, _______, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
        _______, _______, KC_F7, KC_F8, KC_F9, _______, _______, KC_VOLD, KC_BRID, _______, _______, _______, _______, _______,
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

// Tri-state layer _FUNCTION - this seems to break everything
// layer_state_t layer_state_set_user(layer_state_t state) {
//    return update_tri_layer_state(state, _NAVNUM, _SYMBOLS, _FUNCTION);
// }

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }
    return true;
}
