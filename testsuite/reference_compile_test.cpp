#include <reference.hpp>

int main()
{
	log_exp_base = 1.000001;

	std::vector<dna_array<double, 5>> E_p{
		// A     C     G     T
		{ 1.00, 0.00, 0.00, 0.00 }, // 0
		{ 1.00, 0.00, 0.00, 0.00 }, // 1
		{ 0.40, 0.00, 0.25, 0.35 }, // 2
		{ 0.00, 0.38, 0.62, 0.00 }, // 3
		{ 0.00, 0.00, 1.00, 0.00 }, // 4
		{ 0.00, 0.00, 1.00, 0.00 }, // 5
		{ 0.53, 0.00, 0.00, 0.47 }, // 6
		{ 0.65, 0.35, 0.00, 0.00 }, // 7
		{ 0.65, 0.35, 0.00, 0.00 }, // 8
	};
	std::vector<double> M_D_p{
		0.00, // 0 -> 1
		0.00, // 1 -> 2
		0.35, // 2 -> 3
		0.38, // 3 -> 4
		0.00, // 4 -> 5
		0.00, // 5 -> 6
		0.00, // 6 -> 7
		0.00 // 7 -> 8
	};
	std::vector<double> D_D_p{
		0.00, // 0 -> 1
		0.00, // 1 -> 2
		0.00, // 2 -> 3
		0.00, // 3 -> 4
		0.98, // 4 -> 5
		0.42, // 5 -> 6
		0.00, // 6 -> 7
		0.00 // 7 -> 8
	};

	double min_allele_freq = 0.05;
	double substitution_rate = 0.005;

	double gap_open = 0.005;
	double gap_extend = 0.19;

	double insert_open = 0.17;
	double insert_extend = 0.18;

	double left_clip_open = 0.01;
	double left_clip_extend = 0.90;
	double right_clip_open = 0.01;
	double right_clip_extend = 0.90;

	reference_genome<double> fp_pp;
	fp_pp.set_parameters(
		decltype(E_p)(E_p),
		decltype(M_D_p)(M_D_p),
		decltype(D_D_p)(D_D_p),
		background_rates{
			min_allele_freq,
			substitution_rate,
			gap_open,
			gap_extend,
			insert_open,
			insert_extend,
			1.0 / 11,
			left_clip_open,
			left_clip_extend,
			right_clip_open,
			right_clip_extend },
		true);
	fp_pp.display_parameters(std::cout);

	reference_genome<int32_t> int_pp;
	int_pp.set_parameters(
		decltype(E_p)(E_p),
		decltype(M_D_p)(M_D_p),
		decltype(D_D_p)(D_D_p),
		background_rates{
			min_allele_freq,
			substitution_rate,
			gap_open,
			gap_extend,
			insert_open,
			insert_extend,
			1.0 / 11,
			left_clip_open,
			left_clip_extend,
			right_clip_open,
			right_clip_extend },
		true);
	int_pp.display_parameters(std::cout);

	reference_genome<double> fp_pp_convert1(int_pp);
	reference_genome<int32_t> int_pp_convert2(fp_pp_convert1);

	std::cout << "Displaying parameters for doubly converted parameter pack:\n";
	fp_pp_convert1.display_parameters(std::cout);
	int_pp_convert2.display_parameters(std::cout);
	return 0;
}