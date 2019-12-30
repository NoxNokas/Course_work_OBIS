
#pragma once
// Подключение заголовочного файла библиотеки векторных и матричных операций
#include "array.h"
//---------------------------------------------------------------------------

// Опережающие декларации
class TModel;

class TIntegrator
{
    protected:
        // Максимальная погрешность на шаге
		   double Eps;

    public:
        // Базовый конструктор
		TIntegrator() : Eps( 1e-10 ) {}
		inline void setPrecision(double Eps ) { this->Eps = Eps; }
		inline double getPrecision() const { return Eps; }
        // Абстрактный метод, реализующий процедуру численного интегрирования и возвращающий глобальную погрешность вычислений
		virtual double Run(TModel* Model) = 0;
};

//---------------------------------------------------------------------------

class TDormandPrinceIntegrator : public TIntegrator
{
    private:
        // Коэффициенты a,b,c
		static const double c[7], a[7][6], b1[7], b2[7];
        // Коэффициенты K[i]
		TVector K[7];
        // Машинный нуль
		 double u;
    public:
        TDormandPrinceIntegrator();
		double Run(TModel* Model);
};

//---------------------------------------------------------------------------


