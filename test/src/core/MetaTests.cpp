/**
 *  @autor arssivka
 *  @date 11/28/16
 */


#include "gtest/gtest.h"
#include <list>
#include <functional>
#include <rrc/meta.h>
#include <rrc/core/TypeConverter.h>
//#include <rrc/core/Message.h>

using namespace rrc;

// We can't test fucking metaprogramming without fucking types!
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
    auto count = MetaArrayGenerator<int8_t, 1, 2, 3>::size;
    EXPECT_EQ(count, (size_t)3);
    auto array = MetaArrayGenerator<int8_t, 1, 2, 3>::data;
    std::array<int8_t, 3> val = array;
    EXPECT_TRUE(val == array);
}


TEST(MetaTest, Rename) {
    typedef std::vector<int> a;
    typedef std::list<int> b;
    bool eq = std::is_same<MetaRename<a, std::list>, b>::value;
    EXPECT_TRUE(eq);
}

TEST(MetaTest, Length) {
    auto len = rrc::MetaLength<fuck, float, double>::value;
    EXPECT_EQ(len, (size_t)3);
}


TEST(MetaTest, Size) {
    auto size = MetaListSize<std::pair<fuck, float>>::value;
    EXPECT_EQ(size, (size_t)2);
}


TEST(MetaTest, PushFront) {
    typedef MetaPushFront<MetaList<float>, fuck> push;
    bool pushed = std::is_same<MetaList<fuck, float>, push>::value;
    EXPECT_TRUE(pushed);
}


TEST(MetaTest, Front) {
    typedef MetaFront<MetaList<float, fuck>> push;
    bool front = std::is_same<float, push>::value;
    EXPECT_TRUE(front);
}


TEST(MetaTest, PopFront) {
    typedef MetaPopFront<MetaList<float, fuck>> push;
    bool front = std::is_same<MetaList<fuck>, push>::value;
    EXPECT_TRUE(front);
}

TEST(MetaTest, Empty) {
    typedef MetaList<fuck, fuck, fuck, fuck> FUCK;
    typedef MetaList<> EMPTY;
    bool nempty = MetaEmpty<FUCK>::value;
    EXPECT_FALSE(nempty);
    bool empty = MetaEmpty<EMPTY>::value;
    EXPECT_TRUE(empty);
}

TEST(MetaTest, Clear) {
    typedef MetaClearList<MetaList<fuck,fuck,fuck,fuck>> FUCK;
    bool eq = std::is_same<FUCK, MetaList<>>::value;
    EXPECT_TRUE(eq);
}

template <class A>
using AddPointer = typename std::add_pointer<A>::type;

TEST(MetaTest, Transform) {
    typedef MetaTransform<AddPointer , MetaList<fuck, fuck, fuck>> DIRECTIONAL_FUCK;
    bool same = std::is_same<DIRECTIONAL_FUCK, MetaList<fuck*, fuck*, fuck*>>::value;
    EXPECT_TRUE(same);
}

TEST(MetaTest, Append) {
    typedef MetaAppend<MetaList<float>, MetaList<fuck, fuck>, MetaList<fuck, fuck, fuck>> append;
    bool back = std::is_same<MetaList<float, fuck, fuck, fuck, fuck, fuck>, append>::value;
    EXPECT_TRUE(back);
}

TEST(MetaTest, AppendSequence) {
    typedef MetaAppendSequence <MetaIntegralSequence<fuck, 1, 2, 3>, MetaIntegralSequence<fuck, 4, 5, 6>, MetaIntegralSequence<fuck, 7, 8, 9>> append;
    bool back = std::is_same<MetaIntegralSequence<fuck, 1, 2, 3, 4, 5, 6, 7, 8, 9>, append>::value;
    EXPECT_TRUE(back);
}

TEST(MetaTest, PopFrontSequence) {
    typedef MetaPopFrontSequence<MetaIntegralSequence<fuck, 1, 2, 3>> pop;
    bool same = std::is_same<MetaIntegralSequence<fuck, 2, 3>, pop::Type>::value;
    EXPECT_TRUE(same);
    typedef MetaPopFrontSequence<MetaIntegralSequence<fuck>> emptypop;
    bool same2 = std::is_same<MetaIntegralSequence<fuck>, emptypop::Type >::value;
    EXPECT_TRUE(same2);
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
    typedef MetaRenameSequence<MetaIntegralSequence<fuck, 1, 2, 3>, MetaArrayGenerator<fuck>> array;
    auto array1 = array::data;
    auto array2 = std::array<fuck, 3>{1, 2, 3};
    EXPECT_EQ(array1, array2);
}

TEST(MetaTest, Pack) {
    typedef MetaPack<fuck, 1, 2> pack;
    auto value = pack::value;
    EXPECT_EQ(value, 0x10002);
    typedef MetaPack<short, 1, 2> pack2;
    auto value2 = pack2::value;
    EXPECT_EQ(value2, 0x0102);
    typedef MetaPack<long int, 1, 2> pack3;
    auto value3 = pack3::value;
    EXPECT_EQ(value3, 0x100000002);
}

TEST(MetaTest, Packer) {
    typedef MetaPacker<MetaArrayGenerator<short>, MetaIntegralSequence<short, 1>> packer;
    std::array<short, 1> array{0x01};
    auto packed = packer::data;
    EXPECT_EQ(array, packed);
    typedef MetaPacker<MetaArrayGenerator<short>, MetaIntegralSequence<short, 1, 2, 3>> packer2;
    std::array<short, 2> array2{0x0102, 0x03};
    auto packed2 = packer2::data;
    EXPECT_EQ(array2, packed2);
    typedef MetaPacker<MetaArrayGenerator<short>, MetaIntegralSequence<short, 1, 2, 3, 4>> packer3;
    std::array<short, 2> array3{0x0102, 0x0304};
    auto packed3 = packer3::data;
    EXPECT_EQ(array3, packed3);
}


TEST(MetaTest, Concatenator) {
    typedef MetaConcatenator<MetaList<int, float>, MetaList<bool, bool, double>> concatenator;
    bool eq = std::is_same<MetaList<int, float, bool, double>, concatenator >::value;
    EXPECT_TRUE(eq);
    typedef MetaConcatenator<MetaList<bool, bool, double>> concatenator1;
    bool eq1 = std::is_same<MetaList<bool, double>, concatenator1 >::value;
    EXPECT_TRUE(eq1);
    typedef MetaConcatenator<MetaList<int, bool>, MetaList<>, MetaList<bool, bool, double>> concatenator2;
    bool eq2 = std::is_same<MetaList<int, bool, double>, concatenator2>::value;
    EXPECT_TRUE(eq2);
    typedef MetaConcatenator<MetaList<int, bool>, MetaList<bool, bool, double>, MetaList<double, short>> concatenator3;
    bool eq3 = std::is_same<MetaList<int, bool, double, short>, concatenator3>::value;
    EXPECT_TRUE(eq3);
}


TEST(MetaTest, BackSequenceElement) {
    typedef MetaBackSequenceElement<MetaIntegralSequence<short, 1, 2, 3>> back;
    short b = back::value;
    EXPECT_EQ(b, (short) 3);
    typedef MetaBackSequenceElement<MetaIntegralSequence<short, 1>> back1;
    short b1 = back1::value;
    EXPECT_EQ(b1, (short) 1);
}

TEST(MetaTest, FrontSequenceElement) {
    typedef MetaFrontSequenceElement<MetaIntegralSequence<short, 1, 2, 3>> front;
    short b = front::value;
    EXPECT_EQ(b, (short) 1);
    typedef MetaFrontSequenceElement<MetaIntegralSequence<short, 1>> front1;
    short b1 = front1::value;
    EXPECT_EQ(b1, (short) 1);
}

TEST(MetaTest, Back) {
    typedef MetaBack<MetaList<int, float, bool>> back;
    bool eq = std::is_same<bool, back>::value;
    EXPECT_TRUE(eq);
    typedef MetaBack<MetaList<int>> back1;
    bool eq1 = std::is_same<int, back1>::value;
    EXPECT_TRUE(eq1);
}

TEST(MetaTest, SequenceConcatenator) {
    typedef MetaSequenceConcatenator<MetaIntegralSequence<short, 1, 2, 3>, MetaIntegralSequence<short, 4, 5>> concatenator;
    bool eq = std::is_same<MetaIntegralSequence<short, 1, 2, 3, 4, 5>,concatenator>::value;
    EXPECT_TRUE(eq);
    typedef MetaSequenceConcatenator<MetaIntegralSequence<short, 1, 2, 2, 3, 3>> concatenator1;
    bool eq1 = std::is_same<MetaIntegralSequence<short, 1, 2, 3>,concatenator1>::value;
    EXPECT_TRUE(eq1);
    typedef MetaSequenceConcatenator<MetaIntegralSequence<short>> concatenator2;
    bool eq2 = std::is_same<MetaIntegralSequence<short>,concatenator2>::value;
    EXPECT_TRUE(eq2);
    typedef MetaSequenceConcatenator<MetaIntegralSequence<short, 1, 2, 2, 3>, MetaIntegralSequence<short>, MetaIntegralSequence<short, 3, 4, 5, 5, 5>> concatenator3;
    bool eq3 = std::is_same<MetaIntegralSequence<short, 1, 2, 3, 4, 5>, concatenator3>::value;
    EXPECT_TRUE(eq3);
    typedef MetaSequenceConcatenator<MetaIntegralSequence<short, 1, 2, 2, 3>, MetaIntegralSequence<short, 4, 5, 5, 5>,
            MetaIntegralSequence<short, 6, 6, 6>> concatenator4;
    bool eq4 = std::is_same<MetaIntegralSequence<short, 1, 2, 3, 4, 5, 6>, concatenator4>::value;
    EXPECT_TRUE(eq4);
}