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
			unknown,	// Неизвестная фигура, для обработки ошибок
		};

		// Перечисление вращений фигуры
		enum rotation_e {
			rt_standart = 0,	// Стандартное значение вращения для фигуры. Принято за 0 градусов
			rt_90,
			rt_180,
			rt_270				// 3
		};

		// Структура проекции фигуры
		struct projection_s {
			std::vector< bool > data;	// Данные
			bool valid;					// Флаг верности данных
		};

		// Получение типа фигуры
		type_e get_type( void );

		// Получение типа фигуры для печати
		char get_type_char( void );

		// Методы установки и получения вращения фигуры
		void set_rotation( rotation_e rot );
		rotation_e get_rotation( void );

		// Метод определения типа фигуры из cell_field ( только с вращением rt_standart )
		// Размер поля должен быть 4x4
		// Вернет true если тип определен, иначе false ( тип unknown )
		bool set_from_cell_field( cell_field_c *cell_field, cell_field_c::settings_s *settings );

		// Метод возвращает поле ячеек 4x4 для фигуры ( с учетом вращения )
		// Если тип фигуры unknown, вернет пустое поле
		cell_field_c get_cellfield( void );

		// Метод возвращает битовое поле для фигуры ( с учетом вращения )
		// Если тип фигуры unknown, вернет 0
		uint16_t get_bitfield( void );

		// Получение горизонтальной проекции для фигуры ( с учетом вращения )
		// Проходит снизу вверх по каждому столбцу, и ставит 1 если присутствует занятая ячейка
		projection_s get_horizontal_projection( void );

	private:
		// Тип фигуры
		type_e _type;

		// Вращение фигуры
		rotation_e _rotation;

		// Матрица содержит битовые поля для каждой фигуры в каждом состоянии вращения
		static const uint16_t _cf_bitfield_rotation[ 7 ][ 4 ];
};

#endif // FIGURE_HPP
