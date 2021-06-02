#include QMK_KEYBOARD_H
#include "casemodes.h"

enum layer_number {
    _COLEMAK = 0,
    _QWERTY,
    _NUM,
    _NAV,
    _SYM,
    _FUNC,
};

enum custom_keycodes {
    SW_APP = SAFE_RANGE,
    SW_WIND,
    REPEAT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Base Layer: COLEMAK
 *
 * ,----------------------------------------.                              ,---------------------------------------.
 * | --- |   Q  |   W  |   C  |   P  |   B  |                              |   J  |   L  |   U  |   Y  |  /  |  -  |
 * |-----+------+------+------+------+------|                              |------+------+------+------+-----+-----|
 * | Tab |   A  |   R  |  S   |   T  |   G  |                              |   M  |   N  |   E  |   I  |  O  |  '  |
 * |-----+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+-----+-----|
 * | `   |   Z  |   X  |   F  |   D  |   V  | ---- | ---  |  | Del  | ---- |   K  |   H  | ,  < | . >  |  /  |  \  |
 * `-------------------+------+------+------+------+------|  |------+------+------+------+------+------------------'
 *                     | XXXX | Caps | Esc  |1-shot| Enter|  | Bksp | Space|Repeat|Qwerty| XXXX |
 *                     |      |      | Num  | shift| Sym  |  |      | Nav  |      |      |      |
 *                     `----------------------------------'  `----------------------------------'
 */

    [_COLEMAK] = LAYOUT(
        KC_ESC,     KC_Q,         KC_W,         KC_C,         KC_P,         KC_B,                                                                                 KC_J,   KC_L,         KC_U,         KC_Y,         KC_SLSH,      KC_MINS,
        KC_TAB,     LSFT_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LGUI_T(KC_T), KC_G,                                                                                 KC_M,   RGUI_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RSFT_T(KC_O), KC_QUOT,
        KC_GRV,     KC_Z,         KC_X,         KC_F,         KC_D,         KC_V,             XXXXXXX,       XXXXXXX,          KC_DEL,          XXXXXXX,          KC_K,   KC_H,         KC_COMM,      KC_DOT,       KC_SCLN,      KC_BSLS,
                                                XXXXXXX,      KC_CAPS,      LT(_NUM, KC_ESC), OSM(MOD_LSFT), LT(_SYM, KC_ENT), RSFT_T(KC_BSPC), LT(_NAV, KC_SPC), REPEAT, TG(_QWERTY),  XXXXXXX
    ),
                                         
    [_QWERTY] = LAYOUT(                  
        _______, KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,                                        KC_Y,    KC_U,         KC_I,         KC_O,         KC_P,            _______,
        _______, LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G,                                        KC_H,    RGUI_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RSFT_T(KC_SCLN), _______,
        _______, KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    _______, _______, _______, _______, KC_N,    KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,         _______,
                                             _______,      _______,      _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR,         KC_RCBR,        KC_PIPE,                                     A(KC_3), KC_4,    KC_5,    KC_6,  _______, _______,
      _______, KC_LSFT, KC_LALT, LCTL_T(KC_COMM), LGUI_T(KC_DOT), KC_PERC,                                     KC_MINS, KC_1,    KC_2,    KC_3,  KC_0,    KC_COLN,
      _______, KC_PERC, KC_DOT,  KC_COMM,         KC_MINS,        KC_TILD, _______, _______, _______, _______, KC_PLUS, KC_7,    KC_8,    KC_9,  KC_SLSH, _______,
                                                  _______,        _______, _______, _______, _______, _______, _______, KC_0,    KC_LBRC, KC_RBRC
    ),

     [_NAV] = LAYOUT(
       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______,  _______, _______,
       _______, _______, _______, _______, _______, _______,                                     KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______, _______,
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SW_WIND, _______, _______,  _______, _______,
                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
     ),

    [_SYM] = LAYOUT(
      _______, KC_3,     KC_2,    KC_0,    KC_1,    KC_0,                                        KC_CIRC, KC_LCBR, KC_ASTR, KC_RCBR, KC_BSLS, _______,
      _______, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_MINS, KC_LPRN, KC_PLUS, KC_RPRN, KC_EQL,  KC_PIPE,
      _______, KC_TILD,  KC_LT,   KC_GRV,  KC_GT,   _______, _______, _______, _______, _______, KC_AMPR, KC_LBRC, KC_UNDS, KC_RBRC, KC_SLSH, KC_BSLS,
                                  _______, _______, _______, SW_APP,  _______, _______, _______, _______, _______, _______
    ),

    [_FUNC] = LAYOUT(
        _______, _______,  KC_F4,   KC_F5,   KC_F6,   _______,                                    _______, KC_VOLD, KC_VOLU, _______, RGB_HUI, _______,
        _______, _______,  KC_F1,   KC_F2,   KC_F3,   _______,                                    KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, RGB_TOG, _______,
        _______, _______,  KC_F7,   KC_F8,   KC_F9,   _______, _______, _______,_______, _______, _______, KC_BRID, KC_BRIU, _______, RGB_VAI, _______,
                                    _______, _______, _______, _______, _______,_______, _______, _______, _______, _______
    )

//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),

};

// MACROS

bool app_switcher_active = false;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

            return true;    
            
        case REPEAT:
            if (record->event.pressed) {
                register_code16(last_keycode);
            } else {
                unregister_code16(last_keycode);
            }
            return false;

        default:
            if (record->event.pressed) {
                last_keycode = GET_TAP_KC(keycode);
            }
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (app_switcher_active && IS_LAYER_OFF_STATE(state, _NUM)) {
        app_switcher_active = false;
        unregister_code(KC_LGUI);
    }

    // Tri-state layer _FUNC(when both layers are enabled, the third layer is activated
    return update_tri_layer_state(state, _NAV, _SYM, _FUNC);
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif
