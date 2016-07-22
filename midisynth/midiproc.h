#include <stdint.h>

/* callback prototype */
typedef void (midi_msg_handle_fn_t)(uint8_t status, const uint8_t data[], int len);

// initialises the callback
void midi_msg_init(midi_msg_handle_fn_t *fn);
// processes one byte
void midi_msg_proc(uint8_t b);


