// app/src/ip_led_anykey.c

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

/* LED 定義 */
#define LED_NODE DT_ALIAS(led0)
#if !DT_NODE_HAS_STATUS(LED_NODE, okay)
#error "led0 alias not defined"
#endif

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

/* 初期化 */
static int led_init(void) {
    if (!device_is_ready(led.port)) {
        return -ENODEV;
    }
    return gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
}
SYS_INIT(led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);

/* 押下カウント */
static int pressed_count = 0;

/* 任意キー押下イベント */
static int led_anykey_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev =
        as_zmk_keycode_state_changed(eh);

    if (!ev) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (ev->state) {
        pressed_count++;
        gpio_pin_set_dt(&led, 1);
    } else {
        pressed_count--;
        if (pressed_count <= 0) {
            pressed_count = 0;
            gpio_pin_set_dt(&led, 0);
        }
    }

    return ZMK_EV_EVENT_BUBBLE;
}
ZMK_LISTENER(led_anykey, led_anykey_listener);
ZMK_SUBSCRIPTION(led_anykey, zmk_keycode_state_changed);
