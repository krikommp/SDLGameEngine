//
// Created by chenyifei on 2022/1/25.
//

#include "GraphicMath.h"

Matrix::Matrix(int InRows, int InCols) : M(std::vector<std::vector<float>>(InRows, std::vector<float>(InCols, 0.f))), Rows(InRows), Cols(InCols) {}

int Matrix::GetCol() {
    return Cols;
}

int Matrix::GetRow() {
    return Rows;
}

Matrix Matrix::Identity(int Dimensions) {
    Matrix M(Dimensions, Dimensions);
    for (int i = 0; i < Dimensions; ++i) {
        for (int j = 0; j < Dimensions; ++j) {
            M[i][j] = (i == j) ? 1.f : 0.f;
        }
    }
    return M;
}

std::vector<float> &Matrix::operator[](const int Idx) {
    assert(Idx >= 0 && Idx < Rows);
    return M[Idx];
}

Matrix Matrix::operator*(const Matrix &InA) {
    assert(Cols == InA.Rows);
    Matrix Result(Cols, InA.Rows);
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < InA.Cols; ++j) {
            Result.M[i][j] = 0.f;
            for (int k = 0; k < Cols; ++k) {
                Result.M[i][j] += M[i][k] * InA.M[k][j];
            }
        }
    }
    return Result;
}

Matrix Matrix::Transpose() {
    Matrix Result(Cols, Rows);
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            Result[j][i] = M[i][j];
        }
    }
    return Result;
}

Matrix Matrix::Inverse() {
    assert(Rows == Cols);
    // augmenting the square matrix with the identity matrix of the same dimensions A => [AI]
    Matrix result(Rows, Cols*2);
    for(int i=0; i<Rows; i++)
        for(int j=0; j<Cols; j++)
            result[i][j] = M[i][j];
    for(int i=0; i<Rows; i++)
        result[i][i+Cols] = 1;
    // first pass
    for (int i=0; i<Rows-1; i++) {
        // normalize the first row
        for(int j=result.Cols-1; j>=0; j--)
            result[i][j] /= result[i][i];
        for (int k=i+1; k<Rows; k++) {
            float coeff = result[k][i];
            for (int j=0; j<result.Cols; j++) {
                result[k][j] -= result[i][j]*coeff;
            }
        }
    }
    // normalize the last row
    for(int j=result.Cols-1; j>=Rows-1; j--)
        result[Rows-1][j] /= result[Rows-1][Rows-1];
    // second pass
    for (int i=Rows-1; i>0; i--) {
        for (int k=i-1; k>=0; k--) {
            float coeff = result[k][i];
            for (int j=0; j<result.Cols; j++) {
                result[k][j] -= result[i][j]*coeff;
            }
        }
    }
    // cut the identity matrix back
    Matrix truncate(Rows, Cols);
    for(int i=0; i<Rows; i++)
        for(int j=0; j<Cols; j++)
            truncate[i][j] = result[i][j+Cols];
    return truncate;
}

std::ostream& operator<<(std::ostream& In, Matrix& InM) {
    for (int i=0; i<InM.GetRow(); i++)  {
        for (int j=0; j<InM.GetCol(); j++) {
            In << InM[i][j];
            if (j<InM.GetCol()-1) In << "\t";
        }
        In << "\n";
    }
    return In;
}
