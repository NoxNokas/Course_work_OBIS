//---------------------------------------------------------------------------

#pragma once

// Подключение заголовочного файла библиотеки векторных и матричных операций
#include <stdio.h>

#include "array.h"

//---------------------------------------------------------------------------
// Базовый класс модели для интегратора

class TModel
{
    protected:
        // Начальные условия
        TVector X0;
        // Требуемый от интегратора интервал выдачи результатов
		double SamplingIncrement;
		// Начало, окончание времени интегрирования и время начала движения с запущенным двигателем
		double t0, t1, tStart;
		// Начальные значения сопряжённого вектора
		double psi1, psi2, psi3;
        // Хранилище результатов
        TMatrix Result;
        // Счётчик строк в матрице результатов
        int N;

    public:
        // Общий конструктор моделей - инициализация параметров по умолчанию
        TModel()
			: SamplingIncrement( static_cast<double>(1e-2) )
			, t0( 0 )
			, t1( 200)
            , N( 0.01)
			{}
		~TModel() { }
        // Абстрактная перегружаемая функция правых частей ДУ (X - вектор состояния, t - независимый аргумент)
		//virtual TVector getRight( const TVector& X, double t ) = 0;
		//virtual void getRight(TVector& X, double t, TVector& Y) = 0;
		virtual void getRight( const TVector& X, double t, TVector& Y ) = 0;

        // Получение начальных условий
        inline TVector getInitialConditions() const { return X0; }
        // Порядок системы - по размерности вектора начальных условий
        inline int getOrder() const { return X0.size(); }

        // Интервал выдачи результатов
		inline double getSamplingIncrement() const { return SamplingIncrement; }
		inline void setSamplingIncrement(double s) { this->SamplingIncrement = s; }
        // Управление временным интервалом интегрирования
		inline double getT0() const { return t0; }
		inline double getT1() const { return t1; }
		inline double getTStart() const { return tStart; }
		inline void setT0(double p_ldT0 ) { this->t0 = p_ldT0; }
		inline void setT1(double p_ldT1 ) { this->t1 = p_ldT1; }
		inline void setTStart(double p_ldTStart) { this-> tStart = p_ldTStart; }
		// Управление начальным значением сопряжённого вектора
		inline void setPsi1(double p_psi1) { this->psi1 = p_psi1; }
		inline void setPsi2(double p_psi2) { this->psi2 = p_psi2; }
		inline void setPsi3(double p_psi3) { this-> psi3 = p_psi3; }
        // Получение матрицы результатов
        inline TMatrix getResult() const { return Result; }
        // Запись результатов (в этом методе в наследнике допустимо организовать запись в файл
        // вместо или вместе с наполнением матрицы результатов)
		virtual void addResult( const TVector& X, double t );
        // Очистка матрицы результатов (или файла с результатами)
        virtual void clearResult();
        // Подготовка матрицы результатов для более эффективного выделения памяти
        virtual void prepareResult();
};

//---------------------------------------------------------------------------
