#include "src/domain/element.h"

Element::Element() {
}

void Element::setGID(long n) {
  this->GID = n;
}

void Element::setTypeName(int name) {
  this->type_name = name;
}

int Element::getTypeName() {
  return type_name;
}

long Element::getGID() {
  return this->GID;
}
