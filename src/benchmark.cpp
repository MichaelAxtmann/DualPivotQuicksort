/*
 * Copyright (c) 2019 Michael Axtmann <michael.axtmann@gmail.com>
 * 
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

#include <dual_pivot_quicksort.hpp>

template<class T, class Distribution, class Comp>
void run(Distribution dist, Comp comp, std::string descr) {

  std::cout << descr << std::endl;
  
  size_t its = 7;
  
  std::random_device rd;
  std::mt19937_64 gen(rd());

  std::vector<T> v;

  for (size_t size = 1; size <=23; size += 2) {
    
    double total_time_dpq = 0;
    double total_time_stdsort = 0;
    double total_runs = 0;
    
    double time_dpq = 0;
    double time_stdsort = 0;
      
    for (size_t it = 0; it != its; ++it) {
      v.resize(1ul << size);
      for (auto& el : v) el = dist(gen);
        
      auto start = std::chrono::high_resolution_clock::now();

      dual_pivot_quicksort::sort(v.begin(), v.end(), comp);
      if (!std::is_sorted(v.begin(), v.end(), comp)) {
        std::cout << "Error: Unsorted" << std::endl;
      }

      auto stop = std::chrono::high_resolution_clock::now();
      auto finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed_dpq = finish - start;

      if (it != 0) time_dpq += elapsed_dpq.count();
        
      for (auto& el : v) el = dist(gen);
        
      start = std::chrono::high_resolution_clock::now();

      std::sort(v.begin(), v.end(), std::less<>{});

      stop = std::chrono::high_resolution_clock::now();
      finish = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed_stdsort = finish - start;

      if (it != 0) time_stdsort += elapsed_stdsort.count();

      ++total_runs;
      total_time_dpq += time_dpq;
      total_time_stdsort += time_stdsort;
    }
    --total_runs;

    std::cout << "\tsize=" << size
              << "\truns=" << total_runs
              << "\tdpq-avg=" << total_time_dpq / total_runs
              << "\tstd::sort-avg=" << total_time_stdsort / total_runs
              << "\tdpq-speedup=" << total_time_stdsort / total_time_dpq
              << std::endl;
  }
  
}

int main(int argc, char *argv[])
{
  // run<int>(std::uniform_int_distribution<int>(), std::less<>{}, "int uniform");
  // run<int>(std::uniform_int_distribution<int>(0, 0), std::less<>{}, "int zero");

  run<double>(std::uniform_real_distribution<double>(), std::less<>{}, "double uniform");
  // run<double>(std::uniform_int_distribution<int>(0, 0), std::less<>{}, "double zero");
  return 0;
}
