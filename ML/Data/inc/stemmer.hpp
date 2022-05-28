#ifndef STEMMER_PORTER_H
#define STEMMER_PORTER_H

#include <regex>

using namespace std;

class StemmerPorter {
 private:
  static const wstring EMPTY;
  static const wstring S1;
  static const wstring S13;
  static const wstring SN;
  static const wstring const1;
  static const wregex PERFECTIVEGROUND;
  static const wregex REFLEXIVE;
  static const wregex ADJECTIVE;
  static const wregex PARTICIPLE;
  static const wregex VERB;
  static const wregex NOUN;
  static const wregex I;
  static const wregex P;
  static const wregex NN;
  static const wregex DERIVATIONAL;
  static const wregex DER;
  static const wregex SUPERLATIVE;
  static const wregex PUNCTUATION;

 public:
  StemmerPorter();
  static wstring get(wstring s);
};

#include <algorithm>
#include <clocale>
#include <functional>
#include <iterator>

const wstring StemmerPorter::const1 = L"АЕИОУЫЭИЮЯ";
const wstring StemmerPorter::EMPTY = L"";
const wstring StemmerPorter::S1 = L"$1";
const wstring StemmerPorter::S13 = L"$1$3";
const wstring StemmerPorter::SN = L"Н";

const wregex StemmerPorter::PERFECTIVEGROUND =
    wregex(L"(ИВ|ИВШИ|ИВШИСЬ|ЫВ|ЫВШИ|ЫВШИСЬ|ВШИ|ВШИСЬ)$");
const wregex StemmerPorter::REFLEXIVE = wregex(L"(СЯ|СЬ)$");
const wregex StemmerPorter::ADJECTIVE = wregex(
    L"(ЕЕ|ИЕ|ЫЕ|ОЕ|ИМИ|ЫМИ|ЕЙ|ИЙ|ЫЙ|ОЙ|ЕМ|ИМ|ЫМ|ОМ|ЕГО|ОГО|ЕМУ|ОМУ|ИХ|ЫХ|УЮ|ЮЮ|"
    L"АЯ|ЯЯ|ОЮ|ЕЮ)$");
const wregex StemmerPorter::PARTICIPLE =
    wregex(L"(.*)(ИВШ|ЫВШ|УЮЩ)$|([АЯ])(ЕМ|НН|ВШ|ЮЩ|Щ)$");
const wregex StemmerPorter::VERB = wregex(
    L"(.*)(ИЛА|ЫЛА|ЕНА|ЕЙТЕ|УЙТЕ|ИТЕ|ИЛИ|ЫЛИ|ЕЙ|УЙ|ИЛ|ЫЛ|ИМ|ЫМ|ЕН|ИЛО|ЫЛО|ЕНО|"
    L"ЯТ|УЕТ|УЮТ|ИТ|ЫТ|ЕНЫ|ИТЬ|ЫТЬ|ИШЬ|УЮ|Ю)$|([АЯ])(ЛА|НА|ЕТЕ|ЙТЕ|ЛИ|Й|Л|ЕМ|Н|"
    L"ЛО|НО|ЕТ|ЮТ|НЫ|ТЬ|ЕШЬ|ННО)$");
const wregex StemmerPorter::NOUN = wregex(
    L"(А|ЕВ|ОВ|ИЕ|ЬЕ|Е|ИЯМИ|ЯМИ|АМИ|ЕИ|ИИ|И|ИЕЙ|ЕЙ|ОЙ|ИЙ|Й|ИЯМ|ЯМ|ИЕМ|ЕМ|АМ|ОМ|"
    L"О|У|АХ|ИЯХ|ЯХ|Ы|Ь|ИЮ|ЬЮ|Ю|ИЯ|ЬЯ|Я)$");
const wregex StemmerPorter::I = wregex(L"И$");
const wregex StemmerPorter::P = wregex(L"Ь$");
const wregex StemmerPorter::NN = wregex(L"НН$");
const wregex StemmerPorter::DERIVATIONAL =
    wregex(L".*[^АЕИОУЫЭЮЯ]+[АЕИОУЫЭЮЯ].*ОСТЬ?$");
const wregex StemmerPorter::DER = wregex(L"ОСТЬ?$");
const wregex StemmerPorter::SUPERLATIVE = wregex(L"(ЕЙШЕ|ЕЙШ)$");

const wregex StemmerPorter::PUNCTUATION = wregex(L"[^\\w\\s]$");

StemmerPorter::StemmerPorter() {}

wstring StemmerPorter::get(wstring s) {
  transform(s.begin(), s.end(), s.begin(), towupper);
  replace(s.begin(), s.end(), L'Ё', L'Е');

  size_t pos = s.find_first_of(const1, 0);

  if (pos != wstring::npos) {
    wstring pre = s.substr(0, pos + 1);
    wstring rv = s.substr(pos + 1);
    wstring temp = regex_replace(rv, PERFECTIVEGROUND, EMPTY);

    if (rv.size() != temp.size()) {
      rv = temp;
    }

    else {
      rv = regex_replace(rv, REFLEXIVE, EMPTY);
      temp = regex_replace(rv, ADJECTIVE, EMPTY);

      if (rv.size() != temp.size()) {
        rv = temp;
        rv = regex_replace(rv, PARTICIPLE, S13);
      }

      else {
        temp = regex_replace(rv, VERB, S13);
        if (rv.size() != temp.size()) {
          rv = temp;
        } else {
          rv = regex_replace(temp, NOUN, EMPTY);
        }
      }
    }

    rv = regex_replace(rv, I, EMPTY);

    if (regex_match(rv, DERIVATIONAL)) {
      rv = regex_replace(rv, DER, EMPTY);
    }

    temp = regex_replace(rv, P, EMPTY);

    if (temp.length() != rv.length()) {
      rv = temp;
    }

    else {
      rv = regex_replace(rv, SUPERLATIVE, EMPTY);
      rv = regex_replace(rv, NN, SN);
    }
    s = pre + rv;
  }

  transform(s.begin(), s.end(), s.begin(), towlower);
  return s;
}

#endif  // STEMMER_PORTER_H