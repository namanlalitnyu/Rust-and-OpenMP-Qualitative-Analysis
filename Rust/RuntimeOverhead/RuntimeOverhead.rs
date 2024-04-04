use std::sync::{Arc, Barrier};
use std::thread;
use std::time::{Duration, Instant};

fn main() {
    let thread_count = 4; // Number of threads to use
    let barrier = Arc::new(Barrier::new(thread_count + 1)); // +1 for the main thread
    let mut handles = Vec::with_capacity(thread_count);

    // Measure thread creation time
    let creation_start = Instant::now();
    for _ in 0..thread_count {
        let c = barrier.clone();
        handles.push(thread::spawn(move || {
            // Dummy work before synchronization to prevent optimization out
            let mut pre_sum = 0;
            for i in 0..10000 {
                pre_sum += i;
            }

            // Synchronization point: all threads wait here
            let sync_start = Instant::now();
            c.wait();
            let sync_duration = sync_start.elapsed();

            // Dummy work after synchronization to prevent optimization out
            let mut post_sum = 0;
            for i in 0..10000 {
                post_sum += i;
            }

            sync_duration
        }));
    }
    let creation_duration = creation_start.elapsed();

    // Wait for all threads to be ready for synchronization
    let sync_start = Instant::now();
    barrier.wait(); // Main thread also waits, ensuring all child threads have reached the barrier
    let sync_duration = sync_start.elapsed();

    // Measure thread termination time
    let termination_start = Instant::now();
    let mut sync_times: Vec<Duration> = Vec::new();
    for handle in handles {
        let sync_time = handle.join().unwrap(); // Joining threads here
        sync_times.push(sync_time);
    }
    let termination_duration = termination_start.elapsed();

    // Calculate the average synchronization time
    let total_sync_time: Duration = sync_times.iter().sum();
    let average_sync_time = total_sync_time / thread_count as u32;

    // Output the timing information
    println!("Thread creation time: {:?}", creation_duration);
    println!("Average synchronization time: {:?}", average_sync_time);
    println!("Thread termination time: {:?}", termination_duration);
}
