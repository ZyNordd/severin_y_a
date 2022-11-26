#include <vector>
#include <matplot/matplot.h>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <set>
#include <unordered_set>

std::vector<int> N{ 16, 160, 1600, 3200, 6400,  12800, 16000,
19200, 22400, 25600, 28800, 32000, 35200, 38400, 41600, 44800, 48000,
51200, 54400, 57600, 60800, 64000, 67200, 70400, 73600, 76800, 80000,
83200, 86400, 89600, 92800, 96000, 99200, 102400, 105600, 108800, 112000,
115200, 118400, 121600, 124800, 128000, 131200, 134400, 137600, 140800,
144000, 147200, 150400, 153600, 156800, 160000, 163200, 166400, 169600,
172800, 176000, 179200, 182400, 185600, 188800, 192000, 195200, 198400}; 

void f1_reading(int& n, std::vector<int>& data, std::ifstream& fin) {
    fin >> n;
    for (int i = 0; i < n; i += 1) {
        fin >> data[i];
    }
}

void f2_reading(int& n, std::vector<int>& data, std::ifstream& fin) {
    fin >> n;
    for (int i = 0; i < n; i += 1) {
        fin >> data[i];
    }
}

void f1_calculations(int& n, std::vector<int>& data) {
    std::vector<int> as(200001, -1);
    for (int i = 0; i < n; i += 1) {
        as[data[i]] = n - i - 1;
    }
    std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end())) << "\n";
}

void f2_calculations(int& n, std::vector<int>& data) {
    std::unordered_set<int> unique;
    unique.reserve(200000);
    int idx_unique = n;
    for (int i = n - 1; 0 <= i; i -= 1) {
        if (!unique.contains(data[i])) {
            idx_unique = data[i];
            unique.insert(idx_unique);
        }
    }
   std::cout << idx_unique;
}

double timer_read (int& n, std::vector<int>& input, std::ifstream& fin, void (*func)(int& a, std::vector<int>& b, std::ifstream& c))    {
    auto reading_begin = std::chrono::steady_clock::now();
    func(n, input, fin);
    auto reading_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> read_time = reading_end - reading_begin;
    return read_time.count();
}

double timer_calc (int& n, std::vector<int>& input,  void (*func)(int& a, std::vector<int>& b)) {
    auto calculations_begin = std::chrono::steady_clock::now();
    func(n, input);
    auto calculations_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> calculations_time = calculations_end - calculations_begin;
    return calculations_time.count();
}


void generate_data(std::string f, int n) {
    std::ofstream fout;
    fout.open(f);
    fout << n << '\n';
    for (int i = 0; i < n; ++i) fout << rand() % n + 1 << " ";
    fout.close();
}

int main() {

    std::vector<double> t_calc1;
    std::vector<double> t_calc2;
    std::vector<double> t_read1;
    std::vector<double> t_read2;

    for (int n : N) {

        generate_data("data1.txt", n);

        std::ifstream fin1;
        fin1.open("data1.txt");

        std::ifstream fin2;
        fin2.open("data1.txt");

        std::ios_base::sync_with_stdio(0);
        fin1.tie(nullptr);

        std::vector<int> input1(200001, -1);
        double read1 = timer_read(n, input1, fin1, f1_reading);

        fin1.close();

        std::ios_base::sync_with_stdio(0);
        fin2.tie(nullptr);

        std::vector<int> input2(200001, -1);
        double read2 = timer_read(n, input2, fin2, f2_reading);

        fin2.close();

        t_read1.push_back(read1);
        t_read2.push_back(read2);

        
        double calc1 = timer_calc(n, input1, f1_calculations);
        double calc2 = timer_calc(n, input2, f2_calculations);
       

        t_calc1.push_back(calc1);
        t_calc2.push_back(calc2);

    }

    std::vector<double> x = matplot::linspace(16, 200000,64);

    matplot::plot(x, t_calc1, "--x", x, t_calc2, "--");
    matplot::xlabel("n");
    matplot::ylabel("t_{calculations}");
    matplot::save("img/tc(n).png");

    matplot::plot(x, t_read1, x, t_read2, "--"); 
    matplot::xlabel("n");
    matplot::ylabel("t_{reading}");
    matplot::save("img/tr(n).png");

    matplot::plot(x, t_calc1, "--x");
    matplot::save("img/t1c(n).png");

    matplot::plot(x, t_calc2, "--x");
    matplot::save("img/t2c(n).png");
}