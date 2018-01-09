/*********************************************************************/
/*                  (c) Igor Lobov, 2011                             */
/*********************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

template <int N>
void zeroMatrix(double matrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = 0.0;
    }
  }
}

template <int N>
void copyMatrix(double resultMatrix[N][N], double sourceMatrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        resultMatrix[i][j] = sourceMatrix[i][j];
    }
  }
}

template <int N>
void multMatrix(double resAndFirstMatrix[N][N], double secondMatrix[N][N]) {
  double workMatrix[N][N];
  zeroMatrix(workMatrix);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
          workMatrix[i][j] += resAndFirstMatrix[k][j] * secondMatrix[i][k];
      }
    }
  }
  copyMatrix(resAndFirstMatrix, workMatrix);
}

#endif // MATRIX_H
