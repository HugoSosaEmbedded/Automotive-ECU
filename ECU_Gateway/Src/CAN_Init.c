#include "main.h"

volatile uint8_t flag_received;
extern char* fill_buffer;

void CAN1_Init(void)
{
	RCC->APB1ENR |= (1<<25); //Enable clock for CAN1
	/*--------------------------Initialization----------------------------------------------------------------*/
	CAN1->MCR |= CAN_MCR_INRQ; //Initialization request
	CAN1->MCR &= ~CAN_MCR_SLEEP; // Sleep mode request disable
	while(!(CAN1->MSR & CAN_MSR_INAK)); // Wait until hardware indicates CAN is in initialization mode
	while(CAN1->MSR & CAN_MSR_SLAK); // Verify if CAN is not in Sleep mode
	CAN1->MCR |= CAN_MCR_TXFP; // Transmit FIFO priority driven by the identifier of the message
	CAN1->MCR &= ~CAN_MCR_RFLM; // Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming message overwrites the previous one
	CAN1->MCR &= ~CAN_MCR_NART; // The CAN hardware automatically retransmits the message until it has been successfully transmitted
	CAN1->MCR |= CAN_MCR_AWUM; //The sleep mode is left automatically by hardware on CAN message detection
	CAN1->MCR |= CAN_MCR_ABOM; //The Bus-Off state is left automatically by hardware once 128 occurrences of 11 11 recessive bits have been monitored
	/*-----------------------Bit Timing------------------------------------------------------------------------*/
	CAN1->BTR = (3<<0) // BRP = 4, CAN1_BTR_BRP
			          | (5<<16) // TS1 = 5, CAN_BTR_TS1, TS1_Real = 6
			          | (0<<20) // TS2 = 0, CAN_BTR_TS2, TS2_Real = 1
			          | (1<<24); // SJW = 1, CAN_BTR_SJW
	/*-----------------------Filtering--------------------------------------------------------------------------*/
	CAN1->FMR |= CAN_FMR_FINIT; // Initialization mode for the filters
	CAN1->FA1R &= ~CAN_FA1R_FACT0; // Filter 0 is not active to configure it
	CAN1->FM1R |= CAN_FM1R_FBM0; // Two 32 bit registers of filter bank 0 are in identifier list mode
	CAN1->FFA1R &= ~CAN_FFA1R_FFA0; // Filter assigned to FIFO0
	CAN1->sFilterRegister[0].FR1 = (0x123<<21) | (0<<2) | (0<<1); // ID = 0x123, Standard identifier, Data frame
	CAN1->sFilterRegister[0].FR2 = 0x00000000;
	CAN1->FA1R |=CAN_FA1R_FACT0; // Filter 0 is active
	CAN1->FMR &= ~CAN_FMR_FINIT; // Active filters mode

	CAN1->MCR &= ~CAN_MCR_INRQ; // Normal mode
	while(CAN1->MSR & CAN_MSR_INAK); // Wait until CAN get into to Normal mode

	CAN1->IER |= CAN_IER_TMEIE; // Transmit mailbox interrupt enable generated when RQCPx bit is set
	NVIC_EnableIRQ(CAN1_TX_IRQn);
	NVIC_SetPriority(CAN1_TX_IRQn,0);

	CAN1->IER |= CAN_IER_FMPIE0; // FIFO message pending interrupt enable
	NVIC_EnableIRQ(CAN1_RX0_IRQn);
	NVIC_SetPriority(CAN1_RX0_IRQn,0);
}

void CAN1_SetFlag(void) { flag_received = 1; }

bool CAN1_Received(payload_rpm_t* payload, uint8_t* crc_check)
{
	uint32_t received = 0;

	if(flag_received)
	{
		received = CAN1->sFIFOMailBox[0].RDLR; // Save message received into received variable
		uint8_t aux;
		aux = (received >> 8) & (0xFF);
		payload->rpm = (aux << 8) | ((received) & (0xFF));
		payload->alive_counter = (received >> 16) & (0xF);
		payload->crc = (received >> 20) & (0xF);

		*crc_check = ( ((received) & (0xF)) ^ ((aux) & (0xF)) ^ ((payload->alive_counter) & (0xF)) );

		CAN1->RF0R |= CAN_RF0R_RFOM0; //Release

		flag_received = 0;

		return true;
	}

	return false;
}
