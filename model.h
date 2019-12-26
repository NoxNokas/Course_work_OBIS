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
		long double SamplingIncrement;
		// ������, ��������� ������� �������������� � ����� ������ �������� � ���������� ����������
		long double t0, t1, tStart;
        // ��������� �����������
        TMatrix Result;
        // ������� ����� � ������� �����������
        int N;

    public:
        // ����� ����������� ������� - ������������� ���������� �� ���������
        TModel()
			: SamplingIncrement( static_cast<long double>(1e-2) )
			, t0( 0 )
			, t1( 200)
            , N( 0.01)
			{}
		~TModel() { }
        // ����������� ������������� ������� ������ ������ �� (X - ������ ���������, t - ����������� ��������)
		//virtual TVector getRight( const TVector& X, long double t ) = 0;
		//virtual void getRight(TVector& X, long double t, TVector& Y) = 0;
		virtual void getRight( const TVector& X, long double t, TVector& Y ) = 0;

        // ��������� ��������� �������
        inline TVector getInitialConditions() const { return X0; }
        // ������� ������� - �� ����������� ������� ��������� �������
        inline int getOrder() const { return X0.size(); }

        // �������� ������ �����������
		inline long double getSamplingIncrement() const { return SamplingIncrement; }
		inline void setSamplingIncrement(long double s) { this->SamplingIncrement = s; }
        // ���������� ��������� ���������� ��������������
		inline long double getT0() const { return t0; }
		inline long double getT1() const { return t1; }
		inline long double getTStart() const { return tStart; }
		inline void setT0(long double p_ldT0 ) { this->t0 = p_ldT0; }
		inline void setT1(long double p_ldT1 ) { this->t1 = p_ldT1; }
		inline void setTStart(long double p_ldTStart) { this-> tStart = p_ldTStart; }
        // ��������� ������� �����������
        inline TMatrix getResult() const { return Result; }
        // ������ ����������� (� ���� ������ � ���������� ��������� ������������ ������ � ����
        // ������ ��� ������ � ����������� ������� �����������)
		virtual void addResult( const TVector& X, long double t );
        // ������� ������� ����������� (��� ����� � ������������)
        virtual void clearResult();
        // ���������� ������� ����������� ��� ����� ������������ ��������� ������
        virtual void prepareResult();
};

//---------------------------------------------------------------------------
