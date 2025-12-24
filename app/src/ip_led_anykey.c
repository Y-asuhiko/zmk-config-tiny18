// app/src/ip_led_anykey.c

#include <zephyr/kernel.h>
#include <zmk/input_processor.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>

static int pressed_count = 0;

/* イベントハンドラ */
static int ip_led_anykey_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev =
        as_zmk_keycode_state_changed(eh);

    if (!ev) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    if (ev->state) {
        pressed_count++;
        /* 後で LED ON */
    } else {
        pressed_count--;
        if (pressed_count < 0) {
            pressed_count = 0;
        }
        /* 後で LED OFF */
    }

    return ZMK_EV_EVENT_BUBBLE;
}

/* リスナ登録 */
ZMK_LISTENER(ip_led_anykey, ip_led_anykey_listener);
ZMK_SUBSCRIPTION(ip_led_anykey, zmk_keycode_state_changed);
