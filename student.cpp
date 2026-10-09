#include "student.h"
#include <string>
#include <cstring>

Student::Student(const char * const name, int perm) : perm(perm), name(nullptr) {
  setName(name);
}
int Student::getPerm() const { return perm; }
const char * const Student::getName() const { return name; }
void Student::setPerm(const int permNumber) { perm = permNumber; }
void Student::setName(const char * const name) {
  // Copy before deleting to allow setName(getName()).
  char *newName = new char[strlen(name) + 1];
  strcpy(newName, name);
  delete[] this->name;
  this->name = newName;
}
Student::Student(const Student &orig) : perm(orig.perm), name(nullptr) {
  setName(orig.name);
}
Student::~Student() { delete[] name; }
Student & Student::operator=(const Student &right) {
  if (&right == this)
    return (*this);
  setName(right.name);
  setPerm(right.perm);
  return (*this);
}
std::string Student::toString() const {
  return "[" + std::string(name) + "," + std::to_string(perm) + "]";
}
