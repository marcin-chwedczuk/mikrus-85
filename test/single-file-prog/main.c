
#define TRUE (1)
#define FALSE (0)

main() {
	char *data, *control, *input;
	char *ptr;
	char counter, refresh;
	char buf[4];

	// data [DB7 - DB0]
	data = 0x8000;
	// [0 - RS E] (WR = 0)
	control = 0xA000;

	input = 0xC000;

	// --- START ----

	// 2 lines mode
	*control = cbyte(0, 0);
	*data = byte(0, 0, 1, 1, 1, 0, 0, 0);
	delay();
	*control = cbyte(0, 1);
	delay();
	*control = cbyte(0, 0);

	// clear the display
	*control = cbyte(0, 0);
	*data = byte(0, 0, 0, 0, 0, 0, 0, 1);
	delay();
	*control = cbyte(0, 1);
	delay();
	*control = cbyte(0, 0);

	// display and cursor on
	*control = cbyte(0, 0);
	*data = byte(0,0,0,0,  1,1,1,0);
	delay();
	*control = cbyte(0, 1);
	delay();
	*control = cbyte(0, 0);

	// entry mode set
	*control = cbyte(0, 0);
	*data = byte(0,0,0,0,  0,1,1,0);
	delay();
	*control = cbyte(0, 1);
	delay();
	*control = cbyte(0, 0);

	ptr = "Hello world!";
	while (*ptr) {
		// Write character
		*control = cbyte(1, 0);
		*data = *ptr;
		delay();
		*control = cbyte(1, 1);
		delay();
		*control = cbyte(1, 0);

		ptr++;
	}


	counter = 0;
	*buf = 0; *(buf + 1) = 0; *(buf+2) = 0;
	refresh = 1;

	while (1) {
		if (refresh) {
			// Move to the second line
			*control = cbyte(0, 0);
			*data = byte(1,1,0,0,0,0,0,0);
			delay();
			*control = cbyte(0, 1);
			delay();
			*control = cbyte(0, 0);

			counter_to_s(counter, buf);
			
			// Write character
			*control = cbyte(1, 0);
			*data = 48 + *buf;
			delay();
			*control = cbyte(1, 1);
			delay();
			*control = cbyte(1, 0);

			refresh = 0;
		}
		
		if ((*input) & 1) {
			counter++;
			refresh = 1;
		} else if ((*input) & 2) {
			counter = (counter > 0) ? counter-1 : 0;
			refresh = 1;
		}

		if (refresh) {
			delay(); delay(); delay();
			delay(); delay(); delay();
			delay(); delay(); delay();
		}
	}


	*control = 0;
	*data = 0;
	while (1) { }

	return;
}

counter_to_s(n, buf) char n; char* buf;
{
	char i;

	for (i = 0; i < 1; i++) {
		*(buf+i) = n % 10;
		n = n / 10;
	}
}

cbyte(rs, e) char rs; char e;
{
	int r;
	r = (rs << 1) | e;
	return r;
}

byte(a,b,c,d,e,f,g,h)
	char a; char b; char c; char d; char e; char f; char g; char h;
{
	char r;
	r = h | (g << 1) | (f << 2) | (e << 3) |
		(d << 4) | (c << 5) | (b << 6) | (a << 7);
	return r;
}

delay() {
	char x;

	x = 0;
	while (x < 100) {
		x++;
	}
}
