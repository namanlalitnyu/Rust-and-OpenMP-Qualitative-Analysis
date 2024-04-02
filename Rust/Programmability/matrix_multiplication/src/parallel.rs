use rayon::prelude::*;
use rand::prelude::*;

fn generate_matrix() -> Vec<Vec<i32>> {
    let mut matrix = vec![vec![0; 10]; 10];
    let mut rng = thread_rng();

    for i in 0..10 {
        for j in 0..10 {
            matrix[i][j] = rng.gen_range(0..100);
        }
    }
    matrix
}

fn multiply_matrices(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let n = a.len();
    let mut result = vec![vec![0; n]; n];

    result.par_iter_mut().enumerate().for_each(|(i, row)| {
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
    let a = generate_matrix();
    let b = generate_matrix();
    let result = multiply_matrices(&a, &b);
    
    println!("\nResult of multiplication:");
    for row in result {
        println!("{:?}", row);
    }
}