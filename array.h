#pragma once

    /* Anticipating declaration	*/
    class TMatrix;

    /* Declaration of the class vectors	*/
    class TVector
    {
        /* Access modifier	*/
        protected:
            /* Dimension of the vector	*/
            int n;

            /* Data of the vector	*/
			long double *data;

        /* Access modifier	*/
        public:
            /* Constructor standart	*/
            TVector();

            /* Constructor of set	*/
            TVector(int n);

            /* Constructor copy	*/
            TVector(const TVector& rvalue);

            /* Assignment operator	*/
            TVector& operator = (const TVector& rvalue);

            /* Destructor	*/
            virtual ~TVector();

            /* A method of obtaining the number of elements	*/
            inline int size() const { return n; }

            /* A method of obtaining the last item	*/
            inline int high() const { return n - 1; }

            /* Method used to set the number of elements	*/
            void resize(int n);

            /* Access operator elements of vector	*/
			inline long double& operator[](int i) { return data[i]; }

            /* Operator const access elements of a vector	*/
			inline const long double& operator[](int i) const { return data[i]; }

            /* Operator - unary minus	*/
            TVector operator - () const;

            /* Subtraction operator vectors	*/
            TVector operator - (const TVector& arg) const;

            /* Addition operator vectors	*/
            TVector operator + (const TVector& arg) const;

            /* The module (length) vector	*/
			long double length() const;

            /* Operator of vector multiplication of vectors	*/
            TVector operator ^ (const TVector& arg) const;

            /* Operator of multiplication of a vector by a number	*/
			TVector operator * (long double arg) const;

            /* Normalization of the vector	*/
            TVector& norm();

            /* Operator for scalar multiplication of vectors	*/
			long double operator * (const TVector& arg) const;

            /* Operator of multiplication of a vector by a matrix	*/
            TVector operator * (const TMatrix& arg) const;

            /* Friendly function - the operator multiplying the number of vector	*/
			friend TVector operator * (long double lvalue, const TVector& rvalue);
    };



    /* Declaration of the class matrix	*/
    class TMatrix
    {
        /* Access modifier	*/
        protected:
            /* Dimension of the matrix	*/
            int n, m;

            /* Data of the matrix	*/
			long double **data;

        /* Access modifier	*/
        public:
            /* Constructor standart	*/
            TMatrix();

            /* Constructor of set	*/
            TMatrix(int n, int m);

            /* Constructor copy	*/
            TMatrix(const TMatrix& rvalue);

            /* Assignment operator	*/
            TMatrix& operator = (const TMatrix& rvalue);

            /* Destructor	*/
            virtual ~TMatrix();

            /* A method of obtaining the number row of the vector	*/
            inline int rowCount() const { return n; }

            /* A method of obtaining the number column of the vector	*/
            inline int colCount() const { return m; }

            /* Function to obtain the index of the last row	*/
            inline int rowHigh() const { return n-1; }

            /* Function to obtain the index of the last column	*/
            inline int colHigh() const { return m-1; }

            /* Method used to set the number of elements	*/
            void resize(int n, int m);

            /* Access operator elements of matrix	*/
			inline long double& operator()(int i, int j) { return data[i][j]; }

            /* Operator const access elements of a matrix	*/
			inline const long double& operator()(int i, int j) const { return data[i][j]; }

            /* Operator - unary minus	*/
            TMatrix operator - () const;

            /* Subtraction operator matrix	*/
            TMatrix operator - (const TMatrix& arg) const;

            /* Addition operator matrix	*/
            TMatrix operator + (const TMatrix& arg) const;

            /* Operator to multiply a matrix by a number	*/
			TMatrix operator * (long double arg) const;

            /* Matrix multiplication operator	*/
            TMatrix operator * (const TMatrix& arg) const;

            /* Multiplication operator for the matrix-vector	*/
            TVector operator * (const TVector& arg) const;

            /* Transpose of the matrix	*/
            TMatrix t() const;

            /* Friendly feature - the operator multiplying the number of the matrix	*/
			friend TMatrix operator * (long double lvalue, const TMatrix& rvalue);

            /* Function of the formation of the identity matrix	*/
            static TMatrix E(int n);

            /* Inversion operator matrix (Gauss method)	*/
            TMatrix operator ! () const throw(int);

            /* Function swap rows	*/
            TMatrix& swapRows(int i, int j);
    };
