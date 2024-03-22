#include "systemc.h"

#define WIDTH 32
#define VEC_WIDTH 4
#define VEC_NUM 8

#ifndef VECTOR_MUL
#define VECTOR_MUL

SC_MODULE(vector_mul) {
	sc_in<bool> clk, rst_n;
	sc_in<sc_int<WIDTH>> vec1[VEC_WIDTH], vec2[VEC_WIDTH];
	sc_out<sc_int<WIDTH * 2>> vec_o;

	void compute(void) {
		if (rst_n.read() == false) {
			vec_o.write(0);
			return;
		}
		long long sum = 0;
		for (int i = 0; i < VEC_WIDTH; i++) {
			sum += vec1[i].read() * vec2[i].read();
		}
		vec_o.write(sum);
	};

	SC_CTOR(vector_mul) {
		SC_METHOD(compute);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
	};
};


#endif