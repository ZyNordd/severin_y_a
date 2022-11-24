#include <vector>
#include <matplot/matplot.h>
#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <chrono>
#include <unordered_set>
#include <fstream>
#include <iomanip>

typedef std::pair<std::chrono::duration<double>, std::chrono::duration<double>> pdd;

//const int MAX_N = 200001;
const int MAX_N = 2000;
const std::string FIO = "test.txt";

struct solutions {
    static void f_1_read(int& n, std::vector<int>& input, std::ifstream& fin) {
        fin >> n;
        for (int i = 0; i < n; i += 1) {
            fin >> input[i];
        }
    }
    static void f_1_work(int& n, std::vector<int>& input) {
        std::vector<int> as(MAX_N, -1);
        for (int i = 0; i < n; i += 1) {
            int idx = input[i];
            as[idx] = n - i - 1;
        }
        std::distance(as.begin(), std::max_element(as.begin(), as.end()));
        std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end())) << "\n";
    }
    static void f_2_read(int& n, std::vector<int>& input, std::ifstream& fin) {
        fin >> n;
        for (int i = 0; i < n; i += 1) {
            fin >> input[i];
        }

    }
    static void f_2_work(int& n, std::vector<int>& data) {
        std::unordered_set<int> unique;
        unique.reserve(MAX_N);
        int idx_unique = n;
        for (int i = n - 1; 0 <= i; i -= 1) {
            if (unique.find(data[i]) != unique.end()) {
                idx_unique = data[i];
                unique.insert(idx_unique);
            }
        }
        std::cout << idx_unique << "\n";
    }
    static void f_3_work(int& n, std::vector<int>& data) {
        std::unordered_set<int> unique;
        unique.reserve(MAX_N);
        int idx_unique = n;
        for (int i = n - 1; 0 <= i; i -= 1) {
            if (unique.find(data[i]) != unique.end()) {
                idx_unique = data[i];
                unique.insert(idx_unique);
            }
        }
        std::cout << idx_unique << "\n";
    }
};

pdd test(const std::string& filename,
    static void (*f_read) (int& x, std::vector<int>& y, std::ifstream& z),
    static void (*f_work) (int& x, std::vector<int>& y))
{
    std::ifstream fin;
    fin.open(filename);

    if (!(fin.is_open())) {
        std::cout << "FILE IS NOT OPEN\n";
        exit(-1);
    }

    int n;
    std::vector<int> input(MAX_N, 0);

    auto start_read = std::chrono::steady_clock::now();
    f_read(n, input, fin);
    auto end_read = std::chrono::steady_clock::now();
    fin.close();

    auto start_work = std::chrono::steady_clock::now();
    f_work(n, input);
    auto end_work = std::chrono::steady_clock::now();



    std::chrono::duration<double> read_time = end_read - start_read;
    std::chrono::duration<double> work_time = end_work - start_work;

    return { read_time,work_time };
}

void generate_data(std::string f, int n, int m) {
    std::ofstream fout;
    fout.open(f);

    fout << n << '\n';
    for (int i = 0; i < n; ++i)
        fout << rand() % m + 1 << " ";

    fout.close();
}

void tester() {

    std::map<int, std::vector<double>> GRAF_1;
    std::map<int, std::vector<double>> GRAF_2;
    for (int n = 1; n < MAX_N; n += 100) {
        std::cout << n << '\n';
        for (int m = 1; m <= n; m += 100) {
            generate_data(FIO, n, m);

            pdd t1, t2;
            t1 = test(FIO, solutions::f_1_read, solutions::f_1_work);
            t2 = test(FIO, solutions::f_2_read, solutions::f_2_work);

            std::cout << n << " " << m << "\n";

            GRAF_1[m].push_back(t1.second.count() / n);
            GRAF_2[m].push_back(t2.second.count() / n);

            std::cout << t1.first.count() << " " << t1.second.count() << "\n";
            std::cout << t2.first.count() << " " << t2.second.count() << "\n";

        }
    }

    namespace plt = matplot;

    std::set<std::vector<double>> Y = { GRAF_1[1901] };

    plt::plot(Y);
    plt::save("minimal_1.jpg");
    plt::plot(GRAF_2[1901]);
    plt::save("minimal_2.jpg");
}

int main() {

    srand(time(NULL));
    std::cout << std::setprecision(7) << std::fixed;
    tester();


    using namespace matplot;

    std::vector<double> x = { 29, 17, 14, 13, 12, 4, 11 };
    bar(x);
    save("barchart.jpg");

    return 0;
}