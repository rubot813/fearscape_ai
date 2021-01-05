#ifndef CELL_FIELD_HPP
#define CELL_FIELD_HPP

#include <stdint.h>
#include <iostream>
#include <vector>

#include "global.hpp"

// Класс описывающий поле ячеек ( bool зан¤та / свободна )
class cell_field_c {
	public:
		// Обязательно создание с размерами поля
		cell_field_c( sf::Vector2i field_size );
		~cell_field_c( void );

		// Структура настроек для поля ячеек
		struct settings_s {
			// Набор цветов заполненных ячеек
			std::vector< sf::Color > used_cells;

			// Набор цветов пустых ячеек
			std::vector< sf::Color > free_cells;
		};

		// Метод возвращает размер поля
		sf::Vector2i get_size( void );

		// Метод возвращает количество элементов в поле
		unsigned get_count( void );

		// Метод получения значения ячейки
		cell_t get( sf::Vector2i pos );

		// Метод установки значения ¤чейки
		bool set( sf::Vector2i pos, cell_t val );
		bool set( uint8_t id, cell_t val );

		// Метод преобразовывает значение поля и возвращает в виде 16-битного значения
		// Работает только если поле размера 4x4, иначе вернет false
		bool convert_to_16bit( uint16_t *val );

	private:

		// Поле = вектор
		std::vector< cell_t > _field;

		// Пазмеры поля
		sf::Vector2i _field_size;
};

#endif // CELL_FIELD_HPP
