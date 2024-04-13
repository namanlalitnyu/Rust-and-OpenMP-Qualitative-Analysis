use rand::prelude::*;
use std::env;
use std::time::Instant;

fn generate_matrix(matrix_size: usize) -> Vec<Vec<i32>> {
    let mut matrix = vec![vec![0; matrix_size]; matrix_size];
    let mut rng = thread_rng();

    for i in 0..matrix_size {
        for j in 0..matrix_size {
            matrix[i][j] = rng.gen_range(0..99);
        }
    }
    matrix
}

fn multiply_matrices(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let n = a.len();
    let mut result = vec![vec![0; n]; n];

    result.iter_mut().enumerate().for_each(|(i, row)| {
        for j in 0..n {
            let mut sum = 0;
            for k in 0..n {
                sum += a[i][k] * b[k][j];
            }
            row[j] = sum;
        }
    });
    result
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let matrix_size: i32 = args[1].parse().expect("Matrix Length to be entered");
    let matrix_size_usize: usize = matrix_size as usize;

    let a = generate_matrix(matrix_size_usize);
    let b = generate_matrix(matrix_size_usize);

    let start_time = Instant::now();
    let _result = multiply_matrices(&a, &b);
    let elapsed_time = start_time.elapsed();

    println!("Time taken: {:?}", elapsed_time);
}