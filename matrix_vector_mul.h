#include "systemc.h"
#include "vector_mul.h"
#include <sstream>

SC_MODULE(matrix_vector_mul) {
	sc_in<bool> clk, rst_n;
	sc_in<sc_int<WIDTH>> matrix[VEC_NUM][VEC_WIDTH];
	sc_in<sc_int<WIDTH>> vector_in[VEC_WIDTH];
	sc_out<sc_int<WIDTH * 2>> vector_out[VEC_NUM];

	vector_mul* pe[VEC_NUM];

	SC_CTOR(matrix_vector_mul) {
		std::ostringstream pe_name;
		for (int i = 0; i < VEC_NUM; i++) {
			pe_name << "pe" << i;
			pe[i] = new vector_mul(pe_name.str().c_str());
			pe[i]->clk(clk);
			pe[i]->rst_n(rst_n);
			for (int j = 0; j < VEC_WIDTH; j++) {
				pe[i]->vec1[j](matrix[i][j]);
				pe[i]->vec2[j](vector_in[j]);
			}
			pe[i]->vec_o(vector_out[i]);
			pe_name.str("");
		}
	};
};