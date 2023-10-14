// Function to set the UART baud rate
void uart_SetBaudRate(int baud) {
  int ubrr = ((F_CPU) / (baud * 16UL) - 1);  // The formula for calculating the baud rate
  UBRR0H = (ubrr >> 8);                      // shift the register right by 8 bits
  UBRR0L = ubrr;                             // set baud rate bits [0 : 7]
}

// Function to initialize the UART
void uart_init(int baud) {
  uart_SetBaudRate(baud);
  // Enable Receiver and Transmitter
  SET_BIT(UCSR0B, TXEN0);
  SET_BIT(UCSR0B, RXEN0);
  // Set the data format to 8-bit
  SET_BIT(UCSR0C, UCSZ00);
  SET_BIT(UCSR0C, UCSZ01);
}

// Function to transmit a single character
void uart_transmit_char (char data)
{
	int udr_empty;
	do
	{
    udr_empty = (GET_BIT(UCSR0A, UDRE0)) != 0;   // Check if the transmit buffer is empty
	}while(!udr_empty);                            // Wait until the transmit buffer is empty
	UDR0 = data;                                   // Write the character to the transmit buffer
}
// Function to transmit a string
void uart_transmit_string(char data[]) {
  int i;
  //Loops to send every character inside the string using uart_transmit_char
  for(i=0; data[i];i++)
  {
    uart_transmit_char(data[i]);
  }
}

// Function to receive a string
void UART_receive_String(char *receive_str, unsigned char number_of_char) {
	unsigned char i = 0;
	while (i < (number_of_char - 1)) {
		while (GET_BIT(UCSR0A, RXC0) == 0); // Wait for a character to be received
		unsigned char received_data = UDR0; // Read the received character
		
		// Check for end of string
		if (received_data == '\0' || received_data == '\n' || received_data == '\r') {
			break;                            //Quit the while loop
		}
		
		receive_str[i++] = received_data;  // Store the received character in the "receive_str" buffer   
	}
	receive_str[i] = '\0';    // Null-terminate to the end of the string
}

// Function to check if there is a character available to be received from the UART
int uart_receive_ready(void) {
  int flag = (GET_BIT(UCSR0A, RXC0)) != 0;  // check and confirm if the data has been fully received.
  return flag;            // Return 1 if there is a character available, otherwise return 0
}

