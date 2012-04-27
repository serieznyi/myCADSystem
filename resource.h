#ifndef RESOURCE_H
#define RESOURCE_H

#define PLANE_MIN_X                -5.0    // Размеры плоскости (Левая передняя точка, правая задняя)(XOZ)
#define PLANE_MAX_X                 5.0
#define PLANE_MIN_Z                -5.0
#define PLANE_MAX_Z                 5.0

// РЕЖИМЫ РИСОВАНИЯ
#define MODE_REAL                   true
#define MODE_FICTIVE                false

// ВИД
#define MPJ_PERSPECTIVE             0
#define MPJ_TOP                     1
#define MPJ_RIGHT                   2
#define MPJ_FRONT                   3
#define MPJ_MAXIMAZE                4
#define MPJ_RESET                   5
// Прочее
#define COORD_X                     10
#define COORD_Y                     11

//ТИП ЭЛЕМЕНТА
//Примитивы
#define MEL_PRIMITIVE               100
#define MEL_POINT                   101
#define MEL_LINE                    102
#define MEL_CUBE                    103
#define MEL_PYRAMID                 104
#define MEL_CYLINDER                105
//Действия
#define MEL_ACTION                  151
#define MEL_TRANSLATE               152

//ДЕЙСТВИЯ НАД ПРИМИТИВАМИ
#define MEV_TRANSLATE               200 // Переместить
#define MEV_ROTATE                  201 // Вращать
#define MEV_GROUP                   202 // Сгрупировать
#define MEV_SUBSTRACT               203 //
#define MEV_INTERSECT               204 //

//ДЕЙСТВИЯ НАД СЦЕНОЙ
#define MEV_CAMERA_TRANSLATE        251 // Переместить камеру
#define MEV_CAMERA_ROTATE           252 // Вращать камеру
#define MEV_CAMERA_ZOOM             253 // Изменить масштаб

//ТИП ПРИМИТИВА
#define MEV_PRIM_POINT              301 // Точка
#define MEV_PRIM_LINE               302 // Линия
#define MEV_PRIM_QUAD               303 // Куб
#define MEV_PRIM_PYRAMID            304 // Пирамида
#define MEV_PRIM_SPHERE             305 // Сфера
#define MEV_PRIM_CYLINDER           306 // Цилиндр



#endif // RESOURCE_H
