//---------------------------------------------------------------------------

#pragma once

// ����������� ������������� ����� ���������� ��������� � ��������� ��������
#include <stdio.h>

#include "array.h"

//---------------------------------------------------------------------------
// ������� ����� ������ ��� �����������

class TModel
{
    protected:
        // ��������� �������
        TVector X0;
        // ��������� �� ����������� �������� ������ �����������
		double SamplingIncrement;
		// ������, ��������� ������� �������������� � ����� ������ �������� � ���������� ����������
		double t0, t1, tStart;
		// ��������� �������� ����������� �������
		double psi1, psi2, psi3;
        // ��������� �����������
        TMatrix Result;
        // ������� ����� � ������� �����������
        int N;

    public:
        // ����� ����������� ������� - ������������� ���������� �� ���������
        TModel()
			: SamplingIncrement( static_cast<double>(1e-2) )
			, t0( 0 )
			, t1( 200)
            , N( 0.01)
			{}
		~TModel() { }
        // ����������� ������������� ������� ������ ������ �� (X - ������ ���������, t - ����������� ��������)
		//virtual TVector getRight( const TVector& X, double t ) = 0;
		//virtual void getRight(TVector& X, double t, TVector& Y) = 0;
		virtual void getRight( const TVector& X, double t, TVector& Y ) = 0;

        // ��������� ��������� �������
        inline TVector getInitialConditions() const { return X0; }
        // ������� ������� - �� ����������� ������� ��������� �������
        inline int getOrder() const { return X0.size(); }

        // �������� ������ �����������
		inline double getSamplingIncrement() const { return SamplingIncrement; }
		inline void setSamplingIncrement(double s) { this->SamplingIncrement = s; }
        // ���������� ��������� ���������� ��������������
		inline double getT0() const { return t0; }
		inline double getT1() const { return t1; }
		inline double getTStart() const { return tStart; }
		inline void setT0(double p_ldT0 ) { this->t0 = p_ldT0; }
		inline void setT1(double p_ldT1 ) { this->t1 = p_ldT1; }
		inline void setTStart(double p_ldTStart) { this-> tStart = p_ldTStart; }
		// ���������� ��������� ��������� ����������� �������
		inline void setPsi1(double p_psi1) { this->psi1 = p_psi1; }
		inline void setPsi2(double p_psi2) { this->psi2 = p_psi2; }
		inline void setPsi3(double p_psi3) { this-> psi3 = p_psi3; }
        // ��������� ������� �����������
        inline TMatrix getResult() const { return Result; }
        // ������ ����������� (� ���� ������ � ���������� ��������� ������������ ������ � ����
        // ������ ��� ������ � ����������� ������� �����������)
		virtual void addResult( const TVector& X, double t );
        // ������� ������� ����������� (��� ����� � ������������)
        virtual void clearResult();
        // ���������� ������� ����������� ��� ����� ������������ ��������� ������
        virtual void prepareResult();
};

//---------------------------------------------------------------------------
