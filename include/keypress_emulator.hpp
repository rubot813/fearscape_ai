#ifndef KEYPRESS_EMULATOR_HPP
#define KEYPRESS_EMULATOR_HPP

#include <windows.h> // HWND
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>

#include "tetris_ai.hpp"

/*
	Класс эмулирует последовательное нажатие кнопок в окне другого процесса
	Его задача - получить структуру tetris::move_variant_s и преобразовать нужную позицию и вращение фигуры
	в очередь кнопок, и сэмулировать их через задержку
	Работает в отдельном потоке
*/
class keypress_emulator {
	public:
		// Конструктор с указанием задержки между нажатиями кнопок и хэндла окна, которому отправлять события
		keypress_emulator( std::chrono::milliseconds key_press_delay, HWND window_handler );
		~keypress_emulator( void );

		// Метод добавления задачи в очередь кнопок
		void add_keypress_to_queue( tetris_ai_c::move_variant_s move_variant );

		// Метод возвращает количество оставшихся кнопок в очереди
		std::size_t get_keyqueue_count( void );

	private:
		// Метод задачи класса
		void _task( void );

		// Значение задержки между нажатиями кнопок в миллисекундах
		std::chrono::milliseconds _key_press_delay;

		// Указатель на экземпляр потока класса
		std::thread	*_thread;

		// Очередь кнопок. WPARAM - параметр с id кнопки для windows
		std::queue< WPARAM > _key_queue;

		// Мьютекс потока для блокировки _key_queue
		std::mutex	_thread_mutex;

		// Хэндл окна, которому отправлять события
		HWND		_window_handler;
};

#endif // KEYPRESS_EMULATOR_HPP
