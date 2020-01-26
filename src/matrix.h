/*********************************************************************/
/*                  (c) Igor Lobov, 2011                             */
/*********************************************************************/

#ifndef MYCADSYSTEM_SRC_MATRIX_H_
#define MYCADSYSTEM_SRC_MATRIX_H_

template<int N>
void ZeroMatrix(double matrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = 0.0;
    }
  }
}

template<int N>
void CopyMatrix(double result_matrix[N][N], double source_matrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      result_matrix[i][j] = source_matrix[i][j];
    }
  }
}

template<int N>
void MultiMatrix(double res_and_first_matrix[N][N], double second_matrix[N][N]) {
  double work_matrix[N][N];
  ZeroMatrix(work_matrix);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        work_matrix[i][j] += res_and_first_matrix[k][j] * second_matrix[i][k];
      }
    }
  }
  CopyMatrix(res_and_first_matrix, work_matrix);
}

#endif //MYCADSYSTEM_SRC_MATRIX_H_
