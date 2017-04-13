#include "../../include/students/Score.hpp"

Score::Score(Viewer* v) {
  viewer = v;
  score = 0;
  texte = "Score : 0";
  viewer->displayText(texte, std::chrono::seconds(1000000));
}

Score::~Score() {
}

void Score::modifierScore(int points) {
  texte.pop_back();
  if (score >= 10) {
    texte.pop_back();
  }
  score += points;
  texte.append(std::to_string(score));
  viewer->displayText(texte, std::chrono::seconds(1000000));
}
