#include QMK_KEYBOARD_H
#include "rgb_matrix_map.h"

#define _BASE 0
#define _GAME 1
#define _RAISE_BASE 2
#define _RAISE_GAME 3

 enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   SCREEN_CAP,
   COLOUR_PICKER,
   SWITCH_CHAR,
   ZOOM_MUTE,
   ZOOM_VIDEO,
   ZOOM_SHARE,
   ZOOM_END
 };

//tap dances
 enum {
     CAPS,
 };

 void caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LSFT);
    } else {
        register_code16(KC_CAPS);
    }
};

void caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LSFT);
    } else {
        unregister_code16(KC_CAPS);
    }
};

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [CAPS] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, caps_finished, caps_reset, 275),
};

//combos/chording
enum combos {
  ZX_CUT,
  XC_COPY,
  CV_PASTE
};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [ZX_CUT] = COMBO(zx_combo, LGUI(KC_X)),
  [XC_COPY] = COMBO(xc_combo, LGUI(KC_C)),
  [CV_PASTE] = COMBO(cv_combo, LGUI(KC_V))

};



//main map
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

                                    //      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
                                    //      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
                                    //      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
                                    //      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
                                    //      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
                                    //      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

        [_BASE] = LAYOUT(
            KC_ESC,             KC_F1,      KC_F2,          KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,           KC_F12,             LGUI(KC_BSLS),                  KC_MUTE,//
            KC_GRV,             KC_1,       KC_2,           KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,          KC_EQL,             KC_BSPC,                        SCREEN_CAP,//
            KC_TAB,             KC_Q,       KC_W,           KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,          KC_RBRC,                                            COLOUR_PICKER,//
            TT(_RAISE_BASE),    KC_A,       KC_S,           KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,          KC_BSLS,            KC_ENT,                         LCTL(LSFT(KC_LEFT)),//
            KC_LSFT,            KC_LSFT,    KC_Z,           KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,                              RSFT_T(KC_DOT),     KC_UP,      LCTL(LSFT(KC_RGHT)),//
            KC_LCTL,            KC_LALT,    KC_LGUI,                                            KC_SPC,                                         KC_RGUI,    TO(_GAME),        KC_RCTL,            KC_LEFT,            KC_DOWN,    KC_RGHT//
        ),
        [_GAME] = LAYOUT(
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,            KC_F16,                         KC_MUTE,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,            _______,                        SWITCH_CHAR,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,                                            KC_F13,//
            TT(_RAISE_GAME),    _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,            _______,                        KC_F14,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                              _______,            _______,    KC_F,//
            _______,            _______,    _______,                                            _______,                                        _______,    TO(_BASE),        _______,            _______,            _______,    _______//
        ),
        [_RAISE_BASE] = LAYOUT(
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          RESET,              KC_CAPS,                        KC_MEDIA_PLAY_PAUSE,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,            _______,                        ZOOM_MUTE,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,                                            ZOOM_VIDEO,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,          _______,            _______,                        ZOOM_SHARE,//
            _______,            _______,    _______,         _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,                              _______,            KC_HOME,    ZOOM_END,//
            _______,            _______,    _______,                                            _______,                                        _______,    _______,          _______,            KC_PGUP,            KC_END,     KC_PGDN//
        ),
        [_RAISE_GAME] = LAYOUT(
            RESET,              KC_F13,     KC_F14,          KC_F15,    KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,           KC_F24,             KC_CAPS,                        KC_MEDIA_PLAY_PAUSE,//
            XXXXXXX,            XXXXXXX,    XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,          XXXXXXX,            XXXXXXX,                        KC_F15,//
            XXXXXXX,            XXXXXXX,    XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,          XXXXXXX,                                            KC_F16,//
            _______,            XXXXXXX,    XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,          XXXXXXX,            XXXXXXX,                        KC_F17,//
            XXXXXXX,            XXXXXXX,    XXXXXXX,         XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                              XXXXXXX,            XXXXXXX,    LSFT(KC_R),//
            XXXXXXX,            XXXXXXX,    XXXXXXX,                                            XXXXXXX,                                        XXXXXXX,    XXXXXXX,          XXXXXXX,            XXXXXXX,            XXXXXXX,    XXXXXXX//
    ),
};

// RGB timeout elements
#define TIMEOUT_THRESHOLD_DEFAULT   20    // default timeout minutes
#define TIMEOUT_THRESHOLD_MAX       140  // upper limits (2 hours and 10 minutes -- no rgb indicators above this value)
static uint16_t timeout_timer = 0;
static uint16_t timeout_counter = 0;  //in minute intervals
static uint16_t timeout_threshold = TIMEOUT_THRESHOLD_DEFAULT;

void timeout_reset_timer(void) {
    timeout_timer = timer_read();
    timeout_counter = 0;
};

void timeout_update_threshold(bool increase) {
    if (increase && timeout_threshold < TIMEOUT_THRESHOLD_MAX) timeout_threshold++;
    if (!increase && timeout_threshold > 0) timeout_threshold--;
};

//encoder bits - use tap_code16 if it is shortcuts/mod etc
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(get_highest_layer(layer_state)) {
        case _RAISE_BASE: // change media tracks when on either RAISE layer
        case _RAISE_GAME:
            clockwise ? tap_code_delay(KC_MEDIA_NEXT_TRACK,10) : tap_code_delay(KC_MEDIA_PREV_TRACK,10);
            break;
        default: // change volume when on default layer
            clockwise ? tap_code_delay(KC_AUDIO_VOL_UP,10) : tap_code_delay(KC_AUDIO_VOL_DOWN,10);
            break;
    }
    return true;
};

static bool istoggled = false;//used for switching characters with eveo-preview

uint8_t mod_state;//shift delete variable

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    //shift delete
    mod_state = get_mods(); // store the current modifier state in the variable for later reference
    switch (keycode) {
    case KC_BSPC:
        {
        static bool delkey_registered; // variable that keeps track of the delete key status: registered or not?
        if (record->event.pressed) {

            if (mod_state & MOD_MASK_SHIFT) { // detect the activation of either shift keys
                del_mods(MOD_MASK_SHIFT); // first temporarily canceling both shifts so that shift isn't applied to the KC_DEL keycode
                register_code(KC_DEL);
                delkey_registered = true; // update the boolean variable to reflect the status of KC_DEL
                set_mods(mod_state); // reapplying modifier state so that the held shift key(s) still work even after having tapped the Backspace/Delete key.
                return false;
            }
        } else { // on release of KC_BSPC
            if (delkey_registered) { // in case KC_DEL is still being sent even after the release of KC_BSPC
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        return true; // let QMK process the KC_BSPC keycode as usual outside of shift
        break;
    //end shift delete
        case SCREEN_CAP:
           if (record->event.pressed) {
            tap_code16(LSFT(LGUI(KC_4)));
         }
         return false;
         break;

         case COLOUR_PICKER:
            if (record->event.pressed) {
            tap_code16(LSFT(LCTL(KC_C)));
          }
          return false;
          break;

        case SWITCH_CHAR:
         if (record->event.pressed) {
          istoggled ? tap_code(KC_F11) : tap_code16(LSFT(KC_F11));//ternary for switching
          istoggled = !istoggled;//flip variable
        }
        break;

        case ZOOM_MUTE:
           if (record->event.pressed) {
             SEND_STRING(SS_LSFT(SS_LGUI("A")));
         }
         return false;
         break;

        case ZOOM_VIDEO:
            if (record->event.pressed) {
              SEND_STRING(SS_LSFT(SS_LGUI("V")));
          }
         return false;
         break;

        case ZOOM_SHARE:
         if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_LGUI("S")));
        }
        return false;
         break;

        case ZOOM_END:
          if (record->event.pressed) {
            tap_code16(LGUI(KC_W));
        }
        return false;
        break;

        default:
        if (record->event.pressed) { //reset activity timer
            #ifdef RGB_MATRIX_ENABLE
                rgb_matrix_enable();
            #endif
            timeout_reset_timer();
        }
        break;
            }
        }
    return true;
};

void matrix_scan_user(void) {
    if (timeout_threshold > 0) {
        if (timer_elapsed(timeout_timer) >= 60000) { // 1 minute tick
            timeout_counter++;
            timeout_timer = timer_read();
        }
        #ifdef RGB_MATRIX_ENABLE
            if (timeout_threshold > 0 && timeout_counter >= timeout_threshold) {
                rgb_matrix_disable();
            }
        #endif
    } // timeout_threshold = 0 will disable timeout
};

void caps_lock_toggle(void) {
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        for (uint8_t i=0; i<sizeof(LED_SIDE_LEFT)/sizeof(LED_SIDE_LEFT[0]); i++) {
            rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_PURPLE);
            rgb_matrix_set_color(LED_CAPS, RGB_PURPLE);
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
// capslock side lights on left.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    caps_lock_toggle();
    switch(get_highest_layer(layer_state)){  // special handling per layer
    case _GAME:
        rgb_matrix_set_color_all(RGB_WHITE);

        for (uint8_t i=0; i<sizeof(LED_SIDE_LEFT)/sizeof(LED_SIDE_LEFT[0]); i++) {//left side
           rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_RED);
        }
        for (uint8_t i=0; i<sizeof(LED_SIDE_RIGHT)/sizeof(LED_SIDE_RIGHT[0]); i++) {//right side
           rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_RED);
        }

        rgb_matrix_set_color(LED_FN, RGB_RED); //FN key

        for (uint8_t i=0; i<sizeof(LED_LIST_SHORTCUTS)/sizeof(LED_LIST_SHORTCUTS[0]); i++) {//shortcut keys
           rgb_matrix_set_color(LED_LIST_SHORTCUTS[i], RGB_RED);
        }
        caps_lock_toggle();
        istoggled ? rgb_matrix_set_color(LED_DEL, RGB_RED) : rgb_matrix_set_color(LED_DEL, RGB_WHITE); //indicator LED for toggle
        break;
    case _RAISE_BASE:
        rgb_matrix_set_color_all(RGB_PURPLE);
        break;
    case _RAISE_GAME:
        rgb_matrix_set_color_all(RGB_CYAN);
        break;
    case _BASE:
        //for leviathan
        //rgb_matrix_set_color_all(RGB_LEVIATHAN);

        //for MT3 board
        rgb_matrix_set_color_all(RGB_CYAN);

        for (uint8_t i=0; i<sizeof(LED_SIDE_LEFT)/sizeof(LED_SIDE_LEFT[0]); i++) {//left side
           rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_WHITE);
        }
        for (uint8_t i=0; i<sizeof(LED_SIDE_RIGHT)/sizeof(LED_SIDE_RIGHT[0]); i++) {//right side
           rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_WHITE);
        }
        rgb_matrix_set_color(LED_FN, RGB_WHITE); //FN key

        for (uint8_t i=0; i<sizeof(LED_LIST_SHORTCUTS)/sizeof(LED_LIST_SHORTCUTS[0]); i++) {//shortcut keys
           rgb_matrix_set_color(LED_LIST_SHORTCUTS[i], RGB_WHITE);
        }
        caps_lock_toggle();
        break;
    default:
        break;
    }
}

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif

void keyboard_post_init_user(void) {
    timeout_timer = timer_read(); // set initial time for idle timeout
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_LEVIATHAN); // default startup colour
    #endif
}
