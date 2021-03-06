#ifndef PIXEL_FIELD_HPP
#define PIXEL_FIELD_HPP

#include "cell_field.hpp"

// Класс описывает поле, состоящее из пикселей
class pixel_field_c {
	public:
		// Обязательно создание с размерами поля
		pixel_field_c( sf::Vector2i field_size );
		~pixel_field_c( void );

		// Перегрузка операторов
		friend bool operator==( const pixel_field_c &pf_0, const pixel_field_c &pf_1 );
		friend bool operator!=( const pixel_field_c &pf_0, const pixel_field_c &pf_1 );
		pixel_field_c& operator=( const pixel_field_c &pf );

		// Метод возвращает размер поля
		sf::Vector2i get_size( void );

		// Метод возвращает количество элементов в поле
		std::size_t get_count( void );

		// Метод получения цвета поля
		sf::Color get( sf::Vector2i pos );

		// Метод установки цвета поля
		bool set( sf::Vector2i pos, sf::Color col );

		// Метод конвертирует поле цветов в поле ячеек
		// Возвращает true если все успешно
		// Здесь можно добавить реализации для разных программ
		bool convert_to_cellfield( cell_field_c *cell_field, unsigned up_lines_ignored = 0 );

	private:
		// Поле = вектор
		std::vector< sf::Color > _field;

		// Размеры поля
		sf::Vector2i _field_size;
};

#endif // PIXEL_FIELD_HPP
