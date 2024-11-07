#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
 private:
  std::string _title;
  std::string _author;
  int _year;
  double _price;

 public:
  // Конструкторы
  Book();
  Book(const std::string& title, const std::string& author, int year,
       double price);

  // Методы для получения значений полей
  std::string getTitle() const;
  std::string getAuthor() const;
  int getYear() const;
  double getPrice() const;

  // Методы для изменения значений полей
  void setTitle(const std::string& newTitle);
  void setAuthor(const std::string& newAuthor);
  void setYear(int newYear);
  void setPrice(double newPrice);
};

// Операторы сравнения
bool operator<(const Book& lhs, const Book& rhs);
bool operator==(const Book& lhs, const Book& rhs);
bool operator>(const Book& lhs, const Book& rhs);

#endif  // BOOK_H
