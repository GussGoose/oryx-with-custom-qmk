#pragma once

static bool swap_win_active = false;

static bool is_home_row_mod_hold_key(uint16_t keycode) {
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

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  if (is_home_row_mod_hold_key(keycode)) {
    return false;
  }

  return true;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
  if (is_home_row_mod_hold_key(keycode)) {
    return 50;
  }

  return FLOW_TAP_TERM;
}

static void swap_win_release(void) {
  if (swap_win_active) {
    unregister_code(KC_LGUI);
    swap_win_active = false;
  }
}

static void swap_win_step(void) {
  if (!swap_win_active) {
    register_code(KC_LGUI);
    swap_win_active = true;
  }

  tap_code(KC_TAB);
}

bool custom_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (swap_win_active && keycode != KC_F22) {
    swap_win_release();
  }

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

    case KC_F22:
      if (record->event.pressed) {
        swap_win_step();
      }
      return false;
  }

  return true;
}
