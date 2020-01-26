#ifndef RESOURCE_H
#define RESOURCE_H

#define PLANE_MIN_X                (-5.0)    // Размеры плоскости (Левая передняя точка, правая задняя)(XOZ)
#define PLANE_MAX_X                 5.0
#define PLANE_MIN_Z                (-5.0)
#define PLANE_MAX_Z                 5.0

// РЕЖИМЫ РИСОВАНИЯ
#define MODE_REAL                   true
#define MODE_FICTIVE                false


// ВИД
#define VIEW_PERSPECTIVE             0
#define VIEW_TOP                     1
#define VIEW_RIGHT                   2
#define VIEW_FRONT                   3
#define VIEW_FULL_SCREEN             4
#define VIEW_RESET                   5

// Прочее
#define COORD_X                     10
#define COORD_Y                     11

//ТИП ЭЛЕМЕНТА
//Примитивы
#define MEL_PRIMITIVE               100
#define MEL_CUBE                    103
#define MEL_PYRAMID                 104
#define MEL_CYLINDER                105
#define MEL_SPHERE                  106
#define MEL_GROUP                   107
#define MEL_SUBSTRACT               108
#define MEL_INTERSECT               109

//ДЕЙСТВИЯ НАД ПРИМИТИВАМИ
#define ACTION_ACTION               200
#define ACTION_TRANSLATE            201 // Переместить
#define ACTION_SCALE                202 // Масштабировать
#define ACTION_STRETCH              203 // Растянуть
#define ACTION_ROTATE               204 // Вращать
#define ACTION_GROUP                205 // Сгрупировать
#define ACTION_SUBSTRACT            206 // Вычитание
#define ACTION_INTERSECT            207 // Пересечение

//ДЕЙСТВИЯ НАД СЦЕНОЙ
#define CAMERA_TRANSLATE            251 // Переместить камеру
#define CAMERA_ROTATE               252 // Вращать камеру
#define CAMERA_ZOOM                 253 // Изменить масштаб

//ПРОЧЕЕ
#define MCM_SCENE                   300
#define MCM_PRIMITIVE               301

#endif // RESOURCE_H
