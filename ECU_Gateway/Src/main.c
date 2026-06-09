#include "main.h"

extern char* fill_buffer;

volatile uint32_t count = 0, count_1 = 0;

int main()
{
	payload_rpm_t payload;
	uint8_t crc_check;
	uint8_t count_error = 0;

	uint8_t alive_expected;
	uint8_t alive_anterior;

	static uint8_t fisrt_frame = 1;

	static uint8_t received;

	states_t message_state = NORMAL_MESSAGE;

	payload.rpm = 0;

	SetUp();

	TIM3_RegisterCB(TIM_Call);

	while(1)
	{


		if(count >= 100)
		{

			received =CAN1_Received(&payload, &crc_check);

			if(received)
			{
				if(crc_check == payload.crc)
				{

					if(fisrt_frame)
					{
						alive_anterior = payload.alive_counter;
						fisrt_frame = 0;
					}

					else
					{

						alive_expected = (alive_anterior + 1) % 16;

						if(payload.alive_counter == alive_expected)
						{

							if(count_error <= 3 && count_error > 0)
							{
								count_error--;
							}
						}

						else
						{
							if(count_error < 3)
							{
								count_error++;
							}
						}

						alive_anterior = payload.alive_counter;
					}
				}

				else
				{
					if(count_error < 3) count_error++;

				}

			}

			else
			{
				if(count_error < 3) count_error++;
			}


			if(count_error < 3)
			{

			sprintf(fill_buffer, "%d\n\r", payload.rpm);
			UART3_Transmmit();

			}

			else
			{
				sprintf(fill_buffer, "0\n\r");
				UART3_Transmmit();
			}


			Check_State(message_state, count_error);


			count = 0;

			}

	}

	return 0;
}

void Check_State(states_t message, uint8_t count)
{

	if(count == 0)
	{
		message = NORMAL_MESSAGE;
	}

	else if(count > 0 && count < 3)
	{
		message = DEGRADED_MESSAGE;
	}

	else if(count >= 3)
	{
		message = ERROR_MESSAGE;
	}


	if(message == NORMAL_MESSAGE)
	{
		GREEN_LED_ON();
		YELLOW_LED_OFF();
		RED_LED_OFF();
	}

	else if(message == DEGRADED_MESSAGE)
	{
		GREEN_LED_OFF();
		YELLOW_LED_ON();
		RED_LED_OFF();
	}

	else if(message == ERROR_MESSAGE)
	{
		GREEN_LED_OFF();
		YELLOW_LED_OFF();
		RED_LED_ON();
	}

}

void TIM_Call(void)
{
	count++;
	count_1++;
}
