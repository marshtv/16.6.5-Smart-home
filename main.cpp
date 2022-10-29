#include <iostream>
#include <string>
#include <sstream>

int main() {
	int temperature_outside;
	int temperature_inside;
	char moving_char;
	bool is_moving_outside = false;
	char lights_inside_char;
	bool is_lights_inside = false;
	char continue_program;
	int light_temperature = 5000;

	enum switches {
		LIGHTS_INSIDE = 1,
		LIGHTS_OUTSIDE = 2,
		HEATERS = 4,
		WATER_PIPE_HEATING = 8,
		CONDITIONER = 16
	};
	int switches_state;
	switches_state &= ~LIGHTS_INSIDE;
	switches_state &= ~WATER_PIPE_HEATING;
	switches_state &= ~LIGHTS_OUTSIDE;
	switches_state &= ~HEATERS;
	switches_state &= ~CONDITIONER;

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

		if (moving_char == 'y')
			is_moving_outside = true;
		else
			is_moving_outside = false;

		if (lights_inside_char == 'y')
			is_lights_inside = true;
		else
			is_lights_inside = false;

		if (i <= 16)
			light_temperature = 5000;
		else if (i == 17)
			light_temperature = 4425;
		else if (i == 18)
			light_temperature = 3850;
		else if (i == 19)
			light_temperature = 3275;
		else if (i == 20)
			light_temperature = 2700;

		std::cout << "----------------------------" << std::endl;

		if (temperature_outside < 0) {
			if (switches_state & WATER_PIPE_HEATING) {
				std::cout << "Water pipe heating is ON." << std::endl;
				switches_state |= WATER_PIPE_HEATING;
			}
		} else if (temperature_outside > 5) {
			if (switches_state & WATER_PIPE_HEATING) {
				std::cout << "Water pipe heating is OFF." << std::endl;
				switches_state &= ~WATER_PIPE_HEATING;
			}
		}

		if (is_moving_outside && (i < 5 || i > 16)) {
			if (switches_state & ~LIGHTS_OUTSIDE) {
				std::cout << "Lights in garden is ON." << std::endl;
				switches_state |= LIGHTS_OUTSIDE;
			}
		} else {
			if (switches_state & LIGHTS_OUTSIDE) {
				std::cout << "Lights in garden is OFF." << std::endl;
				switches_state &= ~LIGHTS_OUTSIDE;
			}
		}

		if (temperature_inside < 22) {
			if (switches_state & ~HEATERS) {
				std::cout << "Heaters is ON." << std::endl;
				switches_state |= HEATERS;
			}
		} else if (temperature_inside >= 25) {
			if (switches_state & HEATERS) {
				std::cout << "Heaters is OFF." << std::endl;
				switches_state &= ~HEATERS;
			}
		}

		if (temperature_inside >= 30) {
			if (switches_state & ~CONDITIONER) {
				std::cout << "Conditioner is ON." << std::endl;
				switches_state |= CONDITIONER;
			}
		} else if (temperature_inside <= 25) {
			if (switches_state & CONDITIONER) {
				std::cout << "Conditioner is OFF." << std::endl;
				switches_state &= ~CONDITIONER;
			}
		}

		if (is_lights_inside) {
			if (switches_state & ~LIGHTS_INSIDE) {
				std::cout << "Lights inside house is ON with temperature "
						  << light_temperature << "K." << std::endl;
				switches_state |= LIGHTS_INSIDE;
			}
		} else {
			if (switches_state & LIGHTS_INSIDE) {
				std::cout << "Lights inside house is OFF." << std::endl;
				switches_state &= ~LIGHTS_INSIDE;
			}
		}

		std::cout << "----------------------------" << std::endl;

		if (i == 23) {
			std::cout << "The day is over. You want to continue program? (y/n):";
			std::cin >> continue_program;

			if (continue_program == 'y') {
				i = 0;
			} else {
				std::cout << "Exit program. Good by." << std::endl;
				return 0;
			}
		}
	}
}
