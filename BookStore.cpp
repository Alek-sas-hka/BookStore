#include "BookStore.h"

#include <algorithm>

void BookStore::addBook(const Book& book) {
  _books.push_back(book);
  ++_amount;
}

Book* BookStore::findBook(const std::string& title) {
  auto it = std::find_if(
      _books.begin(), _books.end(),
      [&title](const Book& book) { return book.getTitle() == title; });
  return (it != _books.end()) ? &(*it) : nullptr;
}

bool BookStore::removeBook(const std::string& title) {
  Book* book = findBook(title);

  if (book == nullptr) {
    return false;
  }

  auto it = _books.begin() + (book - &_books[0]);
  _books.erase(it);
  --_amount;
  return true;
}

std::vector<Book> BookStore::listBooks(SortType sortType) const {
  // Создаем копию вектора _books
  std::vector<Book> sortedBooks = _books;

  // Сортируем в зависимости от типа сортировки
  switch (sortType) {
    case SortType::Title:
      std::sort(sortedBooks.begin(), sortedBooks.end(),
                [](const Book& a, const Book& b) {
                  return a.getTitle() < b.getTitle();
                });
      break;
    case SortType::Author:
      std::sort(sortedBooks.begin(), sortedBooks.end(),
                [](const Book& a, const Book& b) {
                  return a.getAuthor() < b.getAuthor();
                });
      break;
    case SortType::Year:
      std::sort(sortedBooks.begin(), sortedBooks.end(),
                [](const Book& a, const Book& b) {
                  return a.getYear() < b.getYear();
                });
      break;
  }
  return sortedBooks;
}

std::vector<Book> BookStore::findBooksInPriceRange(double minPrice,
                                                   double maxPrice) const {
  // Создаем копию вектора _books
  std::vector<Book> BooksInPriceRange;

  std::copy_if(
      _books.begin(), _books.end(), std::back_inserter(BooksInPriceRange),
      [minPrice, maxPrice](const Book& book) {
        return book.getPrice() >= minPrice && book.getPrice() <= maxPrice;
      });

  return BooksInPriceRange;
}

bool BookStore::isEmpty() const { return _amount == 0; }