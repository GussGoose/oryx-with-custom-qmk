#include QMK_KEYBOARD_H
#include "version.h"

#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    KC_ESCAPE,      KC_1,                   KC_2,                   KC_3,                   KC_4,                   KC_5,                                           KC_6,                   KC_7,                   KC_8,                   KC_9,                   KC_0,                   KC_NO,
    KC_TAB,         KC_Q,                   KC_W,                   KC_E,                   KC_R,                   KC_T,                                           KC_Y,                   KC_U,                   KC_I,                   KC_O,                   KC_P,                   KC_NO,
    KC_GRAVE,       KC_A,                   MT(MOD_LSFT, KC_S),     MT(MOD_LALT, KC_D),     MT(MOD_LGUI, KC_F),     ALL_T(KC_G),                                    ALL_T(KC_H),            MT(MOD_LGUI, KC_J),     MT(MOD_LALT, KC_K),     MT(MOD_LSFT, KC_L),     KC_SCLN,                KC_QUOTE,
    KC_LEFT_CTRL,   KC_Z,                   KC_X,                   KC_C,                   KC_V,                   KC_B,                                           KC_N,                   KC_M,                   KC_COMMA,               KC_DOT,                 KC_SLASH,               KC_LEFT_CTRL,
                                                            LT(1, KC_BSPC),          MT(MOD_LGUI, KC_ENTER),                                OSM(MOD_LSFT),          LT(2, KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_NO,          KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                                          KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,
    KC_NO,          LGUI(LSFT(KC_4)),       LCTL(LSFT(KC_TAB)),     KC_UP,                  LCTL(KC_TAB),           KC_NO,                                          KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,
    KC_NO,          LGUI(LSFT(KC_5)),       KC_LEFT,                KC_DOWN,                KC_RIGHT,               KC_NO,                                          KC_NO,                  KC_LEFT_GUI,            KC_LEFT_ALT,            KC_LEFT_SHIFT,          KC_NO,                  KC_NO,
    KC_NO,          KC_NO,                  LALT(LGUI(LCTL(LSFT(KC_LBRC)))), LALT(LGUI(LCTL(LSFT(KC_RBRC)))), LGUI(KC_SPACE), KC_F20,                    KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,
                                                            KC_TRANSPARENT,           KC_TRANSPARENT,                                   KC_TRANSPARENT,         KC_TRANSPARENT
  ),
  [2] = LAYOUT_voyager(
    KC_NO,          KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                                          KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,                  KC_NO,
    KC_NO,          KC_NO,                  KC_AUDIO_VOL_DOWN,      KC_AUDIO_MUTE,          KC_AUDIO_VOL_UP,        RM_VALU,                                        KC_EQUAL,               KC_LBRC,                KC_RBRC,                KC_BSLS,                KC_NO,                  KC_NO,
    KC_NO,          KC_NO,                  KC_MEDIA_PREV_TRACK,    KC_MEDIA_PLAY_PAUSE,    KC_MEDIA_NEXT_TRACK,    RM_VALD,                                        KC_PLUS,                KC_LPRN,                KC_RPRN,                KC_PIPE,                KC_NO,                  KC_NO,
    KC_NO,          KC_NO,                  KC_F14,                 KC_NO,                  KC_F15,                 KC_NO,                                          KC_MINUS,               KC_LCBR,                KC_RCBR,                KC_UNDS,                KC_NO,                  KC_NO,
                                                            KC_TRANSPARENT,           KC_TRANSPARENT,                                   KC_TRANSPARENT,         KC_TRANSPARENT
  ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'R', 'R', 'R', 'R', 'R', 'R',
  '*', '*', '*', '*'
);

extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb(hsv);
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
  [0] = {
    {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}
  },
  [1] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,0,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,0,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}
  },
  [2] = {
    {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,255,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,255,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,255}, {0,0,0}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}, {0,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,255,255}, {0,255,255}
  },
};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
      rgb_matrix_set_color(i, 0, 0, 0);
    } else {
      RGB rgb = hsv_to_rgb_with_value(hsv);
      rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    default:
      if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        rgb_matrix_set_color_all(0, 0, 0);
      }
      break;
  }

  return true;
}

static bool is_home_row_mod(uint16_t keycode) {
  switch (keycode) {
    case MT(MOD_LSFT, KC_S):
    case MT(MOD_LALT, KC_D):
    case MT(MOD_LGUI, KC_F):
    case ALL_T(KC_G):
    case ALL_T(KC_H):
    case MT(MOD_LGUI, KC_J):
    case MT(MOD_LALT, KC_K):
    case MT(MOD_LSFT, KC_L):
      return true;
    default:
      return false;
  }
}

static bool is_thumb_tap_hold(uint16_t keycode) {
  switch (keycode) {
    case LT(1, KC_BSPC):
    case MT(MOD_LGUI, KC_ENTER):
    case LT(2, KC_SPACE):
      return true;
    default:
      return false;
  }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  return is_thumb_tap_hold(keycode);
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  if (is_thumb_tap_hold(keycode)) {
    return 0;
  }

  if (is_home_row_mod(keycode)) {
    return FLOW_TAP_TERM;
  }

  return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QK_MODS ... QK_MODS_MAX:
      if (IS_CONSUMER_KEYCODE(QK_MODS_GET_BASIC_KEYCODE(keycode))) {
        if (record->event.pressed) {
          add_mods(QK_MODS_GET_MODS(keycode));
          send_keyboard_report();
          wait_ms(2);
          register_code(QK_MODS_GET_BASIC_KEYCODE(keycode));
          return false;
        } else {
          wait_ms(2);
          del_mods(QK_MODS_GET_MODS(keycode));
        }
      }
      break;

    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}
