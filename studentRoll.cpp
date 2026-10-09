#include <string>
#include "studentRoll.h"

StudentRoll::StudentRoll() { head = tail = nullptr; }
void StudentRoll::insertAtTail(const Student &s) {
  Node *node = new Node{nullptr, nullptr};
  try {
    node->s = new Student(s);
  } catch (...) {
    delete node;
    throw;
  }
  if (tail == nullptr)
    head = node;
  else
    tail->next = node;
  tail = node;
}
std::string StudentRoll::toString() const {
  std::string result = "[";
  for (Node *current = head; current != nullptr; current = current->next) {
    if (current != head)
      result += ",";
    result += current->s->toString();
  }
  return result + "]";
}
StudentRoll::StudentRoll(const StudentRoll &orig) {
  head = tail = nullptr;
  // The temporary roll cleans up partial copies if allocation fails.
  StudentRoll copy;
  for (Node *current = orig.head; current != nullptr; current = current->next)
    copy.insertAtTail(*current->s);
  head = copy.head;
  tail = copy.tail;
  copy.head = copy.tail = nullptr;
}
StudentRoll::~StudentRoll() {
  while (head != nullptr) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead->s;
    delete oldHead;
  }
  tail = nullptr;
}
StudentRoll & StudentRoll::operator=(const StudentRoll &right) {
  if (&right == this)
    return (*this);
  // Copy first, then let the temporary roll destroy the old list.
  StudentRoll copy(right);
  Node *oldHead = head;
  Node *oldTail = tail;
  head = copy.head;
  tail = copy.tail;
  copy.head = oldHead;
  copy.tail = oldTail;
  return (*this);
}
