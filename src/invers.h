//  (c) Drobotenko    http://drobotenko.com
#ifndef MYCADSYSTEM_SRC_INVERS_H_
#define MYCADSYSTEM_SRC_INVERS_H_

#include <cmath>

#define NA_N() (double&)*"Implementation dependent";
//  заполнитель для неразрешенных измерений
//  при невозможности обращения

template<int N>
inline static void InversMatrix(double **m) {
  int gaus_ostatok;
  // дефект линейного преобразования
  // 0 == ОК

  long double gaus_deter;
  //  в случае успешного обращения детерминант

  double gaus_minved;
  //  минимальный ведущий элемент
  //  можно использовать для оценки точности


  int rn[N], cn[N];
  int j, k;

  for (j = N; j--;)
    rn[j] = cn[j] = j;
  gaus_minved = 1e99;
  gaus_deter = 1;
  for (gaus_ostatok = N; gaus_ostatok; gaus_ostatok--) {
    int jved, kved;
    double vved = -1, t;

    // поиск ведущего
    for (j = N; j--;) {
      if (~rn[j])
        for (k = N; k--;)
          if (~cn[k])
            if (vved < fabs(m[j][k]))
              vved = fabs(m[j][k]), jved = j, kved = k;
    }

    if (gaus_minved > vved)
      gaus_minved = vved;
    gaus_deter *= m[jved][kved];
    if (vved < 1e-99) {
      for (j = N; j--;) {
        if (~rn[j])
          for (k = N; k--;)
            m[j][k] = NA_N();
        if (~cn[j])
          for (k = N; k--;)
            m[k][j] = NA_N();
      }
      return;
    }

    int jt = rn[jved], kt = cn[kved];

    // перестановки
    for (j = N; j--;)
      t = m[kt][j], m[kt][j] = m[jved][j], m[jved][j] = t;
    for (j = N; j--;)
      t = m[j][jt], m[j][jt] = m[j][kved], m[j][kved] = t;

    rn[jved] = rn[kt];
    cn[kved] = cn[jt];
    rn[kt] = cn[jt] = -1;

    vved = m[kt][jt];
    m[kt][jt] = 1;
    for (j = N; j--;) {
      if (j == kt)
        continue;
      double mul = m[j][jt] / vved;
      m[j][jt] = 0;
      for (k = N; k--;)
        m[j][k] -= m[kt][k] * mul;
      // самый внутренний цикл ровно N^3 операций
    }
    for (k = N; k--;)
      m[kt][k] /= vved;
  }
}

#endif //MYCADSYSTEM_SRC_INVERS_H_


