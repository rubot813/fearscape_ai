#ifndef PIXEL_FIELD_HPP
#define PIXEL_FIELD_HPP

#include "cell_field.hpp"

// Класс описывает поле, состоящее из пикселей
class pixel_field_c {
	public:
		// Обязательно создание с размерами поля
		pixel_field_c( sf::Vector2i field_size );
		~pixel_field_c( void );

		// Метод возвращает размер поля
		sf::Vector2i get_size( void );

		// Метод возвращает количество элементов в поле
		unsigned get_count( void );

		// Метод получения цвета поля
		sf::Color get( sf::Vector2i pos );

		// Метод установки цвета поля
		bool set( sf::Vector2i pos, sf::Color col );

		// Метод конвертирует поле цветов в поле ячеек
		// Принимает указатель на поле ячеек и структуру настроек конвертирования
		// Возвращает true если все успешно
		// Здесь можно добавить реализации для разных программ
		bool convert_to_cellfield( cell_field_c * cell_field, cell_field_c::settings_s * settings, unsigned up_lines_ignored = 0 );

	private:
		// Поле = вектор
		std::vector< sf::Color > _field;

		// Размеры поля
		sf::Vector2i _field_size;
};

#endif // PIXEL_FIELD_HPP
