#include "prism.h"

prism::prism(unsigned int seed, double l_1, double l_2, double a, double s_t, double a_i, double b_i, double t_i) : rand_gen{seed}, lambda_1{l_1}, lambda_2{l_2}, alpha{a}, sigma_theta{s_t}, A_i{a_i}, B_i{b_i}, theta_0_i{t_i}
{
    n_1_i = std::sqrt(A_i + B_i / std::pow(lambda_1, 2));
    n_2_i = std::sqrt(A_i + B_i / std::pow(lambda_2, 2));

    delta_1_i = 2. * std::asin(n_1_i * std::sin(alpha / 2.)) - alpha;
    delta_2_i = 2. * std::asin(n_2_i * std::sin(alpha / 2.)) - alpha;

    theta_1_i = theta_0_i + delta_1_i;
    theta_2_i = theta_0_i + delta_2_i;
}

void prism::measures()
{
    theta_0_m = rand_gen.gauss_bm(theta_0_i, sigma_theta);
    theta_1_m = rand_gen.gauss_bm(theta_1_i, sigma_theta);
    theta_2_m = rand_gen.gauss_bm(theta_2_i, sigma_theta);
}

void prism::analysis()
{
    delta_1_m = theta_1_m - theta_0_m;
    delta_2_m = theta_2_m - theta_0_m;

    n_1_m = std::sin((delta_1_m + alpha) / 2.) / std::sin(alpha / 2.);
    n_2_m = std::sin((delta_2_m + alpha) / 2.) / std::sin(alpha / 2.);

    A_m = (std::pow(lambda_2 * n_2_m, 2) - std::pow(lambda_1 * n_1_m, 2)) / (std::pow(lambda_2, 2) - std::pow(lambda_1, 2));
    B_m = (std::pow(n_2_m, 2) - std::pow(n_1_m, 2)) / (std::pow(lambda_2, -2) - std::pow(lambda_1, -2));
}
