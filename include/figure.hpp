#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "cell_field.hpp"

// Класс описывающий фигуру
class figure_c {
	public:
		figure_c( void );
		~figure_c( void );

		// Перечисления типов фигур
		enum type_e {
			I	= 0,	// 0
			J,
			L,
			O,
			S,
			T,
			Z,			// 7
			unknown,	// Неизвестная фигура
		};

		// Получение типа фигуры
		type_e get_type( void );

		// Получение типа фигуры для печати
		char get_type_char( void );

		// Метод определения типа фигуры из cell_field
		// Размер поля должен быть 4x4
		// Вернет true если тип определен, иначе false ( тип unknown )
		bool set_from_cell_field( cell_field_c *cell_field, cell_field_c::settings_s *settings );

		// Метод возвращает поле ячеек 4x4 для фигуры с вращением rotation ( 0..4 )
		cell_field_c get_cell_field_rotated( uint8_t rotation );

		// Метод возвращает битовое поле для фигуры с вращением rotation ( 0..4 )
		uint16_t get_bitfield_rotated( uint8_t rotation );

	private:
		// Тип фигуры
		type_e _type;

		// Матрица содержит битовые поля для каждой фигуры в каждом состоянии вращения
		static const uint16_t _cf_bitfield_rotation[ 7 ][ 4 ];
};

#endif // FIGURE_HPP
