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
#define MEL_SPHERE                  106

//ДЕЙСТВИЯ НАД ПРИМИТИВАМИ
#define MEV_ACTION                  200 // Переместить
#define MEV_TRANSLATE               201 // Переместить
#define MEV_ROTATE                  202 // Вращать
#define MEV_GROUP                   203 // Сгрупировать
#define MEV_SUBSTRACT               204 //
#define MEV_INTERSECT               205 //

//ДЕЙСТВИЯ НАД СЦЕНОЙ
#define MEV_CAMERA_TRANSLATE        251 // Переместить камеру
#define MEV_CAMERA_ROTATE           252 // Вращать камеру
#define MEV_CAMERA_ZOOM             253 // Изменить масштаб

#endif // RESOURCE_H
