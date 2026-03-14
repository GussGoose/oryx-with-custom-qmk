#pragma once

static bool app_switch_forward_held = false;
static bool app_switch_backward_held = false;
static uint16_t app_switch_timer = 0;
static bool app_switch_cmd_active = false;

#define APP_SWITCH_INITIAL_DELAY 180
#define APP_SWITCH_REPEAT_DELAY 110

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

static void app_switcher_start(void) {
  if (!app_switch_cmd_active) {
    register_code(KC_LGUI);
    app_switch_cmd_active = true;
  }
}

static void app_switcher_stop(void) {
  if (app_switch_cmd_active) {
    unregister_code(KC_LGUI);
    app_switch_cmd_active = false;
  }
}

static void app_switcher_step_forward(void) {
  tap_code(KC_TAB);
}

static void app_switcher_step_backward(void) {
  register_code(KC_LSFT);
  tap_code(KC_TAB);
  unregister_code(KC_LSFT);
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

void matrix_scan_user(void) {
  static bool initial_repeat_done = false;

  if (app_switch_forward_held || app_switch_backward_held) {
    uint16_t elapsed = timer_elapsed(app_switch_timer);

    if (!initial_repeat_done) {
      if (elapsed >= APP_SWITCH_INITIAL_DELAY) {
        if (app_switch_forward_held) {
          app_switcher_step_forward();
        } else if (app_switch_backward_held) {
          app_switcher_step_backward();
        }
        app_switch_timer = timer_read();
        initial_repeat_done = true;
      }
    } else {
      if (elapsed >= APP_SWITCH_REPEAT_DELAY) {
        if (app_switch_forward_held) {
          app_switcher_step_forward();
        } else if (app_switch_backward_held) {
          app_switcher_step_backward();
        }
        app_switch_timer = timer_read();
      }
    }
  } else {
    initial_repeat_done = false;
  }
}

bool custom_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_F16:
      if (record->event.pressed) {
        app_switch_forward_held = true;
        app_switch_backward_held = false;
        app_switcher_start();
        app_switcher_step_forward();
        app_switch_timer = timer_read();
      } else {
        app_switch_forward_held = false;
        app_switcher_stop();
      }
      return false;

    case KC_F17:
      if (record->event.pressed) {
        app_switch_backward_held = true;
        app_switch_forward_held = false;
        app_switcher_start();
        app_switcher_step_backward();
        app_switch_timer = timer_read();
      } else {
        app_switch_backward_held = false;
        app_switcher_stop();
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
