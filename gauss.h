#ifndef GAUSS_H
#define GAUSS_H
#include <vector>


class gauss
{
private:
    std::vector<std::vector<double>> matrix;
    std::vector<double> roots;
    std::vector<int> ordnung;
    bool find;
public:
    gauss();
    gauss(const std::vector<std::vector<double>>& matrix);
    void showMatrix();
    void MainElem(const int& k);
    void rein();
    void raus();
    std::vector<double> rechnen();
    bool is_find();
    void updateStand(const std::vector<std::vector<double>>& matrix);
};

#endif // GAUSS_H
