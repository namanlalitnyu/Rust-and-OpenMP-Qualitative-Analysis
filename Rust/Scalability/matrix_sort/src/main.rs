use std::time::Instant;

fn main() { 
    matrix_sort();
}

fn matrix_sort(){
    let mut matrix = vec![
        vec![3, 2, 1],
        vec![6, 5, 4],
        vec![9, 8, 7]
    ];

    let mut linear_matrix_vector: Vec<i32> = Vec::new();
    let matrix_length = matrix.len();

    for i in 0..=matrix_length-1 {
        for j in 0..=matrix_length-1 {
            linear_matrix_vector.push(matrix[i][j]);
        }
    }

    let now = Instant::now();
    linear_matrix_vector.sort();
    let elapsed = now.elapsed();
    println!("Elapsed: {:.2?}", elapsed);

    let mut k = 0;

    for i in 0..=matrix_length-1 {
        for j in 0..=matrix_length-1 {
            matrix[i][j] = linear_matrix_vector[k];
            k += 1;
        }
    }

    // println!("Sorted Matrix:");
    // for i in 0..=matrix_length-1 {
    //     for j in 0..=matrix_length-1 {
    //         print!("{} ", matrix[i][j]);
    //     }
    //     println!();
    // }
}