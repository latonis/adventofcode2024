run:
	cd ./day${DAY} &&\
	g++ --std=gnu++23 solution.cpp ../utils/utils.cpp && ./a.out && rm ./a.out