#pragma once

//handedness
#undef MASTER_RIGHT
#define SPLIT_HAND_PIN GP29

//VBUS detect
#define USB_VBUS_PIN GP19

//combo term
#define COMBO_TERM 40

// via
#ifdef VIA_ENABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#endif
