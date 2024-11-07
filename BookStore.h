#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "Book.h"
#include <vector>
#include <string>

enum class SortType { Title, Author, Year };

class BookStore {
 private:
  std::vector<Book> _books;
  size_t _amount = 0;

 public:
  // Методы для работы с книгами
  void addBook(const Book &book);
  bool removeBook(const std::string &title);
  Book* findBook(const std::string &title);
  std::vector<Book> listBooks(SortType sortType) const;
  std::vector<Book> findBooksInPriceRange(double minPrice, double maxPrice) const;
  bool isEmpty() const;
};

#endif // BOOKSTORE_H
