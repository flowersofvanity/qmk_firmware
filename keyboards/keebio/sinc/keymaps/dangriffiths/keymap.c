
#include QMK_KEYBOARD_H

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [_BASE] = LAYOUT_80_iso_with_macro(
        KC_ESC,                                     KC_ESC,             KC_F1,   KC_F2,   KC_F3,       KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,  KC_F12,  LGUI(KC_BSLS),   KC_MUTE,
        SCREEN_CAP,            COLOUR_PICKER,       KC_GRV,             KC_1,    KC_2,    KC_3,        KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, KC_HOME,
        ZOOM_MUTE,             ZOOM_VIDEO,          KC_TAB,             KC_Q,    KC_W,    KC_E,        KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC, KC_RBRC,                   KC_PGUP,
        ZOOM_SHARE,            ZOOM_END,            TT(_RAISE_BASE),    KC_A,    KC_S,    KC_D,        KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT, KC_BSLS, KC_ENT,           KC_PGDN,
        _______,               _______,             KC_LSFT,            KC_LSFT, KC_Z,    KC_X,        KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH, KC_RSFT, KC_UP,            KC_END,
        LCTL(LSFT(KC_LEFT)),   LCTL(LSFT(KC_RGHT)), KC_LCTL,            KC_LALT, KC_LGUI, KC_LGUI,     KC_SPC,  KC_SPC,           MO(1),   KC_SPC,  KC_RGUI, TO(_GAME), KC_RCTL, KC_LEFT, KC_DOWN,          KC_RGHT
      ),
      [_GAME] = LAYOUT_80_iso_with_macro(
        SWITCH_CHAR,                                _______,            _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______,         _______,
        LSFT(KC_R),            KC_F,                _______,            _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______,
        KC_F13,                KC_F14,              _______,            _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,   _______, _______,                   _______,
        KC_F15,                KC_F16,              TT(_RAISE_GAME),    _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______,
        KC_F17,                KC_F18,              _______,            _______, _______, _______,     _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,          _______,
        KC_F19,                KC_F20,              _______,            _______, _______, _______,     _______, _______,          _______, _______, _______, TO(_BASE), _______, _______, _______,          _______
      ),
      [_RAISE_BASE] = LAYOUT_80_iso_with_macro(
          _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CAPS, KC_MEDIA_PLAY_PAUSE,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
          RESET,   _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
        ),
        [_RAISE_GAME] = LAYOUT_80_iso_with_macro(
            _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, RESET
          ),
    };

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}



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

        break;
            }
        }
    return true;
};

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _GAME:
        rgblight_sethsv_noeeprom (HSV_RED);//red
        break;
    case _RAISE_BASE:
        rgblight_sethsv_noeeprom (HSV_CYAN);//cyan
        break;
    case _RAISE_GAME:
        rgblight_sethsv_noeeprom (HSV_CYAN);//cyan
        break;
    case _BASE:
        rgblight_sethsv_noeeprom (HSV_WHITE);//white
        break;
    default:
        rgblight_sethsv_noeeprom (HSV_WHITE);//white
        break;}
return state;
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
