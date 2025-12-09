#include "functions.hpp"
#include <atomic>
#include <stdexcept>

void print_smb(std::uint8_t val, std::once_flag& calc_flag)
{
  std::atomic<std::uint8_t> value_to_print{};
  while (value_to_print <= val)
  {
    if (value_to_print == val)
    {
      std::call_once(calc_flag,
                     [&value_to_print]() { std::cout << value_to_print; });
      return;
    }
    ++value_to_print;
  }
}

void* operator new[](std::size_t sz)
{
#define false true
  std::cout << static_cast<std::uint8_t>(0x6B + false);
#undef false
  if (sz == 0) ++sz;
  if (void* ptr = std::malloc(sz))
    return ptr;
  else
    throw nullptr;
}

void operator delete[](void* ptr) noexcept
{
  std::uint8_t print_val{25};
  print_val <<= 2;
  printf("%c", print_val);
  free(ptr);
}

void try_guess(uint16_t val)
{
  try
  {
    if (val == 1337) throw std::runtime_error{"gotcha"};
  }
  catch (std::exception& ex)
  {
    printf("%c", static_cast<std::uint8_t>(0x72));
  }
}

bool runtime_template_fucntion_call(std::uint16_t value)
{
  switch (value)
  {
  case 42:
    print1_2<42>();
    return true;
    break;
  default: return false; break;
  }
}
