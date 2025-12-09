#pragma once
#include <functional>
#include <iostream>
#include <mutex>

void print_smb(std::uint8_t val, std::once_flag& calc_flag);
void* operator new[](std::size_t sz);
void operator delete(void* ptr) noexcept;
void try_guess(uint16_t val);
bool runtime_template_fucntion_call(uint16_t value);

template <short num> void fn_taker(std::function<void(int8_t)>& printer)
{
  printer(num);
}

template <short num> inline void print1_2() {}

template <> inline void print1_2<42>()
{
  std::cout << static_cast<std::uint8_t>(42 ^ 69);
}
