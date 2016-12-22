/**
 *  @autor arssivka
 *  @date 11/28/16
 */


#include "gtest/gtest.h"
#include <list>
#include <functional>
#include <rrc/core/MetaFunctions.h>
#include <rrc/core/MetaGenerators.h>
#include <rrc/core/MetaArray.h>

using namespace rrc::meta;
using namespace rrc;

typedef int fuck;

class MetaTestClassFixture : public ::testing::Test {
public:
    MetaTestClassFixture () = default;
    float getSomeTest(int x, bool y, double z) {
        return 70.0;
    }
};


TEST(MetaTest, FunctionTraits) {
    typedef std::function<void(float, char[4], int)> Function;
    typedef FunctionTraits<Function> Traits;
    bool result = std::is_same<Traits::Result, void>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, float>::value;
    EXPECT_TRUE(first);
    bool second = std::is_same<Traits::Arg<1>, char*>::value;
    EXPECT_TRUE(second);
    bool third = std::is_same<Traits::Arg<2>, fuck>::value;
    EXPECT_TRUE(third);
    size_t count = Traits::count;
    EXPECT_EQ(count, (size_t)3);
}

bool func(int) {
    return true;
}


TEST(MetaTest, FuntionTraitsPtr) {
    typedef FunctionTraits<decltype(&func)> Traits;
    bool result = std::is_same<Traits::Result, bool>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, fuck>::value;
    EXPECT_TRUE(first);
    size_t count = Traits::count;
    EXPECT_EQ(count, (size_t)1);
}


TEST(MetaTest, ArrayGenerator) {
    auto count = ArrayGenerator<int8_t, 1, 2, 3>::size;
    EXPECT_EQ(count, (size_t)3);
    auto array = ArrayGenerator<int8_t, 1, 2, 3>::data;
    std::array<int8_t, 3> val = array;
    EXPECT_TRUE(val == array);
}


TEST(MetaTest, Rename) {
    typedef std::vector<int> a;
    typedef std::list<int> b;
    bool eq = std::is_same<Rename<a, std::list>, b>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaTest, Length) {
    auto len = rrc::meta::Length<fuck, float, double>::value;
    EXPECT_EQ(len, (size_t)3);
}


TEST(MetaTest, Size) {
    auto size = Size<std::pair<fuck, float>>::value;
    EXPECT_EQ(size, (size_t)2);
}


TEST(MetaTest, PushFront) {
    typedef PushFront<List<float>, fuck> push;
    bool pushed = std::is_same<List<fuck, float>, push>::value;
    EXPECT_TRUE(pushed);
}


TEST(MetaTest, Front) {
    typedef Front<List<float, fuck>> push;
    bool front = std::is_same<float, push>::value;
    EXPECT_TRUE(front);
}


TEST(MetaTest, PopFront) {
    typedef PopFront<List<float, fuck>> push;
    bool front = std::is_same<List<fuck>, push>::value;
    EXPECT_TRUE(front);
}

TEST(MetaTest, TrueFalse) {
    EXPECT_NE(True::value, False::value);
}

TEST(MetaTest, Empty) {
    typedef List<fuck, fuck, fuck, fuck> FUCK;
    typedef List<> EMPTY;
    bool nempty = Empty<FUCK>::value;
    EXPECT_FALSE(nempty);
    bool empty = Empty<EMPTY>::value;
    EXPECT_TRUE(empty);
}

TEST(MetaTest, Clear) {
    typedef Clear<List<fuck,fuck,fuck,fuck>> FUCK;
    bool eq = std::is_same<FUCK, List<>>::value;
    EXPECT_TRUE(eq);
}

template <class A>
using AddPointer = typename std::add_pointer<A>::type;

TEST(MetaTest, Transform) {
    typedef Transform<AddPointer , List<fuck, fuck, fuck>> DIRECTIONAL_FUCK;
    bool same = std::is_same<DIRECTIONAL_FUCK, List<fuck*, fuck*, fuck*>>::value;
    EXPECT_TRUE(same);
}

TEST(MetaTest, Append) {
    typedef Append<List<float>, List<fuck, fuck>, List<fuck, fuck, fuck>> append;
    bool back =std::is_same<List<float, fuck, fuck, fuck, fuck, fuck>, append>::value;
    EXPECT_TRUE(back);
}

TEST(MetaTest, AppendSequence) {
    typedef AppendSequence <IntegralSequence<fuck, 1, 2, 3>, IntegralSequence<fuck, 4, 5, 6>, IntegralSequence<fuck, 7, 8, 9>> append;
    bool back =std::is_same<IntegralSequence<fuck, 1, 2, 3, 4, 5, 6, 7, 8, 9>, append>::value;
    EXPECT_TRUE(back);
}

TEST_F(MetaTestClassFixture, MethodTraits) {
    typedef MethodTraits<decltype(&MetaTestClassFixture::getSomeTest)> Traits;
    bool result = std::is_same<Traits::Result, float>::value;
    EXPECT_TRUE(result);
    bool first = std::is_same<Traits::Arg<0>, fuck>::value;
    EXPECT_TRUE(first);
    bool second = std::is_same<Traits::Arg<1>, bool>::value;
    EXPECT_TRUE(second);
    bool third = std::is_same<Traits::Arg<2>, double>::value;
    EXPECT_TRUE(third);
    size_t count  = Traits::count;
    EXPECT_EQ((size_t)3, count);
}

TEST(MetaTest, GetSequence) {
    typedef RenameSequence<IntegralSequence<fuck, 1, 2, 3>, ArrayGenerator<fuck>> array;
    auto array1 = array::data;
    auto array2 = std::array<fuck, 3>{1, 2, 3};
    EXPECT_EQ(array1, array2);
}

TEST(MetaTest, Pack) {
    typedef Pack<fuck, 1, 2> pack;
    auto value = pack::value;
    EXPECT_EQ(value, 0x10002);
    typedef Pack<short, 1, 2> pack2;
    auto value2 = pack2::value;
    EXPECT_EQ(value2, 0x0102);
    typedef Pack<long int, 1, 2> pack3;
    auto value3 = pack3::value;
    EXPECT_EQ(value3, 0x100000002);
}

TEST(MetaTest, Packer) {
    typedef Packer<ArrayGenerator<short>, IntegralSequence<short, 1>> packer;
    std::array<short, 1> array{0x01};
    auto packed = packer::data;
    EXPECT_EQ(array, packed);
    typedef Packer<ArrayGenerator<short>, IntegralSequence<short, 1, 2, 3>> packer2;
    std::array<short, 2> array2{0x0102, 0x03};
    auto packed2 = packer2::data;
    EXPECT_EQ(array2, packed2);
    typedef Packer<ArrayGenerator<short>, IntegralSequence<short, 1, 2, 3, 4>> packer3;
    std::array<short, 2> array3{0x0102, 0x0304};
    auto packed3 = packer3::data;
    EXPECT_EQ(array3, packed3);
}

TEST(MetaTest, PackedArrayGenerator) {
    typedef PackedArrayGenerator<short, 1, 2, 3> generator;
    std::array<short, 2> array{0x0102, 0x03};
    auto packed = generator::data;
    EXPECT_EQ(array, packed);
    auto size = generator::size;
    EXPECT_EQ(size, (size_t)2);
    typedef PackedArrayGenerator<short, 1, 2> generator2;
    std::array<short, 1> array2{0x0102};
    auto packed2 = generator2::data;
    EXPECT_EQ(array2, packed2);
    auto size2 = generator2::size;
    EXPECT_EQ(size2, (size_t)1);
    typedef PackedArrayGenerator<short, 1, 2, 3, 4> generator3;
    std::array<short, 2> array3{0x0102, 0x0304};
    auto packed3 = generator3::data;
    EXPECT_EQ(array3, packed3);
    auto size3 = generator3::size;
    EXPECT_EQ(size3, (size_t)2);
}

TEST(MetaTest, CleanType) {
    typedef CleanType<const int> inttype;
    bool eq1 = std::is_same<int, inttype>::value;
    EXPECT_TRUE(eq1);
    typedef CleanType<std::vector<int>> inttype1;
    bool eq2 = std::is_same<int, inttype1>::value;
    EXPECT_TRUE(eq2);
    typedef CleanType<std::string> chartype;
    bool eq3 = std::is_same<char, chartype>::value;
    EXPECT_TRUE(eq3);
    typedef CleanType<std::vector<std::vector<int>>> inttype2;
    bool eq4 = std::is_same<int, inttype2>::value;
    EXPECT_TRUE(eq4);
}


TEST(MetaTest, Concatenator) {
    //TODO: It's not working. Fix it.
//    typedef Concatenator<List<int, float>, List<bool, bool, double>> concatenator;
//    bool eq = std::is_same<List<int, float, bool, double>, concatenator >::value;
//    EXPECT_TRUE(eq);
////    typedef Concatenator<List<int, int>, bool> concatenator;
////    bool eq = std::is_same<List<int, float, bool, double>, concatenator >::value;
////    EXPECT_TRUE(eq);
}

TEST(MetaTest, SequenceConcatenator) {
    //TODO: Maybe you need other functionaluity from this?
    typedef SequenceConcatenator<IntegralSequence<short, 1, 2, 3>, IntegralSequence<short, 4, 5>> concatenator;
    bool eq = std::is_same<IntegralSequence<short, 1, 2, 3, 4, 5>,concatenator>::value;
    EXPECT_TRUE(eq);
}