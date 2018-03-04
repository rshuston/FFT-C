#
# A Trip Down Fourier Lane
#

# Clear any pre-existing variables
clear;

# Allow for immediate printf output (good for debugging)
more off;

N = 32;

two_pi_N = 2 * pi / N;

k = [0 : N - 1 ];
n = [0 : N - 1 ];

#
# Plot complex exponential points on the unit circle
#

W_N = complex(zeros(1, N));
for _k_ = 0 : N - 1
    W_N(_k_ + 1) = exp(-j * two_pi_N * _k_);
endfor

circle = complex(zeros(1,100));
for _k_ = 0 : 99
    circle(_k_ + 1) = exp(-j * _k_ * 2 * pi / 100);
endfor

figure(1);
plot (real(circle), imag(circle), "k", real(W_N), imag(W_N), "*");
axis ([-1, 1, -1, 1], "square");
for _k_ = 0 : N - 1
    line([0 real(W_N(_k_+1))], [0 imag(W_N(_k_+1))], "linestyle", "--", "color", "b", "linewidth", 0.5);
endfor
line([-1 1], [0 0], "linestyle", "-", "color", "k", "linewidth", 2);
line([0 0], [-1 1], "linestyle", "-", "color", "k", "linewidth", 2);
set(gca(), "xgrid", "on", "ygrid", "on");
#set(gca(), "xtick", -1 : 0.1 : 1);
#set(gca(), "ytick", -1 : 0.1 : 1);
title ("Complex Exponential Points");

#
# Unit pulse function from 0 <= t < 1
#

T_s = 0.2;
T_d = 1.0;
f_t = zeros(1, length(k));
f_t(1 : T_d / T_s) = 1;

figure(2);
plot(n, f_t, "-x");
axis([0, N]);
set(gca(), "xgrid", "on", "ygrid", "on");
title ("f(t)");

#
# DFT
#

F_w = complex(zeros(1, length(f_t)));
for _n_ = n
    sum = complex(0);
    for _k_ = k
        sum = sum + f_t(_k_ + 1) * exp(-j * two_pi_N * _n_ * _k_);
    endfor
    F_w(_n_ + 1) = sum;
endfor

#
# IDFT
#

#f_t_r = complex(zeros(1, length(F_w)));
#for _k_ = k
#    sum = complex(0);
#    for _n_ = n
#        sum = sum + F_w(_n_ + 1) * exp(j * two_pi_N * _k_ * _n_);
#    endfor
#    f_t_r(_k_ + 1) = sum / N;
#endfor

#
# Plots
#

F_w_mag = abs(F_w);
max_F_W_mag = ceil(max(F_w_mag));

figure(3);
plot(n, F_w_mag, "-x");
axis([0, N, 0, max_F_W_mag]);
set(gca(), "xgrid", "on", "ygrid", "on");
title ("|F(w)|");

figure(4);
plot(real(F_w), imag(F_w), "-x");
axis([-max_F_W_mag, max_F_W_mag, -max_F_W_mag, max_F_W_mag], "square");
line([-max_F_W_mag max_F_W_mag], [0 0], "linestyle", "-", "color", "k", "linewidth", 2);
line([0 0], [-max_F_W_mag max_F_W_mag], "linestyle", "-", "color", "k", "linewidth", 2);
set(gca(), "xgrid", "on", "ygrid", "on");
set(gca(), "xtick", -max_F_W_mag : max_F_W_mag / 5 : max_F_W_mag);
set(gca(), "ytick", -max_F_W_mag : max_F_W_mag / 5 : max_F_W_mag);
title ("Complex plot of F(w)");


filename = "dft-results.txt";
fid = fopen (filename, "w");

fprintf(fid, "complex_f f_t[%d] = {\n", N);
for _k_ = [1 : N]
    fprintf(fid, "    { %ff , 0.0f },\n", f_t(_k_));
endfor
fprintf(fid, "};\n");

fprintf(fid, "complex_f F_w[%d] = {\n", N);
for _k_ = [1 : N]
    fprintf(fid, "    { %ff , %ff },\n", real(F_w(_k_)), imag(F_w(_k_)));
endfor
fprintf(fid, "};\n");

fclose (fid);

