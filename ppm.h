#ifndef PPM_H__
#define PPM_H__

#include "main.h"

#define PPM_CHANNELS 8

//servo signal is usually 1000-2000us, we accept 800-2200us
#define PPM_CHANNEL_WIDTH_MIN  800
#define PPM_CHANNEL_WIDTH_MAX 2200
//sync  signal is roughly 12ms, we accept 7-18ms
#define PPM_SYNC_WIDTH_MIN  7000
#define PPM_SYNC_WIDTH_MAX 18000

#define PPM_STATE_WAIT_FOR_SYNC 0
#define PPM_STATE_FETCH_DATA    1

volatile uint8_t ppm_channel;
volatile uint8_t ppm_detected;
volatile uint8_t ppm_state;
volatile uint16_t ppm_data[PPM_CHANNELS];

volatile uint16_t ww;


void ppm_init(void);
uint8_t ppm_active(void);

#endif
