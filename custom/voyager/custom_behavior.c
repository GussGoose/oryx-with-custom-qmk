#pragma once

static bool app_switcher_active = false;
static uint16_t app_switcher_timer = 0;
static const uint16_t APP_SWITCHER_TIMEOUT = 900;

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

static void app_switcher_begin(void) {
  if (!app_switcher_active) {
    app_switcher_active = true;
    register_code(KC_LGUI);
  }

  app_switcher_timer = timer_read();
}

static void app_switcher_step_forward(void) {
  app_switcher_begin();
  tap_code(KC_TAB);
}

static void app_switcher_step_backward(void) {
  app_switcher_begin();
  register_code(KC_LSFT);
  tap_code(KC_TAB);
  unregister_code(KC_LSFT);
}

void matrix_scan_user(void) {
  if (app_switcher_active && timer_elapsed(app_switcher_timer) > APP_SWITCHER_TIMEOUT) {
    unregister_code(KC_LGUI);
    app_switcher_active = false;
  }
}

bool custom_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F16:
      if (record->event.pressed) {
        app_switcher_step_forward();
      }
      return false;

    case KC_F17:
      if (record->event.pressed) {
        app_switcher_step_backward();
      }
      return false;

    case KC_F18:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        tap_code(KC_GRV);
        unregister_code(KC_LGUI);
      }
      return false;

    case KC_F19:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_GRV);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
      }
      return false;
  }

  return true;
}
