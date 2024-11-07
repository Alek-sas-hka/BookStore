#include "Book.h"

// Конструкторы
Book::Book() : _year(0), _price(0.0) {}
Book::Book(const std::string& title, const std::string& author, int year,
           double price)
    : _title(title), _author(author), _year(year), _price(price) {}

// Методы для получения значений полей
std::string Book::getTitle() const { return _title; }
std::string Book::getAuthor() const { return _author; }
int Book::getYear() const { return _year; }
double Book::getPrice() const { return _price; }

// Методы для изменения значений полей
void Book::setTitle(const std::string& newTitle) { _title = newTitle; }
void Book::setAuthor(const std::string& newAuthor) { _author = newAuthor; }
void Book::setYear(int newYear) { _year = newYear; }
void Book::setPrice(double newPrice) { _price = newPrice; }

// Операторы сравнения для сортировки
bool operator<(const Book& lhs, const Book& rhs) {
  if (lhs.getTitle() != rhs.getTitle()) {
    return lhs.getTitle() < rhs.getTitle();
  }
  if (lhs.getAuthor() != rhs.getAuthor()) {
    return lhs.getAuthor() < rhs.getAuthor();
  }
  if (lhs.getYear() != rhs.getYear()) {
    return lhs.getYear() < rhs.getYear();
  }
  return lhs.getPrice() < rhs.getPrice();
}

bool operator==(const Book& lhs, const Book& rhs) {
  return lhs.getTitle() == rhs.getTitle() &&
         lhs.getAuthor() == rhs.getAuthor() && lhs.getYear() == rhs.getYear() &&
         lhs.getPrice() == rhs.getPrice();
}

bool operator>(const Book& lhs, const Book& rhs) {
  return !(lhs < rhs) && !(lhs == rhs);
}
