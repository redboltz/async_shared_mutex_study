#include <iostream>

#include <boost/asio.hpp>

#include <boost/sam.hpp>

namespace as = boost::asio;
namespace sam = boost::sam;

as::awaitable<void> proc() {
    auto exe = co_await as::this_coro::executor;
    auto smtx = sam::shared_mutex{exe};
    std::cout << "async_lock_shared1" << std::endl;
    co_await smtx.async_lock_shared(as::deferred);
    std::cout << "async_lock_shared2" << std::endl;
    co_await smtx.async_lock_shared(as::deferred);

    std::cout << "unlock_shared1" << std::endl;
    smtx.unlock_shared();
    std::cout << "unlock_shared2" << std::endl;
    smtx.unlock_shared();
    co_return;
}

int main() {
    as::io_context ioc;
    as::co_spawn(
        ioc.get_executor(),
        proc(),
        as::detached
    );
    ioc.run(); // if multi threaded ?
    std::cout << "ioc.run() exit" << std::endl;
}
