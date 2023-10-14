#include <util/delay.h>

//Include the header files
#include "DIO.h"
#include "uart.h"
#include "BIT_MATH.h"
#include "Interrupt.h"

// define some macros
#define BAUD 9600           // Define the baud rate
#define LENGTH 8            // Define the length of the received string
const int LED = 7;          // Define the LED pin
const int PUSH_BUTTON = 2;  // Define the push button pin



int main(void) {
  //Calling the functions
  initInterrupt();  // Initialize the interrupt
  initIO();         // Initialize the Input & Output
  uart_init(BAUD);  // Initialize the UART with the specified baud rate

  char received_String[LENGTH];  // Define a character array to store the received string
  while (1) {
    UART_receive_String(received_String, LENGTH);  // Receive a string from the UART
    if (strcasecmp(received_String, "LED_ON") == 0) {  // Compare the received string with "LED_ON" (Case-Insensitive)
      DIO_SetPinValue(DIO_PORTD, LED, DIO_HIGH);   // Turn on the LED
    }
    if (strcasecmp(received_String, "LED_OFF") == 0) {  // Compare the received string with "LED_OFF" (Case-Insensitive)
      DIO_SetPinValue(DIO_PORTD, LED, DIO_LOW);     // Turn off the LED
    }
    _delay_ms(1000);
  }

  return 0;
}


// Interrupt service routine for external interrupt INT0
ISR(INT0_vect) {
  char* message = "PUSH BUTTON is pressed \n";  // Define a message to be transmitted
  uart_transmit_string(message);                // Transmit the message
  _delay_ms(1000);
}
