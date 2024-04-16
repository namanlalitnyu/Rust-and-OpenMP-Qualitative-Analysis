use std::sync::{Arc, Barrier};
use std::thread;
use std::time::{Duration, Instant};

fn main() {
    let threads_to_test = [1, 2, 4, 8, 16];
    let num_iterations = 1000; // Increase the number of iterations to get a measurable duration

    for &thread_count in &threads_to_test {
        let mut total_creation_time = Duration::new(0, 0);
        let mut max_sync_time = Duration::new(0, 0);
        let mut total_termination_time = Duration::new(0, 0);

        println!("Testing with {} threads:", thread_count);

        for _ in 0..num_iterations {
            let start = Instant::now();

            let barrier = Arc::new(Barrier::new(thread_count + 1));
            let mut handles = Vec::with_capacity(thread_count);
            let mut sync_times = Vec::with_capacity(thread_count);

            for _ in 0..thread_count {
                let c = Arc::clone(&barrier);
                handles.push(thread::spawn(move || {
                    let thread_sync_start = Instant::now();
                    c.wait(); // Synchronization point
                    let thread_sync_end = Instant::now();
                    thread_sync_end.duration_since(thread_sync_start)
                }));
            }

            // Wait for all threads to reach the barrier
            barrier.wait();

            let creation_time = Instant::now().duration_since(start);
            total_creation_time += creation_time;

            for handle in handles {
                let sync_time = handle.join().unwrap();
                sync_times.push(sync_time);
            }

            let sync_end = Instant::now();
            let termination_time = sync_end.duration_since(start) - creation_time;
            total_termination_time += termination_time;

            // Calculate the maximum synchronization time across all threads
            let max_thread_sync_time = *sync_times.iter().max().unwrap();
            max_sync_time += max_thread_sync_time;
        }

        let avg_creation_time = total_creation_time / num_iterations;
        let avg_sync_time = max_sync_time / num_iterations;
        let avg_termination_time = total_termination_time / num_iterations;

        println!("Average thread creation time: {:.9} seconds",
                 avg_creation_time.as_secs_f64());
        println!("Average synchronization time: {:.9} seconds",
                 avg_sync_time.as_secs_f64());
        println!("Average thread termination time: {:.9} seconds\n",
                 avg_termination_time.as_secs_f64());
    }
}