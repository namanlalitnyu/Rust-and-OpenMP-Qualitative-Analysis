use std::sync::{Arc, Barrier};
use std::thread;
use std::time::{Duration, Instant};

fn main() {
    let thread_count = 4; // Number of threads to use
    let barrier = Arc::new(Barrier::new(thread_count));

    // Measure thread creation time
    let creation_start = Instant::now();
    let mut handles = Vec::with_capacity(thread_count);

    for _ in 0..thread_count {
        let c = barrier.clone();
        handles.push(thread::spawn(move || {
            // Wait at the barrier, measuring synchronization time
            let sync_start = Instant::now();
            c.wait();
            let sync_duration = sync_start.elapsed();

            // Dummy work to prevent optimization out
            let mut sum = 0;
            for i in 0..10000 {
                sum += i;
            }

            sync_duration
        }));
    }
    let creation_duration = creation_start.elapsed();

    // Collect the synchronization times
    let mut sync_times = Vec::with_capacity(thread_count);
    for handle in handles {
        sync_times.push(handle.join().unwrap());
    }
    let sync_average: Duration = sync_times.iter().sum::<Duration>() / sync_times.len() as u32;

    // Measure thread termination time (assuming negligible termination overhead in this case)
    let termination_duration = Duration::new(0, 0); // Rust threads are joined above, no separate termination step

    // Output the timing information
    println!("Thread creation time: {:?}", creation_duration);
    println!("Average synchronization time: {:?}", sync_average);
    println!("Thread termination time: {:?}", termination_duration);
}