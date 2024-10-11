#include <iostream>
#include <random>
#include <fstream>

class X { 
public:

    virtual unsigned roll() = 0;

    virtual ~X() = default;
};

class Dice: public X {
public:
    Dice()
        : max(1), dstr(1,max), reng(3) { }

    Dice(unsigned max, unsigned seed)
        : max(max), dstr(1, max), reng(seed) { }

    unsigned roll() override {
        return dstr(reng);
    }

    ~Dice() { }

protected:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public X {
public:
    // можно ли сохранить явный конструктор, когда мы передаём значения max и seed

    ThreeDicePool(X &d_1, X &d_2, X &d_3)
        : d1(&d_1), d2(&d_2), d3(&d_3) { }

    unsigned roll() override {
        return d1->roll() + d2->roll() + d3->roll();
    }

    ~ThreeDicePool() { }
    
protected:
    X *d1, *d2, *d3;
};

class PenaltyDice : public X {
public:
    PenaltyDice() = default;
    PenaltyDice(X &d)
    : d1(&d), d2(&d) { }

    unsigned roll() override {
        return std::min(d1->roll(), d2->roll());
    }

    ~PenaltyDice() { }
private:
    X *d1, *d2;
};

class BonusDice : public X {
public:
    BonusDice() = default;
    BonusDice(X &d)
    : d1(&d), d2(&d) { }

    unsigned roll() override {
        return std::max(d1->roll(), d2->roll());
    }

    ~BonusDice() { }
private:
    X *d1, *d2;
};

// 
// 
// class DoubleDice: public X {
// public:
//     DoubleDice(X& d)
//     : Bonu(d), PenaltyDice(d) { }

//     unsigned roll() override {
//         return BonusDice::roll() + PenaltyDice::roll();
//     }

//     ~DoubleDice() = default;
// // private:
// //     BonusDice b_d;
// //     PenaltyDice p_d;
// };
// 
// 

double expected_value(X& d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(unsigned value, X &d, unsigned number_of_rolls = 1) {
    unsigned counter = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; cnt++)
        if (value == d.roll())
            counter++; 
    return static_cast<double>(counter) / static_cast<double>(number_of_rolls);
}

int main() {
    
    unsigned int number_of_rolls = 1'000'000;
    
    std::ofstream out;

    Dice dice(100, 42);
    Dice dice_(6, 125);
    ThreeDicePool three_dice_pool(dice_, dice_, dice_);
    BonusDice bonusdice(dice);
    BonusDice bonusdice3(three_dice_pool);
    PenaltyDice penaltydice(dice);
    PenaltyDice penaltydice3(three_dice_pool);
    // DoubleDice doubledice(dice);

    std::cout << "Expected value for Dice: " << expected_value(dice, number_of_rolls) << '\n';
    std::cout << "Expected value for ThreeDicePool: " << expected_value(three_dice_pool, number_of_rolls) << '\n';
    // std::cout << "Expected value for DoubleDice: " << expected_value(doubledice, number_of_rolls) << '\n';
    std::cout << "Bonus1: " << bonusdice.roll() << '\n';
    std::cout << "Bonus3: " << bonusdice3.roll() << '\n';
    std::cout << "Penalty1: " << penaltydice.roll() << '\n';
    std::cout << "Penalty3: " << penaltydice3.roll() << '\n';
    // std::cout << "Doubledice: " << doubledice.roll() << std::endl;


    out.open("data/dice.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, dice, number_of_rolls) << std::endl;
    }
    
    out.close();

    out.open("data/pen_dice.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, penaltydice, number_of_rolls) << std::endl;
    }
    
    out.close();

    out.open("data/bon_dice.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, bonusdice, number_of_rolls) << std::endl;
    }
    
    out.close();

    out.open("data/dice3.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, three_dice_pool, number_of_rolls) << std::endl;
    }
    
    out.close();

    out.open("data/pen_dice3.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, penaltydice3, number_of_rolls) << std::endl;
    }
    
    out.close();

    out.open("data/bon_dice3.txt", std::ios::app);

    for (unsigned i = 1; i != 101; i++) {
        out << value_probability(i, bonusdice3, number_of_rolls) << std::endl;
    }
    
    out.close();

    // out.open("data/doubledice.txt", std::ios::app);

    // for (unsigned i = 1; i != 101; i++) {
    //     out << value_probability(i, doubledice, number_of_rolls) << std::endl;
    // }
    
    // out.close();

    return 0;
}

// out.open("lab1_bin_bad.txt", std::ios::app);
// out << time_span.count() << std::endl;
// out.close(); 
