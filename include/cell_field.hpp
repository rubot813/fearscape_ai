#ifndef CELL_FIELD_HPP
#define CELL_FIELD_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <stdint.h>
#include <iostream>
#include <vector>

#include "config_reader.hpp"

// Класс описывающий поле ячеек ( bool зан¤та / свободна )
class cell_field_c {
	public:
		// Обязательно создание с размерами поля
		cell_field_c( sf::Vector2i field_size );
		~cell_field_c( void );

		// Перегрузка операторов
		friend bool operator==( const cell_field_c &cf_0, const cell_field_c &cf_1 );
		friend bool operator!=( const cell_field_c &cf_0, const cell_field_c &cf_1 );
		cell_field_c& operator=( const cell_field_c &cf );

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
		std::size_t get_count( void );

		// Метод получения значения ячейки
		// Если значение pos задано неверно и ячейка не существует, вернет false
		bool get( sf::Vector2i pos );

		// Методы установки значения ячейки
		bool set( sf::Vector2i pos, bool val );
		bool set( uint8_t id, bool val );

		// Метод получения значения ячейки с проверкой ее наличия
		// Возвращает существование ячейки, в value = значение, если она существует
		bool check( sf::Vector2i pos, bool *value );

		// Метод преобразовывает значение поля и возвращает в виде 16-битного значения
		// Работает только если поле размера 4x4, иначе вернет false
		bool convert_to_16bit( uint16_t *val );

	private:

		// Поле = вектор
		std::vector< bool > _field;

		// Пазмеры поля
		sf::Vector2i _field_size;
};

#endif // CELL_FIELD_HPP
