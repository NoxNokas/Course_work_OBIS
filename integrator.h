
#pragma once
// ����������� ������������� ����� ���������� ��������� � ��������� ��������
#include "array.h"
//---------------------------------------------------------------------------

// ����������� ����������
class TModel;

class TIntegrator
{
    protected:
        // ������������ ����������� �� ����
		   double Eps;

    public:
        // ������� �����������
		TIntegrator() : Eps( 1e-10 ) {}
		inline void setPrecision(double Eps ) { this->Eps = Eps; }
		inline double getPrecision() const { return Eps; }
        // ����������� �����, ����������� ��������� ���������� �������������� � ������������ ���������� ����������� ����������
		virtual double Run(TModel* Model) = 0;
};

//---------------------------------------------------------------------------

class TDormandPrinceIntegrator : public TIntegrator
{
    private:
        // ������������ a,b,c
		static const double c[7], a[7][6], b1[7], b2[7];
        // ������������ K[i]
		TVector K[7];
        // �������� ����
		 double u;
    public:
        TDormandPrinceIntegrator();
		double Run(TModel* Model);
};

//---------------------------------------------------------------------------


