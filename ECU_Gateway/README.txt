This repository implements an automotive ECU Gateway with payload validation and fault managment
capabilities. The system operates in three states: Normal, Degraded, and Error mode.
Message integirty is verified using an Alive Counter and CRC validation. This Gateway
monitors communication health and automaticaly canges its operating state when faults or 
invalid message are detacted.

The CAN_Init.c file contains the CAN driver configuration, including bit timing parameters
and filter settings. Interrupt Service Routines (ISRs) are used to handle CAN 
message reception efficiently.

The USART_Init.c contains the UART dirver configuration, with a baud rate of 115200 , 1 stop bit and 8-bit data lenght. 
UART communication is used to transmmit motor speed information from the ECU_Gateway to a Python GUI, enabling
real-time monitoring and display of system data.

The TIM_Init.c module configures a timer with 1 ms period. The timer interrupt is used to implement a non-blocking 
scheduler for periodic ECU communication tasks.
By using an ISR-based approach, the system can monitor and process ECU messages at deterministic intervals
while maintaining real-time performance.


