#pragma once

#include <functional>
#include <iostream>
#include <stdexcept>

template <typename T, typename E> class Result {
public:
  static Result Ok(T value) { return Result(true, value, E()); }

  static Result Err(E error) { return Result(false, T(), error); }

  bool isOk() const { return is_ok; }

  bool isErr() const { return !is_ok; }

  T unwrap() const {
    if (is_ok)
      return value;
    else
      throw std::runtime_error("Can't call unwrap on an Err value!");
  }

  E unwrapErr() const {
    if (!is_ok)
      return error;
    else
      throw std::runtime_error("Can't call unwrapErr on an Ok value!");
  }

  template <typename U> Result<U, E> map(std::function<U(T)> f) const {
    if (is_ok)
      return Result<U, E>::Ok(f(value));
    else
      return Result<U, E>::Err(error);
  }

  template <typename U>
  Result<U, E> andThen(std::function<Result<U, E>(T)> f) const {
    if (is_ok)
      return f(value);
    else
      return Result<U, E>::Err(error);
  }

private:
  Result(bool is_ok, T value, E error)
      : is_ok(is_ok), value(value), error(error) {}

  bool is_ok;
  T value;
  E error;
};