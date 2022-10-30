#include <iostream>
#include <string>
#include <sstream>

int main() {
	int temperature_outside;
	int temperature_inside;
	char moving_char;
	char lights_inside_char;
	char continue_program;
	int light_temperature = 5000;

	enum switches {
		LIGHTS_INSIDE = 1,
		LIGHTS_OUTSIDE = 2,
		HEATERS = 4,
		WATER_PIPE_HEATING = 8,
		CONDITIONER = 16,
		MOVING_OUTSIDE = 32
	};
	int switches_state = 0;
	
	for (int i = 0; i < 24; i++) {
		if (i < 10)
			std::cout << "Time is: 0" << i << ":00" << std::endl;
		else
			std::cout << "Time is: " << i << ":00" << std::endl;

		std::cout << "Input sensors values "
					<< "(temperature outside/temperature inside"
					<< "/moving outside(y/n)/lights inside(y/n)):" << std::endl;
		/*
		std::string buffer;
		std::cin >> buffer;
		std::stringstream buffer_stream(buffer);
		buffer_stream >> temperature_outside >> temperature_inside >> moving_char >> lights_inside_char;
		*/
		std::cin >> temperature_outside >> temperature_inside >> moving_char >> lights_inside_char;

		std::cout << "----------------------------" << std::endl;

		if (moving_char == 'y') {
			if (!(switches_state & MOVING_OUTSIDE))
				switches_state |= MOVING_OUTSIDE;
		} else {
			if (switches_state & MOVING_OUTSIDE)
				switches_state &= ~(MOVING_OUTSIDE);
		}

		if (lights_inside_char == 'y') {
			if (!(switches_state & LIGHTS_INSIDE)) {
				switches_state |= LIGHTS_INSIDE;
				std::cout << "Lights inside house is ON with temperature "
						  << light_temperature << "K." << std::endl;
			}
		} else {
			if (switches_state & LIGHTS_INSIDE) {
				switches_state &= ~(LIGHTS_INSIDE);
				std::cout << "Lights inside house is OFF." << std::endl;
			}
		}

		if (i >= 0 && i <= 16)
			light_temperature = 5000;
		else if (i == 17)
			light_temperature = 4425;
		else if (i == 18)
			light_temperature = 3850;
		else if (i == 19)
			light_temperature = 3275;
		else if (i >= 20)
			light_temperature = 2700;

		if (temperature_outside < 0) {
			if (!(switches_state & WATER_PIPE_HEATING)) {
				switches_state |= WATER_PIPE_HEATING;
				std::cout << "Water pipe heating is ON." << std::endl;
			}
		}
		else if (temperature_outside > 5) {
			if (switches_state & WATER_PIPE_HEATING) {
				switches_state &= ~WATER_PIPE_HEATING;
				std::cout << "Water pipe heating is OFF." << std::endl;
			}
		}

		if (!(switches_state & MOVING_OUTSIDE) && (i < 5 || i > 16)) {
			if (!(switches_state & LIGHTS_OUTSIDE)) {
				switches_state |= LIGHTS_OUTSIDE;
				std::cout << "Lights outside is ON." << std::endl;
			}
		} else {
			if (switches_state & LIGHTS_OUTSIDE) {
				switches_state &= ~LIGHTS_OUTSIDE;
				std::cout << "Lights outside is OFF." << std::endl;
			}
		}

		if (temperature_inside < 22) {
			if (!(switches_state & HEATERS)) {
				switches_state |= HEATERS;
				std::cout << "Heaters is ON." << std::endl;
			}
		}
		else if (temperature_inside >= 25) {
			if (switches_state & HEATERS) {
				switches_state &= ~HEATERS;
				std::cout << "Heaters is OFF." << std::endl;
			}
		}

		if (temperature_inside >= 30) {
			if (!(switches_state & CONDITIONER)) {
				switches_state |= CONDITIONER;
				std::cout << "Conditioners is ON." << std::endl;
			}
		}
		else if (temperature_inside <= 25) {
			if (switches_state & CONDITIONER) {
				switches_state &= ~CONDITIONER;
				std::cout << "Conditioners is OFF." << std::endl;
			}
		}

		std::cout << "----------------------------" << std::endl;

		if (i == 23) {
			std::cout << "The day is over. You want to continue program? (y/n):";
			std::cin >> continue_program;

			if (continue_program == 'y') {
				i = 0;
			} else {
				std::cout << "----------------------------" << std::endl;
				std::cout << "Exit program. Good by." << std::endl;
				return 0;
			}
		}
	}
}
