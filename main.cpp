#include "systemc.h"
#include "matrix_vector_mul.h"
#include "driver.h"
#include <sstream>

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", 10, SC_NS);
	sc_signal<bool> rst_n;
	sc_signal<sc_int<WIDTH>> mat[VEC_NUM][VEC_WIDTH], vec[VEC_WIDTH];
	sc_signal<sc_int<WIDTH * 2>> vec_o[VEC_NUM];

	sc_trace_file* fp;
	fp = sc_create_vcd_trace_file("wave");
	fp->set_time_unit(1, SC_NS);

	matrix_vector_mul dut("dut");
	dut.clk(clk);
	dut.rst_n(rst_n);
	for (int i = 0; i < VEC_NUM; i++) {
		for (int j = 0; j < VEC_WIDTH; j++) {
			dut.matrix[i][j](mat[i][j]);
		}
	}
	for (int j = 0; j < VEC_WIDTH; j++) {
		dut.vector_in[j](vec[j]);
	}
	for (int i = 0; i < VEC_NUM; i++) {
		dut.vector_out[i](vec_o[i]);
	}
	driver d("dri");
	d.clk(clk);
	d.rst_n(rst_n);
	for (int i = 0; i < VEC_WIDTH; i++) {
		for (int j = 0; j < VEC_NUM; j++) {
			d.mat[j][i](mat[j][i]);
		}
		d.vec[i](vec[i]);
	}
	std::ofstream file("vec.txt"); // 打开文件
	vec->dump(file);
	sc_trace(fp, clk, "clk");
	sc_trace(fp, rst_n, "rst_n");

	for (int i = 0; i < VEC_NUM; i++) {
		for (int j = 0; j < VEC_WIDTH; j++) {
			std::ostringstream mat_stream;
			mat_stream << "matrix(" << i << "," << j << ")";
			sc_trace(fp, mat[i][j], mat_stream.str());
			mat_stream.str("");
		}
	}
	for (int i = 0; i < VEC_WIDTH; i++) {
		std::ostringstream vec_stream;

		vec_stream << "vec(" << i << "," << ")";
		sc_trace(fp, vec[i], vec_stream.str());
		vec_stream.str("");
	}

	for (int i = 0; i < VEC_NUM; i++) {
		std::ostringstream vec_o_stream;

		vec_o_stream << "vec_o(" << i << "," << ")";
		sc_trace(fp, vec_o[i], vec_o_stream.str());
		vec_o_stream.str("");
	}
	sc_start(1000, SC_NS);

	sc_close_vcd_trace_file(fp);
	return 0;
}