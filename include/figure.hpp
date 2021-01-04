#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "cell_field.hpp"

// ����� ����������� ������
class figure_c {
	public:
		figure_c( void );
		~figure_c( void );

		// ������������ ����� �����
		enum type_e {
			unknown = 0,	// ����������� ������
			I,				// �����
			J,
			L,
			O,
			S,
			T,
			Z	// 7
		};

		// ����� ����������� ���� ������ �� cell_field
		// ������ ���� ������ ���� 4x4
		// ������ true ���� ��� ���������, ����� false ( ��� unknown )
		bool set_from_cell_field( cell_field_c *cell_field,settings_s *settings );

		// ��������� ���� ������
		type_e get_type( void );
		char get_type_char( void );

	private:
		// ��� ������
		type_e _type;
};

#endif // FIGURE_HPP
