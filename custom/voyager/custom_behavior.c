#pragma once

static bool swap_win_active = false;

static bool f16_waiting_second_tap = false;
static bool f17_waiting_second_tap = false;

static uint16_t f16_double_tap_timer = 0;
static uint16_t f17_double_tap_timer = 0;

#define CUSTOM_DOUBLE_TAP_TERM 250

#define SWAP_WIN_LAYER_KEY LT(1, KC_BSPC)
#define SWAP_WIN_QUIT_KEY LGUI(KC_GRV)

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
    case KC_B:
    case KC_C:
    case KC_D:
    case KC_E:
    case KC_F:
    case KC_G:
    case KC_H:
    case KC_I:
    case KC_J:
    case KC_K:
    case KC_L:
    case KC_M:
    case KC_N:
    case KC_O:
    case KC_P:
    case KC_Q:
    case KC_R:
    case KC_S:
    case KC_T:
    case KC_U:
    case KC_V:
    case KC_W:
    case KC_X:
    case KC_Y:
    case KC_Z:
    case KC_COMM:
    case KC_DOT:
    case KC_SLSH:
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

void matrix_scan_user(void) {
  if (f16_waiting_second_tap && timer_elapsed(f16_double_tap_timer) > CUSTOM_DOUBLE_TAP_TERM) {
    f16_waiting_second_tap = false;
  }

  if (f17_waiting_second_tap && timer_elapsed(f17_double_tap_timer) > CUSTOM_DOUBLE_TAP_TERM) {
    f17_waiting_second_tap = false;
  }
}

bool custom_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F16:
      if (record->event.pressed) {
        if (f16_waiting_second_tap && timer_elapsed(f16_double_tap_timer) <= CUSTOM_DOUBLE_TAP_TERM) {
          f16_waiting_second_tap = false;
          tap_code(KC_SYSTEM_SLEEP);
        } else {
          f16_waiting_second_tap = true;
          f16_double_tap_timer = timer_read();
        }
      }
      return false;

    case KC_F17:
      if (record->event.pressed) {
        if (f17_waiting_second_tap && timer_elapsed(f17_double_tap_timer) <= CUSTOM_DOUBLE_TAP_TERM) {
          f17_waiting_second_tap = false;
          rgb_matrix_toggle();
        } else {
          f17_waiting_second_tap = true;
          f17_double_tap_timer = timer_read();
        }
      }
      return false;

    case KC_F22:
      if (record->event.pressed) {
        swap_win_step();
      }
      return false;

    case SWAP_WIN_QUIT_KEY:
      if (swap_win_active && record->event.pressed) {
        tap_code(KC_Q);
        return false;
      }
      break;

    case SWAP_WIN_LAYER_KEY:
      if (!record->event.pressed) {
        swap_win_release();
      }
      break;
  }

  return true;
}
