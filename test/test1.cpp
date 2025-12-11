#include <gtest/gtest.h>
#include "../include/Twelve.h"

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
    EXPECT_EQ(num.getSize(), 1);
    EXPECT_EQ(num.getDigit(0), 0);
    EXPECT_EQ(num.toString(), "0");
}

TEST(TwelveTest, SizeAndValueConstructor) {
    Twelve num(3, 5);
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.getDigit(0), 5);
    EXPECT_EQ(num.getDigit(1), 5);
    EXPECT_EQ(num.getDigit(2), 5);
    EXPECT_EQ(num.toString(), "555");
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num({'1', 'A', 'B'});
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.getDigit(0), 11);
    EXPECT_EQ(num.getDigit(1), 10);
    EXPECT_EQ(num.getDigit(2), 1);
    EXPECT_EQ(num.toString(), "1AB");
}

TEST(TwelveTest, StringConstructor) {
    Twelve num("1AB");
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.getDigit(0), 11);
    EXPECT_EQ(num.getDigit(1), 10);
    EXPECT_EQ(num.getDigit(2), 1);
    EXPECT_EQ(num.toString(), "1AB");
}

TEST(TwelveTest, UnsignedIntConstructor) {
    Twelve num(171u);
    EXPECT_EQ(num.getSize(), 3);
    EXPECT_EQ(num.getDigit(0), 3);
    EXPECT_EQ(num.getDigit(1), 2);
    EXPECT_EQ(num.getDigit(2), 1);
    EXPECT_EQ(num.toString(), "123");
}

TEST(TwelveTest, CopyConstructor) {
    Twelve original({'1', 'A', 'B'});
    Twelve copy(original);
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.getDigit(0), 11);
    EXPECT_EQ(copy.getDigit(1), 10);
    EXPECT_EQ(copy.getDigit(2), 1);
    EXPECT_EQ(copy.toString(), "1AB");
}

TEST(TwelveTest, CopyFunc) {
    Twelve original({'1', 'A', 'B'});
    Twelve copy = original.copy();
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.getDigit(0), 11);
    EXPECT_EQ(copy.getDigit(1), 10);
    EXPECT_EQ(copy.getDigit(2), 1);
    EXPECT_EQ(copy.toString(), "1AB");
}

TEST(TwelveTest, Addition) {
    Twelve num1("12");
    Twelve num2("B");
    Twelve result = num1.plus(num2);
    EXPECT_EQ(result.toString(), "21");
}

TEST(TwelveTest, AdditionWithCarry) {
    Twelve num1("B");
    Twelve num2("1");
    Twelve result = num1.plus(num2);
    EXPECT_EQ(result.toString(), "10");
}

TEST(TwelveTest, Subtraction) {
    Twelve num1("21");
    Twelve num2("B");
    Twelve result = num1.minus(num2);
    EXPECT_EQ(result.toString(), "12");
}

TEST(TwelveTest, SubtractionThrowsWhenNegative) {
    Twelve num1("5");
    Twelve num2("A");
    EXPECT_THROW({
        num1.minus(num2);
    }, std::logic_error);
}

TEST(TwelveTest, Equality) {
    Twelve num1("1AB");
    Twelve num2("1AB");
    Twelve num3("1AA");
    EXPECT_TRUE(num1.equal(num2));
    EXPECT_FALSE(num1.equal(num3));
}

TEST(TwelveTest, LessThan) {
    Twelve num1("A");
    Twelve num2("10");
    Twelve num3("B");
    EXPECT_TRUE(num1.less(num2));
    EXPECT_TRUE(num1.less(num3));
    EXPECT_FALSE(num2.less(num1));
}

TEST(TwelveTest, GreaterThan) {
    Twelve num1("10");
    Twelve num2("A");
    EXPECT_TRUE(num1.greater(num2));
    EXPECT_FALSE(num2.greater(num1));
}

TEST(TwelveTest, GetSize) {
    Twelve empty;
    Twelve single("5");
    Twelve multiple("123AB");
    EXPECT_EQ(empty.getSize(), 1);
    EXPECT_EQ(single.getSize(), 1);
    EXPECT_EQ(multiple.getSize(), 5);
}

TEST(TwelveTest, GetDigit) {
    Twelve num("1A3");
    EXPECT_EQ(num.getDigit(0), 3);
    EXPECT_EQ(num.getDigit(1), 10);
    EXPECT_EQ(num.getDigit(2), 1);
    EXPECT_THROW({
        num.getDigit(3);
    }, std::out_of_range);
}

TEST(TwelveTest, ToString) {
    Twelve num1({'1', 'A', 'B'});
    Twelve num2("5");
    Twelve num3(0u);
    EXPECT_EQ(num1.toString(), "1AB");
    EXPECT_EQ(num2.toString(), "5");
    EXPECT_EQ(num3.toString(), "0");
}

TEST(TwelveTest, Normalization) {
    Twelve num({'0', '0', '1', '2'});
    EXPECT_EQ(num.getSize(), 2);
    EXPECT_EQ(num.getDigit(0), 2);
    EXPECT_EQ(num.getDigit(1), 1);
    EXPECT_EQ(num.toString(), "12");
}

TEST(TwelveTest, IsValidDigit) {
    EXPECT_TRUE(Twelve::isValidDigit(0));
    EXPECT_TRUE(Twelve::isValidDigit(5));
    EXPECT_TRUE(Twelve::isValidDigit(11));
    EXPECT_FALSE(Twelve::isValidDigit(12));
    EXPECT_FALSE(Twelve::isValidDigit(15));
}

TEST(TwelveTest, CharToDigit) {
    EXPECT_EQ(Twelve::charToDigit('0'), 0);
    EXPECT_EQ(Twelve::charToDigit('5'), 5);
    EXPECT_EQ(Twelve::charToDigit('9'), 9);
    EXPECT_EQ(Twelve::charToDigit('A'), 10);
    EXPECT_EQ(Twelve::charToDigit('B'), 11);
    EXPECT_EQ(Twelve::charToDigit('a'), 10);
    EXPECT_EQ(Twelve::charToDigit('b'), 11);
    EXPECT_THROW({
        Twelve::charToDigit('C');
    }, std::invalid_argument);
    EXPECT_THROW({
        Twelve::charToDigit('Z');
    }, std::invalid_argument);
}

TEST(TwelveTest, DigitToChar) {
    EXPECT_EQ(Twelve::digitToChar(0), '0');
    EXPECT_EQ(Twelve::digitToChar(5), '5');
    EXPECT_EQ(Twelve::digitToChar(9), '9');
    EXPECT_EQ(Twelve::digitToChar(10), 'A');
    EXPECT_EQ(Twelve::digitToChar(11), 'B');
    EXPECT_THROW({
        Twelve::digitToChar(12);
    }, std::invalid_argument);
    EXPECT_THROW({
        Twelve::digitToChar(15);
    }, std::invalid_argument);
}

TEST(TwelveTest, InvalidDigitInConstructor) {
    EXPECT_THROW({
        Twelve num(3, 15);
    }, std::invalid_argument);
    EXPECT_THROW({
        Twelve num({'1', 'C', '3'});
    }, std::invalid_argument);
    EXPECT_THROW({
        Twelve num("1C2");
    }, std::invalid_argument);
}

TEST(TwelveTest, EmptyStringConstructor) {
    Twelve empty("");
    EXPECT_EQ(empty.getSize(), 1);
    EXPECT_EQ(empty.getDigit(0), 0);
    EXPECT_EQ(empty.toString(), "0");
}

TEST(TwelveTest, ComplexOperations) {
    Twelve a("1A3");
    Twelve b("B2");
    Twelve c = a.plus(b);
    EXPECT_EQ(c.toString(), "295");
    Twelve d = a.minus(b);
    EXPECT_EQ(d.toString(), "B1");
}

TEST(TwelveTest, ZeroHandling) {
    Twelve zero1(0u);
    Twelve zero2("");
    Twelve zero3({'0'});
    EXPECT_TRUE(zero1.equal(zero2));
    EXPECT_TRUE(zero2.equal(zero3));
    EXPECT_EQ(zero1.toString(), "0");
    EXPECT_EQ(zero2.toString(), "0");
    EXPECT_EQ(zero3.toString(), "0");
}

TEST(TwelveTest, Print) {
    Twelve num({'1', 'A', 'B'});
    testing::internal::CaptureStdout();
    num.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1AB");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
