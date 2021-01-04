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
			unknown = 0,	// Неизвестная фигура
			I,				// ПАЛКА
			J,
			L,
			O,
			S,
			T,
			Z	// 7
		};

		// Метод определения типа фигуры из cell_field
		// Размер поля должен быть 4x4
		// Вернет true если тип определен, иначе false ( тип unknown )
		bool set_from_cell_field( cell_field_c *cell_field,settings_s *settings );

		// Получение типа фигуры
		type_e get_type( void );
		char get_type_char( void );

	private:
		// Тип фигуры
		type_e _type;
};

#endif // FIGURE_HPP
