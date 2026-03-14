#pragma once

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
    case F16:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_TAB);
      } else {
        unregister_code(KC_LGUI);
      }
      return false;

    case F17:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_TAB);
      } else {
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      }
      return false;

    case F18:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_GRV);
      } else {
        unregister_code(KC_LGUI);
      }
      return false;

    case F19:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_GRV);
      } else {
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      }
      return false;
  }

  return true;
}
