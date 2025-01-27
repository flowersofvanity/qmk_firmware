/*
Copyright 2021 0xCB - Conor Burns

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include <stdio.h>

enum layer_names {
  _HOME,
  _EVE,
  _RGB,
  _BLED
};

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
[_HOME] = LAYOUT(
    KC_MPRV, KC_MNXT, KC_MPLY,
    KC_PGUP, KC_PGDN, TO(3),
    KC_HOME, KC_END,  TO(1)
),
[_EVE] = LAYOUT(
    SWITCH_CHAR, KC_F15, TO(0),
    KC_F13, KC_F16, LSFT(KC_R),
    KC_F14, _______, KC_F
),
[_RGB] = LAYOUT(
    RGB_HUI, RGB_HUD, RGB_MOD,
    RGB_SAI, RGB_SAD, TO(1),
    RGB_SPI, RGB_SPD, TO(3)
),
[_BLED] = LAYOUT(
    BL_STEP, BL_BRTG, BL_TOGG,
    BL_ON,   BL_OFF,  TO(2),
    BL_INC,  BL_DEC,  TO(0)
)
};


/* rotary encoder (SW3) - add more else if blocks for more granular layer control */
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(_RGB)) {
        #ifdef RGBLIGHT_ENABLE
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
        #endif
    } else if (IS_LAYER_ON(_BLED)) {
        if (clockwise) {
            backlight_increase();
        } else {
            backlight_decrease();
        }
        } else if (IS_LAYER_ON(_EVE)) {
        if (clockwise) {
            layer_move(2);

        } else {
           layer_move(0);
        }
    } else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}
#endif

//new stuff

static bool istoggled = false;//used for switching characters with eveo-preview


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

//shift delete
switch (keycode) {
    case SCREEN_CAP:
       if (record->event.pressed) {
        tap_code16(LSFT(LGUI(KC_4)));
     }
     return false;
     break;

     case COLOUR_PICKER:
        if (record->event.pressed) {
         tap_code16(LSFT(LALT(KC_C)));
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
return true;
};


/* oled stuff :) */
#ifdef OLED_DRIVER_ENABLE
uint16_t startup_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  0,  0,  1,  2,  4,  2,  1,  1,  1,  1,  1,  1,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  1,  1,  1,  1,  1,  1,  2,  4,  2,  1,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  5,248,  5,  2,  0,  0,  0,  0,  0,  0,128,192,192,224,224,112,120, 56, 63, 28, 14, 14, 14,254, 14, 14, 30, 28, 63, 56,120,112,224,224,192,128,  0,  0,  0,  0,  0,  0,  0,  2,  5,248,  5,  2,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,160, 19,162, 66, 66, 66, 66, 66, 66, 66,255,255,255,  0,  0,  0,252,254,254,192,192,192,192,255,  0,  0,  0, 62, 62, 60, 60,  0,  0,  1,255,255,255, 66, 66, 66, 66, 66, 66, 66,162, 19,160, 64,  0,
        0,  0,  0,128, 64, 64, 64,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192, 64, 64,192,128,  0,  0,192, 64, 64,192,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192, 64,192,  0,  0,  0,  0,  0,128,192, 64, 64,192,128,  0,  0,128,192, 64, 64,192,128,  0,  0, 64, 64, 64, 64, 64,192,  0,  0,  0,  0,  0,249,  8,  8,  8,  8,  8,  8,  8,  8,127,255,255,192,128,128, 15, 31, 31,  1,  1,  1,  1,255,  0,  0,  0, 30, 30, 14, 14,128,192,192,255,255,127,  8,  8,  8,  8,  8,  8,  8,  8,249,  0,  0,  0,
        0,  0, 31, 49, 64, 78, 64, 49, 31,  0,  0, 97, 22,  8, 22, 97,  0,  0, 31, 49, 96, 64, 64, 96, 32,  0,  0,127, 68, 68,100, 59,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 64,127, 64, 64,  0,  0,  0, 32,100, 68, 68,110, 59,  0,  0, 32,100, 68, 68,110, 59,  0,  0,  0,  0,  0,126,  3,  1,  0,  0,  0,  8, 20, 35, 20,  8,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7,  7, 15,254, 30, 28, 28, 28,255, 28, 28, 28, 30,254, 15,  7,  3,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  4, 10, 17, 10,  4,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16, 40, 68, 40, 16, 16, 16, 16, 16, 16, 31,  0,  0, 16, 40, 71, 40, 16,  0,  0, 31, 16, 16, 16, 16, 16, 16, 40, 68, 40, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}
static void render_logo_font(void) {
    static const char PROGMEM qmk_logo[] = {
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xCB, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0xCB, 0xCB, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9,
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xCB, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xCB, 0xCB, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9,
        0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xCB, 0x88, 0x89, 0x8A, 0x8B, 0x8A, 0x8B, 0x8C, 0x8D, 0xCB, 0xCB, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5,
        0xEC, 0xED, 0xEE, 0xEF, 0xF0, 0xCB, 0xA8, 0xA9, 0xAA, 0xAB, 0xAA, 0xAB, 0xAC, 0xAD, 0xCB, 0xCB, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0x00
    };

    oled_write_P(qmk_logo, false);
}
/* Shows the name of the current layer and locks for the host (CAPS etc.) */
static void render_info(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _HOME:
            oled_write_ln_P(PSTR("Home"), false);
            break;
        case _EVE:
            oled_write_ln_P(PSTR("Eve"), false);
            break;
        case _RGB:
            oled_write_ln_P(PSTR("RGB"), false);
            break;
        case _BLED:
            oled_write_ln_P(PSTR("Backlight"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    //oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_write_ln_P(istoggled ? PSTR("Char 2 ") : PSTR("Char 1 "), false);

}
static void render_rgbled_status(bool full) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_is_enabled() && get_highest_layer(layer_state) == _RGB) {
      if (full) {
          snprintf(buf, sizeof(buf), "RGB mode %2d: %d,%d,%d  \n",
                   rgblight_get_mode(),
                   rgblight_get_hue()/RGBLIGHT_HUE_STEP,
                   rgblight_get_sat()/RGBLIGHT_SAT_STEP,
                   rgblight_get_val()/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
      }
      oled_write(buf, false);
  } else {
      oled_write_ln_P(PSTR("\n"), false);
  }
#endif
}
void oled_task_user(void) {
    static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 1000)) {
        render_logo();
    } else {
        if (!finished_timer) {
            oled_clear();
            finished_timer = true;
        }
        render_info();
        render_rgbled_status(true);
        render_logo_font();
    }
}
#endif
