#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP
#include <stdio.h>
#include <time.h>

#include <iomanip>
#include <iostream>

typedef struct timespec t_time;

#define MEASUREMENT(fnc)                                                     \
  {                                                                          \
    t_time start;                                                            \
    t_time end;                                                              \
    t_time res;                                                              \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);                         \
    fnc;                                                                     \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);                           \
    res.tv_sec = end.tv_sec - start.tv_sec;                                  \
    res.tv_nsec = end.tv_nsec - start.tv_nsec;                               \
                                                                             \
    std::cout << (res.tv_sec * 1000000) + (res.tv_nsec / 1000) << std::endl; \
  }
//if (res.tv_nsec < 0) {                                                   \
    //  res.tv_nsec += 1000000000;                                             \
    //  res.tv_sec -= 1;                                                       \
    //}                                                                        \
    //if (res.tv_sec > 0) {                                                    \
    //  std::cout << res.tv_sec;                                               \
    //  std::cout << std::setfill('0') << std::setw(9) << res.tv_nsec          \
    //            << std::endl;                                                \
    //} else {                                                                 \
    //  std::cout << res.tv_nsec << std::endl;                                 \
    //}                                                                        \
  //}

#define LOOP(fnc)                      \
  for (size_t i = 0; i < 10000; i++) { \
    fnc;                               \
  }

#include <vector>

#include "vector.hpp"

#ifdef STD
#define TEST std
#else
#define TEST ft
#endif

#endif /* ***************************************************** MEASUREMENT_H \
        */