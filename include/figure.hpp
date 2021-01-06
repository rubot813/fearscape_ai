#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "cell_field.hpp"

// Класс описывающий фигуру
class figure_c {
	public:
		figure_c( void );
		~figure_c( void );

		// Перегрузка операторов
		figure_c& operator=( const figure_c &f );

		// Перечисления типов фигур
		enum type_e {
			I	= 0,	// 0
			J,			// 1
			L,			// 2
			O,			// 3
			S,			// 4
			T,			// 5
			Z,			// 6
			unknown,	// 7 - Неизвестная фигура, для обработки ошибок
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

			projection_s( void ) {
				data.clear( );
				valid = 0;
			}

			// Функция возвращает смещение фигуры с левого края
			// Смещение - количество нулей слева
			// Вернет true если успешно
			bool get_left_offset( int8_t *offset );

			// Функция возвращает смещение фигуры с правого края
			// Смещение - количество нулей справа
			// Вернет true если успешно
			bool get_right_offset( int8_t *offset );
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
		projection_s get_horizontal_projection( cell_field_c *cell_field );

		// Метод возвращает, возможно ли положить фигуру в заданную горизонтальную позицию
		// в поле с заданным размером по горизонтали
		// ( где 0 - начальное положение фигуры, обозначает на поле y = 3 )
		// Вернет true если успешно
		// Вернет false если занятая клетка фигуры выходит за пределы поля cell_field
		bool is_can_place( uint8_t field_size_h, int8_t hor_position );

		// Метод возвращает, возможно ли положить фигуру в заданную позицию на указанном поле
		// ( где 0 - начальное положение фигуры, обозначает на поле y = 3 )
		// Значения position могут быть отрицательными
		// Вернет true если успешно
		// Вернет false если одна из ячеек на поле занята или выходит за пределы массива
		bool is_can_place( cell_field_c *cell_field, sf::Vector2i position );

		// Метод принимает поле ячеек и горизонтальную позицию для фигуры
		// ( где 0 - начальное положение фигуры, на поле y = 3 )
		// Меняет поле на поле с фигурой, упавшей на него сверху
		// Возвращает true если фигура успешно установлена
		bool place_to_cellfield( cell_field_c *cell_field, int8_t hor_position );

		// Метод накладывает фигуру на поле
		// Принимает поле и позицию, возвращает true если успешно
		// Если вернет false, значит какая то ячейка занята и поле будет испорчено
		bool apply_to_cellfield( cell_field_c *cell_field, sf::Vector2i position );

	private:
		// Тип фигуры
		type_e _type;

		// Вращение фигуры
		rotation_e _rotation;

		// Матрица содержит битовые поля для каждой фигуры в каждом состоянии вращения
		static const uint16_t _cf_bitfield_rotation[ 7 ][ 4 ];
};

#endif // FIGURE_HPP
