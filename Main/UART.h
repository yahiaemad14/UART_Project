// Function prototype for setting the UART baud rate
void uart_SetBaudRate(int baud);

// Function prototype for initializing the UART
void uart_init(int baud);

// Function prototype for transmitting a character via UART
void uart_transmit_char(char data);

// Function prototype for transmitting a string via UART
void uart_transmit_string(char data[]);

// Function prototype for receiving a string via UART
void UART_receive_String(char *receive_str, unsigned char number_of_char);

// Function prototype for checking if UART receive is ready
int uart_receive_ready(void);