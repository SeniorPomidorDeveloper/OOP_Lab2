#include <gtest/gtest.h>
#include <numeric>
#include <sstream>

#include "../src/libs/dice/dice.hpp"

TEST(DiceTest, DefaultConstructor)
{
    Dice dice = Dice();
    ASSERT_EQ(dice.get_size(), 0);
}

TEST(DiceTest, CopyConstructor)
{
    Dice dice = Dice();
    Dice copy = Dice(dice);
    ASSERT_EQ(copy.get_size(), 0);
}

TEST(DiceTest, MoveConstructor)
{
    Dice dice = Dice(Vector<NumPoints>({1}));
    Dice copy = std::move(dice);
    ASSERT_TRUE(copy.has_NumPoints(1));
}

TEST(DiceTest, ConstructorWithSize)
{
    Dice dice = Dice(3);
    ASSERT_EQ(dice.get_size(), 3);
}

TEST(DiceTest, ConstructorWithValues)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    ASSERT_EQ(dice.sum(), 15);
}

TEST(DiceTest, GetAsciiArt)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    OneDice dices[5] = {OneDice(1), OneDice(2), OneDice(3), OneDice(4), OneDice(5)};
    AsciiArt art = std::accumulate(dices + 1, dices + 5, dices[0].get_value_AsciiArt(),
                                   [](AsciiArt &a, const OneDice &b) { return a + b.get_value_AsciiArt(); });
    std::ostringstream ss;
    std::ostringstream answer;
    ss << dice.get_AsciiArt();
    answer << art;
    ASSERT_EQ(ss.str(), answer.str());
}

TEST(DiceTest, HasNumPoints)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    ASSERT_TRUE(dice.has_NumPoints(1));
    ASSERT_TRUE(dice.has_NumPoints(2));
    ASSERT_TRUE(dice.has_NumPoints(3));
    ASSERT_TRUE(dice.has_NumPoints(4));
    ASSERT_TRUE(dice.has_NumPoints(5));
    ASSERT_FALSE(dice.has_NumPoints(6));
    ASSERT_THROW(dice.has_NumPoints(7), std::invalid_argument);
}

TEST(DiceTest, OperatorCopy)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    size_t size = dice.get_size();
    dice();
    ASSERT_EQ(dice.get_size(), size);
}

TEST(DiceTest, OperatorScope)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    size_t size = dice.get_size();
    dice();
    ASSERT_EQ(dice.get_size(), size);
}

TEST(DiceTest, OperatorIndexScope)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    size_t size = dice.get_size();
    NumPoints n = dice(0);
    ASSERT_EQ(n, dice[0].get_value());
    ASSERT_THROW(dice(7), std::out_of_range);
}

TEST(DiceTest, OperatorPlus)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    dice += OneDice(6);
    ASSERT_TRUE(dice.has_NumPoints(6));
}

TEST(DiceTest, OperatorMinus)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 1, 4, 5}));
    dice -= 2;
    ASSERT_FALSE(dice.has_NumPoints(2));
    dice -= 1;
    ASSERT_FALSE(dice.has_NumPoints(1));
    ASSERT_TRUE(dice.has_NumPoints(4));
    ASSERT_THROW(dice -= 0, std::invalid_argument);
}

TEST(DiceTest, OperatorQaterScope)
{
    Dice dice = Dice(Vector<NumPoints>({1, 2, 3, 4, 5}));
    OneDice dices[5] = {OneDice(1), OneDice(2), OneDice(3), OneDice(4), OneDice(5)};
    for (size_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(dice[i], dices[i]);
    }
    ASSERT_THROW(dice[7], std::out_of_range);
}

TEST(DiceTest, OperatorInput)
{
    std::istringstream ss("3 1 2 3");
    Dice dice;
    ss >> dice;
    ASSERT_EQ(dice.get_size(), 3);
    ASSERT_TRUE(dice.has_NumPoints(1));
    ASSERT_TRUE(dice.has_NumPoints(2));
    ASSERT_TRUE(dice.has_NumPoints(3));
}

TEST(DiceTest, OperatorOutput)
{
    std::ostringstream ss, answer("{1, 2, 3}");
    Dice dice = Dice({1, 2, 3});
    ss << dice;
    ASSERT_EQ(ss.str(), answer.str());
}

TEST(OneDiceTest, CopyConstructor)
{
    OneDice dice = OneDice(3);
    OneDice copy = OneDice(dice);
    ASSERT_EQ(dice.get_value(), copy.get_value());
}

TEST(OneDiceTest, MoveConstructor)
{
    OneDice dice = OneDice(3);
    OneDice copy = OneDice(std::move(dice));
    ASSERT_EQ(copy.get_value(), 3);
}

TEST(OneDiceTest, GetOdds)
{
    Chance ch[6] = {1, 2, 3, 4, 5, 6};
    Odds data(ch);
    OneDice dice(data);
    Odds result = dice.get_odds();
    for (size_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(data[i], result[i]);
    }
}

TEST(OneDiceTest, OperatorInput)
{
    Chance ch[6] = {1, 2, 3, 4, 5, 6};
    Odds data(ch);
    std::istringstream ss("3 1 2 3 4 5 6");
    OneDice dice;
    ss >> dice;
    ASSERT_EQ(dice.get_value(), 3);
    Odds result = dice.get_odds();
    for (size_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(data[i], result[i]);
    }
}

TEST(OneDiceTest, OperatorOutput)
{
    Chance ch[6] = {1, 2, 3, 4, 5, 6};
    Odds data(ch);
    std::ostringstream ss, answer("{value: 3; odds: {1, 2, 3, 4, 5, 6}}");
    OneDice dice(3, data);
    ss << dice;
    ASSERT_EQ(ss.str(), answer.str());
}

TEST(OddsTest, CopyConstructor)
{
    Chance ch[6] = {1, 2, 3, 4, 5, 6};
    Odds data(ch);
    Odds copy = Odds(std::move(data));
    for (size_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(data[i], i + 1);
    }
}