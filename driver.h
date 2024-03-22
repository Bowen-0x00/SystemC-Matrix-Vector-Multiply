#include "vector_mul.h"

SC_MODULE(driver) {
	sc_in<bool> clk;
	sc_out<bool> rst_n;
	sc_out<sc_int<WIDTH>> mat[VEC_NUM][VEC_WIDTH];
	sc_out<sc_int<WIDTH>> vec[VEC_WIDTH];

	void generate_vec(void) {
		for (int i = 0; i < VEC_WIDTH; i++) {
			std::cout << "rand" << rand() % ((int)pow(2, WIDTH) - 1) << endl;
			for (int j = 0; j < VEC_NUM; j++) {
				mat[j][i].write(rand() % ((int)pow(2, WIDTH) - 1));
			}
			vec[i].write(rand() % ((int)pow(2, WIDTH) - 1));
		}
		
		while (1) {
			wait();
			for (int i = 0; i < VEC_WIDTH; i++) {
				for (int j = 0; j < VEC_NUM; j++) {
					mat[j][i].write(rand() % ((int)pow(2, WIDTH) - 1));
				}
				vec[i].write(rand() % ((int)pow(2, WIDTH) - 1));
			}
		}
	};

	void generate_reset(void) {
		rst_n.write(1);
		wait(1, SC_NS);
		rst_n.write(0);
		wait(1, SC_NS);
		rst_n.write(1);
	};

	SC_CTOR(driver) {
		SC_THREAD(generate_vec);
		sensitive_neg << clk;
		SC_THREAD(generate_reset);
	};
};