/*
What each on-screen keyboard key types. CAPS works like Shift on a US keyboard for every key, not just letters,
so the two modes together cover all printable ASCII (WPA passphrases can use any of it).
No Wii headers here so tests/keyboard_chars_test.cpp can build it on the host.
*/

//key = the character printed on the key's texture
static char kbd_char(char key, bool caps){
	if (!caps) return key;
	if (key >= 'a' && key <= 'z') return key - 'a' + 'A';

	switch (key){
		case '1': return '!';
		case '2': return '@';
		case '3': return '#';
		case '4': return '$';
		case '5': return '%';
		case '6': return '^';
		case '7': return '&';
		case '8': return '*';
		case '9': return '(';
		case '0': return ')';
		case '[': return '{';
		case ']': return '}';
		case '\\': return '|';
		case '/': return '?';
		case '\'': return '"';
		case ',': return '<';
		case '.': return '>';
		case '=': return '+';
		case ';': return ':';
		case '#': return '~';
		case '-': return '`'; //'_' already has its own key
		default: return key; //'_' and space
	}
}
