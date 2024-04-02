use rayon::prelude::*;
use rand::prelude::*;

fn merge_sort(vec: &[i32]) -> Vec<i32> {
    if vec.len() < 2 {
        vec.to_vec()
    } else {
        let mid = vec.len() / 2;
        let (left, right) = rayon::join(|| merge_sort(&vec[..mid]), || merge_sort(&vec[mid..]));
        merge(&left, &right)
    }
}

fn merge(left: &[i32], right: &[i32]) -> Vec<i32> {
    let (mut i, mut j) = (0, 0);
    let mut merged: Vec<i32> = Vec::with_capacity(left.len() + right.len());

    while i < left.len() && j < right.len() {
        if left[i] < right[j] {
            merged.push(left[i]);
            i += 1;
        } else {
            merged.push(right[j]);
            j += 1;
        }
    }

    merged.extend_from_slice(&left[i..]);
    merged.extend_from_slice(&right[j..]);
    merged
}

fn main() {
    let mut numbers = vec![0; 100];
    let mut rng = thread_rng();
    for number in numbers.iter_mut() {
        *number = rng.gen_range(0..100);
    }
    let result = merge_sort(&numbers);
    println!("Sorted: {:?}", result);
}
