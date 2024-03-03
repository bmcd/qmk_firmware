// Copyright 2022 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H


//extern rgb_config_t rgb_matrix_config;

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255} },

    [2] = { {0,198,145}, {150,123,179}, {150,123,179}, {150,123,179}, {150,123,179}, {150,123,179}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {150,123,179}, {150,123,179}, {150,123,179}, {150,123,179}, {150,123,179}, {150,123,179}, {0,0,0}, {0,0,0}, {58,123,179}, {138,228,161}, {138,228,161}, {138,228,161}, {0,0,0}, {58,123,179}, {58,123,179}, {58,123,179}, {26,255,255}, {0,0,0}, {0,0,0}, {0,198,145}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,245,245}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {0,0,0}, {0,0,0}, {58,123,179}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {58,123,179}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {26,255,255}, {0,0,255}, {26,255,255}, {150,123,179}, {58,123,179}, {150,123,179}, {26,255,255}, {0,198,145}, {152,255,255}, {58,123,179}, {58,123,179}, {150,123,179}, {0,198,145}, {0,0,0}, {150,123,179}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

int equals_to_voyager(int i) {
    int row = i / 12;
    int col = i % 12;
    int side = col / 6;
    int sidecol = col % 6;
    return (side * 26) + (row * 6) + sidecol;
}

void set_layer_color(int layer) {
  // 10 to 57
  int led_min = 10;
  int led_count = 48;
  for (int i = 0; i < led_count; i++) {
    int map_i = equals_to_voyager(i);
    int equals_i = i + led_min;
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][map_i][0]),
      .s = pgm_read_byte(&ledmap[layer][map_i][1]),
      .v = pgm_read_byte(&ledmap[layer][map_i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( equals_i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( equals_i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
  rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
  set_layer_color(2);
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
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(
	    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS,
	    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
	    KC_LSFT, LALT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
	    KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_LGUI, LT(2,KC_ENT), MEH_T(KC_SPC), KC_NO, KC_NO, KC_NO, KC_NO
	),
	[1] = LAYOUT_ortho_4x12(
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_TRNS, LGUI_T(KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT_ortho_4x12(
	    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_LBRC, KC_RBRC, KC_BSLS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_RALT, KC_TRNS,
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT_ortho_4x12(
	    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
	    RGB_M_P, RGB_M_B, RGB_M_R, RGB_SAI, RGB_HUI, RGB_VAI, KC_TRNS, KC_TRNS, QK_BOOT, KC_TRNS, KC_VOLU, KC_F12,
	    KC_TRNS, KC_TRNS, RGB_TOG, RGB_SAD, RGB_HUD, RGB_VAD, TO(1), TO(0), KC_TRNS, KC_TRNS, KC_VOLD, LCA(KC_DEL),
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
