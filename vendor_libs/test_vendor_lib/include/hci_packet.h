#pragma once
#include <iterator>
#include <memory>

namespace test_vendor_lib {

// Iterator is a custom iterator class for HciPackets.
class Iterator
    : public std::iterator<std::random_access_iterator_tag, uint8_t> {
 public:
  Iterator(std::shared_ptr<class HciPacket> packet, size_t i);
  Iterator(const Iterator& itr);

  ~Iterator() {}

  operator bool() const;

  // All addition and subtraction operators are bounded from 0 to the length of
  // the packet.
  Iterator operator+(size_t offset);
  Iterator& operator+=(size_t offset);
  Iterator operator++(int);
  Iterator& operator++();

  Iterator operator-(size_t offset);
  int operator-(Iterator& itr);
  Iterator& operator-=(size_t offset);
  Iterator operator--(int);
  Iterator& operator--();

  Iterator& operator=(const Iterator& itr);

  bool operator!=(Iterator& itr);
  bool operator==(Iterator& itr);

  bool operator<(Iterator& itr);
  bool operator>(Iterator& itr);

  bool operator<=(Iterator& itr);
  bool operator>=(Iterator& itr);

  uint8_t& operator*() const;
  uint8_t* operator->() const;

 private:
  std::shared_ptr<class HciPacket> hci_packet_;
  size_t index_;

};  // Iterator

// HciPacket is an abstract class that will serve as the base class for all
// packet types.
class HciPacket : public std::enable_shared_from_this<HciPacket> {
 public:
  virtual ~HciPacket() = default;

  Iterator get_begin();
  Iterator get_end();

  uint8_t operator[](size_t i);

  virtual size_t get_length() = 0;

  virtual uint8_t& get_at_index(size_t index) = 0;

};  // HciPacket

};  // namespace test_vendor_lib
