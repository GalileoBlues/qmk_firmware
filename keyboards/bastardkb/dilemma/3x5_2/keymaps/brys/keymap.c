/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// when tapped produces meta, otherwise acts as dead key for num/nav layer (L2)
#define L2_META_DEAD LT(LAYER_NUM_NAV, KC_LEFT_GUI)

// when tapped produces capslock, otherwise acts as dead key for sym/misc layer (L3)
#define L3_CAPS_DEAD LT(LAYER_SYM_MISC, KC_CAPS)

#define SHIFT_ONE OSM(MOD_LSFT)

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUM_NAV,//layer for numbers, arrows and modifier keys
    LAYER_SYM_MISC,//misc keys leftover from the previous layer
};

// clang-format off
/** \brief Recurva (colstag index swap) layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_F,    KC_R,    KC_D,    KC_L,    KC_J,            KC_V,    KC_W,    KC_U,     KC_O,    KC_Y, \
       KC_S,    KC_N,    KC_T,    KC_H,    KC_DOT,          KC_B,    KC_C,    KC_E,     KC_A,    KC_I, \
       KC_Z,    KC_X,    KC_K,    KC_M,    KC_Q,            KC_G,    KC_P,    KC_SCLN,  KC_QUOT, KC_COMM, \
                           L2_META_DEAD, KC_LCTL,           KC_SPC, L3_CAPS_DEAD

#define LAYOUT_NUM_NAV                                                                      \
       KC_ESC,  KC_1,      KC_2,      KC_3,    KC_4,            KC_7,    KC_8,    KC_9,    KC_0,    KC_ENT, \
       KC_TAB,  KC_COPY,   KC_PSTE,   KC_LALT, KC_5,            KC_6,    KC_LEFT, KC_UP, KC_DOWN,   KC_RIGHT, \
       KC_LEFT_GUI, LALT(KC_F3), LCA(KC_T), KC_PSCR, KC_NO,     KC_NO, KC_MPLY, KC_MPRV, KC_MNXT, KC_DEL, \
                               L2_META_DEAD, KC_LSFT,           KC_LSFT, L3_CAPS_DEAD

#define LAYOUT_SYM_MISC                                                                             \
       KC_F1, KC_F2,  KC_F3,  KC_F4,  KC_QUES,            KC_DLR, KC_LPRN, KC_LBRC, KC_RBRC, KC_RPRN, \
       KC_F5, KC_F6,  KC_F7,  KC_F8,  KC_GRV,             KC_EXLM, KC_SLSH, KC_PAST, KC_EQL, KC_MINS, \
       KC_F9, KC_F10, KC_F11, KC_F12, KC_UNDS,            KC_CIRC, KC_RABK, KC_LABK, KC_AT, KC_PERC, \
                        L2_META_DEAD, KC_LSFT,            KC_LSFT, L3_CAPS_DEAD


#define LAYOUT_wrapper(...) LAYOUT_split_3x5_2(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(LAYOUT_LAYER_BASE),
  [LAYER_NUM_NAV] = LAYOUT_wrapper(LAYOUT_NUM_NAV),
  [LAYER_SYM_MISC] = LAYOUT_wrapper(LAYOUT_SYM_MISC)
};

// adds combos for backspace (; + ,) and for enter (q + ')

const uint16_t PROGMEM backspace_combo[] = {KC_T, KC_E, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {KC_Q, KC_QUOT, COMBO_END};
const uint16_t PROGMEM shift_combo[] = {KC_S, KC_I, COMBO_END};
/*
const uint16_t PROGMEM colon_combo[] = {KC_LCTL, KC_SCLN, COMBO_END};
const uint16_t PROGMEM doublequote_combo[] = {KC_LCTL, KC_QUOT, COMBO_END};
const uint16_t PROGMEM RANGLE_BRACKET_combo[] = {KC_LCTL, KC_COMM, COMBO_END};
const uint16_t PROGMEM LANGLE_BRACKET_combo[] = {KC_LCTL, KC_DOT, COMBO_END};
*/

combo_t key_combos[] = {
    COMBO(backspace_combo, KC_BSPC),
    COMBO(enter_combo, KC_ENT),
    COMBO(shift_combo, SHIFT_ONE),
    //COMBO(colon_combo, KC_COLN),
    //COMBO(doublequote_combo, KC_DQUO),
    //COMBO(RANGLE_BRACKET_combo, KC_RABK),
    //COMBO(LANGLE_BRACKET_combo, KC_LABK),
};

/*
 * adds overrides that mimic the shifted value for the punctuation on the base layer.
 *
 * Ctrl + ; = :
 * Ctrl + ' = "
 * Ctrl + . = <
 * Ctrl + , = >
 */

const key_override_t ctrl_semicolon_override = ko_make_basic(MOD_MASK_CTRL, KC_SCLN, KC_COLN);
const key_override_t ctrl_quote_override = ko_make_basic(MOD_MASK_CTRL, KC_QUOT, KC_DQUO);
const key_override_t ctrl_comma_override = ko_make_basic(MOD_MASK_CTRL, KC_COMM, KC_RABK);
const key_override_t ctrl_period_override = ko_make_basic(MOD_MASK_CTRL, KC_DOT, KC_LABK);
//const key_override_t shift_override = ko_make_basic(KC_LCTL, KC_SPC, SHIFT_ONE);

const key_override_t **key_overrides = (const key_override_t *[]){
    &ctrl_semicolon_override,
    &ctrl_quote_override,
    &ctrl_comma_override,
    &ctrl_period_override,
    //&shift_override,
    NULL
};
