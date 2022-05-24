/*
#include <iostream>
#include "dataset.h"
#include "vectorizer.h"
#include "interfaces_use_case.h"
bool Run(std::shared_ptr<IAnalysisText const> interface,
         std::string const& str) {
  return interface->AnalysisText(str);
}
void Tests() {
  {
    std::string str = "привет как дела";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "слышал последние новости о путине";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }
  {
    std::string str = "предлагаю сходить в хороший бар";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "россия и украина должна жить в мире";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }
  {
    std::string str = "лучше гор могут быть только горы";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "что ты можешь сказать об афганской войне";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == true);
  }
  {
    std::string str = "хочу на рыбалку но жена меня не пускает";
    auto analyser = std::make_shared<NN const>();
    assert(Run(analyser, str) == false);
  }
  {
    std::string str = "завтра будут политические дебаты про украину предлагаю посмотреть"; 
    auto analyser = std::make_shared<NN>(); 
    assert(Run(analyser, str) == true);
  }
}
*/