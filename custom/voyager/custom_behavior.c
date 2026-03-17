#pragma once

static bool is_hold_capable_key(uint16_t keycode) {
  return
    (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
    (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);
}

static bool is_target_home_row_hold_key(uint16_t keycode) {
  if (!is_hold_capable_key(keycode)) {
    return false;
  }

  switch (get_tap_keycode(keycode)) {
    case KC_A:
    case KC_S:
    case KC_D:
    case KC_F:
    case KC_G:
    case KC_H:
    case KC_J:
    case KC_K:
    case KC_L:
    case KC_SCLN:
      return true;
    default:
      return false;
  }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  if (is_target_home_row_hold_key(keycode)) {
    return false;
  }

  return true;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  if (is_target_home_row_hold_key(keycode)) {
    return 50;
  }

  return FLOW_TAP_TERM;
}

bool custom_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F16:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_TAB);
      } else {
        unregister_code(KC_LGUI);
      }
      return false;

    case KC_F17:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_TAB);
      } else {
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      }
      return false;

    case KC_F18:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_GRV);
      } else {
        unregister_code(KC_LGUI);
      }
      return false;

    case KC_F19:
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
