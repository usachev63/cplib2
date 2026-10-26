void stress() {
  int iters = stol(getenv("iters"));
  atomic_int it = 1;
  jthread progress_thread([&] {
    while (true) {
      this_thread::sleep_for(1s);
      if (it > iters) break;
      cerr << format("at it {}", (int)it) << endl;
    }
  });
  for (; it <= iters; ++it) {

  }
  progress_thread.join();
  cerr << "stress done" << endl;
}
