use rayon::prelude::*;
use rand::Rng;
use std::env;
use std::time::Instant;

fn merge_sort_parallel<T: Ord + Send + Sync + Clone>(arr: &mut [T]) -> Vec<T> {
    if arr.len() <= 1 {
        return arr.to_vec();
    }

    let mid = arr.len() / 2;
    let (left, right) = arr.split_at_mut(mid);

    let (left, right) = rayon::join(
        || merge_sort_parallel(left),
        || merge_sort_parallel(right),
    );

    merge(&left, &right)
}

fn merge<T: Ord + Clone>(left: &[T], right: &[T]) -> Vec<T> {
    let mut i = 0;
    let mut j = 0;

    let mut merged = Vec::with_capacity(left.len() + right.len());

    while i < left.len() && j < right.len() {
        if left[i] <= right[j] {
            merged.push(left[i].clone());
            i += 1;
        } else {
            merged.push(right[j].clone());
            j += 1;
        }
    }

    while i < left.len() {
        merged.push(left[i].clone());
        i += 1;
    }

    while j < right.len() {
        merged.push(right[j].clone());
        j += 1;
    }

    merged
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let n: i32 = args[1].parse().expect("Array Length to be entered");

    let num_threads: i32 = args[2].parse().expect("Number of Threads to be entered");
    let num_threads_usize: usize = num_threads as usize;

    let mut rng = rand::thread_rng();
    let mut arr: Vec<i32> = (0..n).map(|_| rng.gen_range(0..1000)).collect();

    rayon::ThreadPoolBuilder::new()
        .num_threads(num_threads_usize)
        .build_global()
        .unwrap();

    let start_time = Instant::now();
    let _sorted_arr = merge_sort_parallel(&mut arr);
    let elapsed_time = start_time.elapsed();

    println!("Time taken: {:?}", elapsed_time);
}