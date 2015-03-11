

#ifndef DESTRUCTIBLE_H_
#define DESTRUCTIBLE_H_

namespace aoe
{

class Destructible
{
 private:
  double health;

 public:
  Destructible();
  ~Destructible();

  void increment_health(double amount);

};


}


#endif
