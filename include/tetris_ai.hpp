#ifndef TETRIS_AI_HPP
#define TETRIS_AI_HPP

#include <ctime>		// ai_calc_random
#include "stdlib.h"
#include <chrono>
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

		// Метод возвращает значение высот поля
		height_s* get_height( void );

		// Метод возвращает сумму высот поля
		std::size_t	get_height_sum( void );

		// Метод возвращает количество отверстий в поле
		uint8_t	get_holes_count( void );

		// Метод возвращает имя алгоритма AI, который вызывали последний раз
		std::string* get_ai_alg_name( void );

		// Метод возвращает длительность работы последнего алгоритма AI в миллисекундах
		std::chrono::milliseconds * get_ai_calc_time( void );

		// Алгоритм просто кладет фигуру вниз без стратегии
		// Для тестов
		move_variant_s ai_alg_simple_placer( cell_field_c *cell_field, figure_c *figure );

		// Алгоритм просто кладет фигуру в случайном месте со случайным вращением
		// Для тестов
		move_variant_s ai_alg_random( cell_field_c *cell_field, figure_c *figure );

		// Алгоритм просчитывает все варианты постановки фигуры, и ищет наименьший по высоте без создания отверстий
		// Если такой ход невозможен, возвращает вариант с наименьшей суммой высот высотой
		move_variant_s ai_alg_bm_noholes( cell_field_c *cell_field, figure_c *figure );

	private:

		// Метод рассчитывает значения высоты для заданного поля
		height_s _calculate_height( cell_field_c *cell_field );

		// Метод считает количество отверстий в заданном поле
		uint8_t _calculate_holes( cell_field_c *cell_field );

		// Метод считает количество заполненных горизонтальных линий в заданном поле
		uint8_t _calculate_lines( cell_field_c *cell_field );

		// Высота последнего посчитанного поля ( 0 - нет блока, 1 - n количество блоков по вертикали )
		// Размер зависит от ширины поля cell_field_c
		// Обновляется после вызовов методов ai_calc_
		height_s _height;

		// Количество отверстий последнего посчитанного поля
		// Отверстие - пустая клетка над которой есть одна или более занятых
		uint8_t	_holes;

		// Имя алгоритма AI, который вызывали последний раз
		std::string _ai_alg_name;

		// Длительность работы последнего алгоритма AI в миллисекундах
		std::chrono::milliseconds _calc_time;
};

#endif // TETRIS_AI_HPP
