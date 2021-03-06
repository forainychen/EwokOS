#include <stdio.h>
#include <syscall.h>


void putch(int c) {
	syscall1(SYSCALL_UART_PUTCH, c);
}

int getch() {
	return syscall0(SYSCALL_UART_GETCH);
}

void putstr(const char* s) {
	int i = 0;
	while(1) {
		int c = (int)s[i++];
		if(c == 0)
			break;
		putch(c);
	}
}

/*
 * sprintf formats the given data and outputs the result into the given character
 * pointer. See vsprintf for the format flags currently supported.
 */
int
snprintf(char *target, int size, const char *format, ...)
{
	int length = 0;
	va_list ap;

	va_start(ap, format);
	length = vsnprintf(target, size, format, ap);
	va_end(ap);

	return length;
}

/*
 * printf_base formats and prints the given data. See vsprintf() for the format
 * flags currently supported.
 */
int
printf_base(void (*putch)(int), const char *format, ...)
{
	int length = 0;
	char buffer[BUFFER_MAX_LENGTH+1] = {0};
	int i = 0;
	va_list ap;

	va_start(ap, format);
	length = vsnprintf(buffer, BUFFER_MAX_LENGTH, format, ap);
	va_end(ap);

	while (i < length && buffer[i] != '\0') {
		putch(buffer[i]);
		i++;
	}
	return length;
}
