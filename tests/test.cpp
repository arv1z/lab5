#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"
#include "Transaction.h"

using ::testing::_;
using ::testing::Return;

class MockTransaction : public Transaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};


TEST(Account, Constructor)
{
    Account account(1, 100);

    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(Account, Lock)
{
    Account account(1, 100);

    EXPECT_NO_THROW(account.Lock());
}

TEST(Account, ChangeBalance)
{
    Account account(1, 100);

    account.Lock();
    account.ChangeBalance(50);

    EXPECT_EQ(account.GetBalance(), 150);
}

TEST(Transaction, SetFee)
{
    Transaction transaction;

    transaction.set_fee(10);

    EXPECT_EQ(transaction.fee(), 10);
}

TEST(Transaction, Make)
{
    Transaction transaction;

    Account from(1, 200);
    Account to(2, 100);

    EXPECT_TRUE(transaction.Make(from, to, 100));
}

TEST(MockTransactionTest, SaveToDataBaseCalled)
{
    MockTransaction transaction;

    Account from(1, 1000);
    Account to(2, 1000);

    EXPECT_CALL(transaction, SaveToDataBase(_, _, 100)).Times(1);

    EXPECT_TRUE(transaction.Make(from, to, 100));
}

TEST(MockTransactionTest, SaveToDataBaseNotCalled)
{
    MockTransaction transaction;

    Account from(1, 1000);
    Account to(2, 1000);

    EXPECT_CALL(transaction, SaveToDataBase(_, _, _)).Times(0);

    EXPECT_THROW(transaction.Make(from, to, 50), std::logic_error);
}
