#include <zephyr/device.h>
#include <zephyr/kernel.h>

#include <zmk/behavior.h>
#include <zmk/keymap.h>

static int behavior_rgb_led_pressed(struct zmk_behavior_binding *binding,
                                    struct zmk_behavior_binding_event event) {
    /* ここでは何もしない（次工程でGPIO制御を追加） */
    return ZMK_BEHAVIOR_OPAQUE;
}

static int behavior_rgb_led_released(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    /* ここでは何もしない */
    return ZMK_BEHAVIOR_OPAQUE;
}

/* behavior 定義本体 */
static const struct behavior_driver_api behavior_rgb_led_driver_api = {
    .binding_pressed = behavior_rgb_led_pressed,
    .binding_released = behavior_rgb_led_released,
};

/* behavior 登録 */
BEHAVIOR_DT_INST_DEFINE(0,
    behavior_rgb_led_init,     /* init関数（後で使う） */
    NULL,
    NULL,
    NULL,
    &behavior_rgb_led_driver_api
);

/* initは今は空でOK */
static int behavior_rgb_led_init(const struct device *dev) {
    ARG_UNUSED(dev);
    return 0;
}
