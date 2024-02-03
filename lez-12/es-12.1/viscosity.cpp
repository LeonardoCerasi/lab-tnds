#include "viscosity.h"

viscosity::viscosity(unsigned int seed, double rho, double rho_0, double eta, double radius, double x_1, double x_2, double s_t, double s_x, double s_r) : rand_gen{seed}, ρ{rho}, ρ0{rho_0}, η_i{eta}, r_i{radius}, x1_i{x_1}, x2_i{x_2}, σ_t{s_t}, σ_x{s_x}, σ_r{s_r}
{
    Δt_i = (x2_i - x1_i) * 9 * η_i / (2 * r_i * r_i * g * (ρ - ρ0));
}

void viscosity::measure()
{
    Δt_m = rand_gen.gauss_bm(Δt_i, σ_t);
    x1_m = rand_gen.gauss_bm(x1_i, σ_x);
    x2_m = rand_gen.gauss_bm(x2_i, σ_x);
    r_m = rand_gen.gauss_bm(r_i, σ_r);
}

void viscosity::analysis()
{
    η_m = 2 * r_m * r_m * g * (ρ - ρ0) * Δt_m / (9 * (x2_m - x1_m));
}
