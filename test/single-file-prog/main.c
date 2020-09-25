
#define TRUE (1)
#define FALSE (0)

// Convention is [MSB - LSB]

// LCD display pins [DB7 - DB0] should be connected
// to output port 1.
write_output_1(value)
	char value;
{
	char* ptr;
	ptr = 0x8000;
	*ptr = value;
}

// LCD display pins [0 - 0 RS E] should be connected
// to output port 2. 
// Pin RW should be connected to GND.
write_output_2(value)
	char value;
{
	char* ptr;
	ptr = 0xA000;
	*ptr = value;
}

// We use input port to read the state of two buttons
// [0 - 0 Button1 Button2]
read_input()
{
	char* ptr;
	ptr = 0xC000;
	return *ptr;
}

#define LCD_CMD 0
#define LCD_DATA 2

lcd(regSelect, data)
	char regSelect;
	char data;
{
	char regSE;
	regSE = regSelect + 1;

	write_output_1(data);
	write_output_2(regSelect);

	// Enable processing of the command by sending
	// 1 on E (enable) LCD input.
	
	// Do not set E immediately.
	// Allow data to stabilize on the input first!
	write_output_2(regSE);
	delay();
	write_output_2(regSelect);
}

#define LCD_SET_MODE_8BIT_2LINES_5x8FONT byte(0,0,1,1, 1,0,0,0)
#define LCD_CLEAR_DISPLAY byte(0,0,0,0, 0,0,0,1)
#define LCD_DISPON_CURSON_NOBLINK byte(0,0,0,0, 1,1,1,0)
// CURSINC -> cursor move to the right after write, NOSHFIT -
// but not between lines.
#define LCD_ENTRY_MODE_CURSINC_NOSHIFT byte(0,0,0,0, 0,1,1,0)
#define LCD_MOVE_2ND_LINE byte(1,1,0,0, 0,0,0,0)

#define BTN_1 1
#define BTN_2 2

lcd_print(s)
	char* s;
{
	while(*s) {
		lcd(LCD_DATA, *s);
		s++;
	}
}

main() {
	int counter;
	char refresh, tmp;
	char buf[8];

	lcd(LCD_CMD, LCD_SET_MODE_8BIT_2LINES_5x8FONT);
	lcd(LCD_CMD, LCD_CLEAR_DISPLAY);
	lcd(LCD_CMD, LCD_DISPON_CURSON_NOBLINK);
	lcd(LCD_CMD, LCD_ENTRY_MODE_CURSINC_NOSHIFT);
	lcd_print("Hello, world!");

	counter = 0;
	refresh = 1;

	while (1) {
		if (refresh) {
			lcd(LCD_CMD, LCD_MOVE_2ND_LINE);
			
			int_to_s(counter, buf, 4);
			lcd_print(buf);

			refresh = 0;
		}
		
		tmp = read_input();
		if (tmp & BTN_1) {
			counter++;
			refresh = 1;
		} 
		else if (tmp & BTN_2) {
			counter = (counter > 0) ? counter-1 : 0;
			refresh = 1;
		}

		if (refresh) {
			// Just to slow down the counting...
			delay(); 
			delay(); 
			delay();
		}
	}


	return;
}

int_to_s(n, buf, bsize) 
	int n; 
	char* buf; 
	char bsize;
{
	char i;
	char* ptr;

	for (i = 0; i <= bsize-2; i++) {
		// ASCII 48 == '0'
		*(buf + (bsize - 2 - i)) = 48 + (n % 10);
		n = n / 10;
	}
	*(buf + bsize-1) = 0; // Null terminate
}

byte(a,b,c,d,e,f,g,h)
	char a; char b; char c; char d; 
	char e; char f; char g; char h;
{
	char r;
	r = (a << 7) | (b << 6) |
	    (c << 5) | (d << 4) |
	    (e << 3) | (f << 2) |
     	    (g << 1) | h;

	return r;
}

long_delay() {
	char i;
	for (i = 0; i < 9; i++) {
		delay();
	}
}

delay() {
	signed char x;

	x = 0;
	while (x < 100) {
		x++;
	}
}
