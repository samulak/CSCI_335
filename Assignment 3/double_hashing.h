// Adam Samulak
//
//** Double Hashing Class *//
//
//New funcions were added to get the number of elements,
// table size, load factor, number of collisons, average number of collisions
// and reset collison count.

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>
#include "quadratic_probing.h"

// Double hashing implementation.
//
// *************NEW PUBLIC OPERATIONS***********************
// num_of_elements( )         --> returns current size
// table_size ( )             --> returns the size of the table_size
// load_factor ( )            --> returns the load factor of the table
// num_of_collisions ( )      --> returns number of collisions
// average_collisions ( )     --> returns average collision #
// reset_collision_count ( )  --> resets collison coutn
// set_R ( )                  --> sets the R value of the has table
// ************* END NEW PUBLIC OPERATIONS***********************

template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); }

  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }

  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }

  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;

    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

/*********** NEW PUBLIC FUNCTIONS ***************/

  int num_of_elements(){
  	return this->current_size_;
  }

  int table_size(){
  	return this->array_.size();
  }

  float load_factor(){
  	return float(num_of_elements()) / float(table_size());
  }

  int num_of_collisions(){
  	return this->collision_num;
  }

  float average_collisions(){
        return float(num_of_collisions()) / float(num_of_elements());
  }

  void reset_collision_count(){
  	collision_num = 0;
  }

  void set_R(int x){
  	R = x;
  }
/*********** END NEW PUBLIC FUNCTIONS ***************/
 private:
  struct HashEntry {
    HashedObj element_;
    EntryType info_;

    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }

    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };


  std::vector<HashEntry> array_;
  size_t current_size_;

  /*********** NEW PRIVATE VARIABLE ***************/

  mutable int collision_num = 0;
  int R = 89;
  /*********** END NEW PRIVATE VARIABLE ***************/

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t offset = InternalSecondHash(x); // New
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {

      // NEW: counting collision number
      ++collision_num;

      current_pos += offset;  // Compute ith probe.


      //offset += 2; NEW: commenting this out changes the algorithm to linear probing.

      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;

    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }

  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }
    /*********** NEW PRIVATE FUNCTION ***************/
    size_t InternalSecondHash(const HashedObj &x) const
  {
    static std::hash<HashedObj> hf;
    return (R - ((hf(x) % R)) % array_.size());
  }
   /*********** END NEW PRIVATE FUNCTION ***************/
};


#endif  // DOUBLE_HASHING_H
