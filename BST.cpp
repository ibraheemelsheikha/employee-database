//
//  BST.cpp
//  Lab 5 Search Through A Database
//
//  Created by Author Name, Date
#include "BST.h"

#include "Employee.h"

BST::BST(string order_) {
  root = NULL;
  order = order_;
}

BST::~BST() { delete root; }

bool startsWith(const string& str, const string& cmp) {
  return str.compare(0, cmp.length(), cmp) == 0;
}

void printInOrderHelper(Employee* employee) {
  if (employee != NULL) {
    printInOrderHelper(employee->getLeft());
    employee->print();
    printInOrderHelper(employee->getRight());
  }
}

void BST::printInOrder() { return printInOrderHelper(root); }

Employee* searchIDHelper(Employee* employee, int ID) {
  if (employee == NULL) {
    return NULL;
  } else if (employee->getID() == ID) {
    return employee;
  } else if (employee->getID() > ID) {
    return (searchIDHelper(employee->getLeft(), ID));
  } else {
    return (searchIDHelper(employee->getRight(), ID));
  }
}

Employee* BST::searchID(int ID) { return searchIDHelper(root, ID); }

void searchAgeRangeHelper(Employee* employee, double lowAge, double highAge) {
  if (employee != NULL) {
    searchAgeRangeHelper(employee->getLeft(), lowAge, highAge);
    if (employee->getAge() >= lowAge && employee->getAge() <= highAge) {
      employee->print();
    }
    searchAgeRangeHelper(employee->getRight(), lowAge, highAge);
  }
}

void BST::searchAgeRange(double lowAge, double highAge) {
  searchAgeRangeHelper(root, lowAge, highAge);
}

void insertHelper(Employee* newEmployee, Employee* employee, string order) {
  if (order == "ID") {
    if (newEmployee->getID() == employee->getID()) {
      return;
    } else if (newEmployee->getID() < employee->getID()) {
      if (employee->getLeft() == NULL) {
        employee->setLeft(newEmployee);
      } else {
        insertHelper(newEmployee, employee->getLeft(), order);
      }
    } else {
      if (employee->getRight() == NULL) {
        employee->setRight(newEmployee);
      } else {
        insertHelper(newEmployee, employee->getRight(), order);
      }
    }
  }

  else if (order == "age") {
    if (newEmployee->getAge() <= employee->getAge()) {
      if (employee->getLeft() == NULL) {
        employee->setLeft(newEmployee);

      } else {
        insertHelper(newEmployee, employee->getLeft(), order);
      }
    } else if (newEmployee->getAge() > employee->getAge()) {
      if (employee->getRight() == NULL) {
        employee->setRight(newEmployee);

      } else {
        insertHelper(newEmployee, employee->getRight(), order);
      }
    }
  }

  else if (order == "name") {
    if (newEmployee->getName() < employee->getName()) {
      if (employee->getLeft() == NULL) {
        employee->setLeft(newEmployee);

      } else {
        insertHelper(newEmployee, employee->getLeft(), order);
      }
    } else if (newEmployee->getName() > employee->getName()) {
      if (employee->getRight() == NULL) {
        employee->setRight(newEmployee);

      } else {
        insertHelper(newEmployee, employee->getRight(), order);
      }
    }
  }
}

void BST::insert(Employee* newEmployee) {
  if (root == NULL) {
    root = newEmployee;
    return;
  }
  insertHelper(newEmployee, root, order);
}

void autocompleteHelper(string prefix, Employee* employee) {
  if (employee != NULL) {
    autocompleteHelper(prefix, employee->getLeft());
    if (startsWith(employee->getName(), prefix)) {
      employee->print();
    }
    autocompleteHelper(prefix, employee->getRight());
  }
}

void BST::autocomplete(string prefix) { autocompleteHelper(prefix, root); }
