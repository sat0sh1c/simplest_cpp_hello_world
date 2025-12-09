#include "headers/classes.hpp"
#include <cstdint>
#include <cstdlib>
#include <print>

base::base(const std::string&& str, std::uint16_t num)
    : symbol(str[num]) {};

void base::basic() const
{
  std::print("{}", symbol);
}

num_base::num_base(std::bitset<num_base::BYTE_SIZE>&& bin_symbols)
    : hex_code{}
{

  std::uint8_t result{};
  std::uint32_t value{};
  std::uint32_t bit_iter{};

  for (std::uint32_t i = 0; i < num_base::BYTE_SIZE; ++i)
  {
    switch (bin_symbols[i])
    {
    case 1:
      switch (bit_iter++)
      {
      case 0: value += 8; break;

      case 1: value += 4; break;

      case 2: value += 2; break;

      default: value += 1; break;
      }
      break;

    case 0: bit_iter++; break;
    }

    if (i == 3 || i == 7)
    {
      hex_code[i > 4 ? 1 : 0] = value;
      value                   = 0;
      bit_iter                = 0;
    }
  }

  result = hex_code[0] * 16 + hex_code[1];
  std::print("{:c}", result);
}

void num_base::hex(std::string&& hex_val)
{
  std::uint8_t val{};
  for (std::uint32_t i = 0; i < hex_val.length(); ++i)
  {
    if (!std::isdigit(hex_val[i]))
    {
      if (hex_val.length() - 1 == i)
      {
        switch (hex_val[i])
        {
        case 'F': val += 0xF; break;

        case 'E': val += 0xE; break;

        case 'D': val += 0xD; break;

        case 'C': val += 0xC; break;

        case 'B': val += 0xC; break;

        case 'A': val += 0xA; break;
        }
      }
    }
    else
    {
      if (hex_val.length() - 1 == i)
      {
        val += hex_val[i];
      }
      val += hex_val[i] * 16;
    }
  }
  std::print("{:c}", val);
};

io_stuff::io_stuff(std::uint8_t symbol)
    : smb(symbol)
{
  // this thing was done with iostream initially but for some reason just the
  // usage of it printed some random characters like "ld" or smth in my terminal
  FILE* herp_writer = fopen("file.txt", "w");

  if (!herp_writer)
  {
    exit(-1);
  }

  if (fwrite(&smb, 1, 1, herp_writer) != 1)
  {
    exit(-1);
  }

  static_cast<void>(fclose(herp_writer));
  herp_writer = nullptr;

  FILE* herp     = fopen("file.txt", "r");
  char char_read = static_cast<char>(fgetc(herp));
  if (char_read == EOF)
  {
    exit(-1);
  }

  static_cast<void>(fclose(herp));
  herp = nullptr;

  std::print("{:c}", char_read);
}

asm_block::asm_block(std::uint8_t octal_value)
{
  char print_char[1];
  print_char[0] = static_cast<uint8_t>(to_dec(octal_value));
#if defined(__linux__)
  asm volatile("mov %0, %%eax\n\t"
               "push %%eax\n\t"
               "call printf\n\t"
               "add $4, %%esp\n\t"
               :
               : "r"(print_char)
               : "eax", "memory");
#elif defined(_WIN32)
  __asm
      {
        lea eax, arr
        push eax
        call printf
        add esp, 4
      }
#endif
}

std::uint16_t asm_block::to_dec(std::uint8_t oct_val)
{
  std::uint16_t result{};
  std::string temp{std::to_string(oct_val)};
  if (std::to_string(oct_val).length() > 3 ||
      temp.find('9') != std::string::npos ||
      temp.find('8') != std::string::npos)
  {
    exit(0x228);
  }
  int degree_to(temp.length() - 1);
  for (int i = 0; i < static_cast<int>(temp.length()); ++i)
  {
    result += (temp[i] - '0') * get_degree(8, degree_to);
    --degree_to;
  }
  return result;
}

std::uint16_t asm_block::get_degree(std::uint16_t num, std::uint16_t _degree)
{
  if (_degree)
  {
    int saver{num};
    for (int i = 1; i < _degree; ++i)
    {
      num *= saver;
    }
    return num;
  }
  return 1;
}
