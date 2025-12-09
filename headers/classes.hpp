#pragma once
#include <bitset>
#include <cstdint>
#include <string>

class base
{
  public:
    base(const std::string&& str, std::uint16_t index);
    virtual void basic() const;

  private:
    char symbol;
};

template <int index> class derived : base
{
  public:
    derived()
        : base{"0", 0}
    {
      if (index > 255)
      {
        exit(0x16);
      }
    };
    virtual void basic() const override
    {
      char c{index};
      printf("%c", c);
    };
};

class num_base
{
  public:
    constexpr static std::uint32_t BYTE_SIZE = 8;
    num_base(std::bitset<8>&& bin_symbols);
    void hex(std::string&& hex_val);

  private:
    char hex_code[2];
};

class io_stuff
{
  public:
    io_stuff(unsigned char symbol);

  private:
    unsigned char smb;
};

class asm_block
{
  public:
    asm_block(std::uint8_t octal_value);

  private:
    std::uint16_t to_dec(std::uint8_t oct_val);
    std::uint16_t get_degree(std::uint16_t num, std::uint16_t _degree);
};
