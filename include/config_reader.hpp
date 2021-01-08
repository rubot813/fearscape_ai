#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

/*
	Класс читает настройки из файлов:
	config.txt - общие, в кодировке UTF-8
	config_windowname.txt - название окна тетриса, в кодировке CP1251
	config_figure_colors.txt - список цветов в RGB, обозначающих фигур
	config_back_colors.txt	- список цветов в RGB, обозначающих фон

	Порядок переменных для config.txt, построчно :
	Координаты начала поля в пикселях x
	Координаты начала поля в пикселях y
	Размер поля в ячейках x
	Размер поля в ячейках y
	Координаты начала фигуры в пикселях x
	Координаты начала фигуры в пикселях y
	Размер фигуры в ячейках x
	Размер фигуры в ячейках y
	Размер фигуры в пикселях
	Начальная позиция фигур на поле по горизонтали
	Общее количество фигур
	Время удержания кнопки при эмуляции нажатия ( мсек )
*/

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Для быстрого обращения к конфигу
#define config config_reader_c::get_instance()->get()

class config_reader_c {	// Singletone
	public:
		struct config_s {
			std::string window_name;					// Имя окна программы, в которой запущен тетрис
			sf::Vector2i screen_start_field;				// Координаты начала поля в пикселях
			sf::Vector2i screen_start_figure;			// Координаты начала фигуры в пикселях
			sf::Vector2i field_size;					// Размер поля в ячейках ( 10x20 )
			sf::Vector2i figure_cell_size;				// Размер фигуры в ячейках ( 4x4 )
			std::size_t screen_figure_size;				// Размер фигуры в пикселях
			uint8_t figure_count;						// Общее количество фигур ( 7 )
			uint8_t figure_start_pos;					// Начальная позиция фигур на поле по горизонтали ( 3 )
			std::vector< sf::Color > *figure_colors;	// Указатель на контейнер цветов фигур
			std::vector< sf::Color > *back_colors;		// Указатель на контейнер цветов фона
			long kp_time;								// Время удержания кнопки при эмуляции нажатия ( мсек )
		};

		static config_reader_c* get_instance( void ) {
			static config_reader_c config_reader_instance;
			return &config_reader_instance;
		}

		// Метод чтения конфиг файлов, вернет true если успешно
		bool read( void );

		// Метод возвращает указатель на структуру настроек
		// Пустая структура если настройки не прочитаны
		config_s* get( void );

	private:
		// Запрет операций класса
		config_reader_c( void ) { };
		~config_reader_c( void ) { };
		config_reader_c( const &ex ) = delete;
		config_reader_c& operator=( const config_reader_c& ) = delete;

		// Структура настроек
		config_s _config;

		// Контейнер цветов фигур
		std::vector< sf::Color > _figure_colors;

		// Контейнер цветов фона
		std::vector< sf::Color > _back_colors;
};

#endif // CONFIG_READER_HPP
