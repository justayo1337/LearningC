# C++ Study Path for a Linux Systems Engineer

A phased curriculum (~6–9 months at 5–8 hrs/week) that leans on what you already know — Linux internals, shell, processes, filesystems — and uses C++ as the tool to go deeper. Every phase ends with a project that touches real syscalls, not toy exercises.

Resources are tagged **[free]** or **[paid]**. Your primary Phase 1 text is *A Tour of C++*, which you already own — you can start tonight.

---

## Phase 0 — Setup (1 evening)

- Install a modern toolchain: `g++ >= 13` or `clang++ >= 17`, `cmake`, `gdb`, `valgrind`, `perf`, `strace`, `ltrace`.
- Compile everything with: `-std=c++20 -Wall -Wextra -Wpedantic -g`
- Add sanitizers early and keep them on: `-fsanitize=address,undefined`
- Editor: whatever you use now + [clangd](https://clangd.llvm.org/) LSP **[free]** (works in vim, emacs, VS Code).
- Bookmark [cppreference.com](https://en.cppreference.com) **[free]** — it is the reference, not cplusplus.com.
- Bookmark [Compiler Explorer](https://godbolt.org) **[free]** — paste code, see the assembly; you'll use it in every phase.

---

## Phase 1 — Core Language (4–6 weeks)

**Goal:** read and write idiomatic modern C++ (C++17/20), not "C with classes."

**Primary text: *A Tour of C++* (3rd ed., Stroustrup) — you own it.** Read it front to back, but pace it against the topic list below. It's dense; expect to reread chapters. ([Author's page for errata/extras](https://www.stroustrup.com/tour3.html) **[free]**)

Topics, mapped to the book:

1. **Compilation model** — *Tour* ch. 1 & 3 (Basics, Modularity). The book is light here, so supplement by inspecting your own binaries with `nm`/`objdump`/`ldd` — tools you already know; now point them at what *you* built. Headers vs. source, translation units, linking.
2. **Value semantics** — ch. 1–2. Stack vs. heap, copies, references, `const` correctness.
3. **RAII** — ch. 5–6 (Classes, Essential Operations). The single most important C++ idea: constructors/destructors as resource lifetime. Understand it deeply before touching `new`.
4. **Smart pointers** — ch. 15 (Pointers and Containers). `unique_ptr` first (95% of cases), `shared_ptr` sparingly. Rule: raw `new`/`delete` almost never appear in modern code.
5. **Move semantics** — ch. 6. Why `std::move` exists, what a moved-from object is.
6. **The STL** — ch. 9–14 (Library, Strings, I/O, Containers, Algorithms, Ranges) + ch. 16 (Utilities: `optional`, `variant`, `chrono`). `vector`, `string`, `string_view`, `unordered_map`, `span`, ranges views.
7. **Classes** — ch. 5–6. Rule of zero/five, `= default`, `= delete`, operator overloading basics.
8. **Error handling** — ch. 4. Exceptions vs. error codes vs. `std::expected` (C++23) — know both camps.
9. **Lambdas & templates** — ch. 7–8 (Templates, Concepts) at the "write a function template" level; defer metaprogramming. Skim ch. 18 (Concurrency) but save it for Phase 3.

**Supplements**
- [learncpp.com](https://www.learncpp.com) **[free]** — when a *Tour* chapter is too terse, the matching learncpp section fills the gap with worked examples.
- [Exercism C++ track](https://exercism.org/tracks/cpp) **[free]** — finger practice alongside the reading.
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) **[free]** — skim sections R.* (resource management) and ES.* (expressions/statements).
- Optional deeper references (buy later if wanted, not needed to start):
  - [*Beautiful C++*](https://www.informit.com/store/beautiful-c-plus-plus-30-core-guidelines-for-writing-9780137647842) (Davidson & Gregory) **[paid]** — the Core Guidelines with narrative.
  - [*Effective Modern C++*](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/) (Meyers) **[paid]** — items on move/`auto`/smart pointers are still gold.

**Project 1: `lsplus`** — a colorized `ls` clone. Directory iteration with `std::filesystem`, `stat()` info, sorting with ranges, formatted output with `std::format`. Pure standard library, no raw pointers.

---

## Phase 2 — C++ Meets the Linux API (5–7 weeks)

**Goal:** wrap the POSIX/Linux syscall surface you already know in safe C++.

Topics:
1. Calling C from C++: `extern "C"`, `errno` handling, wrapping C APIs in RAII types (write an `fd` class whose destructor calls `close()` — this exercise teaches half of C++).
2. Files & I/O: `open`/`read`/`write`/`mmap` wrapped in classes; compare with `iostream`/`fstream` and know when each is appropriate.
3. Processes: `fork`/`exec`/`waitpid`, pipes, `posix_spawn`. Signals and why they're miserable in C++ (async-signal-safety).
4. Sockets: TCP client/server, `getaddrinfo`, non-blocking I/O, then **epoll** — the heart of Linux event-driven servers.
5. Time: `std::chrono` (use it everywhere; never raw `time_t` math again), `clock_gettime`, timerfd.
6. Build systems: CMake fundamentals — targets, `target_link_libraries`, `FetchContent`. Every project from here on uses CMake.
7. Third-party libs worth knowing: [fmt](https://github.com/fmtlib/fmt), [spdlog](https://github.com/gabime/spdlog), [CLI11](https://github.com/CLIUtils/CLI11), [nlohmann/json](https://github.com/nlohmann/json) — all **[free]**.

**Resources**
- [*The Linux Programming Interface*](https://man7.org/tlpi/) (Kerrisk) **[paid]** — you likely know chunks already; use it as the syscall reference while you write C++ wrappers. The [man7.org training materials](https://man7.org/training/) and man pages themselves are **[free]**.
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) **[free]** — for sockets (written in C; you'll wrap it).
- CMake: [Modern CMake gitbook](https://cliutils.gitlab.io/modern-cmake/) **[free]** to start; [*Professional CMake*](https://crascit.com/professional-cmake/) (Scott) **[paid]** as the definitive reference.

**Project 2: `procwatch`** — a mini `top`. Parse `/proc/[pid]/stat` and `/proc/meminfo`, refresh on a timer, sort by CPU/RSS, ncurses or plain ANSI output. Exercises parsing, RAII file handles, chrono, and data structures.

**Project 3: epoll chat server** — multi-client TCP chat using a single-threaded epoll event loop. Non-blocking sockets, buffer management, graceful disconnect handling.

---

## Phase 3 — Concurrency & Memory (5–7 weeks)

**Goal:** threads without fear; understand the memory model well enough to know when you *don't* understand it.

Topics:
1. `std::thread` / `std::jthread`, `mutex`, `lock_guard`/`scoped_lock`, `condition_variable`. (Re-read *Tour* ch. 18 now.)
2. The producer/consumer queue — write one; it's the canonical exercise.
3. `std::atomic`, memory ordering (`seq_cst` vs. `acquire`/`release`) — conceptual understanding; default to `seq_cst` in real code.
4. Thread pools; `std::async`/futures and their limitations.
5. False sharing, cache lines, why `perf stat` numbers change when you pad a struct.
6. TSan (`-fsanitize=thread`) — run it on everything in this phase.
7. Memory deep-dive: allocators, arena allocation, `mmap`-backed pools; measure with `valgrind --tool=massif` and [heaptrack](https://github.com/KDE/heaptrack) **[free]**.

**Resources**
- [*C++ Concurrency in Action* (2nd ed.)](https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition) (Williams) **[paid]** — the standard text; chapters 1–5 + 9 are the core.
- Talks **[free]**:
  - Herb Sutter — "atomic<> Weapons" [part 1](https://www.youtube.com/watch?v=A8eCGOqgvH4) / [part 2](https://www.youtube.com/watch?v=KeLBd2EJLOU) (C++ and Beyond 2012; still the memory-model talk).
  - Scott Meyers — ["CPU Caches and Why You Care"](https://www.youtube.com/watch?v=WDIkqP4JbkE) (code::dive 2014).

**Project 4: parallel log grinder** — multithreaded log analyzer: one reader thread feeding a work queue, N workers aggregating stats (per-status-code counts, latency histograms), merged results. Benchmark 1 vs. N threads with `perf stat`; find and fix a false-sharing problem deliberately.

---

## Phase 4 — Debugging, Profiling, Performance (3–4 weeks)

**Goal:** the skills that distinguish a systems engineer who writes C++ from an application dev.

Topics:
1. `gdb` fluency: breakpoints, watchpoints, `bt`, examining core dumps (`ulimit -c unlimited`, `coredumpctl`), debugging a running process, pretty printers for STL.
2. Reading assembly at the "is this loop vectorized?" level — make [Compiler Explorer](https://godbolt.org) a daily habit.
3. `perf record` / `perf report` / flamegraphs on your own projects.
4. Link-time behavior: static vs. shared libs, symbol visibility, `LD_PRELOAD` tricks, ABI basics.
5. Undefined behavior: what it actually means, why the optimizer exploits it; UBSan everywhere.
6. Benchmarking honestly: [Google Benchmark](https://github.com/google/benchmark) **[free]**, avoiding dead-code elimination of the thing you're measuring.

**Resources**
- [*Performance Analysis and Tuning on Modern CPUs*](https://github.com/dendibakh/perf-book) (Bakhvalov) **[free]** (1st ed. PDF on GitHub; [2nd ed. **[paid]**](https://easyperf.net)) — excellent, plus his [easyperf.net blog](https://easyperf.net/notes/) **[free]**.
- Brendan Gregg — [perf examples](https://www.brendangregg.com/perf.html) and [flame graphs](https://www.brendangregg.com/flamegraphs.html) **[free]** — you likely know these pages; now apply them to your own binaries.
- Chandler Carruth — ["Efficiency with Algorithms, Performance with Data Structures"](https://www.youtube.com/watch?v=fHNmRkzxHWs) (CppCon 2014) **[free]**.

**Project 5:** take Project 4 and make it 5–10× faster. `mmap` the input, `string_view` parsing (zero-copy), custom hash map or [Abseil's](https://github.com/abseil/abseil-cpp) `flat_hash_map`, measure every step with perf + benchmarks. Write up before/after numbers.

---

## Phase 5 — Production-Grade C++ (4–6 weeks)

**Goal:** code you'd let a colleague depend on.

Topics:
1. Testing: [GoogleTest](https://github.com/google/googletest) or [Catch2](https://github.com/catchorg/Catch2) **[free]**; fuzzing with [libFuzzer](https://llvm.org/docs/LibFuzzer.html) **[free]** on any parser you wrote.
2. CI hygiene: [clang-format](https://clang.llvm.org/docs/ClangFormat.html), [clang-tidy](https://clang.llvm.org/extra/clang-tidy/), sanitizer jobs, warnings-as-errors.
3. Templates for real: concepts (C++20), CRTP, when *not* to use templates. (*Tour* ch. 7–8 again, now with mileage behind you.)
4. API design: what goes in headers, pimpl, ABI stability concerns for shared libs.
5. Reading real codebases — pick one and read it: [fmt](https://github.com/fmtlib/fmt) (beautifully written, small), [folly](https://github.com/facebook/folly) (Facebook's systems toolkit), or [dragonfly](https://github.com/dragonflydb/dragonfly) (modern C++ Redis-compatible store).

**Capstone (pick one):**
- **A tiny container runtime**: `clone()` with namespace flags, pivot_root, cgroup v2 limits — ties your Linux knowledge directly into C++.
- **A key-value store**: epoll server + append-only log + in-memory index + crash recovery. The classic systems capstone.
- **A metrics agent**: scrapes /proc + cgroups, exposes Prometheus text format over HTTP, <1% CPU overhead — directly relevant to infra work.

---

## Ongoing habits

- **Daily:** 15 min on [Compiler Explorer](https://godbolt.org) or one [cppreference](https://en.cppreference.com) page.
- **Weekly:** one talk from the [CppCon channel](https://www.youtube.com/@CppCon) **[free]** — start with Kate Gregory's ["Stop Teaching C"](https://www.youtube.com/watch?v=YnWhqhNdYyk) (CppCon 2015) — or a short hit from [Jason Turner's C++ Weekly](https://www.youtube.com/@cppweekly) **[free]**.
- **Always:** sanitizers on in debug builds; `-Wall -Wextra` with zero warnings; no raw `new`.
- Skim [r/cpp](https://www.reddit.com/r/cpp/) and the [ISO C++ blog](https://isocpp.org/blog) **[free]** for ecosystem awareness.

## Pitfalls for people coming from scripting/ops backgrounds

- Don't learn C first "as a foundation" — learn modern C++ directly; retrofit C knowledge via the syscall work in Phase 2.
- Don't start with template metaprogramming, inheritance hierarchies, or exceptions-vs-not debates. Value types + RAII + STL carry you a very long way.
- Don't trust tutorials that use `new`/`delete`, `char*` strings, or `#include <bits/stdc++.h>` — they're teaching 1998.
- Undefined behavior is not "it usually works" — it's the compiler assuming it can't happen. Sanitizers are non-negotiable.

## Sources

The path draws on the standard modern-C++ canon: Stroustrup's [*A Tour of C++*](https://www.stroustrup.com/tour3.html), the [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), Kerrisk's [TLPI](https://man7.org/tlpi/), Williams' [*Concurrency in Action*](https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition), Bakhvalov's [perf book](https://github.com/dendibakh/perf-book), and the [CppCon](https://www.youtube.com/@CppCon) / [isocpp.org](https://isocpp.org/blog) communities. Talk URLs were verified via web search on 2026-08-07.
