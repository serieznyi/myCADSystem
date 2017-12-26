/*********************************************************************/
/*                  (c) Igor Lobov, 2011                             */
/*********************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

template <int N>
void copyMatrix(double dstMatrix[N][N], double srcMatrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        dstMatrix[i][j] = srcMatrix[i][j];
    }
  }
}

template <int N>
void multMatrix(double resAndFirstMatrix[N][N], double secondMatrix[N][N]) {
  double workMatrix[N][N];
  zeroMatirx(workMatrix);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
          workMatrix[i][j] += resAndFirstMatrix[k][j] * secondMatrix[i][k];
      }
    }
  }
  copyMatrix(resAndFirstMatrix, workMatrix);
}

template <int N>
void zeroMatirx(double dstMatrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      dstMatrix[i][j] = 0.0;
    }
  }
}

#endif // MATRIX_H
