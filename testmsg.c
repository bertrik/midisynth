#include <stdint.h>
#include <stdio.h>

#include "midisynth/midiproc.h"

static void handle_msg(uint8_t status, const uint8_t data[], int len)
{
    printf("status = %02X:", status);
    for (int i = 0; i < len; i++) {
        printf(" %02X", data[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    midi_msg_init(handle_msg);
    
    // 1st message: normal note on
    midi_msg_proc(0x80);
    
    // 2nd message: real-time message in between
    midi_msg_proc(0xF8);
    
    // continuation of 1st message
    midi_msg_proc(0x12);
    midi_msg_proc(0x34);
    
    // 3rd message: note on with running status
    midi_msg_proc(0x56);
    // 4th message: real-time message in between
    midi_msg_proc(0xF9);
    
    // continuation of 3rd message
    midi_msg_proc(0x78);
    
    // 5th message: system common
    midi_msg_proc(0xF3);
    midi_msg_proc(0x00);

    // attempt running status message: should fail
    midi_msg_proc(0x12);
    midi_msg_proc(0x34);

    return 0;
}

