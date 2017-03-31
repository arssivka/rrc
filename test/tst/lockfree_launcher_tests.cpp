/**
 *  @autor tekatod
 *  @date 3/15/17
 */

#include <gtest/gtest.h>
#include <rrc/lockfree_launcher.h>

using namespace rrc;

class lockfree_launcher_fixture: public ::testing::Test {
public:
    lockfree_launcher_fixture() : lockfree_launcher1() {

    }

protected:
    lockfree_launcher lockfree_launcher1;
    std::vector<int> check_vector;
};

TEST_F(lockfree_launcher_fixture, sync_task) {
    lockfree_launcher1.enqueue_task([this]() {
        check_vector.push_back(1);
    });
    EXPECT_EQ(check_vector, std::vector<int>());
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1}));
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1}));
}

TEST_F(lockfree_launcher_fixture, sync_task_duration) {
    using namespace std::chrono_literals;
    lockfree_launcher1.enqueue_task_for(std::chrono::steady_clock::duration(100ms), [this]() {
        check_vector.push_back(1);
        std::this_thread::sleep_for(200ms);
    });
    lockfree_launcher1.enqueue_task_for(std::chrono::steady_clock::duration(300ms), [this]() {
        check_vector.push_back(2);
        std::this_thread::sleep_for(200ms);
    });
    lockfree_launcher1.enqueue_task_for(std::chrono::steady_clock::duration(500ms), [this]() {
        check_vector.push_back(3);
    });
    EXPECT_EQ(check_vector, std::vector<int>());
    std::this_thread::sleep_for(200ms);
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1, 2, 3}));
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1, 2, 3}));
}

TEST_F(lockfree_launcher_fixture, sync_task_at) {
    using namespace std::chrono_literals;
    lockfree_launcher1.enqueue_task_at(std::chrono::steady_clock::now() + 100ms, [this]() {
        check_vector.push_back(1);
        std::this_thread::sleep_for(200ms);
    });
    lockfree_launcher1.enqueue_task_at(std::chrono::steady_clock::now() + 300ms, [this]() {
        check_vector.push_back(2);
        std::this_thread::sleep_for(200ms);
    });
    lockfree_launcher1.enqueue_task_at(std::chrono::steady_clock::now() + 500ms, [this]() {
        check_vector.push_back(3);
    });
    EXPECT_EQ(check_vector, std::vector<int>());
    std::this_thread::sleep_for(200ms);
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1, 2, 3}));
    lockfree_launcher1.step();
    EXPECT_EQ(check_vector, std::vector<int>({1, 2, 3}));
}

TEST_F(lockfree_launcher_fixture, finalize_task) {
    lockfree_launcher1.enqueue_finalize_task([this](){
        check_vector.push_back(1);
    });
    EXPECT_EQ(check_vector, std::vector<int>());
    lockfree_launcher1.finalize();
    EXPECT_EQ(check_vector, std::vector<int>({1}));
    lockfree_launcher1.finalize();
    EXPECT_EQ(check_vector, std::vector<int>({1}));
}
