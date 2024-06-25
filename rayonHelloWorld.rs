use rayon::prelude::*;

fn main() {
// rayon-hello program uses the rayon crate to say Hello World from
// each available thread.  
// Add rayon = "1.7.0" to your cargo.toml dependencies

// Create our message in shared memory.
    let shared_message = "Hello World".to_string();

// Get the number of available threads for parallelism.
    let num_threads = rayon::current_num_threads();

// Use Rayon's parallel iterator to concurrently execute the code on each thread.
    (0..num_threads).into_par_iter().for_each(|i| {
        
// Each thread prints message.
        println!("{} from thread {}", shared_message, i);
    });

	println!("All threads have completed!");
//end of fn main()
}
