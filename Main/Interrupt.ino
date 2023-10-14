// Function definition for The Interrupt
void initInterrupt() {
  // Set interrupt sense control to trigger on Rising edge
  SET_BIT(EICRA, ISC01);
  SET_BIT(EICRA, ISC00);

  // Enable external interrupt INT0
  SET_BIT(EIMSK, INT0);

  // Enable global interrupts
  sei();
}