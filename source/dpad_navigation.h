/*
D-pad navigation, for using the program without a sensor bar.
Each menu lists the rectangles of its buttons/keys. The D-pad moves the cursor to the center of the
nearest one in the pressed direction, so the existing "A pressed on the cursor" checks work unchanged.
*/

struct NavTarget { int x, y, w, h; };

enum NavDirection { NAV_NONE, NAV_UP, NAV_DOWN, NAV_LEFT, NAV_RIGHT };

//holding a direction repeats it after DPAD_REPEAT_DELAY frames, then every DPAD_REPEAT_RATE frames.
#define DPAD_REPEAT_DELAY 20
#define DPAD_REPEAT_RATE 6

static NavDirection dpad_read(u32 wpadbuttons, u32 padbuttons){
	if (wpadbuttons & WPAD_BUTTON_UP || padbuttons & PAD_BUTTON_UP) return NAV_UP;
	if (wpadbuttons & WPAD_BUTTON_DOWN || padbuttons & PAD_BUTTON_DOWN) return NAV_DOWN;
	if (wpadbuttons & WPAD_BUTTON_LEFT || padbuttons & PAD_BUTTON_LEFT) return NAV_LEFT;
	if (wpadbuttons & WPAD_BUTTON_RIGHT || padbuttons & PAD_BUTTON_RIGHT) return NAV_RIGHT;
	return NAV_NONE;
}

static NavDirection dpad_poll(){
	static int held_frames = 0;

	NavDirection pressed = dpad_read(wpaddown, paddown);
	if (pressed != NAV_NONE){
		held_frames = 0;
		return pressed;
	}

	NavDirection held = dpad_read(wpadheld, padheld);
	if (held == NAV_NONE){
		held_frames = 0;
		return NAV_NONE;
	}

	held_frames++;
	if (held_frames >= DPAD_REPEAT_DELAY && (held_frames - DPAD_REPEAT_DELAY) % DPAD_REPEAT_RATE == 0) return held;
	return NAV_NONE;
}

//distance from p to the range [start, start+length], 0 when p is inside it
static int span_gap(int p, int start, int length){
	if (p < start) return start - p;
	if (p > start + length) return p - (start + length);
	return 0;
}

void dpad_navigate(const NavTarget *targets, int count){
	if (cursor_ir_valid) return; //the pointer moves the cursor every frame, so the d-pad would be overridden

	NavDirection dir = dpad_poll();
	if (dir == NAV_NONE) return;

	int best = -1, best_score = 0;
	bool best_inline = false;
	for (int i=0;i<count;i++){
		const NavTarget &t = targets[i];
		int ahead, sideways; //ahead = distance to the target's near edge

		switch (dir){
			case NAV_UP:    ahead = cursor_positionY - (t.y + t.h); sideways = span_gap(cursor_positionX, t.x, t.w); break;
			case NAV_DOWN:  ahead = t.y - cursor_positionY;         sideways = span_gap(cursor_positionX, t.x, t.w); break;
			case NAV_LEFT:  ahead = cursor_positionX - (t.x + t.w); sideways = span_gap(cursor_positionY, t.y, t.h); break;
			default:        ahead = t.x - cursor_positionX;         sideways = span_gap(cursor_positionY, t.y, t.h); break;
		}
		if (ahead <= 0) continue; //the target isn't entirely in that direction

		//a target in line with the cursor (same row/column) always wins, otherwise sideways distance counts double
		bool is_inline = sideways == 0;
		int score = ahead + 2*sideways;
		if (best < 0 || is_inline > best_inline || (is_inline == best_inline && score < best_score)){
			best = i;
			best_score = score;
			best_inline = is_inline;
		}
	}

	if (best < 0) return; //nothing further in that direction

	cursor_positionX = targets[best].x + targets[best].w/2;
	cursor_positionY = targets[best].y + targets[best].h/2;
	hoversound();
}

template <int N>
void dpad_navigate(const NavTarget (&targets)[N]){ dpad_navigate(targets, N); }
