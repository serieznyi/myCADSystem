#pragma once

#ifndef RESOURCE_H
#define RESOURCE_H

#define PLANE_MIN_X                -5.0    // Размеры плоскости (Левая передняя точка, правая задняя)(XOZ)
#define PLANE_MAX_X                 5.0
#define PLANE_MIN_Z                -5.0
#define PLANE_MAX_Z                 5.0

// ВИД
#define MPJ_PERSPECTIVE                0
#define MPJ_TOP                        1
#define MPJ_RIGHT                      2
#define MPJ_FRONT                      3
//#define WMAXIMAZE                      4
//#define WRESET                         5

//ТИП ЭЛЕМЕНТА
//Примитивы
#define MEL_POINT                   100
#define MEL_LINE                    101
#define MEL_CUBE                    102
#define MEL_PYRAMID                 103
#define MEL_CYLINDER                104
//Действия
#define MEL_TRANSLATE               105

//ДЕЙСТВИЯ НАД ПРИМИТИВАМИ
#define MEV_TRANSLATE           200 // Переместить
#define MEV_ROTATE              201 // Вращать
#define MEV_GROUP               202 // Сгрупировать
#define MEV_SUBSTRACT           203 //
#define MEV_INTERSECT             204 //

//ДЕЙСТВИЯ НАД СЦЕНОЙ
#define MEV_CAMERA_TRANSLATE        301 // Переместить камеру
#define MEV_CAMERA_ROTATE           302 // Вращать камеру
#define MEV_CAMERA_ZOOM             303 // Изменить масштаб

//ТИП ПРИМИТИВА
#define MEV_PRIM_POINT              401 // Точка
#define MEV_PRIM_LINE               402 // Линия
#define MEV_PRIM_QUAD               403 // Куб
#define MEV_PRIM_PYRAMID            404 // Пирамида
#define MEV_PRIM_SPHERE             405 // Сфера
#define MEV_PRIM_CYLINDER           406 // Цилиндр

#endif // RESOURCE_H
