/**
 * Examples of automatic tests for the exercise on binary trees.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
//using std::cout, std::endl;
using namespace std;
#include "badkan.hpp"
using namespace badkan;
#include "Tree.hpp"
using namespace ariel;


int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree;
  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);

  ariel::Tree mytree;
  mytree.insert(50);
  mytree.insert(25);
  mytree.insert(75);
  mytree.insert(30);
  mytree.insert(60);
  mytree.insert(55);
  mytree.insert(52);


  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK    (emptytree.remove(5))
  .CHECK_EQUAL (emptytree.contains(5), false)
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)

  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_THROWS(threetree.left(6))
  .CHECK_OK    (threetree.print())

  .CHECK_EQUAL (mytree.right(mytree.Root->value), 75)
  .CHECK_EQUAL (mytree.size(), 7)
  .CHECK_OK (mytree.remove(75))
  .CHECK_EQUAL (mytree.size(), 6)
  .CHECK_EQUAL (mytree.right(mytree.Root->value), 60)
  .CHECK_THROWS (mytree.parent(mytree.Root->value))
  .CHECK_EQUAL (mytree.parent(55), 60)
  .CHECK_OK    (emptytree.insert(10))
  .CHECK_OK    (emptytree.insert(90))
  .CHECK_EQUAL (mytree.parent(25), mytree.Root->value)
  .CHECK_EQUAL (mytree.left(55), 52)
  .CHECK_EQUAL (mytree.right(25), 30)
  .CHECK_OK (mytree.print())
  .print();





  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}
