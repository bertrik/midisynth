#include <stdint.h>
#include <stdbool.h>

// local state
static uint8_t status;
static uint8_t running_status = 0;
static uint8_t len;
static uint8_t idx;
static uint8_t data[2];

// determines the length of following data from status byte
static void get_len(uint8_t b)
{
    top = b & 0xF0;
    switch (top) {
    case 0x80:  return 2;
    case 0x90:  return 2;
    case 0xA0:  return 2;
    case 0xB0:  return 2;
    case 0xC0:  return 1;
    case 0xD0:  return 1;
    case 0xE0:  return 2;
    case 0xF0:
        // this is a bit tricky, for simplicity use 0
        return 0;
    default:
        break;
    }
    return 0;
}

// determines (running) status from status byte
static uint8_t next_status(uint8_t s)
{
    if (s < 0xF0) {
        // channel voice message or channel mode message
        return s;
    } else if (s < 0xF8) {
        // system common message
        return 0;
    } else {
        // system real-time message
        return s;
    }
}

// determines if a status byte indicates a system realtime message
static bool is_realtime(uint8_t b)
{
    return (b >= 0xF8);
}

// process a fully received MIDI message
static void process_msg(uint8_t status, uint8_t data[], uint8_t len)
{
    (void)status;
    (void)data;
    (void)len;
}

// processes an incoming byte in the midi state machine
void midi_proc(uint8_t b)
{
    bool is_status = ((b & 0x80) != 0);

    // handle status byte
    if (is_status)  {
        if (is_realtime(b)) {
            // real-time, no data, process immediately
            process_msg(b, data, 0);
        } else {
            // non real-time
            idx = 0;
            len = get_len(b);
            if (len == 0) {
                // no data, process immediately
                process_msg(b, data, 0);
            }
            status = next_status(b);
        }
        return;
    }

    // handle data byte
    if ((status > 0) && (len > 0)) {
        if (idx < len) {
            // store data byte
            data[idx++] = b;
            if (idx == len) {
                idx = 0;
                // process it
                process_msg(status, data, len);
                // prepare for next message
                status = next_status(status);
            }
        } else {
            // overrun, should never happen
        }
    } else {
        // unexpected data, ignore it
    }
}