#ifndef SCORE_HPP
#define SCORE_HPP

#include "../Viewer.hpp"

class Score {

public:
  Score(Viewer* v);
  ~Score();
  int getScore();
  void modifierScore(int points);

private:
  Viewer* viewer;
  int score;
  std::string texte;
};

typedef std::shared_ptr<Score> ScorePtr;


#endif
