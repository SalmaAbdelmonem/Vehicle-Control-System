#include <stdio.h>

enum modes
{
	OFF, ON
};

#define WITH_ENGINE_TEMP_CONTROLLER 1

char option, choice;
int AC = OFF;
int vehicle_speed = 100;
int room_temperature = 25;
int engine_temperature_controller = OFF;
int engine_temperature = 120;

/*---------------------------------------------------------------------------------------*/

/*function controls quit mode*/
void quit_the_system (void)
{
	printf("Quit the system.");
	fflush(0);
	return;
}

/*---------------------------------------------------------------------------------------*/

void sensors_menu(int *choice_ptr)
{
	printf("The vehicle engine is turned on.\n");
	fflush(0);
	printf("Please choose an option:\n");
	fflush(0);
	printf("a. Turn off the vehicle engine.\n");
	fflush(0);
	printf("b. Set the traffic light color.\n");
	fflush(0);
	printf("c. Set the room temperature.\n");
	fflush(0);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	printf("d. Set the engine temperature.\n");
	fflush(0);
#endif

	scanf(" %c", choice_ptr);
}

/*---------------------------------------------------------------------------------------*/

/*function controls turn on mode*/
void turn_on_the_vehicle (char *option_ptr, int *AC_ptr, int *vehicle_speed_ptr, int *room_temperature_ptr, int *engine_temperature_controller_ptr, int *engine_temperature_ptr )
{
	char choice, traffic_light;
	int AC_temperature;
	int engine_temperature_controller_temperature ;

	sensors_menu(&choice);

	/*in case of choice is turn off so display modes menu*/
	if(choice == 'a')
	{
		printf("The vehicle engine is turned off.");
		fflush(0);
		printf("Please choose an option:\n a. Turn on the vehicle engine.\n b. Turn off the vehicle engine.\n c. Quit the system.\n");
		fflush(0);
		scanf(" %c", option_ptr);

		/*if choice is turn on mode, goes to turn on function*/
		if(*option_ptr == 'a')
		{
			option = *option_ptr;
			turn_on_the_vehicle(&option, &AC, &vehicle_speed, &room_temperature, &engine_temperature_controller, &engine_temperature );
			return;
		}
	}

	if(choice == 'b')
	{
		printf("Please enter the traffic light color(G, O, R):\n");
		fflush(0);
		scanf(" %c", &traffic_light);

		if (traffic_light == 'G')
		{
			*vehicle_speed_ptr = 100;
		}
		else if (traffic_light == 'O')
		{
			*vehicle_speed_ptr = 30;
		}
		else if (traffic_light == 'R')
		{
			*vehicle_speed_ptr = 0;
		}
		vehicle_speed = *vehicle_speed_ptr;
		display_output();
	}

	if(choice == 'c')
	{
		printf("Please enter the room temperature:\n");
		fflush(0);
		scanf("%d", room_temperature_ptr);

		if (*room_temperature_ptr < 10)
		{
			*AC_ptr = ON;
			AC_temperature = 20;
		}
		else if (*room_temperature_ptr > 30)
		{
			*AC_ptr = ON;
			AC_temperature = 20;
		}
		else
		{
			*AC_ptr = OFF;
			AC_temperature = 0;
		}
		room_temperature = *room_temperature_ptr;
		AC = *AC_ptr;
		display_output();
	}

#if WITH_ENGINE_TEMP_CONTROLLER == 1
	if(choice == 'd')
	{
		printf("Please enter the engine temperature:\n");
		fflush(0);
		scanf(" %d", engine_temperature_ptr);

		if (*engine_temperature_ptr < 100)
		{
			*engine_temperature_controller_ptr = ON;
			engine_temperature_controller_temperature = 125;
		}
		else if (*engine_temperature_ptr > 150)
		{
			*engine_temperature_controller_ptr = ON;
			engine_temperature_controller_temperature = 125;
		}
		else
		{
			*engine_temperature_controller_ptr = OFF;
			engine_temperature_controller_temperature = 0;
		}
		engine_temperature = *engine_temperature_ptr;
		engine_temperature_controller = *engine_temperature_controller_ptr;
		display_output();
	}
#endif

	turn_on_the_vehicle(&option, &AC, &vehicle_speed, &room_temperature, &engine_temperature_controller, &engine_temperature );

}

/*---------------------------------------------------------------------------------------*/

void display_output(void)
{
	printf("The current vehicle state:\n");
	fflush(0);

	if(option == 1)
	{
		printf("Engine state: ON\n");
		fflush(0);
	}
	else
	{
		printf("Engine state: OFF\n");
		fflush(0);
	}

	if(vehicle_speed == 30)
		{
			AC = ON;
			room_temperature = (room_temperature * (5/4)) + 1;

	#if WITH_ENGINE_TEMP_CONTROLLER == 1
			engine_temperature_controller = ON;
			engine_temperature = (engine_temperature * (5/4)) + 1;
	#endif
		}

	if(AC == ON)
	{
		printf("AC: ON\n");
		fflush(0);
	}
	else
	{
		printf("AC == OFF\n");
		fflush(0);
	}

		printf("Vehicle Speed: %d km/hr\n", vehicle_speed);
		fflush(0);

		printf("Room Temperature: %d c\n", room_temperature);
		fflush(0);

#if WITH_ENGINE_TEMP_CONTROLLER == 1
		if(engine_temperature_controller == ON)
		{
			printf("Engine temperature controller state: ON\n");
			fflush(0);
		}
		else
		{
			printf("Engine temperature controller state: OFF\n");
			fflush(0);
		}

		printf("Engine Temperature: %d c\n",engine_temperature);
		fflush(0);
#endif

	}


/*---------------------------------------------------------------------------------------*/

int main(void){

	enum modes mode;
	char option;
	int AC, vehicle_speed, engine_temperature_controller;
	int room_temperature, engine_temperature;

	printf("Please choose an option:\n a. Turn on the vehicle engine.\n b. Turn off the vehicle engine.\n c. Quit the system.\n");
	fflush(0);
	scanf(" %c", &option);

	while(option == 'b'){
		printf("The vehicle engine is turned off.\n");
		fflush(0);
		printf("Please choose an option:\n a. Turn on the vehicle engine.\n b. Turn off the vehicle engine.\n c. Quit the system.\n");
		fflush(0);
		scanf(" %c", &option);
	}

	if(option == 'a')
	{
		turn_on_the_vehicle(&option, &AC, &vehicle_speed, &room_temperature, &engine_temperature_controller, &engine_temperature );
	}

	else if(option == 'c')
	{
		quit_the_system();
		return 0;
	}

	return 0;
}
