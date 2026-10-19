// Host-side check of the on-screen keyboard character mapping.
// Run from the repository root: g++ -Wall -o /tmp/keyboard_chars_test tests/keyboard_chars_test.cpp && /tmp/keyboard_chars_test

#include <cstdio>
#include <cstring>
#include "../source/keyboard_chars.h"

// Every character key on the keyboards (layout in source/keyboard_texture_coords.h). CAPS and ERASE aren't character keys.
static const char keys[] = "1234567890-" "qwertyuiop_" "asdfghjkl;" "zxcvbnm,.=" "[] \\/'#";

static int failures = 0;

static void expect(bool ok, const char *what, int c){
	if (!ok){
		printf("FAIL: %s: 0x%02X '%c'\n", what, c, c);
		failures++;
	}
}

int main(){
	bool reachable[128] = {};
	for (const char *k = keys; *k; k++){
		expect(kbd_char(*k, false) == *k, "CAPS off doesn't type the key's label", *k);
		reachable[(unsigned char)kbd_char(*k, false)] = true;
		reachable[(unsigned char)kbd_char(*k, true)] = true;
	}

	for (int c = 0x20; c <= 0x7E; c++) expect(reachable[c], "printable character not reachable", c);
	for (int c = 0; c < 128; c++) if (c < 0x20 || c > 0x7E) expect(!reachable[c], "non-printable character typed", c);

	// The US Shift layout we promise in the README.
	const char *from = "1234567890[]\\/',.=;#-_ ";
	const char *to   = "!@#$%^&*(){}|?\"<>+:~`_ ";
	for (size_t i = 0; i < strlen(from); i++) expect(kbd_char(from[i], true) == to[i], "wrong CAPS character for key", from[i]);
	for (char c = 'a'; c <= 'z'; c++) expect(kbd_char(c, true) == c - 'a' + 'A', "wrong CAPS letter", c);

	if (failures) return 1;
	printf("OK: all %d printable ASCII characters are reachable\n", 0x7E - 0x20 + 1);
	return 0;
}
