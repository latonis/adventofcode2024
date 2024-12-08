#pragma once

template <typename T>
struct timer;

template <typename R, typename... Args>
struct timer<R (*)(Args...)> {
    using fn = R (*)(Args...);

    static R time(fn func, Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        R retval = func(args...);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << std::format("Func took {}µs", duration.count())
                  << std::endl;

        return retval;
    }
};