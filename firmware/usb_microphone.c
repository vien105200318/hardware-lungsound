#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "bsp/board.h"
#include "tusb.h"

#define SAMPLE_RATE     16000
#define CHANNEL_COUNT   1
#define BITS_PER_SAMPLE 16
#define ADC_PIN         26

uint16_t sample_buffer[64];  // 64 mẫu mỗi lần gửi

void init_adc() {
    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_select_input(0); // GP26 là ADC0
}

void audio_task() {
    static uint32_t last_sample_time = 0;
    uint32_t now = to_ms_since_boot(get_absolute_time());

    if (now - last_sample_time >= (1000 * sample_buffer_len() / SAMPLE_RATE)) {
        for (int i = 0; i < 64; ++i) {
            uint16_t raw = adc_read();  // 12-bit ADC
            sample_buffer[i] = raw << 4;  // mở rộng thành 16-bit PCM
        }

        tud_audio_write((uint8_t*)sample_buffer, sizeof(sample_buffer));
        last_sample_time = now;
    }
}

int main() {
    stdio_init_all();
    board_init();
    tusb_init();
    init_adc();

    while (true) {
        tud_task();  // USB task
        audio_task();
    }
}
