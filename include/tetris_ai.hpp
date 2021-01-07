#ifndef TETRIS_AI_HPP
#define TETRIS_AI_HPP

#include <ctime>		// ai_calc_random
#include <chrono>
#include <algorithm>
#include "stdlib.h"

#include "pixel_field.hpp"
#include "figure.hpp"

/*
	Класс описывает логику искусственного интеллекта для игры в тетрис и подобные
	Его задача - получить текущую фигуру и состояние поля, и в соответствии с алгоритмом выдать структуру move_variant_s
	которая прямо описывает сколько и каких кнопок нажать чтобы положить фигуру
*/

class tetris_ai_c {
	public:
		tetris_ai_c( void );
		~tetris_ai_c( void );

		// Структура варианта перемещения фигуры
		struct move_variant_s {
			// Позиция относительно начального положения фигуры ( на верху экрана и по центру, y == 3 )
			// Положительное значение - перемещение направо, отрицательное значение - перемещение налево
			// > 0 перемещение на pos клеток направо
			// < 0 перемешение на -pos клеток налево
			int8_t	position;

			// Вращение фигуры
			figure_c::rotation_e rotation;
		};

		// Структура высоты поля
		struct height_s {
			std::vector< uint8_t > data;	// Данные
			bool valid;						// Флаг верности данных
		};

		// Структура отладочной информации по работе каждого алгоритма
		struct ai_debug_data_s {
			height_s					height;			// Высота поля
			std::size_t					height_sum;		// Сумма высот поля
			uint8_t						holes_count;	// Количество отверстий
			std::string					alg_name;		// Имя алгоритма
			std::chrono::milliseconds	calc_time;		// Длительность работы алгоритма
		};

		// Алгоритм просто кладет фигуру вниз без стратегии
		// Для тестов
		move_variant_s ai_alg_simple_placer( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug );

		// Алгоритм просто кладет фигуру в случайном месте со случайным вращением
		// Для тестов
		move_variant_s ai_alg_random( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug );

		// Алгоритм просчитывает все варианты постановки фигуры, и ищет наименьший вариант постановки по высоте без создания отверстий
		// Если такой ход невозможен, возвращает вариант с наименьшей суммой высот высотой
		move_variant_s ai_alg_bm( cell_field_c *cell_field, figure_c *figure, ai_debug_data_s *debug );

	private:

		// Структура очков. Чем больше значение score - тем лучше ход
		struct _score_s {
			float score;
			tetris_ai_c::move_variant_s move_variant;

			// Для отладки
			// = = = =
			cell_field_c *cf;
			_score_s( void ) {
				cf = new cell_field_c( sf::Vector2i( field_size_x_c, field_size_y_c ) );
			}
			// = = = =
		};

		// Метод считает значения высоты для заданного поля
		height_s _calculate_height( cell_field_c *cell_field );

		// Метод считает количество отверстий в заданном поле
		uint8_t _calculate_holes( cell_field_c *cell_field );

		// Метод считает количество заполненных горизонтальных линий в заданном поле
		uint8_t _calculate_lines( cell_field_c *cell_field );

		// Метод возвращает сумму высот заданного поля
		std::size_t	_calculate_height_sum( height_s *height );
};

#endif // TETRIS_AI_HPP
