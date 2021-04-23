#include <stdbool.h>
#include <stdint.h>

#include "../isr.h"
#include <kernel/tty.h>

#define KEY_BUFFER_SIZE (1 << 8)
#define KEY_BUFFER_MASK (KEY_BUFFER_SIZE - 1)
#define KEY1_LIMIT 0x40
#define KEY_FLAG_RELEASE 0x80

uint16_t keybufferc, keybufferg;
uint8_t keystate1[0x80];
uint8_t keybuffer[KEY_BUFFER_SIZE];
uint8_t keyboardmap[2][KEY1_LIMIT] = {
  "\000\027"
  "1234567890-=" "\000"
  "\tqwertyuiop[]" "\n\000"
  "asdfghjkl;'"  "\000\000\\"
  "zxcvbnm,./" "\000\000\000 ",
  "\000\027"
  "!@#$%^&*()_+" "\000"
  "\tQWERTYUIOP{}" "\n\000"
  "ASDFGHJKL:\"" "\000\000|"
  "ZXCVBNM<>?" "\000\000\000 ",
};

char to_hex(uint8_t c) {
	return c < 10? '0' + c : 'A' + c - 10;
}

bool keyboard_pending() {
  return (keybufferc != keybufferg);
}

char keyboard_getchar() {
  char c;
  c = keybuffer[keybufferg];
  keybufferg++;
  keybufferg &= KEY_BUFFER_MASK;
	return c;
}

__attribute__((interrupt))
void isr_keyboard(frame_t *pframe) {
  uint8_t c;
  c = isr_read_key();
  if(KEY_FLAG_RELEASE & c) {
    c &= ~KEY_FLAG_RELEASE;
    keystate1[c] = 0;
  } else {
		char t;
    keystate1[c] = 1;
    t = 0;
		if(0 < c && c < KEY1_LIMIT) {
		  t = keyboardmap[keystate1[0x2a]][c];
			keybuffer[keybufferc] = t;
			keybufferc++;
			keybufferc &= KEY_BUFFER_MASK;
			if(t) {
		    terminal_putchar(t);
		  }
		}
		/*if(!t) {
			terminal_putchar('\'');
			terminal_putchar(to_hex(0xF & (c >> 4)));
			terminal_putchar(to_hex(0xF & c));
			terminal_putchar('\'');
		}*/
  }
}
