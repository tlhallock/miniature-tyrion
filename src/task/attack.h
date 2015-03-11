

#ifndef ATTACK_H_
#define ATTACK_H_

class Attack : public Task
{
private:
    Unit* unit;

public:
    Attack(Unit* unit);
    ~Attack();

    void set_unit(Unit* unit);

    void apply(std::vector<UnitListener*>& listeners);
};


#endif
