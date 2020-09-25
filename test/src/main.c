
int value = 12345;

main() {
	short *outreg1, *outreg2;

	outreg1 = 0xffbb;
	outreg2 = 0x1234;

	while (1) {
		*outreg1 = ~(*outreg1);
		*outreg2 = ~(*outreg2);
		delay();
	}

	strlen("compile this shit!");

	return 0;
}

delay() {
	int i;
	for (i = 0; i <= 255; i++)
		;
}

strlen(char* s) {
	int len;
	
	len = 0;
	while (*s++) {
		len++;
	}
	return len;
}
