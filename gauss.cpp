#include "gauss.h"
#include <iostream>

gauss::gauss()
{

}

gauss::gauss(const std::vector<std::vector<double> > &matrix)
{
    this->find = true;
    this->matrix = matrix;
    this->roots = std::vector<double>(matrix.size());
    this->ordnung = std::vector<int>(matrix.size() + 1);
    for (int i = 0; i < this->ordnung.size(); ++ i)
    {
        this->ordnung[i] = i;
    }

}

void gauss::showMatrix()
{
    for (int i = 0; i < this->matrix.size(); ++i)
    {
        for(int j = 0; j < this->matrix[0].size();++j)
        {
            std::cout << this->matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    };
    std::cout << std::endl;
}

void gauss::MainElem(const int &k)
{
    int i, j, i_max = k, j_max = k;
    double temp;
    int n = this->matrix.size();
    //Ищем максимальный по модулю элемент
    for ( i = k; i < n; i++ )
      for ( j = k; j < n; j++ )
        if ( fabs( this->matrix[i_max] [j_max] ) < fabs( this->matrix[i] [j] ) )
        {
          i_max = i;
          j_max = j;
        }
    //Переставляем строки
    for ( j = k; j < n + 1; j++ )
    {
      temp = this->matrix[k] [j];
      this->matrix[k] [j] = this->matrix[i_max] [j];
      this->matrix[i_max] [j] = temp;
    }
    //Переставляем столбцы
    for ( i = 0; i < n; i++ )
    {
      temp = this->matrix[i] [k];
      this->matrix[i] [k] = this->matrix[i] [j_max];
      this->matrix[i] [j_max] = temp;
    }
    //Учитываем изменение порядка корней
    i = this->ordnung[k];
    this->ordnung[k] = this->ordnung[j_max];
    this->ordnung[j_max] = i;
}

void gauss::rein()
{
    int n = this->matrix.size();
    //Прямой ход метода Гаусса
    for ( int k = 0; k < n; k++ )
    { //На какой позиции должен стоять главный элемент
        this->MainElem(k);//Установка главного элемента
        if ( fabs( this->matrix[k] [k] ) < 0.0001 )
        {
            //Система не имеет единственного решения
            this->find = false;
            return;
        }
        for ( int j = n; j >= k; j-- )
        {
          this->matrix[k] [j] /= this->matrix[k] [k];
        }
        for ( int i = k + 1; i < n; i++ )
        {
            for ( int j = n; j >= k; j-- )
            {
              this->matrix[i] [j] -= this->matrix[k] [j] * this->matrix[i] [k];
            }
        }
    }
}

void gauss::raus()
{
    int n = this->matrix.size();
    for (int i = 0; i < n; i++ )
    {
        this->roots[i] = this->matrix[i] [n];
    }
    for (int i = n - 2; i >= 0; i-- )
    {
        for (int j = i + 1; j < n; j++ )
        {
            this->roots[i] -= this->roots[j] * this->matrix[i] [j];
        }
    }
}

std::vector<double> gauss::rechnen()
{
    int n = this->matrix.size();
    std::vector<double> result(this->roots.size());
    this->rein();
    this->raus();
    for (int  i = 0; i < n; i++ )
    {
        for (int j = 0; j < n; j++ )
        {
            if ( i == this->ordnung[j] )
            {
                //Расставляем корни по порядку
                result[i] = this->roots[j];
              break;
            }
        }
    }
    return result;

}

bool gauss::is_find()
{
    return this->find;
}

void gauss::updateStand(const std::vector<std::vector<double> > &matrix)
{
    this->find = true;
    this->matrix = matrix;
    this->roots = std::vector<double>(matrix.size());
    this->ordnung = std::vector<int>(matrix.size() + 1);
    for (int i = 0; i < this->ordnung.size(); ++ i)
    {
        this->ordnung[i] = i;
    }
}
